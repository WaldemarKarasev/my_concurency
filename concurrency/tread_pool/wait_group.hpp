#pragma once

#include <cassert>
#include <cstdlib>

#include <atomic>
#include <condition_variable>
#include <mutex>

#include <iostream>
#include <concurrency/wait/system/wait.hpp>

namespace concurrency::tp {

// mutex + condvar -> simple
// atomic + futex_wait (barrier) -> harder 
class WaitGroup
{
public:

    void Add(size_t count)
    {
        std::lock_guard lock(mutex_);
        counter_.fetch_add(count);
    }

    void Done()
    {
        assert(counter_.load() > 0);
        std::lock_guard lock(mutex_);
        counter_.fetch_sub(1);

        if (counter_.load() == 0)
        {
            wait_zero_.notify_all();
        }
    }

    void Wait()
    {
        std::unique_lock lock(mutex_);

        wait_zero_.wait(lock, [this](){
            return counter_.load() == 0;
        });
    }

private:
    std::atomic<size_t> counter_{0};
    std::mutex mutex_;
    std::condition_variable wait_zero_;
};


class WaitGroup_Futex
{
public:

    void Add(size_t count)
    {
        // std::cout << "Add" << std::endl;
        counter_.fetch_add(count, std::memory_order_seq_cst);
    }

    void Done()
    {
        // std::cout << "Done" << std::endl;
        assert(counter_.load() > 0);
        counter_.fetch_sub(1);

        if (counter_.load(std::memory_order_release) == 0)
        {
            auto key = concurrency::wait::system::PrepareWake(barrier);
            barrier.store(1);
            concurrency::wait::system::WakeOne(key);            
        }
    }

    void Wait()
    {
        // std::cout << "Wait" << std::endl;
        concurrency::wait::system::Wait(barrier, 0);
        // std::cout << barrier.load() << std::endl;
        // std::cout << counter_.load() << std::endl;
        // std::cout << "Wait ends" << std::endl;
        barrier.store(0);
    }

private:
    std::atomic<size_t> counter_{0};
    std::atomic<uint32_t> barrier{0};
};

}