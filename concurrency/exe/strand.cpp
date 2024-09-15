#include <concurrency/exe/strand.hpp>

namespace concurrency::exe {

Strand::Strand(IExecutor& exe)
    : underlying_(&exe) 
{

}

// IExecutor
void Strand::Submit(TaskBase* task)
{
    tasks_.Push(task);

    if (counter_.fetch_add(1) == 0)
    {
        SubmitSelf();
    }
}   

void Strand::Run() noexcept
{
    const size_t done = RunTasks(tasks_.TakeAll());
    const size_t left = counter_.fetch_sub(done);
    if (left > done)
    {
        SubmitSelf();
    }
}

void Strand::SubmitSelf()
{
    // std::cout << "SubmitSelf" << std::endl;
    underlying_->Submit(this);
}

size_t Strand::RunTasks(TaskBatch batch)
{
    size_t count = 0;
    while (!batch.IsEmpty()) {
        TaskBase* task = batch.PopFront();
        task->Run();
        ++count;
    }

    // std::cout << "count=" << count << std::endl;
    return count;
}


}