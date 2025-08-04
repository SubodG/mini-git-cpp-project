#include "DiffEngine.hpp"
#include <fstream>
#include <iostream>

void DiffEngine::showDiff(const std::string& oldFile, const std::string& newFile) {
    std::ifstream f1(oldFile), f2(newFile);
    std::string l1, l2;
    int line = 1;

    while (getline(f1, l1) && getline(f2, l2)) {
        if (l1 != l2) {
            std::cout << "~ Line " << line << "\n- " << l1 << "\n+ " << l2 << "\n";
        }
        line++;
    }

    while (getline(f1, l1)) {
        std::cout << "- Line " << line++ << ": " << l1 << "\n";
    }
    while (getline(f2, l2)) {
        std::cout << "+ Line " << line++ << ": " << l2 << "\n";
    }
}
