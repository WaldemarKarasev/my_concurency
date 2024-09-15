#pragma once

#include <functional>

#include <concurrency/utility.hpp>
#include <concurrency/intrusive/forward_list.hpp>


namespace concurrency {

using Task = std::function<void()>;

struct ITask
{
    virtual ~ITask() = default;

    virtual void Run() noexcept = 0;
};

struct TaskBase : public ITask, 
                  public intruisve::IntrusiveForwardListNode<TaskBase>
{
    // No extra internals
};


class Routine : public TaskBase //ITask
{
public:
    Routine(Task task)
        : fun(std::move(task)) {}

    virtual void Run() noexcept override 
    {
        try {
            fun();
        } catch (std::exception& e) {
            std::cout << "Routine caught exception. what(): " << e.what() << std::endl;            
        } catch (...) {
            std::cout << "Routine caght exception ..." << std::endl;
        }

        delete this;
    }

    static Routine* MakeRoutine(Task task)
    {
        return new Routine(std::move(task));
    }

private:
    Task fun;
};

}