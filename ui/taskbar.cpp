#ifndef TASKBAR_H
#define TASKBAR_H

#include <iostream>
#include <vector>
#include <string>

class Taskbar {
private:
    std::vector<std::string> runningApps;

public:
    void render(SDL_Renderer* renderer, int screenWidth, int screenHeight) {
        // Draw taskbar background
        SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
        SDL_Rect bar = {0, screenHeight - 40, screenWidth, 40};
        SDL_RenderFillRect(renderer, &bar);

        // Draw "Start" button placeholder
        SDL_SetRenderDrawColor(renderer, 0, 120, 215, 255);
        SDL_Rect startButton = {5, screenHeight - 35, 70, 30};
        SDL_RenderFillRect(renderer, &startButton);
    }

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