#pragma once

#include <concurrency/utility.hpp>

namespace concurrency::intruisve {

template <typename T>
struct IntrusiveForwardListNode {
    
    using Node = IntrusiveForwardListNode;

    Node* next_ = nullptr;

    Node* Next() noexcept {
        return next_;
    }

    void SetNext(Node* node); 

    T* AsItem() noexcept {
        return static_cast<T*>(this);
    }

};


template <typename T>
class IntrusiveForwardList {

    using Node = IntrusiveForwardListNode<T>;

    using List = IntrusiveForwardList<T>;

public:

    IntrusiveForwardList() = default;

    // Non-copyable
    IntrusiveForwardList(const List&) = delete;
    IntrusiveForwardList& operator=(const List&) = delete;

    // Move-constructable
    IntrusiveForwardList(List&& that) {
        head_ = that.head_;
        tail_ = that.tail_;
        size_ = that.size_;
        that.Reset();
    }

    IntrusiveForwardList& operator=(List&& that) = delete;


    void PushBack(Node* node) noexcept {
        ++size_;
        node->next_ = nullptr;
        if (IsEmpty())
        {   
            head_ = tail_ = node;
        }
        else
        {
            tail_->next_ = node;
            tail_ = node;
        }
    }

    void PushFront(Node* node)
    {
        ++size_;
        if (IsEmpty())
        {
            head_ = tail_ = node;
        }
        else
        {        
            node->next_ = head_;
            head_ = node;
        }
    }

    T* PopFront() {
        if (IsEmpty())
        {
            return nullptr;
        }

        --size_;
        Node* front = head_;
        
        if (head_ == tail_)
        {
            head_ = tail_ = nullptr;
        }
        else
        {
            head_ = head_->next_;
        }

        front->next_ = nullptr;

        return front->AsItem();
    }

    bool IsEmpty() { return head_ == nullptr; }

private:
    void Reset()
    {
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }

private:
    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    size_t size_ = 0;
};

} // namespace concurrency::intrusive