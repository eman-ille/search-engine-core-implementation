#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include "../include/document.h"
#include "../include/preprocessor.h"
#include "../include/index.h"
#include "../include/query_processor.h"
#include "../src/ranking/tfidf.h"
#include "../src/ingestion/document_loader.h"
#include "../include/query_cache.h"
#include "../src/benchmark/benchmark.h"

using namespace std;

void displayMenu() {
    cout << "\n========== SEARCH ENGINE MENU ==========\n";
    cout << "1. Load and Index Documents\n";
    cout << "2. Search (Single Term)\n";
    cout << "3. Boolean Search (AND/OR)\n";
    cout << "4. Ranked Search (TF-IDF)\n";
    cout << "5. View Index Statistics\n";
    cout << "6. Run Performance Benchmarks\n";
    cout << "7. Clear Query Cache\n";
    cout << "0. Exit\n";
    cout << "========================================\n";
    cout << "Enter choice: ";
}

void displayDocuments(const vector<Document>& docs) {
    cout << "\n--- Loaded Documents ---\n";
    for (const auto& doc : docs) {
        cout << "Doc ID: " << doc.id << " | File: " << doc.filename << "\n";
        cout << "Content preview: " << doc.content.substr(0, 80) << "...\n\n";
    }
}

void displaySearchResults(const vector<pair<int, int>>& results, 
                         const vector<Document>& docs) {
    if (results.empty()) {
        cout << "No documents found.\n";
        return;
    }

    cout << "\n--- Search Results ---\n";
    cout << "Found in " << results.size() << " document(s):\n\n";
    
    for (const auto& result : results) {
        int docId = result.first;
        int frequency = result.second;
        
        // Find the document
        for (const auto& doc : docs) {
            if (doc.id == docId) {
                cout << "Doc ID: " << docId << " (" << doc.filename << ")\n";
                cout << "Term Frequency: " << frequency << "\n";
                cout << "Content: " << doc.content.substr(0, 100) << "...\n\n";
                break;
            }
        }
    }
}

void displayRankedResults(const unordered_map<int, double>& scores,
                         const vector<Document>& docs) {
    if (scores.empty()) {
        cout << "No documents found.\n";
        return;
    }

    // Convert to vector for sorting
    vector<pair<int, double>> sortedScores(scores.begin(), scores.end());
    sort(sortedScores.begin(), sortedScores.end(),
         [](const pair<int, double>& a, const pair<int, double>& b) {
             return a.second > b.second; // Descending order
         });

    cout << "\n--- Ranked Search Results (TF-IDF) ---\n";
    cout << setw(8) << "Rank" << setw(10) << "Doc ID" 
         << setw(15) << "Score" << "  Filename\n";
    cout << string(60, '-') << "\n";

    int rank = 1;
    for (const auto& score : sortedScores) {
        int docId = score.first;
        double tfidfScore = score.second;
        
        for (const auto& doc : docs) {
            if (doc.id == docId) {
                cout << setw(8) << rank++ << setw(10) << docId 
                     << setw(15) << fixed << setprecision(4) << tfidfScore
                     << "  " << doc.filename << "\n";
                break;
            }
        }
    }
}

void displayIndexStats(const Index& index, int totalDocs) {
    cout << "\n--- Index Statistics ---\n";
    cout << "Total Documents Indexed: " << totalDocs << "\n";
    cout << "\nTo see full index, use printIndex() method\n";
}

void runBenchmarks() {
    cout << "\n--- Running Performance Benchmarks ---\n";
    
    cout << "Measuring indexing performance...\n";
    long long indexTime = Benchmark::measureIndexing();
    cout << "Indexing Time: " << indexTime << " microseconds\n";
    
    cout << "\nMeasuring query performance...\n";
    long long queryTime = Benchmark::measureQuery();
    cout << "Query Time: " << queryTime << " microseconds\n";
    
    cout << "\nBenchmark completed!\n";
}

