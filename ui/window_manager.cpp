#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <iostream>
#include <vector>
#include <string>

struct Window {
    std::string title;
    bool isOpen;

    Window(const std::string& t) : title(t), isOpen(true) {}
};

class WindowManager {
private:
    std::vector<Window> windows;

public:
    void openWindow(const std::string& title) {
        windows.emplace_back(title);
        std::cout << "[WindowManager] Opened window: " << title << "\n";
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

    void listOpenWindows() {
        std::cout << "[WindowManager] Open windows:\n";
        for (const auto &w : windows) {
            if (w.isOpen) std::cout << " - " << w.title << "\n";
        }
    }
};

#endif