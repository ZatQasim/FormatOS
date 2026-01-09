#ifndef APP_LOADER_H
#define APP_LOADER_H

#include <iostream>
#include <string>
#include "sandbox.cpp"
#include "formatapi.cpp"

class App {
public:
    std::string name;
    std::string path;

    App(const std::string& n, const std::string& p) : name(n), path(p) {}
    
    virtual void run() {
        std::cout << "[App Loader] Loading app: " << name << " from " << path << "\n";
        Sandbox sandbox;
        sandbox.loadApp(this); // Run inside sandbox
    }
};

class AppLoader {
public:
    void loadApp(App* app) {
        if (app) app->run();
    }
};

void initAppLoader() {
    std::cout << "[App Loader] Initializing runtime...\n";

    // Example: load your first app
    // App exampleApp("Example App", "apps/example_app.cpp");
    // exampleApp.run();

    std::cout << "[App Loader] All apps loaded.\n";
}

#endif