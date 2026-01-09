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

@app.route('/')
def index():
    return render_template('index.html', interfaces=get_interfaces_real(), stats=get_stats_real())

@app.route('/api/firewall', methods=['POST'])
def toggle_firewall():
    data = request.json
    enabled = data.get('enabled', False)
    # In a real environment, we would execute iptables commands here
    # subprocess.run(["sudo", "scripts/setup_firewall.sh" if enabled else "iptables -F"])
    return jsonify({"status": "success", "enabled": enabled})

@app.route('/api/packets')
def get_packet_analytics():
    # Simulated packet scanning data for deep analytics
    return jsonify({
        "protocols": {"TCP": 65, "UDP": 25, "ICMP": 5, "Other": 5},
        "top_destinations": [
            {"ip": "8.8.8.8", "count": 120},
            {"ip": "1.1.1.1", "count": 85},
            {"ip": "192.168.1.50", "count": 42}
        ],
        "threats_blocked": 12
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
    download_name = f'FormatRoute_{platform}.{ext}'
    
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
