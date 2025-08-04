#pragma once
#include <string>

class Restorer {
public:
    void restoreFile(const std::string& filename, const std::string& commitID);
    void checkout(const std::string& commitID);
};
