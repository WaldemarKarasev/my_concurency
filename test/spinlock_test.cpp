#include <utility>

// STL
#include <iostream>
#include <thread>
#include <vector>

// concurency
#include <concurency/utility.hpp>
#include <concurency/spin_lock/spin_lock.hpp>

void Stress()
{
    concurency::spin_lock spinlock;
    size_t counter = 0;

    concurency::StopWatch stop_watch;

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

int main()
{
    while (true)
    {
        Stress();
    }
}