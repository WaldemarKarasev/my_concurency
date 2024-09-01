#include "fiber.hpp"

#include <concurrency/tread_pool/thread_pool.hpp>
#include <concurrency/fiber/coroutine.hpp>


namespace concurrency::fiber {


static thread_local Fiber* current_fiber = nullptr;

Fiber::Fiber(Scheduler* executor, Task task)
    : coro_(std::move(task))
    , scheduler_(executor)
{
    
}

void Fiber::Schedule()
{
    scheduler_->Submit(this);
}

void Fiber::Resume()
{
    if (coro_.IsCompleted())
    {
        delete this;
        return;
    }

    coro_.Resume();
}

void Fiber::Suspend()
{
    Coroutine::Suspend();
}

// Task
void Fiber::Run() noexcept
{
    Fiber* prev = current_fiber;
    current_fiber = this;

    bool terminated = false;
    try {
        coro_.Resume();
    } catch (std::exception& e) {
        terminated = true;
    } catch (...) {
        terminated = true;
    }
    if (coro_.IsCompleted() || terminated) 
    {
        delete this;
        return;
    }
    
    Schedule();
}

Fiber* Fiber::Self()
{
    return current_fiber;
}


} // namespace concurrency::fiber