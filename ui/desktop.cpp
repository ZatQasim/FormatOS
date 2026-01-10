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

        // Cards
        SDL_SetRenderDrawColor(renderer, 36, 40, 45, 255);
        SDL_Rect card1 = {20, 80, 300, 150};
        SDL_Rect card2 = {340, 80, 660, 150};
        SDL_Rect card3 = {20, 250, 980, 250};
        SDL_Rect card4 = {20, 520, 480, 200};
        SDL_Rect card5 = {520, 520, 480, 200};
        
        SDL_RenderFillRect(renderer, &card1);
        SDL_RenderFillRect(renderer, &card2);
        SDL_RenderFillRect(renderer, &card3);
        SDL_RenderFillRect(renderer, &card4);
        SDL_RenderFillRect(renderer, &card5);

        // Traffic Chart mockup (the blue pulse)
        SDL_SetRenderDrawColor(renderer, 13, 110, 253, 100);
        SDL_Rect chart = {40, 400, 940, 80};
        SDL_RenderFillRect(renderer, &chart);
        
        SDL_SetRenderDrawColor(renderer, 13, 110, 253, 255);
        SDL_RenderDrawLine(renderer, 40, 400, 980, 400);

        // Threat List mockup (red text simulation)
        SDL_SetRenderDrawColor(renderer, 220, 53, 69, 255);
        SDL_Rect threatLine = {40, 600, 440, 2};
        SDL_RenderFillRect(renderer, &threatLine);
    }
};
