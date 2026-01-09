#ifndef MEDIA_VIEWER_APP_H
#define MEDIA_VIEWER_APP_H

#include "../runtime/app_loader.cpp"
#include <iostream>

class MediaViewerApp : public App {
public:
    MediaViewerApp() : App("Media Viewer", "apps/media_viewer.cpp") {}
    void run() override {
        App::run();
        std::cout << "[MediaViewerApp] Rendering Media Gallery and Video Player UI...\n";
    }
};

#endif