#pragma once

#include <concurrency/task/task.hpp>

namespace concurrency::exe {

template <typename Exe, typename Fun>
void Submit(Exe& exe, Fun task)
{ 
    exe.Submit(Routine::MakeRoutine(std::move(task)));
}

} // namespace concurrency::tp