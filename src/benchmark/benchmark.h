#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <chrono>

class Benchmark {
public:
    static long long measureIndexing();
    static long long measureQuery();
};

#endif
