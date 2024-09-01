#pragma once

#include <atomic>
#include <concurrency/sync/atomic/atomic.hpp>

#include <concurrency/wait/system/wait.hpp>

#include <mutex>

namespace concurrency {

class mutex
{
    enum State : uint32_t
    {
        Free = 0,
        Locked
    };

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
        while (phase_.exchange(State::Locked) == State::Locked)
        {
            wait::system::Wait(phase_, State::Locked);
        }
    }

    void unlock()
    {
        wait::system::WakeKey key = wait::system::PrepareWake(phase_);
        phase_.store(State::Free);
        wait::system::WakeOne(key);
    }

private:
    atomic_type phase_{State::Free};
    std::mutex mutex_;
};

} // namespace concurrency