//
// Created by dmitri on 09.04.2020.
//

#ifndef CONCURRENCY_THREAD_GUARD_H
#define CONCURRENCY_THREAD_GUARD_H

#include <thread>

namespace advanced_thread {

    class scoped_thread {
    private:
        std::thread t;
    public:
        explicit scoped_thread(std::thread t_);
        ~scoped_thread();
    };

    class joining_thread {
    private:
        std::thread t;

        inline void if_joinable();
    public:
        template<class Callable, typename ... Args>
        explicit joining_thread(Callable &&, Args&& ... args);

        explicit joining_thread(std::thread) noexcept;

        joining_thread(joining_thread &&) noexcept;

        joining_thread& operator=(joining_thread &&) noexcept;

        joining_thread& operator=(std::thread) noexcept;

        ~joining_thread() noexcept;

        void swap(joining_thread&) noexcept;

        std::thread::id get_id() const noexcept;

        bool joinable() const noexcept;

        void join();

        void detach();

        std::thread& as_thread() noexcept;
        const std::thread& as_thread() const noexcept;
    };
}
#endif //CONCURRENCY_THREAD_GUARD_H
