#pragma once

#include <cstdint>

namespace concurrency {

    using int64 = std::int64_t;
    using atomic_int64 = volatile int64;

}

// Load
extern "C" concurrency::int64 atomic_load_relaxed(concurrency::atomic_int64* cell);
extern "C" concurrency::int64 atomic_load_release(concurrency::atomic_int64* cell);
extern "C" concurrency::int64 atomic_load_setcst(concurrency::atomic_int64* cell);

// Store
extern "C" void atomic_store_relaxed(concurrency::atomic_int64* cell, concurrency::int64 value);
extern "C" void atomic_store_release(concurrency::atomic_int64* cell, concurrency::int64 value);
extern "C" void atomic_store_setcst(concurrency::atomic_int64* cell, concurrency::int64 value);


// Exchange

extern "C" concurrency::int64 atomic_echange_seqcst(concurrency::atomic_int64* cell, concurrency::int64 value);