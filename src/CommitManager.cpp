#include "CommitManager.hpp"
#include "Utils.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void CommitManager::createCommit(const std::vector<std::string>& files, const std::string& message) {
    if (files.empty()) {
        std::cout << " No files tracked! .\n";
        return;
    }

    std::string timestamp = getCurrentTimestamp();
    std::string commitID = generateCommitID(message, timestamp);
    std::string commitDir = ".miniGit/" + commitID;

    fs::create_directory(commitDir);
    for (const auto& file : files) {
        fs::copy_file(file, commitDir + "/" + fs::path(file).filename().string(), fs::copy_options::overwrite_existing);
    }

    std::ofstream log(".miniGit/log.txt", std::ios::app);
    log << commitID << "|" << message << "|" << timestamp << "\n";
    std::cout << " Commit created: " << commitID << "\n";
}

void CommitManager::showHistory() {
    std::ifstream log(".miniGit/log.txt");
    std::string line;
    while (getline(log, line)) {
        size_t id_end = line.find('|');
        size_t msg_end = line.find('|', id_end + 1);
        std::string id = line.substr(0, id_end);
        std::string msg = line.substr(id_end + 1, msg_end - id_end - 1);
        std::string time = line.substr(msg_end + 1);
        std::cout << " ID: " << id << "\n Msg: " << msg << "\n Time: " << time << "\n---\n";
    }
}
