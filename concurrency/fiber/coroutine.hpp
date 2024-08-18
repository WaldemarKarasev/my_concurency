#pragma once

// STL
#include <functional>


namespace concurrency::fiber {

class Coroutine {

public:
    using Routine = std::function<void()>;

    explicit Coroutine(Routine routine);

    void Resume();

    // Suspend running coroutine
    static void Suspend();

    bool IsCompleted() const;

private:
    // routine
    // stack
    // context

};

}