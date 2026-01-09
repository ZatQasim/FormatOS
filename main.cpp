#include <SDL2/SDL.h>
#include <iostream>

// Forward declarations for your modules
#include "bootloader/boot.cpp"
#include "linux_kernel/kernel_main.cpp"
#include "services/recovery.cpp"
#include "runtime/app_loader.cpp"
#include "ui/desktop.cpp"

#include "apps/settings_app.h"
#include "apps/file_manager_app.h"

void initRecovery() {
    initRecoveryService();
}

class ExampleApp : public App {
public:
    ExampleApp() : App("Example App", "apps/example_app.cpp") {}
    void launch() override {
        App::launch();
        std::cout << "[ExampleApp] Running graphical interface...\n";
    }
};

// Simple visual boot step renderer
void renderBootStep(SDL_Renderer* renderer, const char* step, int stepNumber) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect progress = {50, 250, stepNumber * 140, 50};
    SDL_RenderFillRect(renderer, &progress);

    SDL_RenderPresent(renderer);
    std::cout << "[BOOT] " << step << std::endl;

    SDL_Delay(1000);
}

int main(int argc, char* argv[]) {
    std::cout << "--- FORMAT OS BOOT SEQUENCE ---\n";

    // Initialize SDL2
    setenv("SDL_VIDEODRIVER", "x11", 1);
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "FormatOS GUI",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1024, 768,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Boot steps
    renderBootStep(renderer, "Initializing Bootloader...", 1);
    boot();

    renderBootStep(renderer, "Loading Linux Kernel...", 2);
    kernelMain();

    renderBootStep(renderer, "Starting Recovery Services...", 3);
    initRecovery();

    renderBootStep(renderer, "Initializing App Loader...", 4);
    initAppLoader();

    renderBootStep(renderer, "Launching Example App...", 5);
    ExampleApp app;
    // app.launch();

    SettingsApp settings;
    // settings.launch();

    FileManagerApp fileManager;
    // fileManager.launch();

    Desktop desktop;
    desktop.login("admin", "1234"); // Auto-login for demo purposes
    desktop.notify("Welcome to FormatOS");
    
    // Detect "mobile" resolution for optimization
    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);
    if (w < 600) {
        std::cout << "[System] Mobile optimization enabled.\n";
        // Mobile layout: one window at a time, full screen
    }

    desktop.openAppWindow("Settings");
    desktop.openAppWindow("File Manager");
    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                // Future: implementation for window selection/dragging
            }
        }

        desktop.render(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60 FPS
    }

    renderBootStep(renderer, "Syncing Disks & Powering Down...", 6);

    std::cout << "\n--- SHUTDOWN SEQUENCE ---\n";
    std::cout << "[System] All processes terminated.\n";
    std::cout << "[System] Power down.\n";

    // Cleanup SDL2
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}