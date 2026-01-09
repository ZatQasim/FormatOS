#ifndef SETTINGS_APP_H
#define SETTINGS_APP_H

#include "../runtime/app_loader.cpp"
#include <iostream>

class SettingsApp : public App {
public:
    SettingsApp() : App("Settings", "apps/settings.cpp") {}
    void launch() override {
        App::launch();
        std::cout << "[SettingsApp] Rendering System Settings UI...\n";
    }
};

#endif