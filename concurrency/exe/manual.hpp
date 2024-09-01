#pragma once 

#include <concurrency/exe/executor.hpp>

#include <concurrency/exe/queues/UnboundedBlockingMPMCQueue.hpp> // ??? Probably not
#include <deque>

namespace concurrency::exe {

class ManualExecutor : public IExecutor
{
public:
    ManualExecutor() = default;

    // Non-copyable
    ManualExecutor(const ManualExecutor&) = delete;
    ManualExecutor& operator=(const ManualExecutor&) = delete;

    // Non-movable
    ManualExecutor(ManualExecutor&&) = delete;
    ManualExecutor& operator=(ManualExecutor&&) = delete;

    // IExecutor
    virtual void Submit(ITask* task) override;

    // Run tasks

    // Run at most `limit` tasks from queue
    // Returns number of completed tasks
    size_t RunAtMost(size_t limit);

    // Run next task if queue is not empty
    bool RunNext() {
        return RunAtMost(1) == 1;
    }

    // Run tasks until queue is empty
    // Returns number of completed tasks
    // Post-condition: IsEmpty() == true
    size_t Drain();

    size_t TaskCount() const {
        return tasks_.size();
    }

    bool IsEmpty() const {
        return tasks_.empty();
    }

    bool NonEmpty() const {
        return !IsEmpty();
    }

private:
    // concurrency::exe::pool::queues::UnboundedBlockingMPMCQueue tasks_;
    std::deque<ITask*> tasks_;
};



} // namespace concurrency::exe