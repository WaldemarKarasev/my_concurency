#include "yield.hpp"


namespace concurrency::fiber {

void Yield()
{
    Fiber* fiber = Fiber::Self();
    if (Fiber::Self() != nullptr)
    {
        fiber->Suspend();
    }
}

} // namespace concurrency::fiber