#include <iostream>
#include "window_manager.cpp"

class Desktop {
private:
    WindowManager wm;

public:
    void initDesktop() {
        std::cout << "[Desktop] Initializing desktop...\n";
        showBackground();
    }

    void showBackground() {
        std::cout << "[Desktop] Displaying desktop background...\n";
    }

    void openAppWindow(const std::string& appName) {
        std::cout << "[Desktop] Opening app window for: " << appName << "\n";
        wm.openWindow(appName);
    }

    void listWindows() {
        wm.listOpenWindows();
    }
};