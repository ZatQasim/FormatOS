#include <iostream>

class Desktop {
public:
    void login(std::string u, std::string p) { std::cout << "Desktop: Logged in as " << u << std::endl; }
    void notify(std::string msg) { std::cout << "Desktop: " << msg << std::endl; }
    void render(void* r) { /* Rendering logic */ }
    void openAppWindow(std::string app) { std::cout << "Desktop: Opening " << app << std::endl; }
};
