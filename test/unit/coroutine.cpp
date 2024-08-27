// STL
#include <iostream>
#include <chrono>
#include <thread>

// Testing
#include <gtest/gtest.h>

// Concurrency
#include <concurrency/fiber/coroutine.hpp>
#include <concurrency/utility.hpp>

using Coroutine = concurrency::fiber::Coroutine;
using concurrency::print;


TEST(Coroutine, JustWorks) {
    Coroutine coro([](){
        std::cout << "Hello coro!" << std::endl;

        Coroutine::Suspend();

        std::cout << "Hello after Suspend and resuming coroutine" << std::endl;

    });

    coro.Resume();

    coro.Resume();

    std::cout << "Coroutine just works" << std::endl;


    Coroutine co([] {
      Coroutine::Suspend();
    });

    EXPECT_EQ(co.IsCompleted(), false);
    ASSERT_FALSE(co.IsCompleted());
    
    co.Resume();
    EXPECT_EQ(co.IsCompleted(), false);
    ASSERT_FALSE(co.IsCompleted());
    
    co.Resume();
    EXPECT_EQ(co.IsCompleted(), true);
    ASSERT_TRUE(co.IsCompleted());
}


TEST(Coroutine, Interleaving) {

    int step = 0;

    Coroutine a([&] {
        ASSERT_EQ(step, 0);
        step = 1;
        Coroutine::Suspend();
        ASSERT_EQ(step, 2);
        step = 3;
    });

    Coroutine b([&] {
        ASSERT_EQ(step, 1);
        step = 2;
        Coroutine::Suspend();
        ASSERT_EQ(step, 3);
        step = 4;
    });

    a.Resume();
    b.Resume();

    ASSERT_EQ(step, 2);

    a.Resume();
    b.Resume();

    ASSERT_TRUE(a.IsCompleted());
    ASSERT_TRUE(b.IsCompleted());

    ASSERT_EQ(step, 4);
}


struct Threads {
    template <typename F>
    void Run(F task) 
    {
        std::thread t([task = std::move(task)]() mutable {
            task();
        });
        t.join();
    }
};
TEST(Coroutine, Threads) {
    size_t steps = 0;

    Coroutine co([&steps] {
        std::cout << "Step" << std::endl;
        ++steps;
        Coroutine::Suspend();
        std::cout << "Step" << std::endl;
        ++steps;
        Coroutine::Suspend();
        std::cout << "Step" << std::endl;
        ++steps;
    });

    auto resume = [&co] {
        co.Resume();
    };

    // Simulate fiber running in thread pool
    Threads threads;
    threads.Run(resume);
    threads.Run(resume);
    threads.Run(resume);

    ASSERT_EQ(steps, 3);
}

TEST(Coroutine, Pipeline) {
    const size_t kSteps = 123;

    size_t step_count = 0;

    Coroutine a([&] {
        Coroutine b([&] {
        for (size_t i = 0; i < kSteps; ++i) {
            ++step_count;
            Coroutine::Suspend();
        }
        });

        while (!b.IsCompleted()) {
            b.Resume();
            Coroutine::Suspend();
        }
    });

    while (!a.IsCompleted()) {
        a.Resume();
    }

    ASSERT_EQ(step_count, kSteps);
}

struct MyException {};

TEST(Coroutine, Exception) {
    Coroutine co([&] {
        Coroutine::Suspend();
        throw MyException{};
        Coroutine::Suspend();
    });

    ASSERT_FALSE(co.IsCompleted());
    co.Resume();
    ASSERT_THROW(co.Resume(), MyException);
    ASSERT_TRUE(co.IsCompleted());
}


TEST(Coroutine, NestedException1) {
    Coroutine a([&] {
        Coroutine b([] {
            throw MyException();
        });
        ASSERT_THROW(b.Resume(), MyException);
    });

    a.Resume();
}

TEST(Coroutine, NestedException2) {
    Coroutine a([&] {
        Coroutine b([] {
            throw MyException();
        });
        b.Resume();
    });

    ASSERT_THROW(a.Resume(), MyException);

    ASSERT_TRUE(a.IsCompleted());
}


TEST(Coroutine, ExceptionsHard) {
    int score = 0;

    Coroutine a([&] {        
        Coroutine b([] {
            throw 1;
        });

        try {
            b.Resume();
        } catch (int) {
            ++score;
            // Context switch during stack unwinding
            Coroutine::Suspend();
            throw 1;
        }
    });

    a.Resume();
    std::thread t([&] {
        try {
            a.Resume();
        } catch (int) {
            ++score;
        }
    });
    t.join();
    ASSERT_EQ(score, 2);
}


TEST(Coroutine, MemoryLeak) {
    auto shared_ptr = std::make_shared<int>(42);
    std::weak_ptr<int> weak_ptr = shared_ptr;

    {
        auto routine = [ptr = std::move(shared_ptr)] {};
        Coroutine co(routine);
        co.Resume();
    }

    ASSERT_FALSE(weak_ptr.lock());
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/*


//////////////////////////////////////////////////////////////////////

TEST_SUITE(Coroutine) {












}

RUN_ALL_TESTS()

*/


