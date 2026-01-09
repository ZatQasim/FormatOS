#include <iostream>

class SampleModule {
public:
    void init() {
        std::cout << "[Kernel Module] Sample module initialized.\n";
    }

    void shutdown() {
        std::cout << "[Kernel Module] Sample module shutting down.\n";
    }
};