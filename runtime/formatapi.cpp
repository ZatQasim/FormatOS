#ifndef FORMATAPI_H
#define FORMATAPI_H

#include <iostream>
#include <string>

class FormatAPI {
public:
    void showMessage(const std::string& message) {
        std::cout << "[FormatAPI] App says: " << message << "\n";
    }

    void logEvent(const std::string& event) {
        std::cout << "[FormatAPI] Event logged: " << event << "\n";
        // Later: write to logs/system.log
    }

    void requestNetwork(const std::string& data) {
        std::cout << "[FormatAPI] Sending network request: " << data << "\n";
        // Later: interact with network_manager.cpp
    }
};

#endif