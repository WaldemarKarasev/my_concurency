// STL
#include <iostream>
#include <chrono>
#include <thread>

// Testing
#include <gtest/gtest.h>

// Concurrency
#include <concurrency/fiber/coroutine.hpp>


TEST(Coroutine, JustWorks) {
    concurrency::fiber::Coroutine coro([](){
        std::cout << "Hello coro!" << std::endl;

        concurrency::fiber::Coroutine::Suspend();

        std::cout << "Hello after Suspend and resuming coroutine" << std::endl;

    });

    coro.Resume();

    coro.Resume();

    std::cout << "Coroutine just works" << std::endl;
}
int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


