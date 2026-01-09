#include <iostream>
#include "include/kernel.h"
#include "modules/sample_module.cpp"

// Make sure these are global functions callable from bootloader
void loadKernelModules() {
    std::cout << "[Kernel] Loading kernel modules...\n";
    SampleModule mod;
    mod.init();
}

void initKernel() {
    std::cout << "[Kernel] Linux kernel initialized.\n";
    loadKernelModules();
}

// Optional main for testing kernel independently
/*
int main() {
    std::cout << "[Kernel] Booting Linux Kernel...\n";
    initKernel();
    std::cout << "[Kernel] Handing control to FormatOS bootloader...\n";
    return 0;
}
*/