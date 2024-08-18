#include "atomic.hpp"

#include <atomic>

#include <iostream>

namespace concurrency {
    
    atomic::Value atomic::load(memory_order mo)
    {
        switch (mo)
        {
        case memory_order::relaxed:
            return atomic_load_relaxed(&cell_);

        case memory_order::release :
            return atomic_load_release(&cell_);

        case memory_order::seqcst:
            return atomic_load_setcst(&cell_);
        default:
            // UB
            return {};
        }

        // UB
        return {}; // for compiler
    }

    void atomic::store(Value value, memory_order mo)
    {
        switch (mo)
        {
        case memory_order::relaxed:
            atomic_store_relaxed(&cell_, value);
            break;
        case memory_order::release:
            atomic_store_release(&cell_, value);
            break;
        case memory_order::seqcst:
            atomic_store_setcst(&cell_, value);
            break;
        default:
            // UB
            break;
        }
    }

    atomic::Value atomic::exchange(Value new_value, memory_order mo)
    {
        switch (mo)
        {
        case memory_order::seqcst:
            return atomic_echange_seqcst(&cell_, new_value);
        default:
            // UB
            break;
        }

        return {}; // for compiler
    }
    
}