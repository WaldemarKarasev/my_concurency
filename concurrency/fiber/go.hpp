#pragma once

#include <concurrency/task/task.hpp>
#include <concurrency/fiber/fiber.hpp>

namespace concurrency::fiber {

void Go(Task);
void Go(Scheduler&, Task);


} // namespace concurrency::fiber