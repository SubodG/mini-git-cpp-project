#pragma once
#include <vector>
#include <string>

class FileTracker {
public:
    FileTracker();
    void addFile(const std::string& filename);
    void removeFile(const std::string& filename);
    std::vector<std::string> getFiles() const;
    void listFiles() const;
    void load();
    void save();
private:
    std::vector<std::string> trackedFiles;
};
