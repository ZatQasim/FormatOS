#include <iostream>
#include <vector>
#include <string>

class Taskbar {
private:
    std::vector<std::string> runningApps;

public:
    void addApp(const std::string& appName) {
        runningApps.push_back(appName);
        std::cout << "[Taskbar] Added running app: " << appName << "\n";
    }

    void removeApp(const std::string& appName) {
        for (auto it = runningApps.begin(); it != runningApps.end(); ++it) {
            if (*it == appName) {
                runningApps.erase(it);
                std::cout << "[Taskbar] Removed app: " << appName << "\n";
                return;
            }
        }
    }

    void showRunningApps() {
        std::cout << "[Taskbar] Running apps:\n";
        for (auto &app : runningApps) {
            std::cout << " - " << app << "\n";
        }
    }
};