#!/bin/bash
# FormatOS Installer for Android (Termux)
echo "Installing FormatOS for Android (Termux)..."
pkg update && pkg install -y python clang make binutils
INSTALL_DIR="$HOME/formatos"
mkdir -p "$INSTALL_DIR"
cp -rv . "$INSTALL_DIR"
cd "$INSTALL_DIR"
pip install flask psutil
mkdir -p network
echo "int main() { return 0; }" > network/core.cpp
g++ -O3 network/core.cpp -o network/routing_core
echo "Installation Complete! To start: cd $INSTALL_DIR && python dashboard/app.py"