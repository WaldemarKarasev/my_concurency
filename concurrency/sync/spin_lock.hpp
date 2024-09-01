#pragma once 

#include <atomic>
#include <concurrency/sync/atomic/atomic.hpp>


using Atomic = std::atomic<int>;
// using Atomic = concurrency::atomic;

namespace concurrency {

class spin_lock
{
private:
    void CPU_relax()
    {
        asm volatile("pause\n" : : : "memory");
    }

public:

    void lock()
    {
        while (locked_.exchange(1, std::memory_order_acquire) == 1) // Cache pin-pong
        {
            // spin wait
            while(locked_.load(std::memory_order_relaxed)) // Preventing cache pin-pong
            {
                CPU_relax();
            }
        }
    }

    void unlock()
    {
        locked_.store(0, std::memory_order_release); // <--- Thundering Herd
    }

    void try_lock()
    {
        // Not implemented
    }

private:
    // Atomic locked_{0};
    std::atomic<int> locked_{0};
};

} // namespace concurrency