//
// Created by dmitri on 20.04.2020.
//

#include <mutex>
#include <cstdint>

#include "mutex.h"

namespace advanced_thread {

    void hierarchical_mutex::check_for_hierarchy_violation() const {
        if (this_thread_h_value <= h_value)
            throw std::logic_error("mutex hierarchy violated");
    }

    void hierarchical_mutex::update_hierarchy_value() {
        prev_h_value = this_thread_h_value;
        this_thread_h_value = h_value;
    }

    hierarchical_mutex::hierarchical_mutex(const std::size_t value):
        inner_mutex(),
        h_value(value),
        prev_h_value(0)
    {}

    void hierarchical_mutex::lock() {
        check_for_hierarchy_violation();
        inner_mutex.lock();
        update_hierarchy_value();
    }

    bool hierarchical_mutex::try_lock() {
        check_for_hierarchy_violation();
        if (!inner_mutex.try_lock())
            return false;
        update_hierarchy_value();
        return true;
    }

    void hierarchical_mutex::unlock() {
        if (this_thread_h_value != h_value)
            throw std::logic_error("mutex hierarchy violated");
        this_thread_h_value = prev_h_value;
        inner_mutex.unlock();
    }
}