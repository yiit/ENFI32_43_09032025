# ESPEasy Custom Build - ENFI32

ESP32-S3 16MB/8MB için özelleştirilmiş ESPEasy firmware.

## 🎯 Özellikler

- ✅ **P130 Serial Auto-Detection**: CONFIG_PORT tabanlı otomatik serial port seçimi
- ✅ **LVGL I2C Fix**: Soft reset sonrası I2C touch controller düzgün başlatılması
- ✅ **PanelLan BOARD_SC07**: 800x480 LCD + CST3240 touch
- ✅ **Custom Plugins**: P120 (FYZ), P130 (EYZ), P140 (IND)

## 🚀 Quick Start

### Yöntem 1: Local Build (Önerilen - Hızlı)

```powershell
# 1. Virtual environment oluştur (ilk kez)
python -m venv .venv
.venv\Scripts\activate
pip install -r requirements.txt  # platformio 6.1.18, cryptography 46.0.3

# 2. Build yap
.\build.ps1

# 3. Upload et
$env:PLATFORMIO_CORE_DIR=".pio"
.venv\Scripts\pio.exe run --target upload -e custom_ESP32s3_16M8M_LittleFS_CDC --upload-port COM29
```

### Yöntem 2: Docker Build (Portable - İzole)

```powershell
# 1. Docker Desktop'ı başlat

# 2. Build yap
.\build.ps1 docker

# 3. Upload (Windows'ta lokal gerekir)
.venv\Scripts\pio.exe run --target upload -e custom_ESP32s3_16M8M_LittleFS_CDC --upload-port COM29
```

## 📁 Proje Yapısı

```
ESPEasy09032025/
├── .venv/              # Python virtual environment (local build)
├── .pio/               # PlatformIO core & cache (local build)
├── src/                # Kaynak kodlar
│   ├── main.cpp        # Ana program
│   ├── _P120_FYZ_Fis_Yazici.ino
│   ├── _P130_EYZ_Etiket_Yazici.ino
│   └── _P140_IND.ino
├── lib/                # Kütüphaneler (LovyanGFX, LVGL, etc.)
├── platformio.ini      # Build konfigürasyonu
├── build.ps1           # Build helper script
├── Dockerfile          # Docker container tanımı
└── docker-compose.yml  # Docker orchestration
```

## 🔧 Build Modları Karşılaştırma

| Özellik | Local (.venv + .pio) | Docker Container |
|---------|---------------------|------------------|
| **Hız** | ⚡ Çok Hızlı | 🐌 Yavaş (ilk build) |
| **Kurulum** | 🔧 Python + PlatformIO | 🐳 Sadece Docker |
| **İzolasyon** | ⚠️ Sistem paylaşımlı | ✅ Tam izole |
| **USB Upload** | ✅ Direkt çalışır | ❌ Karmaşık |
| **IDE Support** | ✅ VS Code entegre | ⚠️ Sınırlı |
| **Taşınabilirlik** | ⚠️ Python versiyonu gerekli | ✅ Her sistemde aynı |
| **Cache** | ✅ Lokal disk | ✅ Docker volume |
| **CI/CD** | ⚠️ Setup gerekli | ✅ Hazır |
| **Disk Kullanımı** | 📊 ~2GB | 📊 ~3GB |

### 💡 Hangi Modu Kullanmalıyım?

- **Günlük Development**: → `.\build.ps1` (Local, hızlı)
- **Farklı Bilgisayarda Build**: → `.\build.ps1 docker` (Portable)
- **CI/CD Pipeline**: → Docker (GitHub Actions)
- **Temiz Environment Test**: → Docker (izole)

## 📝 Build Komutları

```powershell
# Local build (önerilen)
.\build.ps1                    # Normal build
.\build.ps1 local -Clean       # Clean build

# Docker build (portable)
.\build.ps1 docker             # Normal build
.\build.ps1 docker -Clean      # Clean build

# Manuel PlatformIO
$env:PLATFORMIO_CORE_DIR=".pio"
.venv\Scripts\pio.exe run -e custom_ESP32s3_16M8M_LittleFS_CDC

# Docker manuel
docker compose run --rm espeasy-build pio run -e custom_ESP32s3_16M8M_LittleFS_CDC
```

## 🐛 Sorun Giderme

### Local Build Sorunları

```powershell
# Virtual environment eksik
python -m venv .venv
.venv\Scripts\activate
pip install -r requirements.txt

# Cache temizliği
$env:PLATFORMIO_CORE_DIR=".pio"
.venv\Scripts\pio.exe run -e custom_ESP32s3_16M8M_LittleFS_CDC --target clean
```

### Docker Build Sorunları

```powershell
# Docker Desktop çalışmıyor
# → Docker Desktop'ı manuel başlat

# Cache temizliği
docker compose down -v
docker compose build --no-cache
```

## 🔄 Git Workflow

```powershell
# Değişiklikleri kaydet
git add .
git commit -m "Açıklama"
git push

# GitHub'dan güncelleme çek
git pull
```

## 📚 Dokümantasyon

- [DOCKER.md](DOCKER.md) - Docker kullanım detayları
- [README.md](README.md) - Orijinal ESPEasy README
- [ESPEasy Documentation](https://espeasy.readthedocs.io/)
- [PlatformIO Docs](https://docs.platformio.org/)

## ⚙️ Hardware

- **MCU**: ESP32-S3-WROOM-1 (16MB Flash, 8MB PSRAM)
- **Display**: PanelLan BOARD_SC07 (800x480 RGB)
- **Touch**: CST3240 I2C
- **Serial**: USB CDC (Serial0), UART1 (GPIO43/44), UART2 (GPIO17/18)

## 🔧 Yapılan Değişiklikler

### 1. P130 Serial Auto-Detection
- **Sorun**: Serial port hardcoded Serial1'di, web UI'dan seçim çalışmıyordu
- **Çözüm**: CONFIG_PORT tabanlı otomatik port seçimi (P020 pattern)
- **Dosya**: `src/_P130_EYZ_Etiket_Yazici.ino`

### 2. LVGL I2C Touch Fix
- **Sorun**: Soft reset sonrası touch çalışmıyor, power cycle sonrası düzeliyor
- **Çözüm**: `tft.begin()` uncomment (I2C bus initialization)
- **Dosya**: `src/main.cpp`

### 3. Container-like Isolation
- **Local**: `.venv` + `.pio` (self-contained Python + PlatformIO)
- **Docker**: Multi-stage Dockerfile (küçük image, hızlı build)
- **Helper**: `build.ps1` (tek komut ile her iki mod)

## 📄 License

Bu proje ESPEasy tabanlıdır - [License.txt](License.txt) dosyasına bakın.

## 📧 Contact

- **GitHub**: [@yiit](https://github.com/yiit)
- **Repository**: [ENFI32_43_09032025](https://github.com/yiit/ENFI32_43_09032025)
