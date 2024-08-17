#include <atomic>


std::atomic<int> cell{5};

// load
void load_relaxed()
{
    cell.load(std::memory_order_relaxed);
}

void load_release()
{
    cell.load(std::memory_order_release);
}

void load_setsqt()
{
    cell.load(std::memory_order_seq_cst);
}

// store
void store_relaxed()
{
    cell.store(10, std::memory_order_relaxed);
}

void store_release()
{
    cell.store(10, std::memory_order_release);
}

void store_setsqt()
{
    cell.store(10, std::memory_order_seq_cst);
}

// Exchange
void exchange_relaxed()
{
    cell.exchange(10, std::memory_order_relaxed);
}

void exchange_release()
{
    cell.exchange(10, std::memory_order_release);
}

void exchange_setsqt()
{
    cell.exchange(10, std::memory_order_seq_cst);
}

int main()
{

}