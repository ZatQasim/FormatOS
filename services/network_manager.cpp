#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <iostream>

void initNetworkManager() {
    std::cout << "[Network Manager] Initializing network stack...\n";
    std::cout << "[Network Manager] Searching for interfaces...\n";
    std::cout << "[Network Manager] eth0: Connected.\n";
}

#endif