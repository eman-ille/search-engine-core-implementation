#ifndef TFIDF_H
#define TFIDF_H

#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class TFIDF {
public:
    unordered_map<int, double> rankDocuments(
        const vector<int>& docIDs,
        const vector<string>& queryTerms,
        unordered_map<string, unordered_map<int, int>>& termFreq,
        unordered_map<string, int>& docFreq,
        int totalDocs
    );
};

#endif
