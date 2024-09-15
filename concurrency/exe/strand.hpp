#pragma once 

#include <atomic>
#include <mutex>

#include <concurrency/exe/executor.hpp>
#include <concurrency/exe/queues/TreiberLockFreeStack.hpp>

namespace concurrency::exe {

class Strand : public IExecutor, // for receiving ITasks from IExecutor interface via Submit function
               public TaskBase   // for submitinf self into underlying IExucutor and run accumulated tasks_ from ITask Interface via Run function
{
public:
    using TaskBatch = intruisve::IntrusiveForwardList<TaskBase>;

public:
    explicit Strand(IExecutor& exe);

    // Non-copyable
    Strand(const Strand&) = delete;
    Strand& operator=(const Strand&) = delete;

    // Non-movable
    Strand(Strand&&) = delete;
    Strand& operator=(Strand&&) = delete;

    // IExecutor
    virtual void Submit(TaskBase* task) override;

    // ITask
    virtual void Run() noexcept override;

private:
    void SubmitSelf();
    size_t RunTasks(TaskBatch tasks);

private:
public:
    IExecutor* underlying_{nullptr};
    std::atomic<size_t> counter_{0};
    queues::TaskAccumulator<TaskBase> tasks_;
    std::mutex mutex_;
};

} // namespace concurrency::exe