#include "go.hpp"

namespace concurrency::fiber {


static Fiber* CreateFiber(Scheduler& pool, Task task)
{
    Fiber* fiber = new Fiber(&pool, std::move(task));
    return fiber;
}

void Go(Task task)
{
    Scheduler& pool = *Scheduler::Current();
    Go(pool, std::move(task));
}
void Go(Scheduler& pool, Task task)
{
    auto* fiber = CreateFiber(pool, std::move(task));
    pool.Submit(fiber);
}

} // concurrency::fiber