#ifndef QUERY_PROCESSOR_H
#define QUERY_PROCESSOR_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class QueryProcessor {
public:
    QueryProcessor(unordered_map<string, vector<int>>& index);

    vector<int> processQuery(const string& query);
    double getLastQueryTime() const;

private:
    unordered_map<string, vector<int>>& invertedIndex;
    double lastQueryTime;

    vector<string> tokenize(const string& query);
    vector<int> intersect(const vector<int>& a, const vector<int>& b);
    vector<int> unite(const vector<int>& a, const vector<int>& b);
};

#endif
