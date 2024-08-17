#include "wait.hpp"


namespace concurrency::wait::futex {

static_assert(sizeof(std::atomic<uint32_t>) == sizeof(uint32_t));

static uint32_t* Addr(std::atomic<uint32_t>& atomic)
{
    return (uint32_t*)&atomic;
}

// Wait
void Wait(std::atomic<uint32_t>& atomic, uint32_t old,
          std::memory_order mo)
{
    while(atomic.load(mo) == old)
    {
        // SystemWait(Addr(atomic), old);
    }

}

bool WaitTimed(std::atomic<uint32_t>& atomic, uint32_t old,
               std::chrono::milliseconds timeout,
               std::memory_order mo)
{
    // Not implemented
}

// Wake
void WakeOne(WakeKey key)
{
    // SystemWake(key.addr, 1);
}

void WakeAll(WakeKey key)
{
    // SystemWake(key.addr, INT32_MAX);
}   

} // namespace concurrency::wait::futex