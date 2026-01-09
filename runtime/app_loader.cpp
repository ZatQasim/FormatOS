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
    std::string status;

    App(const std::string& n, const std::string& p) : name(n), path(p), status("IDLE") {}
    
    virtual void run() {
        status = "RUNNING";
        std::cout << "[App Loader] Loading app: " << name << " (" << status << ") from " << path << "\n";
        Sandbox sandbox;
        sandbox.loadApp(this);
    }

    virtual void terminate() {
        status = "TERMINATED";
        std::cout << "[App Loader] Terminating app: " << name << " (" << status << ")\n";
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