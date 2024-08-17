#include <bits/stdc++.h>

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

class AtomicCounter
{
public:
    void increment()
    {
        value_.fetch_add(1);
    }

    size_t Get() const
    {
        return value_.load();
    }

private:
    std::atomic<size_t> value_{0};
};


class SharedCounter
{
    static const size_t kShards = 10;

private:
    class Shard
    {
    public:
        void Increment()
        {
            value_.fetch_add(1);
        }

        size_t Get()
        {
            return value_.load();
        }

    private:
        // char padding_[64]; // preventing False-Sharing
        alignas(64) std::atomic<size_t> value_{0}; // second 
        // alignas(std::hardware_destructive_interference_size) std::atomic<size_t> value_{0}; // third 
        // std::atomic<size_t> value_{0}; // False-Sharing
    };

public:
    void Increment()
    {
        size_t shard_index = GetThisThreadShard();
        shards_[shard_index].Increment();
    }

    size_t Get()
    {
        size_t value = 0;
        for (size_t i = 0; i < kShards; ++i)
        {
            value += shards_[i].Get();
        }

        return value;
    }

private:
    static size_t GetThisThreadShard()
    {
        static std::hash<std::thread::id> hasher;

        auto t_id = std::this_thread::get_id();
        return hasher(t_id) % kShards;
    }

private:
    std::array<Shard, kShards> shards_;

};

void Stress()
{
    SharedCounter counter;
    // AtomicCounter counter;

    StopWatch stop_watch;

    std::vector<std::thread> threads;
    for (size_t i = 0; i < 10; ++i)
    {
        threads.emplace_back([&counter]()
        {
            for (size_t j = 0; j < 1'000'000; ++j)
            {
                counter.Increment();
            }
        });
    }

    for (auto& t : threads)
    {
        t.join();
    }

    auto elapsed_ms = stop_watch.ElapsedMills();

    std::cout << counter.Get() << std::endl;

    std::cout << "Elapsed: " << elapsed_ms << "ms" << std::endl;     
}

int main()
{
    while (true)
    {
        Stress();
    }
    
}