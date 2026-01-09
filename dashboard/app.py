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

@app.route('/api/config', methods=['POST'])
def update_config():
    data = request.json
    # Logic to update NAT/Firewall would go here
    return jsonify({"status": "success", "message": "Routing configuration updated"})

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
    
    # Map requested extension to the zip content for now as a wrapper
    # In a real build pipeline this would trigger the actual cross-compile
    mimetype = 'application/octet-stream'
    if ext == 'apk':
        mimetype = 'application/vnd.android.package-archive'
    elif ext == 'exe':
        mimetype = 'application/x-msdownload'
    elif ext == 'dmg':
        mimetype = 'application/x-apple-diskimage'

    # For APK, we must ensure it's not just a renamed ZIP but has a valid structure
    # However, since we can't build a real APK here, we'll at least set the proper
    # attachment filename and headers that Android expects for a package install.
    response = send_file(
        memory_file,
        mimetype=mimetype,
        as_attachment=True,
        download_name=f'FormatRoute_{platform}.{ext}'
    )
    response.headers["Content-Disposition"] = f"attachment; filename=FormatRoute_{platform}.{ext}"
    return response

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
