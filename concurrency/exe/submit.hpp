#pragma once

#include <concurrency/task/task.hpp>

namespace concurrency::exe {

template <typename Exe, typename Fun>
void Submit(Exe& pool, Fun task)
{ 
    pool.Submit(MakeRoutine(std::move(task)));
}

} // namespace concurrency::tp