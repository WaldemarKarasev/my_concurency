#pragma once 

#include <vector>
#include <thread>

#include <concurrency/task/task.hpp>
#include <concurrency/exe/queues/UnboundedBlockingMPMCQueue.hpp>
#include <concurrency/sync/wait_group.hpp>
#include <concurrency/exe/executor.hpp>

namespace concurrency::exe::pool {

class ThreadPool : public exe::IExecutor
{
public:
    explicit ThreadPool(size_t threads);
    ~ThreadPool();

    // Non-copyable
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    // Non-movable
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;

    // Launches worker threads
    void Start();

    // Schedules task for execution in one of the worker threads
    virtual void Submit(ITask* task) override;

    // This function is not part of IExecutor interface. But it can be used for scheduling simple lambdas in current ThreadPool
    void Submit(Task task);


    // Locates current thread pool from worker thread
    static ThreadPool* Current();

    // Waits until outstanding work count reaches zero
    void WaitIdle();

    // Stops the worker threads as soon as possible
    void Stop();

private:
    void JoinWorkers();
    void StartWorkerThreads();
    void WorkerRoutine(std::optional<ITask*> task);

private:
    size_t workers_count_{0};
    std::vector<std::thread> workers_;
    queues::UnboundedBlockingMPMCQueue<ITask*> tasks_;
    // WaitGroup wg_;
    WaitGroup_Futex wg_;
};

} // namespace concurrency::exe::pool