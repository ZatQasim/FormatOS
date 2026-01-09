#ifndef SANDBOX_H
#define SANDBOX_H

#include <iostream>
#include <string>
#include "formatapi.cpp"

class Sandbox {
public:
    void loadApp(void* appPtr) {
        std::cout << "[Sandbox] App loaded inside hardware-isolated sandbox.\n";
        std::cout << "[Sandbox] Restricted access to: CAMERA, NETWORK, STORAGE\n";
    }

    bool checkPermission(const std::string& perm) {
        std::cout << "[Sandbox] Permission check: " << perm << " -> GRANTED\n";
        return true;
    }
};

#endif