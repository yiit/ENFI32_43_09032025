# ESPEasy Build Container - Multi-stage build
FROM python:3.11-slim as builder

# Sistem bağımlılıklarını kur (sadece build için gerekli olanlar)
RUN apt-get update && apt-get install -y \
    git \
    wget \
    curl \
    build-essential \
    libusb-1.0-0 \
    libffi-dev \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

# Çalışma dizini
WORKDIR /workspace

# Önce requirements.txt kopyala (cache için)
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

# Runtime image
FROM python:3.11-slim

# Runtime bağımlılıkları (daha hafif)
RUN apt-get update && apt-get install -y \
    git \
    libusb-1.0-0 \
    && rm -rf /var/lib/apt/lists/*

# Python paketlerini builder'dan kopyala
COPY --from=builder /usr/local/lib/python3.11/site-packages /usr/local/lib/python3.11/site-packages
COPY --from=builder /usr/local/bin /usr/local/bin

# Çalışma dizini
WORKDIR /workspace

# PlatformIO cache için volume mount point
VOLUME ["/workspace/.pio"]

# Environment variables
ENV PLATFORMIO_CORE_DIR=/workspace/.pio \
    PYTHONUNBUFFERED=1

# Default komut (interactive shell)
CMD ["bash"]
