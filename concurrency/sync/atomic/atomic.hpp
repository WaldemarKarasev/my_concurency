#pragma once 

#include "asm/atomic_ops.hpp"


namespace concurrency {

    enum class memory_order : int
    {
        relaxed,
        // consume, // Not implemented
        acquire,
        release,
        // acq_rel  // Not implemented
        seqcst
    };


    class atomic
    {
        using impl = atomic_int64;

    public:
        using Value = int64;


    public:

    explicit atomic(Value initial_value = 0)
            : cell_(initial_value)
    {
       
    }
    
    // Non-copyable
    atomic(const atomic&) = delete;
    atomic& operator=(const atomic&) = delete;

    // Non-movable
    atomic(atomic&&) = delete;
    atomic& opetator(atomic&&) = delete;

    // Operations
    Value load(memory_order mo = memory_order::seqcst);

    operator Value()
    {
        return load();
    }

    void store(Value value, memory_order mo = memory_order::seqcst);

    atomic& operator=(Value value)
    {
        store(value);
        return *this;
    }

    Value exchange(Value new_value, memory_order mo = memory_order::seqcst);


    private:
        impl cell_;

    };

} // namespace concurrency