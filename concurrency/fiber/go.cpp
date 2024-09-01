#include "go.hpp"

namespace concurrency::fiber {


static Fiber* CreateFiber(exe::IExecutor& exe, Task task)
{
    Fiber* fiber = new Fiber(&exe, std::move(task));
    return fiber;
}

void Go(Task task)
{
    auto* fiber = CreateFiber(Fiber::Self()->GetExecutor(), std::move(task));
    
    fiber->Schedule();
}
void Go(exe::IExecutor& exe, Task task)
{
    auto* fiber = CreateFiber(exe, std::move(task));
    exe.Submit(fiber);
}

} // concurrency::fiber