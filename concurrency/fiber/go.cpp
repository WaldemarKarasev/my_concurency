#include "go.hpp"

namespace concurrency::fiber {


void Go(Routine task)
{
    Scheduler::Current()->Submit(std::move(task));
}
void Go(Scheduler& pool, Routine task)
{
    pool.Submit(std::move(task));
}

} // concurrency::fiber