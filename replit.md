# FormatOS

## Overview

FormatOS is a modular operating system built on top of a Linux kernel. It provides a custom runtime environment, UI layer, and sandboxed application system designed for safe and flexible operation. The OS follows a layered architecture with clear separation between the bootloader, kernel, services, runtime, UI, and applications.

The project is in early development (v0.1-alpha) and aims to be easily expandable through its modular design while maintaining security through application sandboxing.

## User Preferences

Preferred communication style: Simple, everyday language.

## System Architecture

### Layered OS Design

The system follows a traditional OS architecture with distinct layers:

1. **Bootloader** - Custom bootloader that loads the Linux kernel with configurable timeout and boot parameters
2. **Linux Kernel** - Base system (v5.20.0-formatos) for x86_64 architecture handling drivers, memory, and CPU management
3. **Services Layer** - System services including recovery, remote console, update manager, and network manager
4. **Runtime Layer** - Application execution environment with app loader, sandbox, and FormatAPI
5. **UI Layer** - Window manager, desktop, taskbar, and FormatUI integration
6. **Applications** - User-facing apps (file explorer, browser, settings, etc.)

### Application Model

Apps are defined in JSON configuration and written in C++. Key characteristics:
- Apps can be set to auto-start or launch on demand
- Sandboxed execution for security isolation
- FormatAPI provides a standardized interface for apps to interact with the system

### Driver Architecture

Dedicated driver modules for:
- Display output
- Input devices
- Storage access
- Network connectivity

### Configuration-Driven Design

The system uses JSON configuration files throughout:
- `bootloader/boot_config.json` - Kernel path, boot parameters, timeout
- `config/system_config.json` - OS settings, resolution, theme, network options
- `config/app_config.json` - Application registry and startup behavior
- `linux_kernel/kernel_config.json` - Kernel modules, scheduler, logging

## External Dependencies

### Linux Kernel

- Custom kernel build (5.20.0-formatos) for x86_64
- Kernel modules enabled for driver flexibility
- Round-robin default scheduler

### System Services

- **Network Manager** - Network connectivity (enabled by default in config)
- **Update Manager** - System updates (auto-update disabled by default)
- **Remote Console** - Remote access capability
- **Recovery Service** - System recovery functionality

### FormatUI

External UI framework integration for rendering the desktop environment, window management, and application interfaces.