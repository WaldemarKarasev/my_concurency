// STL
#include <iostream>
#include <chrono>
#include <string>
#include <thread>

using namespace std::chrono_literals;

// Testing
#include <gtest/gtest.h>

// Concurrency
#include <concurrency/exe/pool/queues/UnboundedBlockingMPMCQueue.hpp>
#include <concurrency/utility.hpp>

template <typename T>
using Queue = concurrency::exe::pool::queues::UnboundedBlockingMPMCQueue<T>;

TEST(MPMCQueue, Exchange)
{
}

TEST(MPMCQueue, JustWorks) {
    Queue<int> queue;

    ASSERT_TRUE(queue.Put(7));

    auto value = queue.Take();
    ASSERT_TRUE(value);
    ASSERT_EQ(*value, 7);

    queue.Close();
    ASSERT_FALSE(queue.Take());
}

TEST(MPMCQueue, Fifo) {
    Queue<int> queue;
    queue.Put(1);
    queue.Put(2);
    queue.Put(3);

    ASSERT_EQ(*queue.Take(), 1);
    ASSERT_EQ(*queue.Take(), 2);
    ASSERT_EQ(*queue.Take(), 3);
}

TEST(MPMCQueue, Close) {
    Queue<std::string> queue;

    queue.Put("Hello");
    queue.Put(",");
    queue.Put("World");

    queue.Close();

    ASSERT_FALSE(queue.Put("!"));

    ASSERT_EQ(*queue.Take(), "Hello");
    ASSERT_EQ(*queue.Take(), ",");
    ASSERT_EQ(*queue.Take(), "World");
    ASSERT_FALSE(queue.Take());
}


struct MoveOnly {
    MoveOnly() = default;

    MoveOnly(const MoveOnly& that) = delete;
    MoveOnly& operator=(const MoveOnly& that) = delete;

    MoveOnly(MoveOnly&& that) = default;
    MoveOnly& operator=(MoveOnly&& that) = default;
};

TEST(MPMCQueue, MoveOnly) {
    Queue<MoveOnly> queue;

    queue.Put(MoveOnly{});
    ASSERT_TRUE(queue.Take().has_value());
}

TEST(MPMCQueue, BlockingTake) {
    Queue<int> queue;

    std::thread producer([&]() 
    {
        std::this_thread::sleep_for(1s);
        queue.Put(7);
    });

    concurrency::StopWatch thread_cpu_timer;

    auto value = queue.Take();

    auto spent = thread_cpu_timer.ElapsedMills();

    ASSERT_TRUE(value);
    ASSERT_EQ(*value, 7);
    ASSERT_TRUE(spent < 1100);

    producer.join();
}

TEST(MPMCQueue, BlockingTake2) {
    Queue<int> queue;

    std::thread producer([&]() {
        std::this_thread::sleep_for(1s);
        queue.Close();
    });

    concurrency::StopWatch thread_cpu_timer;

    auto value = queue.Take();

    auto spent = thread_cpu_timer.ElapsedMills();

    ASSERT_FALSE(value);
    ASSERT_TRUE(spent < 1100);

    producer.join();
}

TEST(MPMCQueue, UnblockConsumers) {
    Queue<int> queue;

    // Consumers
    std::thread consumer1([&]() {
        queue.Take();
    });

    std::thread consumer2([&]() {
        queue.Take();
    });

    // Producer
    std::this_thread::sleep_for(100ms);
    queue.Close();

    consumer1.join();
    consumer2.join();
}

TEST(MPMCQueue, ProducerConsumer) {
    Queue<int> queue;

    concurrency::StopWatch process_cpu_timer;

    std::thread producer([&]() {
        // Producer
        for (int i = 0; i < 10; ++i) 
        {
            queue.Put(i);
            std::this_thread::sleep_for(100ms);
        }
        queue.Close();
    });

    // Consumer
    for (int i = 0; i < 10; ++i) 
    {
        auto value = queue.Take();
        ASSERT_TRUE(value);
        ASSERT_EQ(*value, i);
    }

    ASSERT_FALSE(queue.Take());

    producer.join();

    auto time = process_cpu_timer.ElapsedMills();
    ASSERT_TRUE(time < 1100);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}