#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "../runtime/app_loader.cpp"
#include <iostream>

class FileManagerApp : public App {
public:
    FileManagerApp() : App("File Manager", "apps/file_explorer.cpp") {}
    void launch() override {
        App::launch();
        std::cout << "[FileManagerApp] Rendering File Explorer UI...\n";
    }
};

#endif