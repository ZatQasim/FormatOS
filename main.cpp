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

    SDL_Delay(200); // Faster boot transition
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

    // Quickly clear boot screen and show main UI
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    Desktop desktop;
    desktop.login("admin", "1234"); // Auto-login for demo purposes
    desktop.notify("Welcome to FormatOS");
    
    // Smooth transition animation from black to desktop
    for (int i = 0; i <= 255; i += 15) {
        SDL_SetRenderDrawColor(renderer, 30, 31, 34, i); // Desktop base color
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    desktop.openAppWindow("Settings");
    desktop.openAppWindow("File Manager");
    desktop.openAppWindow("Browser");
    desktop.openAppWindow("App Manager");
    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mx, my;
                SDL_GetMouseState(&mx, &my);
                // Simple click detection for desktop app icons (hardcoded regions for demo)
                // App Manager
                if (mx > 40 && mx < 104 && my > 80 && my < 144) {
                    std::cout << "[System] Launching App Manager...\n";
                    desktop.openAppWindow("App Manager");
                } 
                // Browser
                else if (mx > 140 && mx < 204 && my > 80 && my < 144) {
                    std::cout << "[System] Launching Browser...\n";
                    desktop.openAppWindow("Browser");
                } 
                // File Explorer
                else if (mx > 240 && mx < 304 && my > 80 && my < 144) {
                    std::cout << "[System] Launching File Explorer...\n";
                    desktop.openAppWindow("File Manager");
                }
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