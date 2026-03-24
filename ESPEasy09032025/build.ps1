# ESPEasy Build Helper Script
# Kullanım: .\build.ps1 [local|docker] [clean]

param(
    [Parameter(Position=0)]
    [ValidateSet('local', 'docker', 'help')]
    [string]$Mode = 'local',
    
    [Parameter(Position=1)]
    [switch]$Clean
)

$env_name = "custom_ESP32s3_16M8M_LittleFS_CDC"

function Show-Help {
    Write-Host @"
ESPEasy Build Helper

Kullanım:
  .\build.ps1 [local|docker] [-Clean]

Modlar:
  local   - .venv ve .pio kullanarak lokal build (DEFAULT, HIZLI)
  docker  - Docker container içinde build (PORTABLE, IZOLE)
  help    - Bu yardım mesajını göster

Parametreler:
  -Clean  - Build öncesi temizlik yap

Örnekler:
  .\build.ps1              # Local build (hızlı)
  .\build.ps1 local -Clean # Local clean build
  .\build.ps1 docker       # Docker build (portable)
  .\build.ps1 docker -Clean # Docker clean build

"@ -ForegroundColor Cyan
}

function Build-Local {
    Write-Host "`n🔨 LOCAL BUILD MODE (Fast)" -ForegroundColor Green
    
    # Activate venv
    if (Test-Path ".venv\Scripts\Activate.ps1") {
        Write-Host "✓ Activating Python venv..." -ForegroundColor Yellow
        & .venv\Scripts\Activate.ps1
    } else {
        Write-Host "✗ Virtual environment not found! Run: python -m venv .venv" -ForegroundColor Red
        exit 1
    }
    
    # Set PlatformIO env
    $env:PLATFORMIO_CORE_DIR = ".pio"
    
    if ($Clean) {
        Write-Host "✓ Cleaning build..." -ForegroundColor Yellow
        & .venv\Scripts\pio.exe run -e $env_name --target clean
    }
    
    Write-Host "✓ Building firmware..." -ForegroundColor Yellow
    & .venv\Scripts\pio.exe run -e $env_name
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host "`n✅ BUILD SUCCESS!" -ForegroundColor Green
        Write-Host "Firmware: build_output\bin\firmware.bin" -ForegroundColor Cyan
    } else {
        Write-Host "`n❌ BUILD FAILED!" -ForegroundColor Red
        exit 1
    }
}

function Build-Docker {
    Write-Host "`n🐳 DOCKER BUILD MODE (Portable)" -ForegroundColor Green
    
    # Check if Docker is running
    docker info 2>&1 | Out-Null
    if ($LASTEXITCODE -ne 0) {
        Write-Host "✗ Docker is not running! Start Docker Desktop." -ForegroundColor Red
        exit 1
    }
    
    # Refresh PATH for docker command
    $env:Path = [System.Environment]::GetEnvironmentVariable("Path","Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path","User")
    
    Write-Host "✓ Building Docker image..." -ForegroundColor Yellow
    docker compose build
    
    if ($Clean) {
        Write-Host "✓ Cleaning build in container..." -ForegroundColor Yellow
        docker compose run --rm espeasy-build pio run -e $env_name --target clean
    }
    
    Write-Host "✓ Building firmware in container..." -ForegroundColor Yellow
    docker compose run --rm espeasy-build pio run -e $env_name
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host "`n✅ BUILD SUCCESS!" -ForegroundColor Green
        Write-Host "Firmware: build_output\bin\firmware.bin" -ForegroundColor Cyan
    } else {
        Write-Host "`n❌ BUILD FAILED!" -ForegroundColor Red
        exit 1
    }
}

# Main
switch ($Mode) {
    'local' { Build-Local }
    'docker' { Build-Docker }
    'help' { Show-Help }
}
