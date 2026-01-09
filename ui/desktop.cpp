#ifndef DESKTOP_H
#define DESKTOP_H

#include <iostream>
#include <string>
#include "window_manager.cpp"
#include "taskbar.cpp"
#include "../services/user_manager.h"
#include "../apps/settings_app.h"
#include "../apps/file_manager_app.h"
#include "../apps/browser_app.h"

#include "notification.h"

#include "../apps/media_viewer_app.h"

class Desktop {
private:
    WindowManager wm;
    Taskbar taskbar;
    UserManager userManager;
    NotificationManager nm;
    bool isAuthenticated;
    std::vector<App*> systemApps;

public:
    Desktop() : isAuthenticated(false) {
        systemApps.push_back(new SettingsApp());
        systemApps.push_back(new FileManagerApp());
        systemApps.push_back(new BrowserApp());
        systemApps.push_back(new MediaViewerApp());
    }

    ~Desktop() {
        for (auto app : systemApps) delete app;
    }

    void render(SDL_Renderer* renderer) {
        if (!isAuthenticated) {
            renderLogin(renderer);
            return;
        }

        int w, h;
        SDL_GetRendererOutputSize(renderer, &w, &h);

        // Linux-style Desktop (Dark Slate/Grey)
        SDL_SetRenderDrawColor(renderer, 28, 30, 34, 255);
        SDL_RenderClear(renderer);

        // GNOME-style Sidebar Launcher
        SDL_SetRenderDrawColor(renderer, 40, 42, 54, 240); // Material design dark
        SDL_Rect sidebar = {10, 10, 60, h - 70};
        SDL_RenderFillRect(renderer, &sidebar);

        // Sidebar Apps with simple hover/animation effect (placeholder)
        for (size_t i = 0; i < systemApps.size(); ++i) {
            // Rounded icon background
            SDL_SetRenderDrawColor(renderer, 60, 64, 72, 255);
            SDL_Rect icon = {20, 30 + (int)i * 70, 40, 40};
            SDL_RenderFillRect(renderer, &icon);
            
            // Interaction highlight (active app indicator)
            SDL_SetRenderDrawColor(renderer, 80, 250, 123, 255); // Vibrant green
            SDL_Rect dot = {12, 45 + (int)i * 70, 4, 10};
            SDL_RenderFillRect(renderer, &dot);
        }

        wm.renderWindows(renderer);
        taskbar.render(renderer, w, h);
        nm.render(renderer, w);
    }

    void notify(const std::string& msg) {
        nm.send(msg);
    }

    void renderLogin(SDL_Renderer* renderer) {
        int w, h;
        SDL_GetRendererOutputSize(renderer, &w, &h);
        
        // Modern glass login screen
        SDL_SetRenderDrawColor(renderer, 20, 20, 25, 255);
        SDL_RenderClear(renderer);

        // Glass panel
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 30);
        SDL_Rect panel = {w/2 - 150, h/2 - 150, 300, 300};
        SDL_RenderFillRect(renderer, &panel);

        // Logo in login
        SDL_SetRenderDrawColor(renderer, 0, 200, 255, 255);
        SDL_Rect logo = {w/2 - 15, h/2 - 100, 30, 30};
        SDL_RenderFillRect(renderer, &logo);
    }

    void login(const std::string& user, const std::string& pin) {
        if (userManager.authenticate(user, pin)) isAuthenticated = true;
    }

    void openAppWindow(const std::string& appName) {
        for (auto app : systemApps) {
            if (app->name == appName) {
                app->launch();
                wm.openWindow(appName);
                notify("Started " + appName);
                return;
            }
        }
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