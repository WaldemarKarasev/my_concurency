#pragma once

#include <concurrency/tread_pool/scheduler.hpp>
#include <concurrency/task/task.hpp>
#include <concurrency/fiber/coroutine.hpp>

namespace concurrency::fiber {

using Scheduler = concurrency::tp::Scheduler;

class Fiber : public concurrency::ITask {
public:

    Fiber(Scheduler* executor, Task task);

    void Schedule();

    void Resume();
    void Suspend();

    // ITask
    virtual void Run() noexcept override;

    static Fiber* Self();

private:
    Coroutine coro_;
    Scheduler* scheduler_{nullptr};
    bool is_running_{false};
};

} // namespace concurrency::fiber   