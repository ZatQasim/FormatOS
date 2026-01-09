FROM python:3.11-slim

RUN apt-get update && apt-get install -y \
    iptables \
    iproute2 \
    net-tools \
    procps \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .
RUN pip install flask psutil

# Auto-start dashboard and routing services
CMD ["python", "dashboard/app.py"]
