#pragma once

// std::byte
#include <cstddef>

#include <span>

namespace concurrency::stack {

using StackView = std::span<std::byte>;

} // namespace concurrency::stack