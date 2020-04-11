//
// Created by Dmitri on 11.04.2020.
//

#ifndef CONCURRENCY_CONTAINER_H
#define CONCURRENCY_CONTAINER_H

#include <mutex>
#include <stack>

namespace advanced_thread {
    struct threadsafety_empty : std::runtime_error {
        threadsafety_empty();
        const char* what() const noexcept;
    };


    template<typename T>
    class threadsafety_stack {
    private:
        mutable std::mutex locker;
        std::stack<T> data;

        inline void is_empty() const {
            if (data.empty()) throw threadsafety_empty();
        }
    public:
        threadsafety_stack() = default;

        threadsafety_stack(const threadsafety_stack &other) :
                locker(),
                data([&](const threadsafety_stack &other_) {
                    std::lock_guard guard(other_.locker);
                    data = other_.data;
                }(other)) {}

        void push(T value) {
            std::lock_guard guard(locker);
            data.push(std::move(value));
        }

        std::shared_ptr<T> pop() {
            std::lock_guard guard(locker);
            is_empty();
            const std::shared_ptr<T> result(std::make_shared<T>(std::move(data.top())));
            data.pop();
            return result;
        }

        void pop(T& value) {
            std::lock_guard guard(locker);
            is_empty();
            value = data.top();
            data.pop();
        }

        void empty() const {
            std::lock_guard guard(locker);
            return data.empty();
        }
    };
}
#endif //CONCURRENCY_CONTAINER_H
