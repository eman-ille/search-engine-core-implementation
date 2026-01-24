#include <iostream>
#include "../src/ingestion/document_loader.h"

int main() {
    DocumentLoader loader;
    loader.loadDocuments();

    std::vector<Document> documents = loader.getDocuments();

    for (int i = 0; i < documents.size(); i++) {
        std::cout << "DocID: " << (documents[i].id)+1 << std::endl;
        std::cout << "File: " << documents[i].filename << std::endl;
        std::cout << "Text: " << documents[i].content << std::endl;
        std::cout << "-----------------------\n";
    }

    return 0;
}
