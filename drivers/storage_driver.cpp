#include <iostream>
#include <string>
#include <vector>

class StorageDriver {
public:
    void initialize() {
        std::cout << "[Storage Driver] Initializing storage devices...\n";
    }

    std::vector<std::string> listFiles(const std::string& path) {
        std::cout << "[Storage Driver] Listing files in " << path << "\n";
        // Placeholder files
        std::vector<std::string> files = {"file1.txt", "file2.png", "file3.mp4"};
        for (auto &f : files) std::cout << " - " << f << "\n";
        return files;
    }

    void writeFile(const std::string& path, const std::string& content) {
        std::cout << "[Storage Driver] Writing to " << path << ": " << content << "\n";
    }

    std::string readFile(const std::string& path) {
        std::string content = "Sample file content";
        std::cout << "[Storage Driver] Reading from " << path << ": " << content << "\n";
        return content;
    }
};