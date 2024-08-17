#pragma once

// STL
#include <atomic>
#include <chrono>

// Concurrency
#include <concurrency/atomic/atomic.hpp>


namespace concurrency::wait::futex {

// using Atomic = std::atomic<uint32_t>;
// using MemoryOrder = std::memory_order;

struct WakeKey {
    uint32_t* addr;
};

// Wait
void Wait(std::atomic<uint32_t>& atomic, uint32_t old,
          std::memory_order mo = std::memory_order::seq_cst);

bool WaitTimed(std::atomic<uint32_t>& atomic, uint32_t old,
               std::chrono::milliseconds timeout,
               std::memory_order mo = std::memory_order::seq_cst);


// Wake
void WakeOne(WakeKey key);
void WakeAll(WakeKey key);

} // namespace concurrency::wait::futex