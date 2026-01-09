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
                
                // Animation: slide in and fade
                int animOffset = 0;
                if (now - n.startTime < 500) {
                    animOffset = 300 - (int)((now - n.startTime) * 0.6);
                }
                
                int x = screenWidth - 260 + animOffset;
                SDL_SetRenderDrawColor(renderer, 35, 35, 40, 240);
                SDL_Rect box = {x, yOffset, 250, 65};
                SDL_RenderFillRect(renderer, &box);
                
                SDL_SetRenderDrawColor(renderer, 0, 150, 255, 255);
                SDL_Rect accent = {x, yOffset, 4, 65};
                SDL_RenderFillRect(renderer, &accent);
                
                yOffset += 75;
            }
        }
    }
};

#endif