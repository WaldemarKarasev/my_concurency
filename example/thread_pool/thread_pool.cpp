
#include <iostream>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

// concurrency
#include <concurrency/exe/thread_pool.hpp>

using ThreadPool = concurrency::exe::ThreadPool;

int main()
{
    ThreadPool pool{std::thread::hardware_concurrency()};

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
}