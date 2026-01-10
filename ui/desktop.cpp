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
        // FORCE CLEAR
        SDL_SetRenderDrawColor(renderer, 20, 22, 25, 255);
        SDL_RenderClear(renderer);

        // Navbar Header (Vibrant Blue Accent)
        SDL_SetRenderDrawColor(renderer, 13, 110, 253, 255);
        SDL_Rect navbar = {0, 0, 1024, 70};
        SDL_RenderFillRect(renderer, &navbar);

        // Traffic Card (Large & Distinct)
        SDL_SetRenderDrawColor(renderer, 35, 39, 44, 255);
        SDL_Rect trafficCard = {30, 100, 460, 250};
        SDL_RenderFillRect(renderer, &trafficCard);
        
        // Traffic Bars (Animated-like simulation)
        SDL_SetRenderDrawColor(renderer, 0, 123, 255, 255);
        for(int i=0; i<15; i++) {
            int h = 50 + (rand() % 150);
            SDL_Rect bar = {50 + (i*28), 330 - h, 22, h};
            SDL_RenderFillRect(renderer, &bar);
        }

        // Threat Card (High Alert Red)
        SDL_SetRenderDrawColor(renderer, 45, 20, 20, 255);
        SDL_Rect threatCard = {510, 100, 480, 250};
        SDL_RenderFillRect(renderer, &threatCard);
        
        SDL_SetRenderDrawColor(renderer, 220, 53, 69, 255);
        for(int i=0; i<4; i++) {
            SDL_Rect threatRow = {530, 130 + (i*50), 440, 35};
            SDL_RenderFillRect(renderer, &threatRow);
        }

        // Packet Scanner (Green Flow)
        SDL_SetRenderDrawColor(renderer, 30, 35, 30, 255);
        SDL_Rect scannerCard = {30, 380, 960, 350};
        SDL_RenderFillRect(renderer, &scannerCard);
        
        SDL_SetRenderDrawColor(renderer, 40, 167, 69, 255);
        for(int i=0; i<40; i++) {
            SDL_Rect dot = {50 + (rand()%920), 400 + (rand()%310), 12, 12};
            SDL_RenderFillRect(renderer, &dot);
        }

        // Section Titles (White Blocks)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect t1 = {50, 25, 250, 30}; // Logo/Title
        SDL_Rect t2 = {50, 110, 180, 20}; // Traffic Label
        SDL_Rect t3 = {530, 110, 180, 20}; // Threat Label
        SDL_Rect t4 = {50, 390, 250, 20}; // Scanner Label
        SDL_RenderFillRect(renderer, &t1);
        SDL_RenderFillRect(renderer, &t2);
        SDL_RenderFillRect(renderer, &t3);
        SDL_RenderFillRect(renderer, &t4);
    }
};
