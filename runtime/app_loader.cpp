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
    enum class State { IDLE, RUNNING, SUSPENDED, TERMINATED };
    State state;

    App(const std::string& n, const std::string& p) : name(n), path(p), state(State::IDLE) {}
    
    virtual void launch() {
        state = State::RUNNING;
        std::cout << "[App Lifecycle] Launching: " << name << " (" << path << ")\n";
        Sandbox sandbox;
        sandbox.loadApp(this);
    }

    virtual void suspend() {
        if (state == State::RUNNING) {
            state = State::SUSPENDED;
            std::cout << "[App Lifecycle] Suspending: " << name << "\n";
        }
    }

    virtual void resume() {
        if (state == State::SUSPENDED) {
            state = State::RUNNING;
            std::cout << "[App Lifecycle] Resuming: " << name << "\n";
        }
    }

    virtual void terminate() {
        state = State::TERMINATED;
        std::cout << "[App Lifecycle] Terminated: " << name << "\n";
    }
};

class AppLoader {
public:
    void loadAndLaunch(App* app) {
        if (app) app->launch();
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