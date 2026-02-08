#ifndef QUERY_CACHE_H
#define QUERY_CACHE_H

#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class QueryCache {
private:
    unordered_map<string, vector<int>> cache;

public:
    bool hasQuery(const string& query);
    vector<int> getResult(const string& query);
    void storeResult(const string& query, const vector<int>& result);
};

#endif