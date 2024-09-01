#pragma once

#include <concurrency/task/task.hpp>
#include <concurrency/fiber/fiber.hpp>
#include <concurrency/exe/executor.hpp>

namespace concurrency::fiber {

void Go(Task);
void Go(exe::IExecutor&, Task);


} // namespace concurrency::fiber