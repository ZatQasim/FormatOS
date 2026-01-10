#!/bin/bash
# FormatOS Installer for Linux
echo "Installing FormatOS for Linux..."
sudo apt-get update && sudo apt-get install -y python3-pip python3-venv g++ iptables
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