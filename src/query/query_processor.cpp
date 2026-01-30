#include "../../include/query_processor.h"
#include <sstream>
#include <algorithm>
#include <chrono>

using namespace std;

QueryProcessor::QueryProcessor(
    unordered_map<string, vector<int>>& index
) : invertedIndex(index), lastQueryTime(0) {}

vector<string>
QueryProcessor::tokenize(const string& query) {
    vector<string> parts;
    string word;
    stringstream ss(query);

    while (ss >> word)
        parts.push_back(word);

    return parts;
}

vector<int>
QueryProcessor::intersect(const vector<int>& a, const vector<int>& b) {
    vector<int> result;
    int i = 0, j = 0;

    while (i < a.size() && j < b.size()) {
        if (a[i] == b[j]) {
            result.push_back(a[i]);
            i++; j++;
        }
        else if (a[i] < b[j])
            i++;
        else
            j++;
    }
    return result;
}

vector<int>
QueryProcessor::unite(const vector<int>& a, const vector<int>& b) {
    vector<int> result = a;

    for (int i = 0; i < b.size(); i++) {
        if (find(result.begin(), result.end(), b[i]) == result.end())
            result.push_back(b[i]);
    }

    sort(result.begin(), result.end());
    return result;
}

vector<int>
QueryProcessor::processQuery(const string& query) {

    auto start = chrono::high_resolution_clock::now();

    vector<string> parts = tokenize(query);
    vector<int> result;

    if (parts.size() == 1) {
        result = invertedIndex[parts[0]];
    }
    else if (parts.size() == 3) {
        if (parts[1] == "AND")
            result = intersect(
                invertedIndex[parts[0]],
                invertedIndex[parts[2]]
            );
        else if (parts[1] == "OR")
            result = unite(
                invertedIndex[parts[0]],
                invertedIndex[parts[2]]
            );
    }

    auto end = chrono::high_resolution_clock::now();
    lastQueryTime =
        chrono::duration<double, milli>(end - start).count();

    return result;
}

double QueryProcessor::getLastQueryTime() const {
    return lastQueryTime;
}
