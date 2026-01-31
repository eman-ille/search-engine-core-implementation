#include <iostream>
#include "../src/ranking/tfidf.h"

using namespace std;

int main() {
    TFIDF ranker;

    // Documents returned from query
    vector<int> docIDs = {1, 2, 3};

    // Query words
    vector<string> queryTerms = {"search", "engine"};

    // Term Frequency: word -> (docID -> count)
    unordered_map<string, unordered_map<int, int>> termFreq;
    termFreq["search"][1] = 3;
    termFreq["search"][2] = 1;
    termFreq["engine"][1] = 2;
    termFreq["engine"][3] = 4;

    // Document Frequency
    unordered_map<string, int> docFreq;
    docFreq["search"] = 2;
    docFreq["engine"] = 2;

    int totalDocs = 5;

    auto scores = ranker.rankDocuments(
        docIDs, queryTerms, termFreq, docFreq, totalDocs
    );

    for (auto& s : scores) {
        cout << "Doc " << s.first << " Score: " << s.second << endl;
    }

    return 0;
}
