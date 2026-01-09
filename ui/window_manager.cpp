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

    void listOpenWindows() {
        std::cout << "[WindowManager] Open windows:\n";
        for (const auto &w : windows) {
            if (w.isOpen) std::cout << " - " << w.title << "\n";
        }
    }
};

#endif