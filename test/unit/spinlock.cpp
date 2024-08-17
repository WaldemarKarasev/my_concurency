#include <utility>

// STL
#include <iostream>
#include <thread>
#include <vector>

// Testing
#include <gtest/gtest.h>

// Concurrency
#include <concurrency/utility.hpp>
#include <concurrency/spin_lock/spin_lock.hpp>

void Stress()
{
    concurrency::spin_lock spinlock;
    size_t counter = 0;

    concurrency::StopWatch stop_watch;

    std::vector<std::thread> threads;
    // for (size_t i = 0; i < std::thread::hardware_concurrency(); ++i)
    for (size_t i = 0; i < 5; ++i)
    {
        threads.emplace_back([&](){
            // Contender thread
            for (size_t j = 0; j < 100'500; ++j)
            {
                spinlock.lock();
                ++counter; // Critical section
                spinlock.unlock();
            }
        });
    }

    for (auto& t : threads)
    {
        t.join();
    }


    auto elapsed_ms = stop_watch.ElapsedMills();

    std::cout << counter << std::endl;

    std::cout << "Elapsed: " << elapsed_ms << "ms" << std::endl;     
}

TEST(SpinLock, LockUnlock) {
    concurrency::spin_lock spinlock;

    spinlock.lock();
    spinlock.unlock();  
}

TEST(SpinLock, SequentialLockUnlock) {
    concurrency::spin_lock  spinlock;

    spinlock.lock();
    spinlock.unlock();

    spinlock.lock();
    spinlock.unlock();   
}

TEST(SpinLock, Stress) {
    int steps = 10;
    while (steps > 0)
    {
        Stress();
        steps--;
    }
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}