#pragma once

#include <concurrency/task/task.hpp>

namespace concurrency::exe {

template <typename Exe, typename Fun>
void Submit(Exe& exe, Fun&& fun)
{ 
    exe.Submit(Routine::MakeRoutine(std::forward<Fun>(fun)));
}

} // namespace concurrency::tp