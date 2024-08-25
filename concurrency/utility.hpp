#pragma once

#include <chrono>
#include <iostream>

namespace concurrency {

class StopWatch
{
public:

    StopWatch()
    {
        start_time_ = std::chrono::steady_clock::now();

    }

    int64_t ElapsedMills()
    {
        decltype(start_time_) elapsed = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed - start_time_).count();
    }

private:
    std::chrono::steady_clock::time_point start_time_;    

};

}