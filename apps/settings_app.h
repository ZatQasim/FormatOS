#ifndef SETTINGS_APP_H
#define SETTINGS_APP_H

#include "../runtime/app_loader.cpp"
#include <iostream>

class SettingsApp : public App {
public:
    SettingsApp() : App("Settings", "apps/settings.cpp") {}
    void run() override {
        App::run();
        std::cout << "[SettingsApp] Rendering System Settings UI...\n";
    }
};

#endif