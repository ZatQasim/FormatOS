#ifndef DESKTOP_H
#define DESKTOP_H

#include <iostream>
#include <string>
#include "window_manager.cpp"

#include "taskbar.cpp"

class Desktop {
private:
    WindowManager wm;
    Taskbar taskbar;

public:
    void render(SDL_Renderer* renderer) {
        int w, h;
        SDL_GetRendererOutputSize(renderer, &w, &h);

        // Draw wallpaper
        SDL_SetRenderDrawColor(renderer, 30, 60, 90, 255);
        SDL_RenderClear(renderer);

        // Draw icons (placeholder)
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        for (int i = 0; i < 4; ++i) {
            SDL_Rect icon = {50, 50 + (i * 100), 64, 64};
            SDL_RenderFillRect(renderer, &icon);
        }

        wm.renderWindows(renderer);
        taskbar.render(renderer, w, h);
    }

    void openAppWindow(const std::string& appName) {
        wm.openWindow(appName);
    }

    void closeAppWindow(const std::string& appName) {
        wm.closeWindow(appName);
    }

    void listWindows() {
        // Method removed as wm.listOpenWindows() was replaced by renderWindows()
    }
    
    void handleInput(const std::string& input) {
        std::cout << "[Desktop] Input received: " << input << "\n";
    }
};

#endif