#ifndef BROWSER_APP_H
#define BROWSER_APP_H

#include "../runtime/app_loader.cpp"
#include <iostream>

class BrowserApp : public App {
public:
    BrowserApp() : App("Browser", "apps/browser.cpp") {}
    void launch() override {
        App::launch();
        std::cout << "[BrowserApp] Launching FormatOS Web Browser (v1.0)...\n";
    }
};

#endif