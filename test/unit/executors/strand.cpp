// gtest
#include <gtest/gtest.h>

// STL
#include <thread>
#include <deque>
#include <atomic>
using namespace std::chrono_literals;
#include <iostream>

// concurrency
#include <concurrency/exe/strand.hpp>
#include <concurrency/exe/manual.hpp>
#include <concurrency/exe/submit.hpp>
#include <concurrency/exe/thread_pool.hpp>
#include <concurrency/utility.hpp>

// using Strand = concurrency::exe::Strand;
// using ManualExecutor = concurrency::exe::ManualExecutor;
// using ThreadPool = concurrency::exe::ThreadPool;
// using IExecutor = concurrency::exe::IExecutor;

using namespace concurrency::exe;


void AssertRunningOn(ThreadPool& pool) {
    ASSERT_TRUE(ThreadPool::Current() == &pool);
}

TEST(Strand, JustWorks) {
    ThreadPool pool{4};
    pool.Start();

    Strand strand{pool};

    bool done = false;

    Submit(strand, [&] {
        done = true;    
    });

    pool.WaitIdle();

    ASSERT_TRUE(done);

    pool.Stop();
}

TEST(Strand, Decorator) {
    ThreadPool pool{4};
    pool.Start();

    Strand strand{pool};

    bool done{false};

    for (size_t i = 0; i < 128; ++i) {
        Submit(strand, [&] {
            AssertRunningOn(pool);
            done = true;
        });
    }

    pool.WaitIdle();

    ASSERT_TRUE(done);

    pool.Stop();
}

TEST(Strand, Counter) {
    ThreadPool pool{13};
    pool.Start();

    size_t counter = 0;

    Strand strand{pool};

    static const size_t kIncrements = 1234;

    for (size_t i = 0; i < kIncrements; ++i) {
        Submit(strand, [&] {
            AssertRunningOn(pool);
            ++counter;
        });
    };

    pool.WaitIdle();

    ASSERT_EQ(counter, kIncrements);

    pool.Stop();
}

TEST(Strand, Fifo) {
    ThreadPool pool{13};
    pool.Start();

    Strand strand{pool};

    size_t done = 0;

    static const size_t kTasks = 12345;

    for (size_t i = 0; i < kTasks; ++i) {
        Submit(strand, [&, i] {
            AssertRunningOn(pool);
            ASSERT_EQ(done++, i);
        });
    };

    pool.WaitIdle();

    ASSERT_EQ(done, kTasks);

    pool.Stop();
}

class Robot {
public:
    explicit Robot(IExecutor& executor)
        : strand_(executor) {
    }

    void Push() {
        Submit(strand_, [this] {
            ++steps_;
        });
    }

    size_t Steps() const {
        return steps_;
    }

private:
    Strand strand_;
    size_t steps_{0};
};

TEST(Strand, ConcurrentStrands) {
    ThreadPool pool{16};
    pool.Start();

    static const size_t kStrands = 50;

    std::deque<Robot> robots;
        for (size_t i = 0; i < kStrands; ++i) {
        robots.emplace_back(pool);
    }

    static const size_t kPushes = 25;
    static const size_t kIterations = 25;

    for (size_t i = 0; i < kIterations; ++i) {
        for (size_t j = 0; j < kStrands; ++j) {
            for (size_t k = 0; k < kPushes; ++k) {
                robots[j].Push();
            }
        }
    }

    pool.WaitIdle();

    for (size_t i = 0; i < kStrands; ++i) {
        ASSERT_EQ(robots[i].Steps(), kPushes * kIterations);
    }

    pool.Stop();
}

TEST(Strand, ConcurrentSubmits) {
    ThreadPool workers{2};
    Strand strand{workers};

    ThreadPool clients{4};

    workers.Start();
    clients.Start();

    static const size_t kTasks = 1024;

    size_t task_count{0};

    for (size_t i = 0; i < kTasks; ++i) {
        Submit(clients, [&] {
            Submit(strand, [&] {
                AssertRunningOn(workers);
                ++task_count;
            });
        });
    }

    clients.WaitIdle();
    workers.WaitIdle();

    ASSERT_EQ(task_count, kTasks);

    workers.Stop();
    clients.Stop();
}

TEST(Strand, StrandOverManual) {
    ManualExecutor manual;
    Strand strand{manual};

    static const size_t kTasks = 117;

    size_t tasks = 0;

    for (size_t i = 0; i < kTasks; ++i) {
        Submit(strand, [&] {
            ++tasks;
        });
    }

    manual.Drain();

    ASSERT_EQ(tasks, kTasks);
}

TEST(Strand, Batching) {
    ManualExecutor manual;
    Strand strand{manual};

    static const size_t kTasks = 100;

    size_t completed = 0;
    for (size_t i = 0; i < kTasks; ++i) {
        Submit(strand, [&completed] {
            ++completed;
        });
    };

    size_t tasks = manual.Drain();
    ASSERT_LT(tasks, 5);
}

TEST(Strand, StrandOverStrand) {
    ThreadPool pool{4};
    pool.Start();

    Strand strand_1{pool};
    Strand strand_2{(IExecutor&)strand_1};

    static const size_t kTasks = 17;

    size_t tasks = 0;

    for (size_t i = 0; i < kTasks; ++i) {
        Submit(strand_2, [&tasks] {
            ++tasks;
        });
    }

    pool.WaitIdle();

    ASSERT_EQ(tasks, kTasks);

    pool.Stop();
}

TEST(Strand, DoNotOccupyThread) {
    ThreadPool pool{1};
    pool.Start();

    Strand strand{pool};

    Submit(pool, [] {
        std::this_thread::sleep_for(1s);
    });

    std::atomic<bool> stop_requested{false};

    auto snooze = []() {
        std::this_thread::sleep_for(10ms);
    };

    for (size_t i = 0; i < 100; ++i) {
        Submit(strand, snooze);
    }

    Submit(pool, [&stop_requested] {
        stop_requested.store(true);
    });

    while (!stop_requested.load()) {
        Submit(strand, snooze);
        std::this_thread::sleep_for(10ms);
    }

    pool.WaitIdle();
    pool.Stop();
}

TEST(Strand, NonBlockingSubmit) {
    ThreadPool pool{1};
    Strand strand{pool};

    pool.Start();

    Submit(strand, [&] {
    // Bubble
        std::this_thread::sleep_for(3s);
    });

    std::this_thread::sleep_for(256ms);

    {
        concurrency::StopWatch stop_watch;
        Submit(strand, [&] {
        // Do nothing
    });

        ASSERT_LE(stop_watch.ElapsedMills(), 100);
    }

    pool.WaitIdle();
    pool.Stop();
}



int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}