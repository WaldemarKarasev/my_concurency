#pragma once

#include <concurrency/task/task.hpp>

namespace concurrency::exe {

class IExecutor 
{
public:
    // Submit ITasks into underlying scheduler implementation
    virtual void Submit(ITask* task) = 0;

};

} // namespace concurrency::exe