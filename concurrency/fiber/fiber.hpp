#pragma once

#include <concurrency/tread_pool/thread_pool.hpp>
#include <concurrency/fiber/coroutine.hpp>


namespace concurrency::fiber {

using Scheduler = concurrency::tp::ThreadPool;

class Fiber {
public:
    void Schedule();

    // Task
    void Run();

    static Fiber* Self();

private:
    Coroutine coro_;
    Scheduler* current{nullptr};

};

} // namespace concurrency::fiber