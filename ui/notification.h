#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <iostream>

struct Notification {
    std::string message;
    Uint32 startTime;
    bool active;
};

class NotificationManager {
private:
    std::vector<Notification> notifications;

public:
    void send(const std::string& msg) {
        notifications.push_back({msg, SDL_GetTicks(), true});
        std::cout << "[Notification] " << msg << std::endl;
    }

    void render(SDL_Renderer* renderer, int screenWidth) {
        Uint32 now = SDL_GetTicks();
        int yOffset = 20;
        for (auto& n : notifications) {
            if (n.active) {
                if (now - n.startTime > 5000) {
                    n.active = false;
                    continue;
                }
                // Animation: slide in from right
                int x = screenWidth - 260;
                SDL_SetRenderDrawColor(renderer, 45, 45, 50, 230);
                SDL_Rect box = {x, yOffset, 250, 60};
                SDL_RenderFillRect(renderer, &box);
                
                SDL_SetRenderDrawColor(renderer, 0, 200, 255, 255);
                SDL_Rect accent = {x, yOffset, 5, 60};
                SDL_RenderFillRect(renderer, &accent);
                
                yOffset += 70;
            }
        }
    }
};

#endif