#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>

class Desktop {
public:
    void login(std::string u, std::string p) { std::cout << "Desktop: Logged in as " << u << std::endl; }
    void notify(std::string msg) { std::cout << "Desktop: " << msg << std::endl; }
    void openAppWindow(std::string app) { std::cout << "Desktop: Opening " << app << std::endl; }
    
    void render(SDL_Renderer* renderer) {
        // Dark background
        SDL_SetRenderDrawColor(renderer, 26, 29, 33, 255);
        SDL_RenderClear(renderer);

        // Sidebar/Navbar
        SDL_SetRenderDrawColor(renderer, 33, 37, 41, 255);
        SDL_Rect navbar = {0, 0, 1024, 60};
        SDL_RenderFillRect(renderer, &navbar);

        // Cards (Layout containers)
        SDL_SetRenderDrawColor(renderer, 36, 40, 45, 255);
        SDL_Rect trafficCard = {20, 80, 480, 200};     // Real-time Traffic Monitor
        SDL_Rect statsCard = {520, 80, 480, 200};      // System Stats
        SDL_Rect threatCard = {20, 300, 980, 200};     // Security Threat Report
        SDL_Rect scannerCard = {20, 520, 980, 220};    // Live Packet Scanner
        
        SDL_RenderFillRect(renderer, &trafficCard);
        SDL_RenderFillRect(renderer, &statsCard);
        SDL_RenderFillRect(renderer, &threatCard);
        SDL_RenderFillRect(renderer, &scannerCard);

        // --- Traffic Monitor (Real-time graph bars) ---
        SDL_SetRenderDrawColor(renderer, 13, 110, 253, 255); // Blue
        for(int i=0; i<15; i++) {
            SDL_Rect bar = {40 + (i*30), 240 - (rand()%100), 20, 0};
            bar.h = 240 - bar.y;
            SDL_RenderFillRect(renderer, &bar);
        }

        // --- Security Threat Report (Rows) ---
        SDL_SetRenderDrawColor(renderer, 220, 53, 69, 255); // Red for threats
        for(int i=0; i<3; i++) {
            SDL_Rect threatRow = {40, 340 + (i*40), 940, 2};
            SDL_RenderFillRect(renderer, &threatRow);
        }

        // --- Live Packet Scanner (Flow simulation) ---
        SDL_SetRenderDrawColor(renderer, 25, 135, 84, 255); // Green for active packets
        for(int i=0; i<10; i++) {
            SDL_Rect packet = {40 + (rand()%900), 550 + (rand()%150), 10, 10};
            SDL_RenderFillRect(renderer, &packet);
        }

        // Navbar Title
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect titlePlaceholder = {20, 20, 150, 20};
        SDL_RenderFillRect(renderer, &titlePlaceholder);
    }
};
