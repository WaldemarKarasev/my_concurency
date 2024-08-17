#include <bits/stdc++.h>

#include <cassert>
#include <cstdlib>

#include <bits/stdc++.h>

// prevent compile reordering
inline void CompileBarrier()
{
    asm volatile ("" ::: "memory");
}

void StoreBuffer(size_t iter)
{

    // Shared
    int x = 0;
    int y = 0;

    // Local
    int r1 = 0; // t1
    int r2 = 0; // t2

    std::thread t1([&](){
        x = 1;
        CompileBarrier();
        r1 = y;
    });

    std::thread t2([&](){
        y = 2;
        CompileBarrier();
        r2 = x;
    });

    t1.join();
    t2.join();

    if (r1 == 0 && r2 == 0)
    {
        std::cout << "Iteration #" << iter << ": Broken CPU!" << std::endl;
        std::abort();
    }
}

int main()
{

    for (size_t i = 0; ; ++i)
    {
        StoreBuffer(i);
        if (i % 10000 == 0)
        {
            std::cout << "Iterates made: " << i + 1 << std::endl;
        }
    }

    return 0;
}