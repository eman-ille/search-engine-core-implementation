#include "index.h"
#include <iostream>

using namespace std;

void Index::addDocument(int docId, const vector<string>& tokens) {
    unordered_map<string, int> termFreq;

    for (const auto& token : tokens) {
        termFreq[token]++;
    }

    for (const auto& entry : termFreq) {
        invertedIndex[entry.first].push_back(
            {docId, entry.second}
        );
    }
}

vector<pair<int, int>> Index::search(const string& term) const {
    auto it = invertedIndex.find(term);
    if (it != invertedIndex.end()) {
        return it->second;
    }
    return {};
}

void Index::printIndex() const {
    for (const auto& entry : invertedIndex) {
        cout << entry.first << " : ";
        for (const auto& doc : entry.second) {
            cout << "(Doc " << doc.first
                 << ", Freq " << doc.second << ") ";
        }
        cout << endl;
    }
}
