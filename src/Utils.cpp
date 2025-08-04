#include "Utils.hpp"
#include <filesystem>
#include <ctime>
#include <functional>

namespace fs = std::filesystem;

std::string getCurrentTimestamp() {
    time_t now = time(0);
    tm* local = localtime(&now);
    char buf[32];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", local);
    return std::string(buf);
}

std::string generateCommitID(const std::string& msg, const std::string& time) {
    std::hash<std::string> hash_fn;
    return std::to_string(hash_fn(msg + time));
}

void ensureMiniGitDirectory() {
    if (!fs::exists(".miniGit")) fs::create_directory(".miniGit");
}
