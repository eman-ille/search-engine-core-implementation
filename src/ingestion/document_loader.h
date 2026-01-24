#ifndef DOCUMENT_LOADER_H
#define DOCUMENT_LOADER_H

#include <vector>
#include <string>
#include "../../include/document.h"
using namespace std;

class DocumentLoader {
private:
    vector<Document> docs;

public:
    void loadDocuments();
    vector<Document> getDocuments();
};

#endif
