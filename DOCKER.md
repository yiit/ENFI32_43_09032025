# ESPEasy Docker Build Environment

## 🐳 Docker ile Kullanım

### 1. Container'ı Başlat
```powershell
# Docker Compose ile
docker-compose up -d

# Container'a gir
docker exec -it espeasy-build bash
```

### 2. İçeride Build Yap
```bash
# Container içinde
pio run -e custom_ESP32s3_16M8M_LittleFS_CDC
```

### 3. Firmware Dosyasını Al
```powershell
# Host'ta (Windows)
docker cp espeasy-build:/workspace/build_output/bin/firmware.bin .
```

## 🔧 Manuel Docker Kullanımı

### Image Oluştur
```powershell
docker build -t espeasy-build .
```

### Container Çalıştır
```powershell
docker run -it --rm `
  -v ${PWD}:/workspace `
  -v espeasy-pio-cache:/workspace/.pio `
  espeasy-build
```

### Build Komutu (Tek seferde)
```powershell
docker run --rm `
  -v ${PWD}:/workspace `
  -v espeasy-pio-cache:/workspace/.pio `
  espeasy-build `
  pio run -e custom_ESP32s3_16M8M_LittleFS_CDC
```

## 📦 Avantajlar

✅ **Tam İzolasyon**: Sistem Python/PlatformIO'yu etkilemez
✅ **Taşınabilir**: Her sistemde aynı şekilde çalışır
✅ **Temiz**: Host sistemi kirletmez
✅ **Hızlı Setup**: `docker-compose up` ile hazır
✅ **Cache**: PlatformIO cache persistent volume'de

## ⚠️ Windows USB Upload

Windows'ta USB üzerinden upload için:
1. **WSL2 USB/IP**: https://github.com/dorssel/usbipd-win
2. **Docker Desktop**: Device sharing ayarları
3. **Ya da**: Host'ta upload, container'da sadece build

## 🎯 Workflow

```powershell
# 1. Container başlat
docker-compose up -d

# 2. Build yap
docker exec espeasy-build pio run -e custom_ESP32s3_16M8M_LittleFS_CDC

# 3. Firmware al
docker cp espeasy-build:/workspace/build_output/bin/firmware.bin .

# 4. Host'ta upload et
.venv\Scripts\pio.exe run --target upload -e custom_ESP32s3_16M8M_LittleFS_CDC
```

## 🧹 Temizlik

```powershell
# Container'ı durdur ve sil
docker-compose down

# Volume'leri de sil (cache temizliği)
docker-compose down -v

# Image'ı sil
docker rmi espeasy-build
```
