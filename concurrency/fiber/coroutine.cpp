#include "coroutine.hpp"

#include <concurrency/utility.hpp>

namespace concurrency::fiber {
 
static thread_local Coroutine* current = nullptr;

Coroutine::Coroutine(std::function<void()> routine)
    : stack_(concurrency::stack::MmapStack::AllocateBytes(64 * 1024))
{
    fun_ = std::move(routine);
    // stack_.AllocateBytes(/*at_least*/64 * 1024);
    coro_context_.Setup(stack_.MutView(), this);
}

void Coroutine::Resume()
{
    Coroutine* prev = current;
    current = this;
    caller_context_.SwitchTo(coro_context_);   

    current = prev;

    if (coro_exception_)
    {
        std::rethrow_exception(coro_exception_);
    }

}

// Suspend running coroutine
void Coroutine::Suspend()
{
    if (current == nullptr)
    {
        std::abort();
    }

    current->coro_context_.SwitchTo(current->caller_context_);
}

bool Coroutine::IsCompleted() const
{
    return is_completed_;
}

void Coroutine::Run() noexcept
{
    try {
        fun_();
    } catch (...)
    {
        coro_exception_ = std::current_exception();
        std::cout << "Unknown exception" << std::endl;
    }

    // finilize coroutine
    is_completed_ = true;
    coro_context_.ExitTo(caller_context_);

    // Unreachable region
    std::abort();
}

}