import os
import subprocess
import json
from flask import Flask, render_template, jsonify, request

app = Flask(__name__)

from network.monitor import get_interfaces_real, get_stats_real

@app.route('/')
def index():
    return render_template('index.html', interfaces=get_interfaces_real(), stats=get_stats_real())

@app.route('/api/config', methods=['POST'])
def update_config():
    data = request.json
    # Logic to update NAT/Firewall would go here
    return jsonify({"status": "success", "message": "Routing configuration updated"})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
