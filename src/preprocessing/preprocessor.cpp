#include "../../include/preprocessor.h"

std::vector<std::string> Preprocessor::process(const std::string& text) {
    std::vector<std::string> tokens;

    // EDGE CASE: empty document
    if (text.length() == 0)
        return tokens;

    std::string word = "";

    for (int i = 0; i < text.length(); i++) {
        char c = text[i];

        // Lowercasing
        if (c >= 'A' && c <= 'Z')
            c = c + 32;

        // Ignore numbers
        if (c >= '0' && c <= '9')
            continue;

        // Tokenization: only letters allowed
        if (c >= 'a' && c <= 'z') {
            word += c;
        }
        // Punctuation or space
        else {
            if (word != "") {
                if (!isStopWord(word)) {
                    tokens.push_back(stem(word));
                }
                word = "";
            }
        }
    }

    // last word
    if (word != "" && !isStopWord(word))
        tokens.push_back(stem(word));

    return tokens;
}

bool Preprocessor::isStopWord(const std::string& word) {
    std::string stopWords[] = {
        "the", "is", "and", "of", "to", "in", "a", "on", "are", "for", "with", "that", "as", "by", "at", "an", "be", "this", "from", "or", "it"
    };

    for (int i = 0; i < 21; i++) {
        if (word == stopWords[i])
            return true;
    }
    return false;
}

// OPTIONAL VERY SIMPLE STEMMING
std::string Preprocessor::stem(const std::string& word) {
    int len = word.length();

    if (len > 4) {
        if (word.substr(len - 3) == "ing")
            return word.substr(0, len - 3);
        if (word.substr(len - 2) == "ed")
            return word.substr(0, len - 2);
    }

    return word;
}
