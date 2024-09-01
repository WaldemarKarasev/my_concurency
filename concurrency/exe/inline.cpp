#include <concurrency/exe/inline.hpp>

namespace concurrency::exe {

class InlineExecutor : public IExecutor
{
public:
    // IExecutor
    virtual void Submit(ITask* task) override
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