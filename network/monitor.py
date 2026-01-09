import psutil
import socket
import fcntl
import struct
import array

def get_interfaces_real():
    interfaces = {}
    addrs = psutil.net_if_addrs()
    stats = psutil.net_if_stats()
    
    for name, addr_list in addrs.items():
        ip = "N/A"
        for addr in addr_list:
            if addr.family == socket.AF_INET:
                ip = addr.address
                break
        
        status = "down"
        if name in stats and stats[name].isup:
            status = "up"
            
        interfaces[name] = {
            "ip": ip,
            "status": status,
            "speed": stats[name].speed if name in stats else 0
        }
    return interfaces

def get_stats_real():
    io_counters = psutil.net_io_counters()
    return {
        "rx": f"{io_counters.bytes_recv / (1024*1024):.2f} MB",
        "tx": f"{io_counters.bytes_sent / (1024*1024):.2f} MB",
        "active_clients": 0 # This would need ARP table parsing or similar
    }
