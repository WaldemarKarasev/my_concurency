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
    if (is_running_)
    {
        is_running_ = false;
        Coroutine::Suspend();
    }
    else
    {
        scheduler_->Submit(this);
    }
}

// Task
void Fiber::Run() noexcept
{
    Fiber* prev = current_fiber;
    current_fiber = this;

    bool terminated = false;
    is_running_ = true;
    try {
        coro_.Resume();
    } catch (std::exception& e) {
        terminated = true;
    } catch (...) {
        terminated = true;
    }
    is_running_ = false;
    if (coro_.IsCompleted() || terminated) 
    {
        delete this;
    }
    else
    {
        Schedule();
    }
}

Fiber* Fiber::Self()
{
    return current_fiber;
}


} // namespace concurrency::fiber