// STL
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

// Testing
#include <gtest/gtest.h>

// Concurrency
#include <concurrency/tread_pool/thread_pool.hpp>
#include <concurrency/utility.hpp>

TEST(Thread_Pool, JustWorks) {
    concurrency::tp::ThreadPool pool{4};

    pool.Start();

    pool.Submit([]() {
        std::cout << "Hello from thread pool!" << std::endl;
    });

    pool.WaitIdle();
    pool.Stop();
}

TEST(Thread_Pool, Wait) {
    concurrency::tp::ThreadPool pool{4};

    pool.Start();

    bool done = false;

    pool.Submit([&]() {
        std::this_thread::sleep_for(1s);
        done = true;
    });

    pool.WaitIdle();
    pool.Stop();

    ASSERT_TRUE(done);
}

TEST(Thread_Pool, MultiWait) {
    concurrency::tp::ThreadPool pool{1};

    pool.Start();

    for (size_t i = 0; i < 3; ++i) {
        bool done = false;

        pool.Submit([&]() {
        std::this_thread::sleep_for(1s);
        done = true;
        });

        pool.WaitIdle();

        ASSERT_TRUE(done);
    }

    pool.Stop();
}

TEST(Thread_Pool, Exceptions) {
    concurrency::tp::ThreadPool pool{1};

    pool.Start();

    pool.Submit([]() {
        throw std::runtime_error("Task failed");
    });

    pool.WaitIdle();
    pool.Stop();
}

TEST(Thread_Pool, ManyTasks) {
    concurrency::tp::ThreadPool pool{4};

    pool.Start();

    static const size_t kTasks = 17;

    std::atomic<size_t> tasks{0};

    for (size_t i = 0; i < kTasks; ++i) {
        pool.Submit([&]() {
            ++tasks;
        });
    }

    pool.WaitIdle();
    pool.Stop();

    ASSERT_EQ(tasks.load(), kTasks);
}

TEST(Thread_Pool, Parallel) {
    concurrency::tp::ThreadPool pool{4};

    pool.Start();

    std::atomic<size_t> tasks{0};

    pool.Submit([&]() {
        std::this_thread::sleep_for(1s);
        ++tasks;
    });

    pool.Submit([&]() {
        ++tasks;
    });

    std::this_thread::sleep_for(100ms);

    ASSERT_EQ(tasks.load(), 1);

    pool.WaitIdle();
    pool.Stop();

    ASSERT_EQ(tasks.load(), 2);
}

TEST(Thread_Pool, TwoPools) {
    concurrency::tp::ThreadPool pool1{1};
    concurrency::tp::ThreadPool pool2{1};

    pool1.Start();
    pool2.Start();

    std::atomic<size_t> tasks{0};

    concurrency::StopWatch stop_watch;

    pool1.Submit([&]() {
        std::this_thread::sleep_for(1s);
        ++tasks;
    });

    pool2.Submit([&]() {
        std::this_thread::sleep_for(1s);
        ++tasks;
    });

    pool2.WaitIdle();
    pool2.Stop();

    pool1.WaitIdle();
    pool1.Stop();

    ASSERT_TRUE(stop_watch.ElapsedMills() < 1500);
    ASSERT_EQ(tasks.load(), 2);
}

TEST(Thread_Pool, Stop) {
    concurrency::tp::ThreadPool pool{1};

    pool.Start();

    for (size_t i = 0; i < 3; ++i) {
        pool.Submit([] {
        std::this_thread::sleep_for(128ms);
        });
    }

    pool.Stop();
}

TEST(Thread_Pool, DoNotBurnCPU) {
    concurrency::tp::ThreadPool pool{4};

    pool.Start();

    // Warmup
    for (size_t i = 0; i < 4; ++i) {
        pool.Submit([&]() {
            std::this_thread::sleep_for(100ms);
        });
    }

    concurrency::StopWatch cpu_timer;

    std::this_thread::sleep_for(1s);

    pool.WaitIdle();
    pool.Stop();

    ASSERT_TRUE(cpu_timer.ElapsedMills() < 1100);
}

TEST(Thread_Pool, Current) {
    concurrency::tp::ThreadPool pool{1};

    pool.Start();

    ASSERT_EQ(concurrency::tp::ThreadPool::Current(), nullptr);

    pool.Submit([&]() {
        ASSERT_EQ(concurrency::tp::ThreadPool::Current(), &pool);
    });

    pool.WaitIdle();
    pool.Stop();
}

TEST(Thread_Pool, SubmitAfterWaitIdle) {
    concurrency::tp::ThreadPool pool{4};

    pool.Start();

    bool done = false;

    pool.Submit([&]() {
        std::this_thread::sleep_for(500ms);

        concurrency::tp::ThreadPool::Current()->Submit([&]() {
        std::this_thread::sleep_for(500ms);
        done = true;
        });
    });

    pool.WaitIdle();
    pool.Stop();

    ASSERT_TRUE(done);
}

// TEST(UseThreads, wheels::test::TestOptions().TimeLimit(1s)) {
TEST(Thread_Pool, UseThreads) {
    concurrency::tp::ThreadPool pool{4};

    pool.Start();

    std::atomic<size_t> tasks{0};

    for (size_t i = 0; i < 4; ++i) {
        pool.Submit([&]() {
        std::this_thread::sleep_for(750ms);
        ++tasks;
        });
    }

    pool.WaitIdle();
    pool.Stop();

    ASSERT_EQ(tasks.load(), 4);
}

TEST(Thread_Pool, Racy) {
    concurrency::tp::ThreadPool pool{4};

    pool.Start();

    std::atomic<int> shared_counter{0};
    std::atomic<int> tasks{0};

    for (size_t i = 0; i < 100500; ++i) {
        pool.Submit([&]() {
        int old = shared_counter.load();
        shared_counter.store(old + 1);

        ++tasks;
        });
    }

    pool.WaitIdle();
    pool.Stop();

    std::cout << "Racy counter value: " << shared_counter << std::endl;

    ASSERT_EQ(tasks.load(), 100500);
    ASSERT_LE(shared_counter.load(), 100500);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}