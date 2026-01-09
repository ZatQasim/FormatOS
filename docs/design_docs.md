# FormatOS Design Document

## Overview
FormatOS is a modular OS built on top of a Linux kernel. It uses a custom runtime, UI layer, and sandboxed apps to provide safe and flexible operation.

## Architecture
- Bootloader: Handles loading the kernel and boot configuration.
- Linux Kernel: Base system for drivers, memory, CPU management.
- Services: recovery, remote_console, update_manager, network_manager.
- Runtime: app_loader, sandbox, formatapi.
- UI: window_manager, desktop, taskbar, formatui_integration.
- Apps: example_app, file_explorer, browser, settings.
- Drivers: display, input, storage, network.

## Goals
- Modular design for easy expansion.
- Safe app execution using sandboxing.
- Simple UI integration with FormatUI.