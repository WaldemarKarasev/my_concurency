#pragma once

#include "future.hpp"

#include <memory>
#include <variant>
#include <exception>

namespace concurrency::futures {

template <typename T>
class Promise {
public:
    Promise() {
        shared_state_ = std::make_shared<detail::SharedState<T>>();
    }

    // Non-copyable
    Promise(const Promise&) = delete;
    Promise& operator=(const Promise&) = delete;

    // Movable
    Promise(Promise&&) = default;
    Promise& operator=(Promise&&) = default;

    // One-shot
    Future<T> MakeFuture() {
        return Future(shared_state_);
    }

    // One-shot
    // Fulfill promise with value
    void SetValue(T value) {
        shared_state_->SetValue(std::move(value));
    }

    // One-shot
    // Fulfill promise with exception
    void SetException(std::exception_ptr e) {
        shared_state_->SetException(std::move(e));
    }

private:
    std::shared_ptr<detail::SharedState<T>> shared_state_;
};

}  // namespace concurrency::futures
