
#include <iostream>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

#include <concurrency/tread_pool/thread_pool.hpp>


int main()
{
    concurrency::tp::ThreadPool pool(2);

    pool.Submit([](){
        std::this_thread::sleep_for(3s);
        std::cout << "1st" << std::endl;
    });


    pool.Submit([](){
        std::cout << "2nd" << std::endl;
    });


    pool.Submit([](){
        std::cout << "3rd" << std::endl;
    });

    pool.WaitIdle();

    pool.Stop();
}