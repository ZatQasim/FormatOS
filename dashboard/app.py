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
    return render_template('index.html', 
                         interfaces=get_interfaces_real(), 
                         stats=get_stats_real(),
                         threats=get_threats_real())

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
def download_script():
    platform = request.args.get('platform', 'pc')
    ext = request.args.get('ext', 'zip')
    
    # Create a zip file in memory containing all necessary project files
    memory_file = io.BytesIO()
    with zipfile.ZipFile(memory_file, 'w', zipfile.ZIP_DEFLATED) as zf:
        # List of files/directories to include (recursive for directories)
        for root, dirs, files in os.walk('.'):
            # Skip hidden files/folders and replit specific stuff
            if any(part.startswith('.') for part in root.split(os.sep)):
                continue
            for file in files:
                file_path = os.path.join(root, file)
                # Remove leading './'
                arcname = os.path.relpath(file_path, '.')
                zf.write(file_path, arcname)
    
    memory_file.seek(0)
    
    mimetype = 'application/octet-stream'
    download_name = f'FormatOS_{platform}.{ext}'
    
    if ext == 'apk':
        mimetype = 'application/vnd.android.package-archive'
        # Serve the generated binary as the APK to ensure it's a valid binary format
        return send_file(
            'android_installer.bin',
            mimetype=mimetype,
            as_attachment=True,
            download_name=download_name
        )
    elif ext == 'exe':
        mimetype = 'application/x-msdownload'
    elif ext == 'dmg':
        mimetype = 'application/x-apple-diskimage'

    return send_file(
        memory_file,
        mimetype=mimetype,
        as_attachment=True,
        download_name=download_name
    )

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
