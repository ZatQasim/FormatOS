#include <iostream>
#include <string>

class FormatUIWidget {
public:
    std::string type;

    FormatUIWidget(const std::string& t) : type(t) {}

    void render() {
        std::cout << "[FormatUI] Rendering widget of type: " << type << "\n";
    }

    void update(const std::string& data) {
        std::cout << "[FormatUI] Updating widget with data: " << data << "\n";
    }
};