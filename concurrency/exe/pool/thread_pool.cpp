#include "thread_pool.hpp"

#include <iostream>

namespace concurrency::exe::pool {

static thread_local ThreadPool* pool = nullptr;

ThreadPool::ThreadPool(size_t threads)
    : workers_count_(threads)
{
}

ThreadPool::~ThreadPool()
{
    assert(workers_.empty());
}

// Launches worker threads
void ThreadPool::Start()
{
    StartWorkerThreads();
}

// Schedules task for execution in one of the worker threads
void ThreadPool::Submit(TaskBase* task)
{
    wg_.Add(1);
    tasks_.Put(task);
}

void ThreadPool::Submit(Task task)
{
    wg_.Add(1);
    tasks_.Put(Routine::MakeRoutine(std::move(task)));
}

// Locates current thread pool from worker thread
ThreadPool* ThreadPool::Current()
{
    return pool;
}

// Waits until outstanding work count reaches zero
void ThreadPool::WaitIdle()
{
    wg_.Wait();
}

// Stops the worker threads as soon as possible
void  ThreadPool::Stop()
{
    tasks_.Close();
    JoinWorkers();
}


// Private ThreadPool methods
void ThreadPool::JoinWorkers()
{
    for (size_t i = 0; i < workers_.size(); ++i)
    {
        workers_[i].join();
    }
    workers_.clear();
}

void ThreadPool::StartWorkerThreads()
{
    for (size_t i = 0; i < workers_count_; ++i)
    {
        workers_.push_back(std::thread([this](){
            pool = this;
            auto task = tasks_.Take();
            while(task)
            {
                WorkerRoutine(task);
                wg_.Done();
                task = tasks_.Take();
            }
        }));
    }
}
#include <iostream>
void ThreadPool::WorkerRoutine(std::optional<TaskBase*> task)
{
    try {
        (*task)->Run();
    } catch (std::exception& e) {
        std::cout << "Exception occured: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown exception" << std::endl;
    }

}


} // namespace concurrency::exe::pool
