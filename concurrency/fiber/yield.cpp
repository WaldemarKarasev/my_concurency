#include "yield.hpp"

#include <concurrency/tread_pool/thread_pool.hpp>

namespace concurrency::fiber {

void Yield()
{
    Fiber::Self()->Schedule();
}

} // namespace concurrency::fiber