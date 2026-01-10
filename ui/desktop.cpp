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
            int h = 40 + (rand() % 100);
            SDL_Rect bar = {40 + (i*30), 250 - h, 20, h};
            SDL_RenderFillRect(renderer, &bar);
        }

        // --- Security Threat Report (Rows) ---
        SDL_SetRenderDrawColor(renderer, 220, 53, 69, 255); // Red for threats
        for(int i=0; i<3; i++) {
            SDL_Rect threatRow = {40, 340 + (i*50), 940, 30};
            SDL_RenderFillRect(renderer, &threatRow);
        }

        // --- Live Packet Scanner (Flow simulation) ---
        SDL_SetRenderDrawColor(renderer, 25, 135, 84, 255); // Green for active packets
        for(int i=0; i<20; i++) {
            SDL_Rect packet = {40 + (rand()%900), 540 + (rand()%180), 8, 8};
            SDL_RenderFillRect(renderer, &packet);
        }

        // Labels / Headers (White placeholders)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 180);
        SDL_Rect label1 = {40, 95, 150, 15};  // Traffic
        SDL_Rect label2 = {540, 95, 150, 15}; // Stats
        SDL_Rect label3 = {40, 315, 200, 15}; // Threats
        SDL_Rect label4 = {40, 535, 200, 15}; // Scanner
        SDL_RenderFillRect(renderer, &label1);
        SDL_RenderFillRect(renderer, &label2);
        SDL_RenderFillRect(renderer, &label3);
        SDL_RenderFillRect(renderer, &label4);

        // Navbar Title
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect titlePlaceholder = {20, 20, 180, 25};
        SDL_RenderFillRect(renderer, &titlePlaceholder);
    }
};
