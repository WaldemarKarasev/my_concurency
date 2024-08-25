#pragma once

// STL
#include <functional>

// concurrency
#include <concurrency/stack/stack.hpp>
#include <concurrency/context/context.hpp>

namespace concurrency::fiber {

class Coroutine : public concurrency::ITrampoline {

public:
    using Routine = std::function<void()>;

    explicit Coroutine(std::function<void()> routine);

    void Resume();

    // Suspend running coroutine
    static void Suspend();

    bool IsCompleted() const;

    void Run() noexcept override;

private:
    // routine
    std::function<void()> fun_;
    // stack
    concurrency::stack::MmapStack stack_;
    // context
    concurrency::contex::ExecutionContext coro_context_;
    concurrency::contex::ExecutionContext caller_context_;

    // completion flag
    bool is_completed_{false};

};

}