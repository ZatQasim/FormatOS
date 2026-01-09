#ifndef SANDBOX_H
#define SANDBOX_H

#include <iostream>
#include <string>
#include "formatapi.cpp"

class Sandbox {
public:
    void loadApp(void* appPtr) {
        std::cout << "[Sandbox] App loaded inside sandbox.\n";

        // Example: limit access to system
        std::cout << "[Sandbox] Restricting app access to system APIs...\n";

        // Simulate app calling FormatAPI
        FormatAPI api;
        api.showMessage("Hello from sandboxed app!");
    }
};

#endif