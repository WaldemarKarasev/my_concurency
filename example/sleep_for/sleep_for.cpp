#include <boost/asio/io_context.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/defer.hpp>

#include <concurrency/fiber/fiber.hpp>
#include <concurrency/fiber/go.hpp>

#include <concurrency/fiber/coroutine.hpp>

#include <iostream>
#include <thread>

using namespace boost;
int main() {
  
    // Планировщик для файберов
    asio::io_context io;
    // concurrency::fiber::Go(scheduler, [] {
    // for (size_t i = 0; i < 10; ++i) {
    //     std::cout << "Step {}" << i << std::endl;
    //     // Файбер останавливается на 1 секунду, но
    //     // не блокирует при этом цикл планировщика 
    // //   fibers::SleepFor(1s);
    // }

    // });

    concurrency::fiber::Coroutine coro([](){
        std::cout << "hello" << std::endl;
        concurrency::fiber::Coroutine::Suspend();
        std::cout << "hello" << std::endl;
        concurrency::fiber::Coroutine::Suspend();
        std::cout << "hello" << std::endl;
    });

    asio::post(io, [&coro](){
        while(!coro.IsCompleted())
        {
            coro.Resume();
        }
    });

    
    asio::post(io, [&io](){
        std::cout << "before defer" << std::endl;

        asio::defer([](){ 
            std::cout << "defer" << std::endl;
            return;
        });

    });

    asio::post(io, [&coro](){
        std::cout << "AAAA" << std::endl;
    });
    // Запускаем планировщик
    // Вызов `run` завершится через 10 секунд

    std::cout << "wait" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    std::cout << "after wait" << std::endl;
    io.run();

}