int main() {
    // Module instances
    DocumentLoader loader;
    Preprocessor preprocessor;
    Index index;
    QueryCache cache;
    TFIDF ranker;
    
    vector<Document> documents;
    
    // For TF-IDF ranking
    unordered_map<string, unordered_map<int, int>> termFreq;
    unordered_map<string, int> docFreq;
    
    bool indexed = false;
    int choice;
    
    cout << "========================================\n";
    cout << "   SEARCH ENGINE CORE IMPLEMENTATION   \n";
    cout << "========================================\n";

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Clear newline
        
        switch (choice) {
            case 1: {
                // Load and Index Documents
                cout << "\nLoading documents...\n";
                loader.loadDocuments();
                documents = loader.getDocuments();
                
                if (documents.empty()) {
                    cout << "No documents loaded. Check your documents folder.\n";
                    break;
                }
                
                displayDocuments(documents);
                
                cout << "\nIndexing documents...\n";
                auto start = chrono::high_resolution_clock::now();
                
                for (const auto& doc : documents) {
                    vector<string> tokens = preprocessor.process(doc.content);
                    index.addDocument(doc.id, tokens);
                    
                    // Build term frequency and doc frequency for TF-IDF
                    unordered_map<string, int> docTerms;
                    for (const auto& token : tokens) {
                        termFreq[token][doc.id]++;
                        docTerms[token]++;
                    }
                    
                    for (const auto& entry : docTerms) {
                        docFreq[entry.first]++;
                    }
                }
                
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
                
                indexed = true;
                cout << "Indexing completed in " << duration.count() << " ms\n";
                cout << documents.size() << " documents indexed successfully!\n";
                break;
            }
            
            case 2: {
                // Single Term Search
                if (!indexed) {
                    cout << "Please load and index documents first (Option 1).\n";
                    break;
                }
                
                cout << "\nEnter search term: ";
                string term;
                getline(cin, term);
                
                // Preprocess the query term
                vector<string> processedTerms = preprocessor.process(term);
                if (processedTerms.empty()) {
                    cout << "Invalid search term.\n";
                    break;
                }
                
                auto start = chrono::high_resolution_clock::now();
                vector<pair<int, int>> results = index.search(processedTerms[0]);
                auto end = chrono::high_resolution_clock::now();
                
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                
                displaySearchResults(results, documents);
                cout << "Query executed in " << duration.count() << " microseconds\n";
                break;
            }
            
            case 3: {
                // Boolean Search (AND/OR)
                if (!indexed) {
                    cout << "Please load and index documents first (Option 1).\n";
                    break;
                }
                
                cout << "\nEnter boolean query (e.g., 'term1 AND term2' or 'term1 OR term2'): ";
                string query;
                getline(cin, query);
                
                // Simple parsing
                vector<string> parts;
                string word;
                for (char c : query) {
                    if (c == ' ') {
                        if (!word.empty()) {
                            parts.push_back(word);
                            word = "";
                        }
                    } else {
                        word += c;
                    }
                }
                if (!word.empty()) parts.push_back(word);
                
                if (parts.size() != 3) {
                    cout << "Invalid query format. Use: term1 AND/OR term2\n";
                    break;
                }
                
                // Preprocess terms
                vector<string> term1_tokens = preprocessor.process(parts[0]);
                vector<string> term2_tokens = preprocessor.process(parts[2]);
                
                if (term1_tokens.empty() || term2_tokens.empty()) {
                    cout << "Invalid terms.\n";
                    break;
                }
                
                auto start = chrono::high_resolution_clock::now();
                
                vector<pair<int, int>> results1 = index.search(term1_tokens[0]);
                vector<pair<int, int>> results2 = index.search(term2_tokens[0]);
                
                // Extract just doc IDs for set operations
                vector<int> docIds1, docIds2;
                for (const auto& r : results1) docIds1.push_back(r.first);
                for (const auto& r : results2) docIds2.push_back(r.second);
                
                vector<int> finalDocs;
                
                if (parts[1] == "AND") {
                    // Intersection
                    sort(docIds1.begin(), docIds1.end());
                    sort(docIds2.begin(), docIds2.end());
                    set_intersection(docIds1.begin(), docIds1.end(),
                                   docIds2.begin(), docIds2.end(),
                                   back_inserter(finalDocs));
                } else if (parts[1] == "OR") {
                    // Union
                    finalDocs = docIds1;
                    for (int id : docIds2) {
                        if (find(finalDocs.begin(), finalDocs.end(), id) == finalDocs.end()) {
                            finalDocs.push_back(id);
                        }
                    }
                    sort(finalDocs.begin(), finalDocs.end());
                } else {
                    cout << "Invalid operator. Use AND or OR.\n";
                    break;
                }
                
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                
                // Display results
                cout << "\n--- Boolean Search Results ---\n";
                cout << "Found " << finalDocs.size() << " document(s)\n\n";
                for (int docId : finalDocs) {
                    for (const auto& doc : documents) {
                        if (doc.id == docId) {
                            cout << "Doc ID: " << docId << " (" << doc.filename << ")\n";
                            break;
                        }
                    }
                }
                
                cout << "Query executed in " << duration.count() << " microseconds\n";
                break;
            }
            
            case 4: {
                // Ranked Search using TF-IDF
                if (!indexed) {
                    cout << "Please load and index documents first (Option 1).\n";
                    break;
                }
                
                cout << "\nEnter search query: ";
                string query;
                getline(cin, query);
                
                // Check cache
                if (cache.hasQuery(query)) {
                    cout << "[Cache Hit] Retrieving from cache...\n";
                    vector<int> cachedResults = cache.getResult(query);
                    
                    cout << "\n--- Cached Results ---\n";
                    for (int docId : cachedResults) {
                        for (const auto& doc : documents) {
                            if (doc.id == docId) {
                                cout << "Doc ID: " << docId << " (" << doc.filename << ")\n";
                                break;
                            }
                        }
                    }
                    break;
                }
                
                // Preprocess query
                vector<string> queryTerms = preprocessor.process(query);
                if (queryTerms.empty()) {
                    cout << "Invalid query.\n";
                    break;
                }
                
                auto start = chrono::high_resolution_clock::now();
                
                // Find all documents containing any query term
                vector<int> relevantDocs;
                for (const auto& term : queryTerms) {
                    vector<pair<int, int>> termResults = index.search(term);
                    for (const auto& result : termResults) {
                        if (find(relevantDocs.begin(), relevantDocs.end(), result.first) 
                            == relevantDocs.end()) {
                            relevantDocs.push_back(result.first);
                        }
                    }
                }
                
                // Rank documents using TF-IDF
                unordered_map<int, double> scores = ranker.rankDocuments(
                    relevantDocs, queryTerms, termFreq, docFreq, documents.size()
                );
                
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                
                displayRankedResults(scores, documents);
                cout << "\nQuery executed in " << duration.count() << " microseconds\n";
                
                // Cache the top results
                vector<int> topDocs;
                vector<pair<int, double>> sortedScores(scores.begin(), scores.end());
                sort(sortedScores.begin(), sortedScores.end(),
                     [](const pair<int, double>& a, const pair<int, double>& b) {
                         return a.second > b.second;
                     });
                for (size_t i = 0; i < min((size_t)5, sortedScores.size()); i++) {
                    topDocs.push_back(sortedScores[i].first);
                }
                cache.storeResult(query, topDocs);
                
                break;
            }
            
            case 5: {
                // View Index Statistics
                if (!indexed) {
                    cout << "Please load and index documents first (Option 1).\n";
                    break;
                }
                
                displayIndexStats(index, documents.size());
                
                cout << "\nShow full index? (y/n): ";
                char show;
                cin >> show;
                cin.ignore();
                
                if (show == 'y' || show == 'Y') {
                    cout << "\n--- Full Inverted Index ---\n";
                    index.printIndex();
                }
                break;
            }
            
            case 6: {
                // Run Benchmarks
                runBenchmarks();
                break;
            }
            
            case 7: {
                // Clear cache
                cache = QueryCache();
                cout << "Query cache cleared.\n";
                break;
            }
            
            case 0: {
                cout << "\nExiting Search Engine. Goodbye!\n";
                return 0;
            }
            
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
    
    return 0;
}