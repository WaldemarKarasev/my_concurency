#pragma once 

#include <concurrency/exe/executor.hpp>

#include <concurrency/exe/queues/lock_free_queue.hpp>

namespace concurrency::exe {

class Strand : public IExecutor, // for receiving ITasks from IExecutor interface via Submit function
               public ITask      // for submitinf self into underlying IExucutor and run accumulated tasks_ from ITask Interface via Run function
{
public:
    explicit Strand(IExecutor& exe);

    // Non-copyable
    Strand(const Strand&) = delete;
    Strand& operator=(const Strand&) = delete;

    // Non-movable
    Strand(Strand&&) = delete;
    Strand& operator=(Strand&&) = delete;

    // IExecutor
    virtual void Submit(ITask* task) override;

    // ITask
    virtual void Run() noexcept override;

private:
    void SubmitSelf();

private:
    // queues::LockFreeQueue<ITask*> tasks_;
    IExecutor* underlying_{nullptr};
};

} // namespace concurrency::exe