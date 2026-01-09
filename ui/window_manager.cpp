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
                SDL_SetRenderDrawColor(renderer, 50, 52, 60, 245);
                SDL_Rect shadow = {w.x + 8, w.y + 8, w.width, w.height};
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 80); // Softer shadow
                SDL_RenderFillRect(renderer, &shadow);

                SDL_SetRenderDrawColor(renderer, 40, 42, 54, 255);
                SDL_Rect frame = {w.x, w.y, w.width, w.height};
                SDL_RenderFillRect(renderer, &frame);

                // Modern Title Bar (Linux Adwaita style)
                SDL_SetRenderDrawColor(renderer, 50, 54, 60, 255);
                SDL_Rect titleBar = {w.x, w.y, w.width, 40};
                SDL_RenderFillRect(renderer, &titleBar);

                // Close Button (Red)
                SDL_SetRenderDrawColor(renderer, 255, 85, 85, 255);
                SDL_Rect closeBtn = {w.x + 15, w.y + 14, 12, 12};
                SDL_RenderFillRect(renderer, &closeBtn);
                
                // Minimize (Yellow)
                SDL_SetRenderDrawColor(renderer, 255, 184, 108, 255);
                SDL_Rect minBtn = {w.x + 35, w.y + 14, 12, 12};
                SDL_RenderFillRect(renderer, &minBtn);
                
                // Maximize (Green)
                SDL_SetRenderDrawColor(renderer, 80, 250, 123, 255);
                SDL_Rect maxBtn = {w.x + 55, w.y + 14, 12, 12};
                SDL_RenderFillRect(renderer, &maxBtn);

                // --- App Icons on Desktop/Inside Window ---
                // App Manager Icon (Cyan with "A" symbol)
                SDL_SetRenderDrawColor(renderer, 139, 233, 253, 255); 
                SDL_Rect appMgrIcon = {w.x + 40, w.y + 80, 64, 64};
                SDL_RenderFillRect(renderer, &appMgrIcon);
                // "A" Symbol placeholder
                SDL_SetRenderDrawColor(renderer, 40, 42, 54, 255);
                SDL_Rect appMgrSym = {w.x + 60, w.y + 90, 24, 40};
                SDL_RenderFillRect(renderer, &appMgrSym);

                // Browser Icon (Pink with "B" symbol)
                SDL_SetRenderDrawColor(renderer, 255, 121, 198, 255);
                SDL_Rect browserIcon = {w.x + 140, w.y + 80, 64, 64};
                SDL_RenderFillRect(renderer, &browserIcon);
                // "B" Symbol placeholder
                SDL_SetRenderDrawColor(renderer, 40, 42, 54, 255);
                SDL_Rect browserSym = {w.x + 160, w.y + 90, 24, 40};
                SDL_RenderFillRect(renderer, &browserSym);

                // File Explorer Icon (Yellow with "F" symbol)
                SDL_SetRenderDrawColor(renderer, 241, 250, 140, 255);
                SDL_Rect fileExpIcon = {w.x + 240, w.y + 80, 64, 64};
                SDL_RenderFillRect(renderer, &fileExpIcon);
                // "F" Symbol placeholder
                SDL_SetRenderDrawColor(renderer, 40, 42, 54, 255);
                SDL_Rect fileExpSym = {w.x + 260, w.y + 90, 24, 40};
                SDL_RenderFillRect(renderer, &fileExpSym);

                // Handling click to launch apps (simulated in event loop)
                // Note: Real click detection would be in main.cpp or window_manager input handler
                // Labels are implicitly the app identity for this visualization phase.
            }
        }
    }
};

#endif