
#include <iostream>

#include <concurrency/atomic/atomic.cpp>
#include <atomic>
int main()
{
    int init_value = 64;
    std::cout << "init value of cell = " << init_value << std::endl;
    concurrency::atomic cell{init_value};
    
    std::cout << "cell.load() = " << cell.load() << std::endl;

    std::cout << "cell.store(5)" << std::endl;
    cell.store(5);

    std::cout << "cell.load() = " << cell.load() << std::endl;

}