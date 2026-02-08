#include "benchmark.h"

long long Benchmark::measureIndexing() {
    auto start = std::chrono::high_resolution_clock::now();

    // fake indexing work
    for (int i = 0; i < 1000000; i++) {
        int x = i * i;
    }

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

long long Benchmark::measureQuery() {
    auto start = std::chrono::high_resolution_clock::now();

    // fake query work
    for (int i = 0; i < 200000; i++) {
        int y = i + 10;
    }

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}
