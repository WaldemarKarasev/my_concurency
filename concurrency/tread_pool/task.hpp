#pragma once

#include <functional>

namespace concurrency::tp {

    using Task = std::function<void()>;

}