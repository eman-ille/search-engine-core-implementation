#include "../../include/query_cache.h"

bool QueryCache::hasQuery(const string& query) {
    return cache.find(query) != cache.end();
}

vector<int> QueryCache::getResult(const string& query) {
    return cache[query];
}

void QueryCache::storeResult(const string& query, const vector<int>& result) {
    cache[query] = result;
}