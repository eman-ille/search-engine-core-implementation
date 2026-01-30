#include <iostream>
#include "../include/query_processor.h"

using namespace std;

int main() {

    // Dummy inverted index (for testing only)
    unordered_map<string, vector<int>> invertedIndex;

    invertedIndex["search"] = {0, 1, 2};
    invertedIndex["engine"] = {1, 2};
    invertedIndex["data"]   = {2, 3};

    QueryProcessor qp(invertedIndex);

    // -------- Single word query --------
    cout << "Query: search\n";
    vector<int> result1 = qp.processQuery("search");

    for (int i = 0; i < result1.size(); i++)
        cout << result1[i] << " ";

    cout << "\nTime (ms): " << qp.getLastQueryTime() << "\n\n";

    // -------- AND query --------
    cout << "Query: search AND engine\n";
    vector<int> result2 = qp.processQuery("search AND engine");

    for (int i = 0; i < result2.size(); i++)
        cout << result2[i] << " ";

    cout << "\nTime (ms): " << qp.getLastQueryTime() << "\n\n";

    // -------- OR query --------
    cout << "Query: search OR data\n";
    vector<int> result3 = qp.processQuery("search OR data");

    for (int i = 0; i < result3.size(); i++)
        cout << result3[i] << " ";

    cout << "\nTime (ms): " << qp.getLastQueryTime() << "\n";

    return 0;
}
