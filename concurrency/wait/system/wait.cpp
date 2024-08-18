#include "wait.hpp"

#include "futex/futex_wait.hpp"

namespace concurrency::wait::system {

static_assert(sizeof(std::atomic<uint32_t>) == sizeof(uint32_t));

static uint32_t* Addr(std::atomic<uint32_t>& atomic)
{
    return (uint32_t*)&atomic;
}

WakeKey PrepareWake(std::atomic<uint32_t>& atomic)
{
    return {(uint32_t*)&atomic};
}

// Wait
void Wait(std::atomic<uint32_t>& atomic, uint32_t old, std::memory_order mo)
{
    while(atomic.load(mo) == old)
    {
        futex::SystemWait(Addr(atomic), old);
    }

}

bool WaitTimed(std::atomic<uint32_t>& atomic, uint32_t old, std::chrono::milliseconds timeout, std::memory_order mo)
{
    // Not implemented
    return false; // for compiler
}

// Wake
void WakeOne(WakeKey key)
{
    futex::SystemWake(key.addr, 1);
}

void WakeAll(WakeKey key)
{
    futex::SystemWake(key.addr, INT32_MAX);
}   

} // namespace concurrency::wait::futex