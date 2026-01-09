#include <iostream>
#include <string>

class InputDriver {
public:
    void initialize() {
        std::cout << "[Input Driver] Initializing input devices (keyboard, mouse)...\n";
    }

    std::string getKeyPress() {
        // Placeholder: return simulated key press
        std::string key = "A";
        std::cout << "[Input Driver] Key pressed: " << key << "\n";
        return key;
    }

    std::pair<int,int> getMousePosition() {
        // Placeholder: return simulated mouse position
        int x = 100, y = 200;
        std::cout << "[Input Driver] Mouse position: (" << x << "," << y << ")\n";
        return {x, y};
    }
};