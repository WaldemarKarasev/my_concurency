// STL
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

// Testing
#include <gtest/gtest.h>

// Concurrency
#include <concurrency/fiber/fiber.hpp> // fiber
#include <concurrency/fiber/go.hpp> // Go
#include <concurrency/fiber/yield.hpp> // Yield
#include <concurrency/tread_pool/thread_pool.hpp> // scheduler

using ThreadPool = concurrency::tp::ThreadPool;



void AssertOn(ThreadPool& pool)
{
    ASSERT_EQ(ThreadPool::Current(), &pool);
}


TEST(Fiber, JustWorks) {
    ThreadPool pool{3};
    pool.Start();

    bool done = false;

    Go(pool, [&]() {
        AssertOn(pool);
        done = true;
    });

    pool.WaitIdle();

    ASSERT_TRUE(done);

    pool.Stop();
}

TEST(Fiber, Child) {
    ThreadPool pool{3};
    pool.Start();

    std::atomic<size_t> done{0};

    auto init = [&]() {
        AssertOn(pool);

        Go([&]() {
            AssertOn(pool);
            ++done;
        });

        ++done;
    };

    Go(pool, init);

    pool.WaitIdle();

    ASSERT_EQ(done.load(), 2);

    pool.Stop();
}

TEST(Fiber, RunInParallel) {
    ThreadPool pool{3};
    pool.Start();

    std::atomic<size_t> completed{0};

    auto sleeper = [&]() {
        std::this_thread::sleep_for(3s);
        completed.fetch_add(1);
    };

    wheels::StopWatch stop_watch;

    Go(pool, sleeper);
    Go(pool, sleeper);
    Go(pool, sleeper);

    pool.WaitIdle();

    ASSERT_EQ(completed.load(), 3);
    ASSERT_TRUE(stop_watch.Elapsed() < 3s + 500ms);

    pool.Stop();
}

TEST(Fiber, Yield1) {
    ThreadPool pool{1};
    pool.Start();

    bool done = false;

    Go(pool, [&] {
        Yield();

        AssertOn(pool);
        done = true;
    });

    pool.WaitIdle();
    ASSERT_TRUE(done);

    pool.Stop();
}

TEST(Fiber, Yield2) {
    ThreadPool pool{1};

    enum State : int {
        Ping = 0,
        Pong = 1
    };

    int state = Ping;

    Go(pool, [&] {
        for (size_t i = 0; i < 2; ++i) {
            ASSERT_EQ(state, Ping);
            state = Pong;

            Yield();
        }
    });

    Go(pool, [&] {
        for (size_t j = 0; j < 2; ++j) {
            ASSERT_EQ(state, Pong);
            state = Ping;

            Yield();
        }
    });

    pool.Start();

    pool.WaitIdle();
    pool.Stop();
}

TEST(Fiber, Yield3) {
    ThreadPool pool{4};

    static const size_t kYields = 1024;

    auto runner = [] {
        for (size_t i = 0; i < kYields; ++i) {
            Yield();
        }
    };

    Go(pool, runner);
    Go(pool, runner);

    pool.Start();

    pool.WaitIdle();
    pool.Stop();
}

TEST(Fiber, TwoPools1) {
    ThreadPool pool_1{4};
    ThreadPool pool_2{4};

    pool_1.Start();
    pool_2.Start();

    auto make_tester = [](ThreadPool& pool) {
        return [&pool]() {
            AssertOn(pool);
        };
    };

    Go(pool_1, make_tester(pool_1));
    Go(pool_2, make_tester(pool_2));

    pool_1.WaitIdle();
    pool_2.WaitIdle();

    pool_1.Stop();
    pool_2.Stop();
}

TEST(Fiber, TwoPools2) {
    ThreadPool pool_1{4};
    pool_1.Start();

    ThreadPool pool_2{4};
    pool_2.Start();

    auto make_tester = [](ThreadPool& pool) {
        return [&pool]() {
            static const size_t kIterations = 128;

            for (size_t i = 0; i < kIterations; ++i) {
                AssertOn(pool);

                Yield();

                Go(pool, [&pool]() {
                    AssertOn(pool);
                });
            }
        };
    };

    Go(pool_1, make_tester(pool_1));
    Go(pool_2, make_tester(pool_2));

    pool_1.WaitIdle();
    pool_2.WaitIdle();

    pool_1.Stop();
    pool_2.Stop();
}


int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}