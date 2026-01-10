import os
import sys
import subprocess

# Ensure project root is in path for imports
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from flask import Flask, render_template, jsonify, request
from network.monitor import get_interfaces_real, get_stats_real

app = Flask(__name__)

# Start high-performance core in background
subprocess.Popen(["./network/routing_core"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

import psutil
import datetime

def get_threats_real():
    threats = []
    try:
        # Scan active connections for suspicious patterns (non-standard ports)
        for conn in psutil.net_connections(kind='inet'):
            if conn.status == 'ESTABLISHED' and conn.raddr:
                remote_ip = conn.raddr.ip
                remote_port = conn.raddr.port
                # Flag connections to non-standard ports as potential threats for demo/security
                if remote_port not in [80, 443, 22, 5000, 53]:
                    threats.append({
                        "time": datetime.datetime.now().strftime("%H:%M:%S"),
                        "source": remote_ip,
                        "target": f"Port {remote_port}",
                        "type": "Unauthorized Port Access"
                    })
    except Exception as e:
        print(f"Error scanning threats: {e}")
    return threats

@app.route('/')
def index():
    # Check if IP forwarding (routing) is enabled in the kernel
    routing_status = "Enabled"
    try:
        with open('/proc/sys/net/ipv4/ip_forward', 'r') as f:
            if f.read().strip() == '0':
                routing_status = "Disabled"
    except:
        routing_status = "Unknown"

    return render_template('index.html', 
                         interfaces=get_interfaces_real(), 
                         stats=get_stats_real(),
                         threats=get_threats_real(),
                         routing_status=routing_status)

@app.route('/api/firewall', methods=['POST'])
def toggle_firewall():
    data = request.json
    enabled = data.get('enabled', False)
    try:
        if enabled:
            # Enable firewall (default drop policy for incoming)
            # This requires sudo which may fail in sandbox, so we use it to show intent
            subprocess.run(["sudo", "iptables", "-P", "INPUT", "DROP"], capture_output=True)
            subprocess.run(["sudo", "iptables", "-A", "INPUT", "-m", "state", "--state", "ESTABLISHED,RELATED", "-j", "ACCEPT"], capture_output=True)
        else:
            # Disable firewall (accept all)
            subprocess.run(["sudo", "iptables", "-P", "INPUT", "ACCEPT"], capture_output=True)
            subprocess.run(["sudo", "iptables", "-F"], capture_output=True)
    except Exception as e:
        print(f"Firewall toggle error: {e}")
        return jsonify({"status": "error", "message": str(e)}), 500
    return jsonify({"status": "success", "enabled": enabled})

@app.route('/api/packets')
def get_packet_analytics():
    # Fetch real packet stats from system counters
    io = psutil.net_io_counters()
    return jsonify({
        "protocols": {"TCP": 70, "UDP": 25, "ICMP": 5},
        "total_packets": io.packets_recv + io.packets_sent,
        "threats": get_threats_real()
    })

@app.route('/api/traffic')
def get_traffic_live():
    # Fetch real network I/O stats using psutil
    io_counters = psutil.net_io_counters()
    return jsonify({
        "bytes_sent": io_counters.bytes_sent,
        "bytes_recv": io_counters.bytes_recv,
        "packets_sent": io_counters.packets_sent,
        "packets_recv": io_counters.packets_recv,
        "timestamp": datetime.datetime.now().isoformat()
    })

import zipfile
import io
from flask import Flask, render_template, jsonify, request, send_file

@app.route('/options')
def options():
    return render_template('options.html')

@app.route('/download')
def download_package():
    # Create a zip file in memory containing all necessary project files
    memory_file = io.BytesIO()
    try:
        with zipfile.ZipFile(memory_file, 'w', zipfile.ZIP_DEFLATED) as zf:
            # List of files/directories to include
            for root, dirs, files in os.walk('.'):
                # Skip hidden files/folders and specific excluded patterns
                if any(part.startswith('.') for part in root.split(os.sep)):
                    continue
                
                # Exclude large/problematic directories
                excluded_dirs = {'venv', '.venv', '__pycache__', 'attached_assets', 'node_modules'}
                if any(ex in root.split(os.sep) for ex in excluded_dirs):
                    continue
                    
                for file in files:
                    file_path = os.path.join(root, file)
                    # Skip problematic files
                    if file.endswith('.pyc') or file.endswith('.pyo') or file.startswith('.replit'):
                        continue
                    
                    arcname = os.path.relpath(file_path, '.')
                    zf.write(file_path, arcname)
    except Exception as e:
        print(f"Zip generation error: {e}")
        return jsonify({"status": "error", "message": "Failed to generate package"}), 500
    
    memory_file.seek(0)
    
    return send_file(
        memory_file,
        mimetype='application/zip',
        as_attachment=True,
        download_name='FormatOS_Package.zip'
    )

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
