#include <utility>

// STL
#include <iostream>
#include <thread>
#include <vector>

// Testing
#include <gtest/gtest.h>

// Concurrency
#include <concurrency/utility.hpp>
#include <concurrency/sync/wait_group.hpp>
#include <concurrency/fiber/go.hpp>
#include <concurrency/exe/thread_pool.hpp>

using ThreadPool = concurrency::exe::ThreadPool;
using WaitGroup = concurrency::WaitGroup_Futex;


TEST(Wait_Group, OneWaiter) {
    ThreadPool scheduler{/*threads=*/5};
    scheduler.Start();

    WaitGroup wg;

    std::atomic<size_t> workers{0};
    std::atomic<bool> waiter{false};

    static const size_t kWorkers = 3;

    wg.Add(kWorkers);

    concurrency::fiber::Go(scheduler, [&]() {
        wg.Wait();
        ASSERT_EQ(workers.load(), kWorkers);
        waiter = true;
    });

    for (size_t i = 0; i < kWorkers; ++i) {
        concurrency::fiber::Go(scheduler, [&]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            ++workers;
            wg.Done();
        });
    }

    scheduler.WaitIdle();

    ASSERT_TRUE(waiter);

    scheduler.Stop();
}

TEST(Wait_Group, MultipleWaiters) {
    ThreadPool scheduler{/*threads=*/5};
    scheduler.Start();

    WaitGroup wg;

    std::atomic<size_t> workers{0};
    std::atomic<size_t> waiters{0};

    static const size_t kWorkers = 3;
    static const size_t kWaiters = 4;

    wg.Add(kWorkers);

    for (size_t i = 0; i < kWaiters; ++i) {
        concurrency::fiber::Go(scheduler, [&]() {
            wg.Wait();
            ASSERT_EQ(workers.load(), kWorkers);
            ++waiters;
        });
    }

    for (size_t i = 0; i < kWorkers; ++i) {
        concurrency::fiber::Go(scheduler, [&]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            ++workers;
            wg.Done();
        });
    }

    scheduler.WaitIdle();

    ASSERT_EQ(waiters, kWaiters);

    scheduler.Stop();
}

TEST(Wait_Group, BlockingWait) {
    ThreadPool scheduler{/*threads=*/4};
    scheduler.Start();

    WaitGroup wg;

    std::atomic<size_t> workers = 0;

    concurrency::StopWatch timer;

    static const size_t kWorkers = 3;

    wg.Add(kWorkers);

    concurrency::fiber::Go(scheduler, [&]() {
        wg.Wait();
        ASSERT_EQ(workers.load(), kWorkers);
    });

    for (size_t i = 0; i < kWorkers; ++i) {
        concurrency::fiber::Go(scheduler, [&]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            ++workers;
            wg.Done();
        });
    }

    scheduler.WaitIdle();

    auto time = timer.ElapsedMills();

    ASSERT_TRUE(time < 110);

    scheduler.Stop();
}


int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}