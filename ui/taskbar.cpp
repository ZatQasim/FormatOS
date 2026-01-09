#ifndef TASKBAR_H
#define TASKBAR_H

#include <iostream>
#include <vector>
#include <string>

#include <ctime>

class Taskbar {
private:
    std::vector<std::string> runningApps;

    void renderLogo(SDL_Renderer* renderer, int x, int y) {
        // Procedural FormatOS Logo
        SDL_SetRenderDrawColor(renderer, 0, 200, 255, 255);
        SDL_Rect r1 = {x, y, 10, 30};
        SDL_Rect r2 = {x + 5, y + 10, 20, 10};
        SDL_RenderFillRect(renderer, &r1);
        SDL_RenderFillRect(renderer, &r2);
    }

    void renderIndicators(SDL_Renderer* renderer, int x, int y) {
        // Wi-Fi Icon
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for(int i=0; i<3; ++i) {
            SDL_Rect bar = {x + (i*8), y + (15 - i*5), 5, 5 + (i*5)};
            SDL_RenderFillRect(renderer, &bar);
        }

        // Bluetooth Icon
        SDL_SetRenderDrawColor(renderer, 50, 150, 255, 255);
        SDL_RenderDrawLine(renderer, x + 35, y, x + 35, y + 20);
        SDL_RenderDrawLine(renderer, x + 35, y, x + 40, y + 5);
        SDL_RenderDrawLine(renderer, x + 40, y + 5, x + 30, y + 15);
        
        // Time
        time_t now = time(0);
        tm *ltm = localtime(&now);
        // Simplified text-less clock (procedural bars for hours/mins)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect clockBase = {x + 60, y, 2, 20};
        SDL_RenderFillRect(renderer, &clockBase);
    }

public:
    void render(SDL_Renderer* renderer, int screenWidth, int screenHeight) {
        // Modern Taskbar
        SDL_SetRenderDrawColor(renderer, 20, 20, 25, 230); // Transparent dark
        SDL_Rect bar = {0, screenHeight - 50, screenWidth, 50};
        SDL_RenderFillRect(renderer, &bar);

        renderLogo(renderer, 15, screenHeight - 40);
        renderIndicators(renderer, screenWidth - 120, screenHeight - 35);
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