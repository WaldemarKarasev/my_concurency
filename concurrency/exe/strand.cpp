#include <concurrency/exe/strand.hpp>


namespace concurrency::exe {

Strand::Strand(IExecutor& exe)
    : underlying_(&exe) 
{

}

// IExecutor
void Strand::Submit(ITask* task)
{
    // tasks_.Put(std::move(task));
    // if (tasks_.Size() == 1) // Means we just started Submiting new tasks or started submiting after SubmitSelf -> Run finished
    // {
    //     SubmitSelf();
    // }
}   

void Strand::Run() noexcept
{
    // size_t left = 0;

    // while

    // if (left < )
    // {
    //     SubmitSelf(); // New tasks are arrived!!!
    // }
}


void Strand::SubmitSelf()
{
    underlying_->Submit(this);
}

}