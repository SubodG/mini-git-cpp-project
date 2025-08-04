#include "Restorer.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

void Restorer::restoreFile(const std::string& filename, const std::string& commitID) {
    std::string path = ".miniGit/" + commitID + "/" + fs::path(filename).filename().string();
    if (!fs::exists(path)) {
        std::cout << "❌ File version not found.\n";
        return;
    }
    fs::copy_file(path, filename, fs::copy_options::overwrite_existing);
    std::cout << "✅ Restored " << filename << " to commit " << commitID << "\n";
}

void Restorer::checkout(const std::string& commitID) {
    std::string dir = ".miniGit/" + commitID;
    if (!fs::exists(dir)) {
        std::cout << "❌ Commit not found.\n";
        return;
    }

    for (const auto& entry : fs::directory_iterator(dir)) {
        std::string filename = entry.path().filename().string();
        fs::copy_file(entry.path(), filename, fs::copy_options::overwrite_existing);
        std::cout << "Restored " << filename << "\n";
    }
}
