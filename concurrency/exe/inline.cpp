#include <concurrency/exe/inline.hpp>

namespace concurrency::exe {

class InlineExecutor : public IExecutor
{
public:
    // IExecutor
    virtual void Submit(TaskBase* task) override
    {
        task->Run();
    }
};

IExecutor& Inline()
{
    static InlineExecutor instance;
    return instance;
}

} // namespace concurrency::exe