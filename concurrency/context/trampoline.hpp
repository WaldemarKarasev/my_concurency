#pragma once 

namespace concurrency {

struct ITrampoline {
    virtual ~ITrampoline() = default;

    // Never returns
    virtual void Run() noexcept = 0;
};

}