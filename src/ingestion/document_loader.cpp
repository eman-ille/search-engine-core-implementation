#include "document_loader.h"
#include <fstream>
#include <iostream>

void DocumentLoader::loadDocuments() {
    std::string filenames[5] = {
        "documents/doc1.txt",
        "documents/doc2.txt",
        "documents/doc3.txt",
        "documents/doc4.txt",
        "documents/doc5.txt"
    };

    for (int i = 0; i < 5; i++) {
        std::ifstream file(filenames[i]);

        if (!file) {
            std::cout << "Cannot open " << filenames[i] << std::endl;
            continue;
        }

        Document d;
        d.id = i;
        d.filename = filenames[i];

        std::string line;
        d.content = "";
        while (getline(file, line)) {
            d.content += line + " ";
        }

        docs.push_back(d);
        file.close();
    }
}

std::vector<Document> DocumentLoader::getDocuments() {
    return docs;
}
