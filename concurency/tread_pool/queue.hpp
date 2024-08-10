#pragma once 

#include <condition_variable>
#include <deque>
#include <optional>
#include <mutex>

namespace concurency::tp {

// Unbounded Mutli-Producer / Multi-Consumer (MPMC) Blocking Queue

template <typename T>
class UnboundedBlockingMPMCQueue 
{
public:

    // Thread role: producer
    bool Put(T value)
    {
        std::lock_guard lock(mutex);

        if (is_stopped.load())
        {
            return false;
        }

        buffer_.push_back(std::move(value));
        is_empty_.notify_one();
        
        return true;
    }

    // Thread role: consumer
    std::optional<T> Take()
    {
        std::unique_lock lock(mutex);
        
        is_empty_.wait(lock, [this](){
            return is_stopped.load() || !buffer_.empty();
        })
        
        if (buffer_.empty())
        {
            return std::nullopt;
        }

        std::optional<T> value(std::move(buffer_.front()));
        buffer_.pop_front();

        return value;        
    }

    void Close()
    {
        std::lock_guard lock(mutex_);
        is_stopped.store(true);
        is_empty_.notify_all();
    }

private:

    std::deque<T> buffer_;
    std::mutex mutex_;
    std::condition_variable is_empty_;
    std::atomic<bool> is_stopped{false};
};

} // namespace concurency::tp