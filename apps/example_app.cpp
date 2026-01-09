#include <iostream>
#include <string>
#include "../runtime/formatapi.cpp"
#include "../ui/desktop.cpp"
#include "../ui/taskbar.cpp"

class ExampleApp {
private:
    FormatAPI api;
    Desktop desktop;
    Taskbar taskbar;

public:
    void run() {
        std::cout << "[Example App] Running Example App...\n";

        // Open a window on the desktop
        desktop.openAppWindow("Example App");

        // Add app to taskbar
        taskbar.addApp("Example App");

        // Show message via FormatAPI
        api.showMessage("Hello from Example App!");

        // List open windows
        desktop.listWindows();

        // List running apps
        taskbar.showRunningApps();
    }
};

/*
int main() {
    ExampleApp app;
    app.run();
    return 0;
}
*/