//
// Created by dmitri on 09.04.2020.
//

#ifndef CONCURRENCY_FUNCTIONS_H
#define CONCURRENCY_FUNCTIONS_H

#define MIN_PER_THREAD 25lu
#define DEFAULT_HARDWARE_THREADS 4u

namespace advanced_thread {

    unsigned long num_threads(unsigned long data_length);

    template<typename Iterator, typename T>
    struct accumulate_block {
        void operator()(Iterator first, Iterator last, T &result) { result = std::accumulate(first, last, result); }
    };

    template <typename Iterator, typename T, typename ThreadType = std::thread>
    T parallel_accumulate(Iterator first, Iterator last, T init) {
        const unsigned long length     = std::distance(first, last);
        const unsigned long n_threads  = num_threads(length);
        const unsigned long block_size = length / n_threads;

        std::vector<T> results(n_threads);
        std::vector<ThreadType> threads{};
        threads.reserve(n_threads);

        Iterator start = first;
        for (unsigned long i = 0; i < (n_threads - 1); i++) {
            Iterator end = first;
            std::advance(end, block_size);
            threads.emplace_back(
                accumulate_block<Iterator, T>(),
                start, end, std::ref(results[i])
            );
            start = end;
        }
        accumulate_block<Iterator, T>()(
            start, last, results[n_threads - 1u]
        );
        for (auto& t : threads)
            t.join();
        return std::accumulate(results.begin(), results.end(), init);
    }
}

#endif //CONCURRENCY_FUNCTIONS_H
