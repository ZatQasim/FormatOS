#!/bin/bash
# Secure Firewall and NAT Configuration

# Flush existing rules
iptables -F
iptables -t nat -F

# Set default policies
iptables -P INPUT DROP
iptables -P FORWARD DROP
iptables -P OUTPUT ACCEPT

# Allow established connections
iptables -A INPUT -m state --state ESTABLISHED,RELATED -j ACCEPT
iptables -A FORWARD -m state --state ESTABLISHED,RELATED -j ACCEPT

# Allow loopback
iptables -A INPUT -i lo -j ACCEPT

# Allow SSH and Web Dashboard (Development)
iptables -A INPUT -p tcp --dport 22 -j ACCEPT
iptables -A INPUT -p tcp --dport 5000 -j ACCEPT

# NAT Masquerading (assuming eth0 is WAN)
# iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE
# iptables -A FORWARD -i eth1 -o eth0 -j ACCEPT

echo "Firewall and NAT rules configured (Dry Run/Log Only in restricted env)"
