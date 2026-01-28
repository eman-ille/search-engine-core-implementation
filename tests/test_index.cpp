#include "index.h"
#include <iostream>

using namespace std;

int main() {
    Index index;

    index.addDocument(1, {"quick", "brown", "fox", "quick"});
    index.addDocument(2, {"quick", "fox", "jumps"});

    index.printIndex();

    auto result = index.search("quick");
    cout << "\nSearch result for 'quick':\n";
    for (auto &p : result) {
        cout << "DocID: " << p.first
             << " Frequency: " << p.second << endl;
    }

    return 0;
}
