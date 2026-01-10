#!/bin/bash

# --- 1. Auto-Detection of Interfaces ---
# Finds the interface with the default gateway (WAN)
WAN_IF=$(ip route | grep default | awk '{print $5}' | head -n1)
# Finds the first local Ethernet/Bridge interface that isn't the WAN
LAN_IF=$(ip -o link show | awk -F': ' '{print $2}' | grep -vE "lo|$WAN_IF|docker|veth" | head -n1)

echo "Detected WAN: $WAN_IF"
echo "Detected LAN: $LAN_IF"

# --- 2. System Hardening ---
# Enable IP Forwarding
echo 1 > /proc/sys/net/ipv4/ip_forward

# Protect against common attacks
for f in /proc/sys/net/ipv4/conf/*/rp_filter; do echo 1 > $f; done # Reverse Path Filtering (Spoofing)
echo 1 > /proc/sys/net/ipv4/icmp_echo_ignore_broadcasts          # Ignore Broadcast Pings
echo 0 > /proc/sys/net/ipv4/conf/all/accept_source_route        # Disable Source Routing

# --- 3. Flush & Default Policies ---
iptables -F
iptables -t nat -F
iptables -X
iptables -P INPUT DROP
iptables -P FORWARD DROP
iptables -P OUTPUT ACCEPT

# --- 4. Core Rules ---
# Allow Loopback and Established Traffic
iptables -A INPUT -i lo -j ACCEPT
iptables -A INPUT -m state --state ESTABLISHED,RELATED -j ACCEPT
iptables -A FORWARD -m state --state ESTABLISHED,RELATED -j ACCEPT

# --- 5. Incoming Services (Management) ---
# Allow SSH (Port 22) and Web Dash (Port 5000)
iptables -A INPUT -p tcp --dport 22 -j ACCEPT
iptables -A INPUT -p tcp --dport 5000 -j ACCEPT

# --- 6. Routing & NAT (The "Engine") ---
# Allow LAN to access WAN
if [ ! -z "$LAN_IF" ] && [ ! -z "$WAN_IF" ]; then
    iptables -A FORWARD -i $LAN_IF -o $WAN_IF -j ACCEPT
    iptables -t nat -A POSTROUTING -o $WAN_IF -j MASQUERADE
    echo "Routing enabled from $LAN_IF to $WAN_IF"
else
    echo "Error: Could not detect network interfaces for routing."
fi

# --- 7. Logging ---
# Log dropped packets (limited to 5 per minute to prevent log spam)
iptables -A INPUT -m limit --limit 5/min -j LOG --log-prefix "FW-DROP: " --log-level 7

echo "Advanced Firewall Applied Successfully."
