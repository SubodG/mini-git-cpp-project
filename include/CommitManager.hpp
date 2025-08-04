#pragma once
#include <vector>
#include <string>

class CommitManager {
public:
    void createCommit(const std::vector<std::string>& files, const std::string& message);
    void showHistory();
};
