#include "tfidf.h"
#include <cmath>

using namespace std;

unordered_map<int, double> TFIDF::rankDocuments(
    const vector<int>& docIDs,
    const vector<string>& queryTerms,
    unordered_map<string, unordered_map<int, int>>& termFreq,
    unordered_map<string, int>& docFreq,
    int totalDocs
) {
    unordered_map<int, double> scores;

    for (int docID : docIDs) {
        double score = 0.0;

        for (const string& term : queryTerms) {
            if (termFreq[term].count(docID) == 0)
                continue;

            double tf = termFreq[term][docID];
            double idf = log((double)totalDocs / (1 + docFreq[term]));

            score += tf * idf;
        }

        scores[docID] = score;
    }

    return scores;
}
