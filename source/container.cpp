//
// Created by Dmitri on 11.04.2020.
//


#include <memory>
#include <exception>

#include "container.h"

namespace advanced_thread {
    threadsafety_empty::threadsafety_empty(): runtime_error("threadsafety stack is empty") {}

    const char * threadsafety_empty::what() const noexcept {
        return "threadsafety stack is empty";
    }
}
