# FormatOS

## Overview

FormatOS is a modular operating system project built on a Linux kernel foundation. It combines:

1. **C++ Core System** - A custom OS runtime with SDL2-based graphical interface, sandboxed applications, and system services
2. **Python Dashboard** - A Flask-based web interface for network monitoring, routing management, and system administration

The project aims to provide full control over Linux-based networking and system configuration with a focus on modularity, security (sandboxing, SELinux hardening, AES-256 encryption), and ease of customization.

## User Preferences

Preferred communication style: Simple, everyday language.

## System Architecture

### Frontend Architecture
- **Web Dashboard**: Flask with Jinja2 templates, Bootstrap 5 for styling
- **Desktop UI**: SDL2-based rendering (SDL2, SDL2_image, SDL2_ttf, SDL2_mixer) compiled from C++
- **Design**: Dark theme UI with responsive layout for the web dashboard

### Backend Architecture
- **Web Server**: Python Flask application (`dashboard/app.py`) serving the monitoring interface
- **Core Runtime**: C++ compiled binary for OS-level operations
- **High-Performance Routing**: Separate binary (`network/routing_core`) launched as background subprocess

### Application Model
- **Modular Apps**: Defined in `config/app_config.json` with paths to C++ source files
- **Sandboxing**: Apps run in isolated environments for security
- **Auto-start**: Configurable per-app launch behavior

### Network Monitoring
- Uses `psutil` library for real-time network interface detection
- Monitors traffic statistics (RX/TX bytes)
- Threat detection by scanning active connections for non-standard ports
- Reads kernel routing status from `/proc/sys/net/ipv4/ip_forward`

### Configuration Management
- JSON-based configuration files in `config/` directory
- `system_config.json`: OS settings, resolution, security options
- `app_config.json`: Application registry and startup preferences

## External Dependencies

### Python Packages
- **Flask**: Web framework for the dashboard
- **psutil**: System and network monitoring
- **Jinja2**: Template rendering (Flask dependency)

### C++ Libraries
- **SDL2**: Core graphics and window management
- **SDL2_image**: Image loading support
- **SDL2_ttf**: TrueType font rendering
- **SDL2_mixer**: Audio playback

### Frontend CDN Resources
- **Bootstrap 5**: CSS framework loaded from cdn.jsdelivr.net

### System Dependencies
- Linux kernel with `/proc` filesystem access
- IP forwarding capability for routing features
- GCC/G++ compiler for C++ components