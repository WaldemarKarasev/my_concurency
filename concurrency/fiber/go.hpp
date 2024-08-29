#pragma once

#include <concurrency/tread_pool/task.hpp>
#include <concurrency/tread_pool/thread_pool.hpp>

namespace concurrency::fiber {

using Scheduler = concurrency::tp::ThreadPool;
using Routine   = concurrency::tp::Task;


void Go(Routine);
void Go(Scheduler&, Routine);


} // namespace concurrency::fiber