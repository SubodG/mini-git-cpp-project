#include "FileTracker.hpp"
#include "Utils.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <algorithm>

namespace fs = std::filesystem;

FileTracker::FileTracker() {
    ensureMiniGitDirectory();
    load();
}

void FileTracker::load() {
    trackedFiles.clear();
    std::ifstream fin(".miniGit/tracked.txt");
    std::string file;
    while (getline(fin, file)) {
        trackedFiles.push_back(file);
    }
}

void FileTracker::save() {
    std::ofstream fout(".miniGit/tracked.txt");
    for (const auto& file : trackedFiles) {
        fout << file << "\n";
    }
}

void FileTracker::addFile(const std::string& filename) {
    if (!fs::exists(filename)) {
        std::cout << "File not found.\n";
        return;
    }
    if (std::find(trackedFiles.begin(), trackedFiles.end(), filename) != trackedFiles.end()) {
        std::cout << "File already tracked.\n";
        return;
    }
    trackedFiles.push_back(filename);
    save();
    std::cout << "File added to tracking.\n";
}

void FileTracker::removeFile(const std::string& filename) {
    auto it = std::remove(trackedFiles.begin(), trackedFiles.end(), filename);
    if (it != trackedFiles.end()) {
        trackedFiles.erase(it, trackedFiles.end());
        save();
        std::cout << "File removed from tracking.\n";
    } else {
        std::cout << "File not tracked.\n";
    }
}

void FileTracker::listFiles() const {
    std::cout << "📄 Tracked Files:\n";
    for (const auto& file : trackedFiles) {
        std::cout << " - " << file << "\n";
    }
}

std::vector<std::string> FileTracker::getFiles() const {
    return trackedFiles;
}
