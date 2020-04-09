//
// Created by dmitri on 09.04.2020.
//

#include <thread>
#include <numeric>
#include <vector>

#include "thread_guard.h"

#include "functions.h"

namespace advanced_thread {
    unsigned long num_threads(const unsigned long data_length) {
        const unsigned long max_threads = (data_length + MIN_PER_THREAD - 1) / MIN_PER_THREAD;
        const unsigned long hardware_thread = std::thread::hardware_concurrency();
        return std::min(
                hardware_thread == 0 ? 2 : hardware_thread,
                max_threads
        );
    }
}
