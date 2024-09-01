#pragma once

#include <concurrency/exe/executor.hpp>
#include <concurrency/task/task.hpp>
#include <concurrency/fiber/coroutine.hpp>

namespace concurrency::fiber {


class Fiber : public concurrency::ITask {
public:

    Fiber(exe::IExecutor* executor, Task task);

    void Schedule();

    void Resume();
    void Suspend();

    exe::IExecutor& GetExecutor() const { return *executor_; }

    // ITask
    virtual void Run() noexcept override;

    static Fiber* Self();

private:
    Coroutine coro_;
    exe::IExecutor* executor_{nullptr};
    bool is_running_{false};
};

} // namespace concurrency::fiber   