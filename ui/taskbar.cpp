#ifndef TASKBAR_H
#define TASKBAR_H

#include <iostream>
#include <vector>
#include <string>

class Taskbar {
private:
    std::vector<std::string> runningApps;

public:
    void addApp(const std::string& appName) {
        runningApps.push_back(appName);
        std::cout << "[Taskbar] Icon added for: " << appName << "\n";
    }

    void removeApp(const std::string& appName) {
        for (auto it = runningApps.begin(); it != runningApps.end(); ++it) {
            if (*it == appName) {
                runningApps.erase(it);
                std::cout << "[Taskbar] Icon removed for: " << appName << "\n";
                return;
            }
        }
    }

    void showRunningApps() {
        std::cout << "[Taskbar] Active tasks: ";
        for (const auto &app : runningApps) std::cout << "[" << app << "] ";
        std::cout << "\n";
    }
};

#endif