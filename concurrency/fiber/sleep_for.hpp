#pragma once

#include <chrono>

namespace concurrency::fiber {

using Millis = std::chrono::milliseconds;

void SleepFor(Millis);

} // namespace concurrency::fibers