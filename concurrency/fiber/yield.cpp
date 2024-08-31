#include "yield.hpp"


namespace concurrency::fiber {

void Yield()
{
    Fiber::Self()->Schedule();
}

} // namespace concurrency::fiber