#include <concurrency/exe/manual.hpp>

namespace concurrency::exe {

// IExecutor
void ManualExecutor::Submit(TaskBase* task)
{
    tasks_.push_back(task);
}


//----------------- Run tasks -----------------//

// Run at most `limit` tasks from queue
// Returns number of completed tasks
size_t ManualExecutor::RunAtMost(size_t limit)
{
    size_t executed = 0;

    if (IsEmpty()) { return 0; } // task queue is empty

    if (limit > TaskCount())
    {
        limit = TaskCount();
    }
    for (size_t start = 0; start < limit; ++start)
    {
        auto* task = tasks_.front();
        tasks_.pop_front();
        
        if (task == nullptr)
        {
            continue;
        }

        try {
            task->Run();
        } catch(...)
        {

        }
        ++executed;
    }

    return executed;
}

// Run tasks until queue is empty
// Returns number of completed tasks
// Post-condition: IsEmpty() == true
size_t ManualExecutor::Drain()
{
    size_t executed = 0;

    while(!tasks_.empty())
    {
        auto* task = tasks_.front();
        tasks_.pop_front();
        
        if (task == nullptr)
        {
            std::cout << "nullptr" << std::endl;
            continue;
        }

        try {
            task->Run();
        } catch(...)
        {

        }
        ++executed;
    }

    return executed;
}

} // namespace concurrency::exe