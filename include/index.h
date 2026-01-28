#ifndef INDEX_H
#define INDEX_H

#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class Index {
private:
    unordered_map<string, vector<pair<int, int>>> invertedIndex;

public:
    void addDocument(int docId, const vector<string>& tokens);
    vector<pair<int, int>> search(const string& term) const;
    void printIndex() const;
};

#endif
