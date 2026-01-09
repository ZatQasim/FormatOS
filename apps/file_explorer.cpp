#include <iostream>
#include <vector>
#include <string>
#include "../runtime/formatapi.cpp"
#include "../ui/desktop.cpp"
#include "../ui/taskbar.cpp"

class FileExplorer {
private:
    FormatAPI api;
    Desktop desktop;
    Taskbar taskbar;
    std::vector<std::string> files;

public:
    void run() {
        std::cout << "[File Explorer] Opening File Explorer...\n";

        files = {"Document1.txt", "Photo1.png", "Video1.mp4"};

        // Open window
        desktop.openAppWindow("File Explorer");
        taskbar.addApp("File Explorer");

        // List files
        std::cout << "[File Explorer] Files in directory:\n";
        for (auto &f : files) {
            std::cout << " - " << f << "\n";
        }

        api.showMessage("File Explorer is ready.");
    }
};

int main() {
    FileExplorer explorer;
    explorer.run();
    return 0;
}