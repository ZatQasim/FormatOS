#ifndef SETTINGS_APP_H
#define SETTINGS_APP_H
#include <iostream>

class App {
public:
    std::string name;
    App(std::string n, std::string p) : name(n) {}
    virtual void launch() { std::cout << "App: Launching " << name << std::endl; }
};

class SettingsApp : public App {
public:
    SettingsApp() : App("Settings", "apps/settings.cpp") {}
};
#endif
