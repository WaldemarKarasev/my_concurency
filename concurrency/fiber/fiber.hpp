#pragma once

#include <concurrency/tread_pool/thread_pool.hpp>
#include <concurrency/task/task.hpp>
#include <concurrency/fiber/coroutine.hpp>

namespace concurrency::fiber {

using Scheduler = concurrency::tp::ThreadPool;


class Fiber : public concurrency::ITask {
public:

    Fiber(Scheduler* executor, Task task);

    void Schedule();

    // ITask
    virtual void Run() noexcept override;

    static Fiber* Self();

private:
    Coroutine coro_;
    Scheduler* scheduler_{nullptr};
    bool is_running_{false};
};

} // namespace concurrency::fiber   