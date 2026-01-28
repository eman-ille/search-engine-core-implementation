#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <vector>
#include <string>

class Preprocessor {
public:
    std::vector<std::string> process(const std::string& text);

private:
    bool isStopWord(const std::string& word);
    std::string stem(const std::string& word);   // optional
};

#endif
