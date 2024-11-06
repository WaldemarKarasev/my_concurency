#pragma once

#include <exception>
#include <variant>
#include <memory>
#include <cassert>

// for synchronization
#include <mutex>
#include <condition_variable>

namespace concurrency::futures {

    namespace detail {
        template <typename T>
        class SharedState   
        {
        public: 
            using type = std::variant<T, std::exception_ptr>;

        public:
            SharedState()
            {}

            void SetValue(T value)
            {
                std::lock_guard lock(ready_mutex_);
                state_ = std::move(value);
                is_ready_ = true;
                contract_.notify_one();
            }

            void SetException(std::exception_ptr e)
            {
                std::lock_guard lock(ready_mutex_);
                state_ = std::move(e);
                is_ready_ = true;
                contract_.notify_one();
            }

            T GetValue()
            {
                std::unique_lock lock(ready_mutex_);

                contract_.wait(lock, [this](){
                    return is_ready_;
                });

                T result;

                if (std::holds_alternative<T>(state_))
                {
                    result = std::get<T>(state_);
                }
                if (std::holds_alternative<std::exception_ptr>(state_))
                {
                    std::rethrow_exception(std::get<std::exception_ptr>(state_));
                }

                return result;
            }

        private:
            std::variant<T, std::exception_ptr> state_;
            std::condition_variable contract_;
            std::mutex ready_mutex_;
            bool is_ready_{false};
        };
    }


template <typename T>
class Future {
template <typename U>
friend class Promise;

public:
    // Non-copyable
    Future(const Future&) = delete;
    Future& operator=(const Future&) = delete;

    // Movable
    Future(Future&&) = default;
    Future& operator=(Future&&) = default;

    // One-shot
    // Wait for result (value or exception)
    T Get() {
        return shared_state_->GetValue();
    }

private:
    Future(std::shared_ptr<detail::SharedState<T>> shared_state) {
        shared_state_ = shared_state;
    }

private:
    std::shared_ptr<detail::SharedState<T>> shared_state_;
};

}  // namespace concurrency::futures
