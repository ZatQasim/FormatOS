#include "bootloader/boot.cpp"
#include "linux_kernel/kernel_main.cpp"
#include "services/recovery.cpp"
#include "runtime/app_loader.cpp"
#include "apps/example_app.cpp"
#include <iostream>

int main() {
    std::cout << "--- FORMAT OS BOOT SEQUENCE ---\n";
    
    // 1. Bootloader & Kernel
    boot();

    // 2. Runtime & Apps
    initAppLoader();
    
    std::cout << "\n--- LOADING USER ENVIRONMENT ---\n";
    ExampleApp* app = new ExampleApp();
    app->run();
    delete app;

    std::cout << "\n--- SHUTDOWN SEQUENCE ---\n";
    std::cout << "[System] All processes terminated. Syncing disks...\n";
    std::cout << "[System] Power down.\n";

    return 0;
}