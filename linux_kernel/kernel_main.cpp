#include <iostream>
#include "include/kernel.h"
#include "modules/sample_module.cpp"

// Make sure these are global functions callable from bootloader
void kernelMain() {
    std::cout << "[Kernel] Main entry point reached.\n";
    initKernel();
}

void loadKernelModules() {
    std::cout << "[Kernel] Loading kernel modules...\n";
    SampleModule mod;
    mod.init();
}

void initSystemServices() {
    std::cout << "[Kernel] Starting init system (PID 1)...\n";
    std::cout << "[Kernel] Services started reliably.\n";
}

void powerManagement(const std::string& action) {
    std::cout << "[Kernel] Power Management: " << action << " initiated...\n";
}

void initKernel() {
    std::cout << "[Kernel] Linux kernel (LTS) initialized.\n";
    loadKernelModules();
    initSystemServices();
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