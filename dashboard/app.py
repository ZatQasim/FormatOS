import os
import subprocess
import json
from flask import Flask, render_template, jsonify, request

app = Flask(__name__)

# Mock data for demonstration as we don't have root for actual iptables/ip cmds
def get_interfaces():
    try:
        # In a real system we would use 'ip -j addr'
        return {"eth0": {"ip": "192.168.1.1", "status": "up"}, "lo": {"ip": "127.0.0.1", "status": "up"}}
    except:
        return {}

def get_stats():
    return {"rx": "1.2GB", "tx": "850MB", "active_clients": 5}

@app.route('/')
def index():
    return render_template('index.html', interfaces=get_interfaces(), stats=get_stats())

@app.route('/api/config', methods=['POST'])
def update_config():
    data = request.json
    # Logic to update NAT/Firewall would go here
    return jsonify({"status": "success", "message": "Routing configuration updated"})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
