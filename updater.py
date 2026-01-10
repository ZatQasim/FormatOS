import os
import requests
import zipfile
import shutil
import datetime

VERSION_FILE = "version.txt"
UPDATE_URL = "http://0.0.0.0:5000/api/check_update"

def get_current_version():
    if os.path.exists(VERSION_FILE):
        with open(VERSION_FILE, 'r') as f:
            return f.read().strip()
    return "1.0.0"

def check_for_updates():
    current_version = get_current_version()
    try:
        response = requests.get(f"{UPDATE_URL}?version={current_version}", timeout=5)
        if response.status_code == 200:
            update_info = response.json()
            if update_info.get("update_available"):
                print(f"Update available: {update_info['version']}")
                return update_info
    except Exception as e:
        print(f"Update check failed: {e}")
    return None

def apply_update(download_url):
    print("Downloading update...")
    try:
        response = requests.get(download_url, stream=True)
        if response.status_code == 200:
            with open("update.zip", 'wb') as f:
                for chunk in response.iter_content(chunk_size=8192):
                    f.write(chunk)
            
            print("Extracting update...")
            with zipfile.ZipFile("update.zip", 'r') as zip_ref:
                zip_ref.extractall(".")
            
            os.remove("update.zip")
            print("Update applied successfully.")
            return True
    except Exception as e:
        print(f"Failed to apply update: {e}")
    return False

if __name__ == "__main__":
    update = check_for_updates()
    if update:
        apply_update(update["download_url"])
