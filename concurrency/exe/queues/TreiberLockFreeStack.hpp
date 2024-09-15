#pragma once

#include <atomic>

#include <concurrency/intrusive/forward_list.hpp>
#include <concurrency/utility.hpp>

namespace concurrency::exe::queues {

// Multi-producer/single-consumer (MPSC) unbounded lock-free queue

template <typename T> // Node == Intrusive Node
class TreiberLockFreeStack 
{
    using Node = intruisve::IntrusiveForwardListNode<T>;
public:
    void Push(Node* item) {     
        #if 1
        Node* old_top = top_.load();
        
        item->next_ = old_top;

        do {
            old_top = top_.load();
            item->next_ = old_top;
        } while(!top_.compare_exchange_weak(old_top, item));
        #else
        Node* node = item;
        while (!top_.compare_exchange_weak(node->next_, node)) {
        }
        #endif

    }

    Node* Pop() {
        Node* old_top;
        Node* new_top;

        do {
            old_top = top_.load();
            if (old_top == nullptr)
            {
                return nullptr;
            }

            new_top = old_top->next_;
        } while (!top_.compare_exchange_weak(old_top, new_top));

        return old_top; 
    }

    template <typename F>
    void ConsumeAll(F consumer) {
        auto top = top_.exchange(nullptr); // acquire
        Node* curr = top;
        while (curr != nullptr) {
            Node* next =  curr->next_;
            consumer(curr->AsItem());
            curr = next;
        }
    }

    bool IsEmpty() const {
        return top_.load() == nullptr;
    }


private:
    std::atomic<Node*> top_{nullptr};
};


template <typename T>
class TaskAccumulator 
{
public:
    using List = intruisve::IntrusiveForwardList<T>;
    // static_assert(std::is_same_v<T, intruisve::IntrusiveForwardListNode<TaskBase>>);

public:
    void Push(T* task)
    {
        stack_.Push(task);
    }

    List TakeAll()
    {
        List batch;
        stack_.ConsumeAll([&batch](T* value){
            batch.PushFront(value);
        });

        return batch;
    }


private:
    TreiberLockFreeStack<T> stack_;
};


} // namespace concurrency::exe::queues