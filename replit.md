# FormatOS

## Overview

FormatOS is a modular operating system project built on a Linux kernel foundation. It consists of two main components:

1. **Core OS Layer** - A C++ based system with custom runtime, UI layer, sandboxed applications, and drivers. Uses SDL2 for graphics rendering.

2. **Network Dashboard** - A Python Flask web application that provides real-time network monitoring, routing status, and security threat detection.

The project aims to provide advanced network routing, interface management, and system configuration tools with a focus on modularity and security (SELinux hardening, app sandboxing, AES-256 encryption).

## User Preferences

Preferred communication style: Simple, everyday language.

## System Architecture

### Frontend Architecture
- **Web Dashboard**: Flask with Jinja2 templates, Bootstrap 5 for styling
- **Dark theme UI** with responsive card-based layout
- **OS UI Layer**: SDL2-based graphics (SDL2_image, SDL2_ttf, SDL2_mixer) compiled via C++

### Backend Architecture
- **Dashboard Server**: Python Flask application in `dashboard/app.py`
- **Network Monitoring**: Python module using `psutil` for real-time interface stats and threat detection
- **High-Performance Core**: C++ compiled binary (`network/routing_core`) for routing operations
- **App Runtime**: C++ based app loader with sandboxing via FormatAPI

### Configuration Management
- `config/system_config.json` - OS settings (resolution, theme, security, boot options)
- `config/app_config.json` - Application registry with auto-start preferences

### Build System
- C++ compilation via g++ with SDL2 libraries
- npm script `dev` handles compilation and execution
- Python Flask server runs independently

### Security Model
- SELinux kernel hardening
- Application sandboxing
- Secure boot support
- Connection monitoring for unauthorized port access

## External Dependencies

### Python Packages
- **Flask** - Web framework for dashboard
- **psutil** - System and network monitoring

### C++ Libraries
- **SDL2** - Core graphics library
- **SDL2_image** - Image loading
- **SDL2_ttf** - Font rendering
- **SDL2_mixer** - Audio support

### Frontend CDN
- **Bootstrap 5** - CSS framework (loaded via CDN)

### System Requirements
- Linux kernel with `/proc/sys/net/ipv4/ip_forward` for routing status
- Network interfaces accessible via standard Linux APIs