#pragma once 

#include <atomic>
#include <optional>

namespace concurrency::exe::queues {

template <typename T>
class MichielSchottQueue
{
public:
    using size_type = std::size_t;

public:
    struct Node
    {
        std::atomic<Node*> next_;
        T data_;
    };

public:

    MichielSchottQueue()
    {
        Node* dummy = new Node();
        dummy->next_ = nullptr;
        head_ = tail_ = dummy;
    }

    void Enqueue(T data)
    {
        Node* node = new Node{nullptr, std::move(data)};

        Node* tail;
        Node* next;
        while(true)
        {
            tail = tail_.load();
            next = tail->next_.load();

            if (tail == tail_.load())
            {
                if (next == nullptr)
                {
                    if (tail_.compare_exchange_strong(next, node))
                    {
                        break;
                    }
                }
                else
                {
                    tail_.compare_exchange_strong(tail, next);
                }
            }
        }

        tail_.compare_exchange_strong(tail, node);
    }

    std::optional<T> Dequeue()
    {
        std::optional<T> value;
        Node* head;
        Node* tail;
        Node* next;
        while(true)
        {
            head = head_.load();
            tail = tail_.load();
            next = head->next_.load();
            
            if (head == head_.load())
            {
                if (head == tail)
                {
                    if (next == nullptr)
                    {
                        return std::nullopt; 
                    }
                    else
                    {
                        tail_.compare_exchange_strong(tail, next);
                    }
                }
                else
                {
                    value = next->data_;
                    head_.compare_exchange_strong(head, next);
                    break;
                }
            }
        }
        delete head;

        return value;
    }

private:
    std::atomic<Node*> head_;
    std::atomic<Node*> tail_;
    size_type size_;
};


} // namespace concurrency::exe::queues