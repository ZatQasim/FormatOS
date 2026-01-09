#include <iostream>
#include "../linux_kernel/include/kernel.h"  // include kernel interface

void boot() {
    std::cout << "[Bootloader] Starting FormatOS bootloader...\n";

    // Call Linux kernel initialization
    initKernel();

    std::cout << "[Bootloader] Kernel initialized. Handing control to FormatOS runtime...\n";

    // Here you would start services/runtime
    // e.g., initServices(); initRuntime();
}