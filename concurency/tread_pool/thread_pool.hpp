#pragma once 

#include <vector>

#include "task.hpp"
#include "queue.hpp"
#include "wait_group.hpp"

namespace concurency::tp {

class ThreadPool 
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
    void WorkerRoutine(std::optional<Task> task);

private:
    size_t workers_count_{0};
    std::vector<std::thread> workers_;
    UnboundedBlockingMPMCQueue<Task> tasks_;
    WaitGroup wg_;
};

} // namespace concurency::tp
