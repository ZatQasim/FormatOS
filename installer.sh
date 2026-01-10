#!/bin/bash
# FormatOS Installer for Windows (WSL2), Mac, and Android (Termux)

echo "FormatOS Installation started..."

# Detect Platform
OS_TYPE="unknown"
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    if [ -f /proc/version ] && grep -q "Microsoft" /proc/version; then
        OS_TYPE="windows_wsl"
    else
        OS_TYPE="linux"
    fi
elif [[ "$OSTYPE" == "darwin"* ]]; then
    OS_TYPE="mac"
elif [[ "$OSTYPE" == "linux-android"* ]] || [ -d "/data/data/com.termux" ]; then
    OS_TYPE="android"
fi

echo "Detected platform: $OS_TYPE"

case $OS_TYPE in
    "windows_wsl")
        echo "Installing for Windows (WSL2)..."
        sudo apt-get update && sudo apt-get install -y python3-pip python3-venv g++ iptables
        ;;
    "mac")
        echo "Installing for macOS..."
        if ! command -v brew &> /dev/null; then
            echo "Homebrew not found. Please install it first: https://brew.sh/"
            exit 1
        fi
        brew install python g++
        ;;
    "android")
        echo "Installing for Android (Termux)..."
        pkg update && pkg install -y python clang make binutils
        ;;
    *)
        echo "Unsupported platform. Attempting generic Linux install..."
        sudo apt-get update && sudo apt-get install -y python3-pip python3-venv g++ iptables
        ;;
esac

# Common Setup
mkdir -p ~/formatos
cp -r . ~/formatos
cd ~/formatos

if [ "$OS_TYPE" == "android" ]; then
    pip install flask psutil
else
    python3 -m venv .venv
    source .venv/bin/activate
    pip install flask psutil
fi

# Compile Core
g++ -O3 network/core.cpp -o network/routing_core 2>/dev/null || echo "Note: Core compilation skipped or failed."

echo "------------------------------------------------"
echo "FormatOS Installation Complete!"
echo "To start the dashboard, run:"
if [ "$OS_TYPE" == "android" ]; then
    echo "python dashboard/app.py"
else
    echo "source .venv/bin/activate && python dashboard/app.py"
fi
echo "------------------------------------------------"
