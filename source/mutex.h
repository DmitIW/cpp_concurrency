//
// Created by dmitri on 20.04.2020.
//

#ifndef CONCURRENCY_MUTEX_H
#define CONCURRENCY_MUTEX_H

namespace advanced_thread {

    class hierarchical_mutex {
    private:
            std::mutex inner_mutex;

            const std::size_t h_value;
            std::size_t prev_h_value;

            static inline thread_local std::size_t this_thread_h_value{UINT64_MAX};

            void check_for_hierarchy_violation() const;
            void update_hierarchy_value();
    public:
            explicit hierarchical_mutex(std::size_t);

            void lock();
            void unlock();
            bool try_lock();
    };
}

#endif //CONCURRENCY_MUTEX_H
