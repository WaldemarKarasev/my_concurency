#pragma once 

#include <concurrency/exe/executor.hpp>


namespace concurrency::exe {

class Strand : public IExecutor
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
    void Submit(ITask* task) override;

private:


};

} // namespace concurrency::exe