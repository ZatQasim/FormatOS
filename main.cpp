#include "bootloader/boot.cpp"
#include "linux_kernel/kernel_main.cpp"
#include "services/recovery.cpp"
#include "runtime/app_loader.cpp"
#include "apps/example_app.cpp"

int main() {
    // Start bootloader (calls initKernel)
    boot();

    // Start recovery service
    initRecoveryService();

    // Load and run example app
    AppLoader loader;
    // ExampleApp now should inherit from App if we want to use AppLoader
    // For now let's just run it directly as the user code had it
    ExampleApp* app = new ExampleApp();
    app->run();

    return 0;
}