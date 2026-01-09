#ifndef DESKTOP_H
#define DESKTOP_H

#include <iostream>
#include <string>
#include "window_manager.cpp"

class Desktop {
private:
    WindowManager wm;

public:
    void initDesktop() {
        std::cout << "[Desktop] Loading wallpaper and icons...\n";
        std::cout << "[Desktop] Icons: Browser, File Explorer, Settings, Example App.\n";
    }

    void openAppWindow(const std::string& appName) {
        wm.openWindow(appName);
    }

    void closeAppWindow(const std::string& appName) {
        wm.closeWindow(appName);
    }

    void listWindows() {
        wm.listOpenWindows();
    }
    
    void handleInput(const std::string& input) {
        std::cout << "[Desktop] Input received: " << input << "\n";
    }
};

#endif