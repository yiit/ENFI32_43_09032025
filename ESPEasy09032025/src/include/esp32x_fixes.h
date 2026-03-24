// src/include/esp32x_fixes.h
#pragma once
// Borrowed from the Tasmota branch, to support ESP32-C3 and ESP32-S3
// Many thanks to Theo Arends and the rest of the Tasmota team!

/*
   esp32x_fixes.h - fix esp32x toolchain
   GPL-3.0-or-later
*/

#include <sdkconfig.h>
#if __has_include(<esp_idf_version.h>)
  #include <esp_idf_version.h>
#endif

/*
 * Xtensa toolchain declares `int32_t` as `int` but RISC-V toolchain
 * declares `int32_t` as `long int` which causes compilation errors.
 * See: https://github.com/espressif/esp-idf/issues/6906
 *       https://github.com/espressif/arduino-esp32/issues/5086
 *
 * Add to build_flags if needed:
 *   -I$PROJECT_DIR/include
 *   -include "esp32x_fixes.h"
 */
#ifdef __riscv
  #undef __INT32_TYPE__
  #define __INT32_TYPE__      int
  #undef __UINT32_TYPE__
  #define __UINT32_TYPE__     unsigned int
#endif // __riscv

// ---------- SPI host aliases (legacy names) ----------
#ifdef CONFIG_IDF_TARGET_ESP32
  #define SPI_HOST    SPI1_HOST
  #define HSPI_HOST   SPI2_HOST
  #define VSPI_HOST   SPI3_HOST

#elif defined(CONFIG_IDF_TARGET_ESP32S2)
  // SPI1 not supported by SPI Master/Slave on S2+
  #define SPI_HOST    SPI1_HOST
  #define FSPI_HOST   SPI2_HOST
  #define HSPI_HOST   SPI3_HOST
  #define VSPI_HOST   SPI3_HOST

#elif defined(CONFIG_IDF_TARGET_ESP32S3)
  // SPI1 not supported by SPI Master/Slave on S2+
  #define SPI_HOST    SPI1_HOST
  #define FSPI_HOST   SPI2_HOST
  #define HSPI_HOST   SPI3_HOST
  #define VSPI_HOST   SPI3_HOST

  // Only for IDF4.x (Arduino-ESP32 2.x). IDF5'te LovyanGFX kendi tanımlarını getirir.
  #if defined(ESP_IDF_VERSION_MAJOR) && (ESP_IDF_VERSION_MAJOR < 5)
    #ifndef REG_SPI_BASE
      #define REG_SPI_BASE(i) (DR_REG_SPI1_BASE + (((i) > 1) ? (((i) * 0x1000) + 0x20000) : (((~(i)) & 1) * 0x1000)))
    #endif
    // SPI_MOSI_DLEN_REG eski ad; IDF4 için SPI_MS_DLEN_REG'e yönlendir.
    #if !defined(SPI_MOSI_DLEN_REG) && defined(SPI_MS_DLEN_REG)
      #define SPI_MOSI_DLEN_REG(x) SPI_MS_DLEN_REG(x)
    #endif
  #endif

#elif defined(CONFIG_IDF_TARGET_ESP32C3)
  #define SPI_HOST    SPI1_HOST
  #define HSPI_HOST   SPI2_HOST
  #define VSPI_HOST   SPI2_HOST /* No SPI3 on C3 */

  #if defined(ESP_IDF_VERSION_MAJOR) && (ESP_IDF_VERSION_MAJOR < 5)
    // IDF 4.4 C3 düzeltmeleri
    #ifndef REG_SPI_BASE
      #define REG_SPI_BASE(i) (DR_REG_SPI1_BASE + (((i) > 1) ? (((i) * 0x1000) + 0x20000) : (((~(i)) & 1) * 0x1000)))
    #endif
    #if !defined(SPI_MOSI_DLEN_REG) && defined(SPI_MS_DLEN_REG)
      #define SPI_MOSI_DLEN_REG(x) SPI_MS_DLEN_REG(x)
    #endif
  #endif

#elif defined(CONFIG_IDF_TARGET_ESP32C2) || defined(CONFIG_IDF_TARGET_ESP32C6)
  #define SPI_HOST    SPI1_HOST
  #define HSPI_HOST   SPI2_HOST
  #define VSPI_HOST   SPI2_HOST /* No SPI3 on C2/C6 */
  #define VSPI        SPI

  // Sadece IDF4.x’te alias ver, IDF5+’ta dokunma
  #if defined(ESP_IDF_VERSION_MAJOR) && (ESP_IDF_VERSION_MAJOR < 5)
    #if !defined(SPI_MOSI_DLEN_REG) && defined(SPI_MS_DLEN_REG)
      #define SPI_MOSI_DLEN_REG(x) SPI_MS_DLEN_REG(x)
    #endif
  #endif

#endif // target
