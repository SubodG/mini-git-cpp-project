#include "../include/FileTracker.hpp"
#include "../include/CommitManager.hpp"
#include "../include/DiffEngine.hpp"
#include "../include/Restorer.hpp"
#include <iostream>
#include <sstream>

int main() {
    FileTracker tracker;
    CommitManager committer;
    DiffEngine diff;
    Restorer restorer;

    std::string cmd;
    std::cout << "Welcome to MiniGit (Type 'help' for commands)\n";

    while (true) {
        std::cout << "\n>>> ";
        std::getline(std::cin, cmd);
        std::stringstream ss(cmd);
        std::string op;
        ss >> op;

        if (op == "add") {
            std::string fname;
            ss >> fname;
            if (fname.empty()) {
                std::cout << "Usage: add <filename>\n";
            } else {
                tracker.addFile(fname);
            }

        } else if (op == "remove") {
            std::string fname;
            ss >> fname;
            if (fname.empty()) {
                std::cout << "Usage: remove <filename>\n";
            } else {
                tracker.removeFile(fname);
            }

        } else if (op == "list") {
            tracker.listFiles();

        } else if (op == "commit") {
            std::string msg;
            std::getline(ss, msg);
            if (msg.empty()) {
                std::cout << "Usage: commit <message>\n";
            } else {
                committer.createCommit(tracker.getFiles(), msg.substr(1)); // remove leading space
            }

        } else if (op == "history") {
            committer.showHistory();

        } else if (op == "diff") {
            std::string filename, commitID;
            ss >> filename >> commitID;
            if (filename.empty() || commitID.empty()) {
                std::cout << "Usage: diff <filename> <commitID>\n";
            } else {
                std::string oldFile = ".miniGit/" + commitID + "/" + filename;
                diff.showDiff(oldFile, filename);
            }

        } else if (op == "restore") {
            std::string filename, commitID;
            ss >> filename >> commitID;
            if (filename.empty() || commitID.empty()) {
                std::cout << "Usage: restore <filename> <commitID>\n";
            } else {
                restorer.restoreFile(filename, commitID);
            }

        } else if (op == "checkout") {
            std::string commitID;
            ss >> commitID;
            if (commitID.empty()) {
                std::cout << "Usage: checkout <commitID>\n";
            } else {
                restorer.checkout(commitID);
            }

        } else if (op == "help") {
            std::cout << "Available commands:\n"
                      << " - add <filename>       : Track a new file\n"
                      << " - remove <filename>    : Stop tracking a file\n"
                      << " - list                 : Show tracked files\n"
                      << " - commit <message>     : Commit changes\n"
                      << " - history              : Show commit history\n"
                      << " - diff <file> <id>     : Compare file to a commit\n"
                      << " - restore <f> <id>     : Restore file from a commit\n"
                      << " - checkout <id>        : Restore all files from a commit\n"
                      << " - help                 : Show this message\n"
                      << " - exit                 : Exit MiniGit\n";

        } else if (op == "exit") {
            std::cout << "Exiting MiniGit. Bye!\n";
            break;

        } else if (!op.empty()) {
            std::cout << "Unknown command. Type 'help' to list options.\n";
        }
    }

    return 0;
}
