// STL
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

// Testing
#include <gtest/gtest.h>

// Concurrency
#include <concurrency/mutex/mutex.hpp>
#include <concurrency/utility.hpp>

TEST(Mutex, LockUnlock)
{
    concurrency::mutex mutex;
    mutex.lock();
    mutex.unlock();
}

TEST(Mutex, SequentialLockUnlock)
{
    concurrency::mutex mutex;
    mutex.lock();
    mutex.unlock();
    mutex.lock();
    mutex.unlock();
}

TEST(Mutex, NoSharedLocations)
{
    concurrency::mutex mutex;
    mutex.lock();

    concurrency::mutex mutex2;
    mutex2.lock();
    mutex2.unlock();

    mutex.unlock();
}


TEST(Mutex, MutualExclusion)
{
    concurrency::mutex mutex;
    bool cs = false;

    std::thread locker([&]() {
      mutex.lock();
      cs = true;
      std::this_thread::sleep_for(3s);
      cs = false;
      mutex.unlock();
    });

    std::this_thread::sleep_for(1s);
    mutex.lock();
    ASSERT_FALSE(cs);
    mutex.unlock();

    locker.join();
}

TEST(Mutex, Blocking)
{
    concurrency::mutex mutex;

    // Warmup
    mutex.lock();
    mutex.unlock();

    std::thread sleeper([&]() {
      mutex.lock();
      std::this_thread::sleep_for(3s);
      mutex.unlock();
    });

    std::thread waiter([&]() {
        std::this_thread::sleep_for(1s);

        concurrency::StopWatch cpu_timer;

        mutex.lock();
        mutex.unlock();

        auto spent = cpu_timer.ElapsedMills();

        ASSERT_TRUE(spent < 200);
    });

    sleeper.join();
    waiter.join();
}


int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}