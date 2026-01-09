#!/bin/bash
# FormatRoute Android Termux Setup Script

echo "Installing FormatRoute on Android via Termux..."

# Install dependencies
pkg update
pkg install -y python clang make binutils

# Create project directory
mkdir -p ~/formatroute
cd ~/formatroute

# Install Python requirements
pip install flask psutil

# Compile high-performance core
g++ -O3 network/core.cpp -o network/routing_core

echo "Setup complete! Run 'python dashboard/app.py' to start."
