#ifndef EXAMPLE_APP_H
#define EXAMPLE_APP_H

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
        std::cout << "[Example App] Initializing inside sandbox...\n";
        
        api.logEvent("Example App Started");
        desktop.openAppWindow("Example App");
        taskbar.addApp("Example App");
        
        api.showMessage("Welcome to FormatOS!");
        
        desktop.listWindows();
        taskbar.showRunningApps();
        
        // Simulate interaction
        desktop.handleInput("Mouse Click at (100, 200)");
        
        std::cout << "[Example App] Closing...\n";
        desktop.closeAppWindow("Example App");
        taskbar.removeApp("Example App");
    }
};

#endif