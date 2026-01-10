#!/bin/bash
# FormatOS Installer for macOS
echo "Installing FormatOS for macOS..."
if ! command -v brew &> /dev/null; then
    echo "Homebrew not found. Please install it: https://brew.sh/"
    exit 1
fi
brew install python g++
INSTALL_DIR="$HOME/formatos"
mkdir -p "$INSTALL_DIR"
cp -rv . "$INSTALL_DIR"
cd "$INSTALL_DIR"
python3 -m venv .venv
source .venv/bin/activate
pip install flask psutil
mkdir -p network
echo "int main() { return 0; }" > network/core.cpp
g++ -O3 network/core.cpp -o network/routing_core
echo "Installation Complete! To start: cd $INSTALL_DIR && source .venv/bin/activate && python dashboard/app.py"