#pragma once
#include <string>

std::string getCurrentTimestamp();
std::string generateCommitID(const std::string& msg, const std::string& time);
void ensureMiniGitDirectory();
