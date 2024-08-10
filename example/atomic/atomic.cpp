
#include <iostream>

#include <concurency/atomic/atomic.cpp>

int main()
{
    int init_value = 64;
    std::cout << "init value of cell = " << init_value << std::endl;
    concurency::atomic cell{init_value};
    
    std::cout << "cell.load() = " << cell.load() << std::endl;

    std::cout << "cell.store(5) = " << std::endl;
    cell.store(5);

    std::cout << "cell.load() = " << cell.load() << std::endl;

}