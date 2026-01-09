#!/bin/bash
# FormatRoute Setup Script for Linux/WSL2

echo "Installing FormatRoute Routing Software..."

# Install dependencies
sudo apt-get update
sudo apt-get install -y python3-pip python3-venv g++ iptables

# Create project directory
mkdir -p ~/formatroute
cd ~/formatroute

# Create virtual environment
python3 -m venv .venv
source .venv/bin/activate

# Download source (simplified for instruction)
echo "Please ensure you have copied the FormatRoute files to $(pwd)"

# Install Python requirements
pip install flask psutil

# Compile high-performance core
g++ -O3 network/core.cpp -o network/routing_core

# Setup systemd service (Linux only)
if [ -d "/etc/systemd/system" ]; then
    sudo cp scripts/formatroute.service /etc/systemd/system/
    sudo systemctl daemon-reload
    sudo systemctl enable formatroute
    sudo systemctl start formatroute
    echo "Service started and enabled on boot."
fi

echo "Setup complete! Dashboard available at http://localhost:5000"
