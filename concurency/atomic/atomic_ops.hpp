#pragma once

#include <cstdint>

namespace concurency {

    using int64 = std::int64_t;
    using atomic_int64 = volatile int64;

}

// Load
extern "C" concurency::int64 atomic_load_relaxed(concurency::atomic_int64* cell);
extern "C" concurency::int64 atomic_load_release(concurency::atomic_int64* cell);
extern "C" concurency::int64 atomic_load_setcst(concurency::atomic_int64* cell);

// Store
extern "C" void atomic_store_relaxed(concurency::atomic_int64* cell, concurency::int64 value);
extern "C" void atomic_store_release(concurency::atomic_int64* cell, concurency::int64 value);
extern "C" void atomic_store_setcst(concurency::atomic_int64* cell, concurency::int64 value);


// Exchange

extern "C" concurency::int64 atomic_echange_seqcst(concurency::atomic_int64* cell, concurency::int64 value);