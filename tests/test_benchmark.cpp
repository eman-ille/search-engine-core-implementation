#include <iostream>
#include "../src/benchmark/benchmark.h"

using namespace std;

int main() {
    long long indexingTime = Benchmark::measureIndexing();
    long long queryTime = Benchmark::measureQuery();

    cout << "Indexing Time: " << indexingTime << " microseconds" << endl;
    cout << "Query Time: " << queryTime << " microseconds" << endl;

    return 0;
}
