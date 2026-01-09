#include <iostream>
#include <string>

class DisplayDriver {
public:
    void initialize() {
        std::cout << "[Display Driver] Initializing display...\n";
    }

    void drawPixel(int x, int y, std::string color) {
        std::cout << "[Display Driver] Drawing pixel at (" << x << "," << y << ") with color " << color << "\n";
    }

    void renderFrame() {
        std::cout << "[Display Driver] Rendering frame...\n";
    }
};