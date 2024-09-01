#pragma once 

#include <deque>

namespace concurrency::exe::queues {

template <typename T>
class LockFreeQueue 
{
public:

T Front()
{
    T elem = buffer_.front();
    buffer_.pop_front();

    return elem;
}

void Push(T elem)
{
    buffer_.push_back(std::move(elem));
}

size_t Size()
{
    return buffer_.size();
}

private:
    std::deque<T> buffer_;
};

} // namespace concurrency::exe::queues