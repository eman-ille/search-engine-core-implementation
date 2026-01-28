#include <iostream>
#include "../include/preprocessor.h"

int main() {
    Preprocessor p;

    std::string text = "The QUICK brown foxes are running and jumped!";
    auto tokens = p.process(text);

    std::cout << "Processed tokens:\n";
    for (auto &t : tokens) {
        std::cout << t << " ";
    }
    std::cout << std::endl;

    return 0;
}
