# search-engine-core-implementation
DSA Project: Building search engine from scratch
Project Overview
    Implementing core search engine algorithms including:
    - Document Ingestion
    - Text Preprocessing
    - Inverted Index
    - Query Processing
    - Ranking (TF-IDF)
    - Optimization
    - Benchmarking

How to Compile & Test Each Module
1️⃣ Ingestion Module

    Loads documents from files.

    g++ src/ingestion/document_loader.cpp tests/test_ingestion.cpp -o test_ingestion && ./test_ingestion

2️⃣ Text Preprocessing Module

    Tokenization, lowercasing, stop-word removal.

    g++ src/preprocessing/preprocessor.cpp tests/test_preprocessing_on_docs.cpp -o test_preprocessing && ./test_preprocessing

3️⃣ Query Processing Module

    Handles single-word, multi-word, AND / OR queries.

    g++ src/query/query_processor.cpp tests/test_query_processing.cpp -o test_query_processing && ./test_query_processing

4️⃣ Ranking Module (TF-IDF)

    Ranks documents based on relevance.

    g++ src/ranking/tfidf.cpp tests/test_ranking.cpp -o test_ranking && ./test_ranking

5️⃣ Optimization Module (Query Caching)

    Improves performance for repeated queries.

    (Integrated inside query processing — no separate run needed)

6️⃣ Benchmarking & Analysis Module

    Measures indexing time and query time.

    g++ src/benchmark/benchmark.cpp tests/test_benchmark.cpp -o test_benchmark && ./test_benchmark


    To save benchmark output:

    ./test_benchmark > benchmark_log.txt

FINAL RUN COMMAND TO COMIPILE ALL THESE FILES 

g++ -std=c++17 -Iinclude main.cpp src/ingestion/document_loader.cpp src/preprocessing/preprocessor.cpp src/index/index.cpp src/query/query_processor.cpp src/ranking/tfidf.cpp src/optimization/query_cache.cpp src/benchmark/benchmark.cpp -o search_engine && search_engine.exe