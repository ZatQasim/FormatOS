#ifndef APP_MANAGER_H
#define APP_MANAGER_H

#include "../runtime/app_loader.cpp"
#include <iostream>

class AppManagerApp : public App {
public:
    AppManagerApp() : App("App Manager", "apps/app_manager.cpp") {}
    void launch() override {
        App::launch();
        std::cout << "[AppManagerApp] Initializing Application Registry and Process Monitor...\n";
    }
};

#endif