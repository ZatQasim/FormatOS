#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <iostream>
#include <vector>
#include <string>

struct Window {
    std::string title;
    bool isOpen;
    int x, y, width, height;

    Window(const std::string& t) : title(t), isOpen(true), x(0), y(0), width(800), height(600) {}
};

class WindowManager {
private:
    std::vector<Window> windows;

public:
    void openWindow(const std::string& title) {
        windows.emplace_back(title);
        std::cout << "[WindowManager] Opened window: " << title << "\n";
    }

    void moveWindow(const std::string& title, int nx, int ny) {
        for (auto &w : windows) {
            if (w.title == title) {
                w.x = nx; w.y = ny;
                std::cout << "[WindowManager] Moved window '" << title << "' to " << nx << "," << ny << "\n";
                return;
            }
        }
    }

    void resizeWindow(const std::string& title, int nw, int nh) {
        for (auto &w : windows) {
            if (w.title == title) {
                w.width = nw; w.height = nh;
                std::cout << "[WindowManager] Resized window '" << title << "' to " << nw << "x" << nh << "\n";
                return;
            }
        }
    }

    void closeWindow(const std::string& title) {
        for (auto &w : windows) {
            if (w.title == title) {
                w.isOpen = false;
                std::cout << "[WindowManager] Closed window: " << title << "\n";
                return;
            }
        }
        std::cout << "[WindowManager] Window not found: " << title << "\n";
    }

    void renderWindows(SDL_Renderer* renderer) {
        for (const auto &w : windows) {
            if (w.isOpen) {
                // Modern Glass-like window
                SDL_SetRenderDrawColor(renderer, 45, 45, 50, 240);
                SDL_Rect shadow = {w.x + 5, w.y + 5, w.width, w.height};
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 50);
                SDL_RenderFillRect(renderer, &shadow);

                SDL_SetRenderDrawColor(renderer, 35, 35, 40, 255);
                SDL_Rect frame = {w.x, w.y, w.width, w.height};
                SDL_RenderFillRect(renderer, &frame);

                // Modern Title Bar
                SDL_SetRenderDrawColor(renderer, 60, 60, 70, 255);
                SDL_Rect titleBar = {w.x, w.y, w.width, 35};
                SDL_RenderFillRect(renderer, &titleBar);

                // Close Button (Red dot)
                SDL_SetRenderDrawColor(renderer, 255, 95, 87, 255);
                SDL_Rect closeBtn = {w.x + 10, w.y + 10, 12, 12};
                SDL_RenderFillRect(renderer, &closeBtn);
            }
        }
    }
};

#endif