#include <iostream>
#include <string>
#include "../runtime/formatapi.cpp"
#include "../ui/desktop.cpp"
#include "../ui/taskbar.cpp"

class Settings {
private:
    FormatAPI api;
    Desktop desktop;
    Taskbar taskbar;

public:
    void run() {
        std::cout << "[Settings] Opening Settings...\n";

        desktop.openAppWindow("Settings");
        taskbar.addApp("Settings");

        std::cout << "[Settings] Options available:\n";
        std::cout << " 1. Display\n 2. Network\n 3. Apps\n 4. About\n";

        api.showMessage("Settings ready for changes.");
    }
};

int main() {
    Settings settings;
    settings.run();
    return 0;
}