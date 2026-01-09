#include <iostream>
#include <string>

class FormatUIWindow {
public:
    std::string title;

    FormatUIWindow(const std::string& t) : title(t) {}

    void render() {
        std::cout << "[FormatUI] Rendering window: " << title << "\n";
    }

    void close() {
        std::cout << "[FormatUI] Closing window: " << title << "\n";
    }
};