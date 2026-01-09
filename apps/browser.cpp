#include <iostream>
#include <string>
#include "../runtime/formatapi.cpp"
#include "../ui/desktop.cpp"
#include "../ui/taskbar.cpp"

class Browser {
private:
    FormatAPI api;
    Desktop desktop;
    Taskbar taskbar;

public:
    void run() {
        std::cout << "[Browser] Launching Browser...\n";

        desktop.openAppWindow("Browser");
        taskbar.addApp("Browser");

        // Simulate visiting a website
        std::string url = "https://example.com";
        std::cout << "[Browser] Navigating to: " << url << "\n";

        api.showMessage("Browser loaded website: " + url);
    }
};

int main() {
    Browser browser;
    browser.run();
    return 0;
}