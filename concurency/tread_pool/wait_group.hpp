#pragma once

#include <cassert>
#include <cstdlib>

#include <atomic>
#include <condition_variable>
#include <mutex>

namespace concurency::tp {

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
        std::lock_guard(mutex_);
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

}