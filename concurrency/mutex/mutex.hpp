#pragma once

#include <atomic>
#include <concurrency/atomic/atomic.hpp>

#include <concurrency/wait/system/wait.hpp>

namespace concurrency {

class mutex
{
public:
    using atomic_type = std::atomic<uint32_t>;

public:

    mutex() = default;

    // Non-copyable
    mutex(const mutex&) = delete;
    mutex& operator=(const mutex&) = delete;

    // Non-movable
    mutex(mutex&&) = delete;
    mutex& operator=(mutex&&) = delete;

    void lock()
    {

    }

    void unlock()
    {

    }

private:
    atomic_type phase_{0};
};

}