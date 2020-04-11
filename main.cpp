#include <iostream>
#include <thread>
#include <vector>
#include <numeric>

#include "source/thread_guard.h"
#include "source/functions.h"
#include "source/container.h"

#include "source/profile.h"

int main() {
    std::vector<unsigned long> numbers(1'000'000'000);
    std::iota(numbers.begin(), numbers.end(), 1);

    unsigned long parallel_result, result;
    {
        LOG_DURATION("Parallel time")
        parallel_result = advanced_thread::parallel_accumulate(numbers.begin(), numbers.end(), 0);
    }
    {
        LOG_DURATION("Not parallel time")
        result = std::accumulate(numbers.begin(), numbers.end(), 0);
    }

    std::cout << "Parallel result: " << parallel_result << std::endl;
    std::cout << "Not parallel result: " << result << std::endl;
    std::cout << "Thread num: " << advanced_thread::num_threads(numbers.size()) << std::endl;
    std::cout << "Per thread: " << numbers.size() / advanced_thread::num_threads(numbers.size()) << std::endl;

    advanced_thread::threadsafety_stack<int> s{};
    for (int i = 0; i < 10; i++)
        s.push(i);

    while (!s.empty())
        std::cout << "Stack: " << *s.pop() << std::endl;
    return 0;
}
