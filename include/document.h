#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
using namespace std;

// Structure to store document information
struct Document {
    int id;              // Unique document ID
    string filename;     // Name of the file
    string content;      // Full text content of document
    
    // Constructor
    Document(int docId, string fname, string text) 
        : id(docId), filename(fname), content(text) {}
    
    // Default constructor
    Document() : id(0), filename(""), content("") {}
};

#endif