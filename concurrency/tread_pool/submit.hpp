#pragma once


namespace concurrency::tp {

template <typename Exe, typename Fun>
void Submit(Exe& pool, Fun task)
{
    pool.Submit(std::move(task));
}

} // namespace concurrency::tp