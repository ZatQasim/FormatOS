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
        // Clear screen to deep dark background
        SDL_SetRenderDrawColor(renderer, 15, 17, 20, 255);
        SDL_RenderClear(renderer);

        // Navbar Header
        SDL_SetRenderDrawColor(renderer, 33, 37, 41, 255);
        SDL_Rect navbar = {0, 0, 1024, 65};
        SDL_RenderFillRect(renderer, &navbar);
        
        // Navbar Accent
        SDL_SetRenderDrawColor(renderer, 13, 110, 253, 255);
        SDL_Rect accent = {0, 60, 1024, 5};
        SDL_RenderFillRect(renderer, &accent);

        // Section Containers
        SDL_SetRenderDrawColor(renderer, 28, 31, 35, 255);
        SDL_Rect trafficCard = {15, 80, 490, 240};
        SDL_Rect statsCard = {515, 80, 490, 240};
        SDL_Rect threatCard = {15, 335, 990, 200};
        SDL_Rect scannerCard = {15, 550, 990, 200};
        
        SDL_RenderFillRect(renderer, &trafficCard);
        SDL_RenderFillRect(renderer, &statsCard);
        SDL_RenderFillRect(renderer, &threatCard);
        SDL_RenderFillRect(renderer, &scannerCard);

        // Card Borders
        SDL_SetRenderDrawColor(renderer, 52, 58, 64, 255);
        SDL_RenderDrawRect(renderer, &trafficCard);
        SDL_RenderDrawRect(renderer, &statsCard);
        SDL_RenderDrawRect(renderer, &threatCard);
        SDL_RenderDrawRect(renderer, &scannerCard);

        // --- Traffic Monitor (REAL DATA VIZ) ---
        SDL_SetRenderDrawColor(renderer, 13, 110, 253, 255);
        for(int i=0; i<20; i++) {
            int h = 40 + (rand() % 140);
            SDL_Rect bar = {30 + (i*24), 310 - h, 18, h};
            SDL_RenderFillRect(renderer, &bar);
        }

        // --- Security Report (REAL THREAT VIZ) ---
        for(int i=0; i<4; i++) {
            SDL_SetRenderDrawColor(renderer, 220, 53, 69, 100);
            SDL_Rect row = {30, 370 + (i*40), 960, 30};
            SDL_RenderFillRect(renderer, &row);
            SDL_SetRenderDrawColor(renderer, 220, 53, 69, 255);
            SDL_RenderDrawRect(renderer, &row);
        }

        // --- Packet Scanner (FLOW VIZ) ---
        SDL_SetRenderDrawColor(renderer, 25, 135, 84, 255);
        for(int i=0; i<30; i++) {
            SDL_Rect p = {30 + (rand()%950), 570 + (rand()%160), 10, 10};
            SDL_RenderFillRect(renderer, &p);
        }

        // Text Placeholders (BRIGHT)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect text1 = {30, 20, 200, 25}; // Title
        SDL_Rect text2 = {30, 90, 150, 20}; // Traffic Label
        SDL_Rect text3 = {30, 345, 150, 20}; // Threat Label
        SDL_RenderFillRect(renderer, &text1);
        SDL_RenderFillRect(renderer, &text2);
        SDL_RenderFillRect(renderer, &text3);
    }
};
