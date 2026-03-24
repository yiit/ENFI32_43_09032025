#include "../Helpers/StringProvider.h"

#if FEATURE_ETHERNET
# include <ETH.h>
#endif // if FEATURE_ETHERNET

#include "../../ESPEasy-Globals.h"

#include "../CustomBuild/CompiletimeDefines.h"

#include "../ESPEasyCore/ESPEasyNetwork.h"
#include "../ESPEasyCore/ESPEasyWifi.h"
#if FEATURE_ETHERNET
#include "../ESPEasyCore/ESPEasyEth.h"
#endif

#include "../Globals/Device.h"
#include "../Globals/ESPEasy_Console.h"
#include "../Globals/ESPEasy_Scheduler.h"
#include "../Globals/ESPEasy_time.h"
#include "../Globals/ESPEasyWiFiEvent.h"

#if FEATURE_ETHERNET
#include "../Globals/ESPEasyEthEvent.h"
#endif

#include "../Globals/NetworkState.h"
#include "../Globals/SecuritySettings.h"
#include "../Globals/Settings.h"
#include "../Globals/WiFi_AP_Candidates.h"

#include "../Helpers/Convert.h"
#include "../Helpers/ESPEasy_Storage.h"
#include "../Helpers/Hardware_device_info.h"
#include "../Helpers/Hardware_temperature_sensor.h"
#include "../Helpers/Memory.h"
#include "../Helpers/Misc.h"
#include "../Helpers/Networking.h"
#include "../Helpers/Scheduler.h"
#include "../Helpers/StringConverter.h"
#include "../Helpers/StringGenerator_System.h"
#include "../Helpers/StringGenerator_WiFi.h"

#include "../WebServer/JSON.h"
#include "../WebServer/AccessControl.h"

#ifdef ESP32
#include <soc/rtc.h>
#endif

String getInternalLabel(LabelType::Enum label, char replaceSpace) {
  return to_internal_string(getLabel(label), replaceSpace);
}

const __FlashStringHelper * getLabel(LabelType::Enum label) {
  switch (label)
  {
    case LabelType::UNIT_NR:                return F("Unit Number");
    #if FEATURE_ZEROFILLED_UNITNUMBER
    case LabelType::UNIT_NR_0:              return F("Unit Number 0-filled");
    #endif // FEATURE_ZEROFILLED_UNITNUMBER
    case LabelType::UNIT_NAME:              return F("Unit Name");
    case LabelType::HOST_NAME:              return F("Hostname");

    case LabelType::LOCAL_TIME:             return F("Local Time");
    case LabelType::TIME_SOURCE:            return F("Time Source");
    case LabelType::TIME_WANDER:            return F("Time Wander");
#if FEATURE_EXT_RTC
    case LabelType::EXT_RTC_UTC_TIME:       return F("UTC time stored in RTC chip");
#endif
    case LabelType::UPTIME:                 return F("Uptime");
    case LabelType::LOAD_PCT:               return F("Load");
    case LabelType::LOOP_COUNT:             return F("Load LC");
    case LabelType::CPU_ECO_MODE:           return F("CPU Eco Mode");
#if FEATURE_SET_WIFI_TX_PWR
    case LabelType::WIFI_TX_MAX_PWR:        return F("Max WiFi TX Power");
    case LabelType::WIFI_CUR_TX_PWR:        return F("Current WiFi TX Power");
    case LabelType::WIFI_SENS_MARGIN:       return F("WiFi Sensitivity Margin");
    case LabelType::WIFI_SEND_AT_MAX_TX_PWR:return F("Send With Max TX Power");
#endif
    case LabelType::WIFI_NR_EXTRA_SCANS:    return F("Extra WiFi scan loops");
    case LabelType::WIFI_USE_LAST_CONN_FROM_RTC: return F("Use Last Connected AP from RTC");

    case LabelType::FREE_MEM:               return F("Free RAM");
    case LabelType::FREE_STACK:             return F("Free Stack");
#ifdef USE_SECOND_HEAP
    case LabelType::FREE_HEAP_IRAM:         return F("Free 2nd Heap");
#endif

#if defined(CORE_POST_2_5_0) || defined(ESP32)
  #ifndef LIMIT_BUILD_SIZE
    case LabelType::HEAP_MAX_FREE_BLOCK:    return F("Heap Max Free Block");
  #endif
#endif // if defined(CORE_POST_2_5_0) || defined(ESP32)
#if defined(CORE_POST_2_5_0)
  #ifndef LIMIT_BUILD_SIZE
    case LabelType::HEAP_FRAGMENTATION:     return F("Heap Fragmentation");
  #endif
#endif // if defined(CORE_POST_2_5_0)

#ifdef ESP32
    case LabelType::HEAP_SIZE:              return F("Heap Size");
    case LabelType::HEAP_MIN_FREE:          return F("Heap Min Free");
#ifdef BOARD_HAS_PSRAM
    case LabelType::PSRAM_SIZE:             return F("PSRAM Size");
    case LabelType::PSRAM_FREE:             return F("PSRAM Free");
    case LabelType::PSRAM_MIN_FREE:         return F("PSRAM Min Free");
    case LabelType::PSRAM_MAX_FREE_BLOCK:   return F("PSRAM Max Free Block");
#endif // BOARD_HAS_PSRAM
#endif // ifdef ESP32

    case LabelType::JSON_BOOL_QUOTES:           return F("JSON bool output without quotes");
#if FEATURE_TIMING_STATS
    case LabelType::ENABLE_TIMING_STATISTICS:   return F("Collect Timing Statistics");
#endif
    case LabelType::ENABLE_RULES_CACHING:       return F("Enable Rules Cache");
    case LabelType::ENABLE_SERIAL_PORT_CONSOLE: return F("Enable Serial Port Console");
    case LabelType::CONSOLE_SERIAL_PORT:        return F("Console Serial Port");
#if USES_ESPEASY_CONSOLE_FALLBACK_PORT
    case LabelType::CONSOLE_FALLBACK_TO_SERIAL0: return F("Fallback to Serial 0");
    case LabelType::CONSOLE_FALLBACK_PORT:       return F("Console Fallback Port");
#endif

//    case LabelType::ENABLE_RULES_EVENT_REORDER: return F("Optimize Rules Cache Event Order"); // TD-er: Disabled for now
    case LabelType::TASKVALUESET_ALL_PLUGINS:   return F("Allow TaskValueSet on all plugins");
    case LabelType::ALLOW_OTA_UNLIMITED:        return F("Allow OTA without size-check");
#if FEATURE_CLEAR_I2C_STUCK
    case LabelType::ENABLE_CLEAR_HUNG_I2C_BUS:  return F("Try clear I2C bus when stuck");
#endif
    #if FEATURE_I2C_DEVICE_CHECK
    case LabelType::ENABLE_I2C_DEVICE_CHECK:    return F("Check I2C devices when enabled");
    #endif // if FEATURE_I2C_DEVICE_CHECK
#ifndef BUILD_NO_RAM_TRACKER
    case LabelType::ENABLE_RAM_TRACKING:    return F("Enable RAM Tracker");
#endif
#if FEATURE_AUTO_DARK_MODE
    case LabelType::ENABLE_AUTO_DARK_MODE:  return F("Web light/dark mode");
#endif // FEATURE_AUTO_DARK_MODE
#if FEATURE_RULES_EASY_COLOR_CODE
    case LabelType::DISABLE_RULES_AUTOCOMPLETE:  return F("Disable Rules auto-completion");
#endif // if FEATURE_RULES_EASY_COLOR_CODE
#if FEATURE_TARSTREAM_SUPPORT
    case LabelType::DISABLE_SAVE_CONFIG_AS_TAR:  return F("Disable Save Config as .tar");
#endif // if FEATURE_TARSTREAM_SUPPORT

    case LabelType::BOOT_TYPE:              return F("Last Boot Cause");
    case LabelType::BOOT_COUNT:             return F("Boot Count");
    case LabelType::DEEP_SLEEP_ALTERNATIVE_CALL: return F("Deep Sleep Alternative");
    case LabelType::RESET_REASON:           return F("Reset Reason");
    case LabelType::LAST_TASK_BEFORE_REBOOT: return F("Last Action before Reboot");
    case LabelType::SW_WD_COUNT:            return F("SW WD count");


    case LabelType::WIFI_CONNECTION:        return F("WiFi Connection");
    case LabelType::WIFI_RSSI:              return F("RSSI");
    case LabelType::IP_CONFIG:              return F("IP Config");
#if FEATURE_USE_IPV6
    case LabelType::IP6_LOCAL:              return F("IPv6 link local");
    case LabelType::IP6_GLOBAL:             return F("IPv6 global");
//    case LabelType::IP6_ALL_ADDRESSES:      return F("IPv6 all addresses");
#endif
    case LabelType::IP_CONFIG_STATIC:       return F("Static");
    case LabelType::IP_CONFIG_DYNAMIC:      return F("DHCP");
    case LabelType::IP_ADDRESS:             return F("IP Address");
    case LabelType::IP_SUBNET:              return F("IP Subnet");
    case LabelType::IP_ADDRESS_SUBNET:      return F("IP / Subnet");
    case LabelType::GATEWAY:                return F("Gateway");
    case LabelType::CLIENT_IP:              return F("Client IP");
    #if FEATURE_MDNS
    case LabelType::M_DNS:                  return F("mDNS");
    #endif // if FEATURE_MDNS
    case LabelType::DNS:                    return F("DNS");
    case LabelType::DNS_1:                  return F("DNS 1");
    case LabelType::DNS_2:                  return F("DNS 2");
    case LabelType::ALLOWED_IP_RANGE:       return F("Allowed IP Range");
    case LabelType::STA_MAC:                return F("STA MAC");
    case LabelType::AP_MAC:                 return F("AP MAC");
    case LabelType::SSID:                   return F("SSID");
    case LabelType::BSSID:                  return F("BSSID");
    case LabelType::CHANNEL:                return F("Channel");
    case LabelType::ENCRYPTION_TYPE_STA:    return F("Encryption Type");
    case LabelType::CONNECTED:              return F("Connected");
    case LabelType::CONNECTED_MSEC:         return F("Connected msec");
    case LabelType::LAST_DISCONNECT_REASON: return F("Last Disconnect Reason");
    case LabelType::LAST_DISC_REASON_STR:   return F("Last Disconnect Reason str");
    case LabelType::NUMBER_RECONNECTS:      return F("Number Reconnects");
    case LabelType::WIFI_STORED_SSID1:      return F("Configured SSID1");
    case LabelType::WIFI_STORED_SSID2:      return F("Configured SSID2");


    case LabelType::FORCE_WIFI_BG:          return F("Force WiFi B/G");
    case LabelType::RESTART_WIFI_LOST_CONN: return F("Restart WiFi Lost Conn");
    case LabelType::FORCE_WIFI_NOSLEEP:     return F("Force WiFi No Sleep");
    case LabelType::PERIODICAL_GRAT_ARP:    return F("Periodical send Gratuitous ARP");
    case LabelType::CONNECTION_FAIL_THRESH: return F("Connection Failure Threshold");
#ifndef ESP32
    case LabelType::WAIT_WIFI_CONNECT:      return F("Extra Wait WiFi Connect");
#endif
    case LabelType::CONNECT_HIDDEN_SSID:    return F("Include Hidden SSID");
#ifdef ESP32
    case LabelType::WIFI_PASSIVE_SCAN:      return F("Passive WiFi Scan");
#endif
    case LabelType::HIDDEN_SSID_SLOW_CONNECT: return F("Hidden SSID Slow Connect");
    case LabelType::SDK_WIFI_AUTORECONNECT: return F("Enable SDK WiFi Auto Reconnect");
#if FEATURE_USE_IPV6
    case LabelType::ENABLE_IPV6:            return F("Enable IPv6");
#endif


    case LabelType::BUILD_DESC:             return F("Build");
    case LabelType::GIT_BUILD:              return F("Git Build");
    case LabelType::SYSTEM_LIBRARIES:       return F("System Libraries");
#ifdef ESP32
    case LabelType::ESP_IDF_SDK_VERSION:    return F("ESP-IDF Version");
#endif
    case LabelType::PLUGIN_COUNT:           return F("Plugin Count");
    case LabelType::PLUGIN_DESCRIPTION:     return F("Plugin Description");
    case LabelType::BUILD_TIME:             return F("Build Time");
    case LabelType::BINARY_FILENAME:        return F("Binary Filename");
    case LabelType::BUILD_PLATFORM:         return F("Build Platform");
    case LabelType::GIT_HEAD:               return F("Git HEAD");
    #ifdef CONFIGURATION_CODE
    case LabelType::CONFIGURATION_CODE_LBL: return F("Configuration code");
    #endif // ifdef CONFIGURATION_CODE

    case LabelType::I2C_BUS_STATE:          return F("I2C Bus State");
    case LabelType::I2C_BUS_CLEARED_COUNT:  return F("I2C bus cleared count");

    case LabelType::SYSLOG_LOG_LEVEL:       return F("Syslog Log Level");
    case LabelType::SERIAL_LOG_LEVEL:       return F("Serial Log Level");
    case LabelType::WEB_LOG_LEVEL:          return F("Web Log Level");
#if FEATURE_SD
    case LabelType::SD_LOG_LEVEL:           return F("SD Log Level");
#endif // if FEATURE_SD

    case LabelType::ESP_CHIP_ID:            return F("ESP Chip ID");
    case LabelType::ESP_CHIP_FREQ:          return F("ESP Chip Frequency");
#ifdef ESP32
    case LabelType::ESP_CHIP_XTAL_FREQ:     return F("ESP Crystal Frequency");
    case LabelType::ESP_CHIP_APB_FREQ:      return F("ESP APB Frequency");
#endif
    case LabelType::ESP_CHIP_MODEL:         return F("ESP Chip Model");
    case LabelType::ESP_CHIP_REVISION:      return F("ESP Chip Revision");
    case LabelType::ESP_CHIP_CORES:         return F("ESP Chip Cores");

    case LabelType::BOARD_NAME:         return F("ESP Board Name");

    case LabelType::FLASH_CHIP_ID:          return F("Flash Chip ID");
    case LabelType::FLASH_CHIP_VENDOR:      return F("Flash Chip Vendor");
    case LabelType::FLASH_CHIP_MODEL:       return F("Flash Chip Model");
    case LabelType::FLASH_CHIP_REAL_SIZE:   return F("Flash Chip Real Size");
    case LabelType::FLASH_CHIP_SPEED:       return F("Flash Chip Speed");
    case LabelType::FLASH_IDE_SIZE:         return F("Flash IDE Size");
    case LabelType::FLASH_IDE_SPEED:        return F("Flash IDE Speed");
    case LabelType::FLASH_IDE_MODE:         return F("Flash IDE Mode");
    case LabelType::FLASH_WRITE_COUNT:      return F("Flash Writes");
    case LabelType::SKETCH_SIZE:            return F("Sketch Size");
    case LabelType::SKETCH_FREE:            return F("Sketch Free");
#ifdef USE_LITTLEFS
    case LabelType::FS_SIZE:                return F("Little FS Size");
    case LabelType::FS_FREE:                return F("Little FS Free");
#else // ifdef USE_LITTLEFS
    case LabelType::FS_SIZE:                return F("SPIFFS Size");
    case LabelType::FS_FREE:                return F("SPIFFS Free");
#endif // ifdef USE_LITTLEFS
    case LabelType::MAX_OTA_SKETCH_SIZE:    return F("Max. OTA Sketch Size");
    case LabelType::OTA_2STEP:              return F("OTA 2-step Needed");
    case LabelType::OTA_POSSIBLE:           return F("OTA possible");
    #if FEATURE_INTERNAL_TEMPERATURE
    case LabelType::INTERNAL_TEMPERATURE:   return F("Internal Temperature");
    #endif // if FEATURE_INTERNAL_TEMPERATURE
#if FEATURE_ETHERNET
    case LabelType::ETH_IP_ADDRESS:         return F("Eth IP Address");
    case LabelType::ETH_IP_SUBNET:          return F("Eth IP Subnet");
    case LabelType::ETH_IP_ADDRESS_SUBNET:  return F("Eth IP / Subnet");
    case LabelType::ETH_IP_GATEWAY:         return F("Eth Gateway");
    case LabelType::ETH_IP_DNS:             return F("Eth DNS");
#if FEATURE_USE_IPV6
    case LabelType::ETH_IP6_LOCAL:          return F("Eth IPv6 link local");
#endif
    case LabelType::ETH_MAC:                return F("Eth MAC");
    case LabelType::ETH_DUPLEX:             return F("Eth Mode");
    case LabelType::ETH_SPEED:              return F("Eth Speed");
    case LabelType::ETH_STATE:              return F("Eth State");
    case LabelType::ETH_SPEED_STATE:        return F("Eth Speed State");
    case LabelType::ETH_CONNECTED:          return F("Eth connected");
    case LabelType::ETH_CHIP:               return F("Eth chip");
#endif // if FEATURE_ETHERNET
# if FEATURE_ETHERNET || defined(USES_ESPEASY_NOW)
    case LabelType::ETH_WIFI_MODE:          return F("Network Type");
#endif
    case LabelType::SKT:                    return F("Son Kullanım Tarihi");
    case LabelType::SUNRISE:                return F("Sunrise");
    case LabelType::SUNSET:                 return F("Sunset");
    case LabelType::SUNRISE_S:              return F("Sunrise sec.");
    case LabelType::SUNSET_S:               return F("Sunset sec.");
    case LabelType::SUNRISE_M:              return F("Sunrise min.");
    case LabelType::SUNSET_M:               return F("Sunset min.");
    case LabelType::ISNTP:                  return F("Use NTP");
    case LabelType::UPTIME_MS:              return F("Uptime (ms)");
    case LabelType::TIMEZONE_OFFSET:        return F("Timezone Offset");
    case LabelType::LATITUDE:               return F("Latitude");
    case LabelType::LONGITUDE:              return F("Longitude");

    case LabelType::XML_TARIH_V:            return F("XML TARIH DEGISKEN");
    case LabelType::XML_SAAT_V:             return F("XML SAAT DEGISKEN");
    case LabelType::XML_NET_C:              return F("NET");
    case LabelType::XML_NET_S:              return F("NET_S");
    case LabelType::XML_DARA_C:             return F("DARA");
    case LabelType::XML_DARA_S:             return F("DARA_S");
    case LabelType::XML_BRUT_C:             return F("BRUT");
    case LabelType::XML_BRUT_S:             return F("BRUT_S");
    case LabelType::XML_NET_2:              return F("NET2");
    case LabelType::XML_DARA_2:             return F("DARA2");
    case LabelType::XML_BRUT_2:             return F("BRUT2");
    case LabelType::XML_ADET:               return F("ADET");
    case LabelType::XML_ADET_GRAMAJ:        return F("ADET GRAMAJ");
    case LabelType::XML_URUN_NO:            return F("URUN NO");
    case LabelType::XML_URUN_ISMI:          return F("URUN ISMI");
    case LabelType::XML_URUN_KOD:           return F("URUN KOD");
    case LabelType::XML_URUN_MESAJ:         return F("URUN MESAJ");
    case LabelType::XML_BARKOD:             return F("BARKOD");
    case LabelType::XML_BIRIM_FIYAT:        return F("BIRIM FIYAT");
    case LabelType::XML_TUTAR:              return F("TUTAR");
    case LabelType::XML_SNO:                return F("SNO");
    case LabelType::XML_SAYAC_1:            return F("SAYAC1");
    case LabelType::XML_SAYAC_2:            return F("SAYAC2");
    case LabelType::XML_SAYAC_3:            return F("SAYAC3");
    case LabelType::XML_SAYAC_4:            return F("SAYAC4");
    case LabelType::XML_SAYAC_1_C:          return F("SAYAC1_C");
    case LabelType::XML_SAYAC_2_C:          return F("SAYAC2_C");
    case LabelType::XML_SAYAC_3_C:          return F("SAYAC3_C");
    case LabelType::XML_SAYAC_4_C:          return F("SAYAC4_C");
    case LabelType::XML_SERI_NO:            return F("SERI NO");
    case LabelType::XML_PARTI_NO:           return F("PARTI NO");
    case LabelType::XML_FIS_NO:             return F("FIS NO");
    case LabelType::XML_TOP_NET:            return F("TOP NET");
    case LabelType::XML_TOP_DARA:           return F("TOP DARA");
    case LabelType::XML_TOP_BRUT:           return F("TOP BRUT");
    case LabelType::XML_TOP_ADET:           return F("TOP ADET");

    case LabelType::XML_EAN8:               return F("XML EAN8");
    case LabelType::XML_EAN13:              return F("XML EAN13");
    case LabelType::XML_QRKOD:              return F("XML QRkod");
    case LabelType::XML_STABIL:             return F("XML STABIL");
    
    case LabelType::XML_MESAJ1:             return F("XML MESAJ1");
    case LabelType::XML_MESAJ2:             return F("XML MESAJ2");
    case LabelType::XML_MESAJ3:             return F("XML MESAJ3");
    case LabelType::XML_MESAJ4:             return F("XML MESAJ4");
    case LabelType::XML_MESAJ5:             return F("XML MESAJ5");
    case LabelType::XML_MESAJ6:             return F("XML MESAJ6");
    case LabelType::XML_MESAJ7:             return F("XML MESAJ7");
    case LabelType::XML_MESAJ8:             return F("XML MESAJ8");
    case LabelType::XML_MESAJ9:             return F("XML MESAJ9");

    case LabelType::XML_FISBAS1:            return F("XML FISBAS1");
    case LabelType::XML_FISBAS2:            return F("XML FISBAS2");
    case LabelType::XML_FISBAS3:            return F("XML FISBAS3");
    case LabelType::XML_FISBAS4:            return F("XML FISBAS4");
    case LabelType::KFONT1:                 return F("KFONT1");
    case LabelType::KFONT2:                 return F("KFONT2");
    case LabelType::KFONT3:                 return F("KFONT3");
    case LabelType::KFONT4:                 return F("KFONT4");
    case LabelType::KFONT5:                 return F("KFONT5");
    case LabelType::KFONT6:                 return F("KFONT6");
    case LabelType::FONT1:                  return F("FONT1");
    case LabelType::FONT2:                  return F("FONT2");
    case LabelType::FONT3:                  return F("FONT3");
    case LabelType::FONT4:                  return F("FONT4");
    case LabelType::FONT5:                  return F("FONT5");
    case LabelType::FONT6:                  return F("FONT6");
    case LabelType::LOGO:                   return F("LOGO");
    case LabelType::SOL:                    return F("SOL");
    case LabelType::ORTA:                   return F("ORTA");
    case LabelType::SAG:                    return F("SAG");
    case LabelType::BEYAZ:                  return F("BEYAZ");
    case LabelType::SIYAH:                  return F("SIYAH");
    case LabelType::KOYU:                   return F("KOYU");
    case LabelType::ACIK:                   return F("ACIK");
    case LabelType::KES:                    return F("KES");
    case LabelType::CEKMECE:                return F("CEKMECE");
    //case LabelType::ALTCIZGIPASIF:          return F("ALTCIZGI PASIF");
    //case LabelType::ALTCIZGIAKTIF:          return F("ALTCIZGI AKTIF");

    case LabelType::XML_V0:                 return F("XML V0");
    case LabelType::XML_V1:                 return F("XML V1");
    case LabelType::XML_V2:                 return F("XML V2");
    case LabelType::XML_V3:                 return F("XML V3");
    case LabelType::XML_V4:                 return F("XML V4");
    case LabelType::XML_V5:                 return F("XML V5");
    case LabelType::XML_V6:                 return F("XML V6");
    case LabelType::XML_V7:                 return F("XML V7");
    case LabelType::XML_V8:                 return F("XML V8");
    case LabelType::XML_V9:                 return F("XML V9");
    case LabelType::XML_V10:                return F("XML V10");
    case LabelType::XML_V11:                return F("XML V11");
    case LabelType::XML_V12:                return F("XML V12");
    case LabelType::XML_V13:                return F("XML V13");
    case LabelType::XML_V14:                return F("XML V14");
    case LabelType::XML_V15:                return F("XML V15");
    case LabelType::XML_V16:                return F("XML V16");
    case LabelType::XML_V17:                return F("XML V17");
    case LabelType::XML_V18:                return F("XML V18");
    case LabelType::XML_V19:                return F("XML V19");
    case LabelType::XML_V20:                return F("XML V20");
    case LabelType::XML_V21:                return F("XML V21");
    case LabelType::XML_V22:                return F("XML V22");
    case LabelType::XML_V23:                return F("XML V23");
    case LabelType::XML_V24:                return F("XML V24");
    case LabelType::XML_V25:                return F("XML V25");
    case LabelType::XML_V26:                return F("XML V26");
    case LabelType::XML_V27:                return F("XML V27");
    case LabelType::XML_V28:                return F("XML V28");
    case LabelType::XML_V29:                return F("XML V29");

    case LabelType::XML_FIRMA_ISMI:         return F("XML FIRMA ISMI");
    case LabelType::XML_MUSTERI_ISMI:       return F("XML MUSTERI ISMI");
    case LabelType::XML_NET_V:              return F("NET_V");
    case LabelType::XML_PLAKA_NO:           return F("XML PLAKA NO");
    case LabelType::XML_OPERATOR:           return F("XML OPERATOR");    
    case LabelType::XML_DARA_V:             return F("DARA_V");
    case LabelType::XML_BRUT_V:             return F("BRUT_V");

    case LabelType::IRDA_DATA:              return F("IRDA DATA");

    case LabelType::XML_TOPLAM_DETAY:       return F("TOPLAM DETAY");

    case LabelType::MAX_LABEL:
    break;

  }
  return F("MissingString");
}

String getValue(LabelType::Enum label) {
  int retval = INT_MAX;
  switch (label)
  {
    case LabelType::UNIT_NR:                retval = Settings.Unit; break;
    #if FEATURE_ZEROFILLED_UNITNUMBER
    case LabelType::UNIT_NR_0: 
    {
      // Fixed 3-digit unitnumber
      return formatIntLeadingZeroes(Settings.Unit, 3);
    }
    #endif // FEATURE_ZEROFILLED_UNITNUMBER
    case LabelType::UNIT_NAME:              return Settings.getName(); // Only return the set name, no appended unit.
    case LabelType::HOST_NAME:              return NetworkGetHostname();


    case LabelType::LOCAL_TIME:             return node_time.getDateTimeString('-', ':', ' ');
    case LabelType::TIME_SOURCE:
    {
      String timeSource_str = toString(node_time.getTimeSource());
      if (((node_time.getTimeSource() == timeSource_t::ESPEASY_p2p_UDP) ||
           (node_time.getTimeSource() == timeSource_t::ESP_now_peer)) &&
          (node_time.timeSource_p2p_unit != 0))
      {
        return strformat(F("%s (%u)"), timeSource_str.c_str(), node_time.timeSource_p2p_unit);
      }
      return timeSource_str;
    }
    case LabelType::TIME_WANDER:            return String(node_time.timeWander, 3);
    #if FEATURE_EXT_RTC
    case LabelType::EXT_RTC_UTC_TIME:
    {
      if (Settings.ExtTimeSource() != ExtTimeSource_e::None) {
        // Try to read the stored time in the ext. time source to allow to check if it is working properly.
        uint32_t unixtime;
        if (node_time.ExtRTC_get(unixtime)) {
          struct tm RTC_time;
          breakTime(unixtime, RTC_time);
          return formatDateTimeString(RTC_time);
        } else {
          return F("Not Set");
        }
      }
      return String('-');
    }
    #endif
    case LabelType::UPTIME:                 retval = getUptimeMinutes(); break;
    case LabelType::LOAD_PCT:               return toString(getCPUload(), 2);
    case LabelType::LOOP_COUNT:             retval = getLoopCountPerSec(); break;
    case LabelType::CPU_ECO_MODE:           return jsonBool(Settings.EcoPowerMode());
#if FEATURE_SET_WIFI_TX_PWR
    case LabelType::WIFI_TX_MAX_PWR:        return toString(Settings.getWiFi_TX_power(), 2);
    case LabelType::WIFI_CUR_TX_PWR:        return toString(WiFiEventData.wifi_TX_pwr, 2);
    case LabelType::WIFI_SENS_MARGIN:       retval = Settings.WiFi_sensitivity_margin; break;
    case LabelType::WIFI_SEND_AT_MAX_TX_PWR:return jsonBool(Settings.UseMaxTXpowerForSending());
#endif
    case LabelType::WIFI_NR_EXTRA_SCANS:    retval = Settings.NumberExtraWiFiScans; break;
    case LabelType::WIFI_USE_LAST_CONN_FROM_RTC: return jsonBool(Settings.UseLastWiFiFromRTC());

    case LabelType::FREE_MEM:               retval = FreeMem(); break;
    case LabelType::FREE_STACK:             retval = getCurrentFreeStack(); break;

#ifdef USE_SECOND_HEAP
    case LabelType::FREE_HEAP_IRAM:         retval = FreeMem2ndHeap(); break;
#endif

#if defined(CORE_POST_2_5_0)
  #ifndef LIMIT_BUILD_SIZE
    case LabelType::HEAP_MAX_FREE_BLOCK:    retval = ESP.getMaxFreeBlockSize(); break;
  #endif
#endif // if defined(CORE_POST_2_5_0)
#if  defined(ESP32)
  #ifndef LIMIT_BUILD_SIZE
    case LabelType::HEAP_MAX_FREE_BLOCK:    retval = ESP.getMaxAllocHeap(); break;
  #endif
#endif // if  defined(ESP32)
#if defined(CORE_POST_2_5_0)
  #ifndef LIMIT_BUILD_SIZE
    case LabelType::HEAP_FRAGMENTATION:     retval = ESP.getHeapFragmentation(); break;
  #endif
#endif // if defined(CORE_POST_2_5_0)
#ifdef ESP32
    case LabelType::HEAP_SIZE:              retval = ESP.getHeapSize(); break;
    case LabelType::HEAP_MIN_FREE:          retval = ESP.getMinFreeHeap(); break;
    #ifdef BOARD_HAS_PSRAM
    case LabelType::PSRAM_SIZE:             retval = UsePSRAM() ? ESP.getPsramSize() : 0; break;
    case LabelType::PSRAM_FREE:             retval = UsePSRAM() ? ESP.getFreePsram() : 0; break;
    case LabelType::PSRAM_MIN_FREE:         retval = UsePSRAM() ? ESP.getMinFreePsram() : 0; break;
    case LabelType::PSRAM_MAX_FREE_BLOCK:   retval = UsePSRAM() ? ESP.getMaxAllocPsram() : 0; break;
    #endif // BOARD_HAS_PSRAM
#endif // ifdef ESP32


    case LabelType::JSON_BOOL_QUOTES:           return jsonBool(Settings.JSONBoolWithoutQuotes());
#if FEATURE_TIMING_STATS
    case LabelType::ENABLE_TIMING_STATISTICS:   return jsonBool(Settings.EnableTimingStats());
#endif
    case LabelType::ENABLE_RULES_CACHING:       return jsonBool(Settings.EnableRulesCaching());
    case LabelType::ENABLE_SERIAL_PORT_CONSOLE: return jsonBool(Settings.UseSerial);
    case LabelType::CONSOLE_SERIAL_PORT:        return ESPEasy_Console.getPortDescription();

#if USES_ESPEASY_CONSOLE_FALLBACK_PORT
    case LabelType::CONSOLE_FALLBACK_TO_SERIAL0: return jsonBool(Settings.console_serial0_fallback);
    case LabelType::CONSOLE_FALLBACK_PORT:       return ESPEasy_Console.getFallbackPortDescription();
#endif

//    case LabelType::ENABLE_RULES_EVENT_REORDER: return jsonBool(Settings.EnableRulesEventReorder()); // TD-er: Disabled for now
    case LabelType::TASKVALUESET_ALL_PLUGINS:   return jsonBool(Settings.AllowTaskValueSetAllPlugins());
    case LabelType::ALLOW_OTA_UNLIMITED:        return jsonBool(Settings.AllowOTAUnlimited());
#if FEATURE_CLEAR_I2C_STUCK
    case LabelType::ENABLE_CLEAR_HUNG_I2C_BUS:  return jsonBool(Settings.EnableClearHangingI2Cbus());
#endif
#if FEATURE_I2C_DEVICE_CHECK
    case LabelType::ENABLE_I2C_DEVICE_CHECK:    return jsonBool(Settings.CheckI2Cdevice());
#endif // if FEATURE_I2C_DEVICE_CHECK
#ifndef BUILD_NO_RAM_TRACKER
    case LabelType::ENABLE_RAM_TRACKING:        return jsonBool(Settings.EnableRAMTracking());
#endif
#if FEATURE_AUTO_DARK_MODE
    case LabelType::ENABLE_AUTO_DARK_MODE:      return toString(Settings.getCssMode());
#endif // FEATURE_AUTO_DARK_MODE
#if FEATURE_RULES_EASY_COLOR_CODE
    case LabelType::DISABLE_RULES_AUTOCOMPLETE: return jsonBool(Settings.DisableRulesCodeCompletion());
#endif // if FEATURE_RULES_EASY_COLOR_CODE
#if FEATURE_TARSTREAM_SUPPORT
    case LabelType::DISABLE_SAVE_CONFIG_AS_TAR: return jsonBool(Settings.DisableSaveConfigAsTar());
#endif // if FEATURE_TARSTREAM_SUPPORT

    case LabelType::BOOT_TYPE:              return getLastBootCauseString();
    case LabelType::BOOT_COUNT:             break;
    case LabelType::DEEP_SLEEP_ALTERNATIVE_CALL: return jsonBool(Settings.UseAlternativeDeepSleep());
    case LabelType::RESET_REASON:           return getResetReasonString();
    case LabelType::LAST_TASK_BEFORE_REBOOT: return ESPEasy_Scheduler::decodeSchedulerId(lastMixedSchedulerId_beforereboot);
    case LabelType::SW_WD_COUNT:            retval = sw_watchdog_callback_count; break;

    case LabelType::WIFI_CONNECTION:        break;
    case LabelType::WIFI_RSSI:              retval = WiFi.RSSI(); break;
    case LabelType::IP_CONFIG:              return useStaticIP() 
                                                     ? getLabel(LabelType::IP_CONFIG_STATIC) 
                                                     : getLabel(LabelType::IP_CONFIG_DYNAMIC);
    case LabelType::IP_CONFIG_STATIC:       break;
    case LabelType::IP_CONFIG_DYNAMIC:      break;
    case LabelType::IP_ADDRESS:             return formatIP(NetworkLocalIP());
    case LabelType::IP_SUBNET:              return formatIP(NetworkSubnetMask());
    case LabelType::IP_ADDRESS_SUBNET:      return strformat(F("%s / %s"), getValue(LabelType::IP_ADDRESS).c_str(), getValue(LabelType::IP_SUBNET).c_str());
    case LabelType::GATEWAY:                return formatIP(NetworkGatewayIP());
#if FEATURE_USE_IPV6
    case LabelType::IP6_LOCAL:              return formatIP(NetworkLocalIP6(), true);
    case LabelType::IP6_GLOBAL:             return formatIP(NetworkGlobalIP6());
#if FEATURE_ETHERNET
    case LabelType::ETH_IP6_LOCAL:          return formatIP(NetworkLocalIP6(), true);
#endif
/*
    case LabelType::IP6_ALL_ADDRESSES:
    {
      IP6Addresses_t addresses = NetworkAllIPv6();
      String res;
      for (auto it = addresses.begin(); it != addresses.end(); ++it)
      {
        if (!res.isEmpty()) {
          res += F("<br>");
        }
        res += it->toString();
      }
      return res;
    }
*/
#endif
    case LabelType::CLIENT_IP:              return formatIP(web_server.client().remoteIP(), true);
    #if FEATURE_INTERNAL_TEMPERATURE
    case LabelType::INTERNAL_TEMPERATURE:   return toString(getInternalTemperature());
    #endif // if FEATURE_INTERNAL_TEMPERATURE

    #if FEATURE_MDNS
    case LabelType::M_DNS:                  return NetworkGetHostname() + F(".local");
    #endif // if FEATURE_MDNS
    case LabelType::DNS:                    return strformat(F("%s / %s"), getValue(LabelType::DNS_1).c_str(), getValue(LabelType::DNS_2).c_str());
    case LabelType::DNS_1:                  return formatIP(NetworkDnsIP(0));
    case LabelType::DNS_2:                  return formatIP(NetworkDnsIP(1));
    case LabelType::ALLOWED_IP_RANGE:       return describeAllowedIPrange();
    case LabelType::STA_MAC:                return WifiSTAmacAddress().toString();
    case LabelType::AP_MAC:                 return WifiSoftAPmacAddress().toString();
    case LabelType::SSID:                   return WiFi.SSID();
    case LabelType::BSSID:                  return WiFi.BSSIDstr();
    case LabelType::CHANNEL:                retval = WiFi.channel(); break;
    case LabelType::ENCRYPTION_TYPE_STA:    return // WiFi_AP_Candidates.getCurrent().encryption_type();
                                                   WiFi_encryptionType(WiFiEventData.auth_mode);
    case LabelType::CONNECTED:
      #if FEATURE_ETHERNET
      if(active_network_medium == NetworkMedium_t::Ethernet) {
        return format_msec_duration(EthEventData.lastConnectMoment.millisPassedSince());
      }
      #endif // if FEATURE_ETHERNET
      return format_msec_duration(WiFiEventData.lastConnectMoment.millisPassedSince());

    // Use only the nr of seconds to fit it in an int32, plus append '000' to have msec format again.
    case LabelType::CONNECTED_MSEC:         
      #if FEATURE_ETHERNET
      if(active_network_medium == NetworkMedium_t::Ethernet) {
        return String(static_cast<int32_t>(EthEventData.lastConnectMoment.millisPassedSince() / 1000ll)) + F("000"); 
      }
      #endif // if FEATURE_ETHERNET
      return String(static_cast<int32_t>(WiFiEventData.lastConnectMoment.millisPassedSince() / 1000ll)) + F("000");
    case LabelType::LAST_DISCONNECT_REASON: return String(WiFiEventData.lastDisconnectReason);
    case LabelType::LAST_DISC_REASON_STR:   return getLastDisconnectReason();
    case LabelType::NUMBER_RECONNECTS:      retval = WiFiEventData.wifi_reconnects; break;
    case LabelType::WIFI_STORED_SSID1:      return String(SecuritySettings.WifiSSID);
    case LabelType::WIFI_STORED_SSID2:      return String(SecuritySettings.WifiSSID2);


    case LabelType::FORCE_WIFI_BG:          return jsonBool(Settings.ForceWiFi_bg_mode());
    case LabelType::RESTART_WIFI_LOST_CONN: return jsonBool(Settings.WiFiRestart_connection_lost());
    case LabelType::FORCE_WIFI_NOSLEEP:     return jsonBool(Settings.WifiNoneSleep());
    case LabelType::PERIODICAL_GRAT_ARP:    return jsonBool(Settings.gratuitousARP());
    case LabelType::CONNECTION_FAIL_THRESH: retval = Settings.ConnectionFailuresThreshold; break;
#ifndef ESP32
    case LabelType::WAIT_WIFI_CONNECT:      return jsonBool(Settings.WaitWiFiConnect());
#endif
    case LabelType::CONNECT_HIDDEN_SSID:    return jsonBool(Settings.IncludeHiddenSSID());
#ifdef ESP32
    case LabelType::WIFI_PASSIVE_SCAN:      return jsonBool(Settings.PassiveWiFiScan());
#endif
    case LabelType::HIDDEN_SSID_SLOW_CONNECT: return jsonBool(Settings.HiddenSSID_SlowConnectPerBSSID());
    case LabelType::SDK_WIFI_AUTORECONNECT: return jsonBool(Settings.SDK_WiFi_autoreconnect());
#if FEATURE_USE_IPV6
    case LabelType::ENABLE_IPV6:            return jsonBool(Settings.EnableIPv6());
#endif


    case LabelType::BUILD_DESC:             return getSystemBuildString();
    case LabelType::GIT_BUILD:
    {
      const String res(F(BUILD_GIT));

      if (!res.isEmpty()) { return res; }
      return get_git_head();
    }
    case LabelType::SYSTEM_LIBRARIES:       return getSystemLibraryString();
#ifdef ESP32
    case LabelType::ESP_IDF_SDK_VERSION:    return strformat(
      F("%d.%d.%d"), 
      ESP_IDF_VERSION_MAJOR, 
      ESP_IDF_VERSION_MINOR, 
      ESP_IDF_VERSION_PATCH);
#endif

    case LabelType::PLUGIN_COUNT:           retval = getDeviceCount() + 1; break;
    case LabelType::PLUGIN_DESCRIPTION:     return getPluginDescriptionString();
    case LabelType::BUILD_TIME:             return String(get_build_date()) + ' ' + get_build_time();
    case LabelType::BINARY_FILENAME:        return get_binary_filename();
    case LabelType::BUILD_PLATFORM:         return get_build_platform();
    case LabelType::GIT_HEAD:               return get_git_head();
    #ifdef CONFIGURATION_CODE
    case LabelType::CONFIGURATION_CODE_LBL: return getConfigurationCode();
    #endif // ifdef CONFIGURATION_CODE
    case LabelType::I2C_BUS_STATE:          return toString(I2C_state);
    case LabelType::I2C_BUS_CLEARED_COUNT:  retval = I2C_bus_cleared_count; break;
    case LabelType::SYSLOG_LOG_LEVEL:       return getLogLevelDisplayString(Settings.SyslogLevel);
    case LabelType::SERIAL_LOG_LEVEL:       return getLogLevelDisplayString(getSerialLogLevel());
    case LabelType::WEB_LOG_LEVEL:          return getLogLevelDisplayString(getWebLogLevel());
  #if FEATURE_SD
    case LabelType::SD_LOG_LEVEL:           return getLogLevelDisplayString(Settings.SDLogLevel);
  #endif // if FEATURE_SD

    case LabelType::ESP_CHIP_ID:            return formatToHex(getChipId(), 6);
    case LabelType::ESP_CHIP_FREQ:          retval = ESP.getCpuFreqMHz(); break;
#ifdef ESP32
    case LabelType::ESP_CHIP_XTAL_FREQ:     retval = getXtalFrequencyMHz(); break;
    case LabelType::ESP_CHIP_APB_FREQ:      retval = rtc_clk_apb_freq_get() / 1000000; break;
    //getApbFrequency() / 1000000; break;
#endif
    case LabelType::ESP_CHIP_MODEL:         return getChipModel();
    case LabelType::ESP_CHIP_REVISION:      return getChipRevision();
    case LabelType::ESP_CHIP_CORES:         retval = getChipCores(); break;
    case LabelType::BOARD_NAME:             return get_board_name();
    case LabelType::FLASH_CHIP_ID:          return formatToHex(getFlashChipId(), 6);
    case LabelType::FLASH_CHIP_VENDOR:      return formatToHex(getFlashChipId() & 0xFF, 2);
    case LabelType::FLASH_CHIP_MODEL:
    {
      const uint32_t flashChipId = getFlashChipId();
      const uint32_t flashDevice = (flashChipId & 0xFF00) | ((flashChipId >> 16) & 0xFF);
      return formatToHex(flashDevice, 4);
    }
    case LabelType::FLASH_CHIP_REAL_SIZE:   retval = getFlashRealSizeInBytes(); break;
    case LabelType::FLASH_CHIP_SPEED:       retval = getFlashChipSpeed() / 1000000; break;
    case LabelType::FLASH_IDE_SIZE:         break;
    case LabelType::FLASH_IDE_SPEED:        break;
    case LabelType::FLASH_IDE_MODE:         return getFlashChipMode();
    case LabelType::FLASH_WRITE_COUNT:      break;
    case LabelType::SKETCH_SIZE:            break;
    case LabelType::SKETCH_FREE:            break;
    case LabelType::FS_SIZE:                retval = SpiffsTotalBytes(); break;
    case LabelType::FS_FREE:                retval = SpiffsFreeSpace(); break;
    case LabelType::MAX_OTA_SKETCH_SIZE:    break;
    case LabelType::OTA_2STEP:              break;
    case LabelType::OTA_POSSIBLE:           break;
#if FEATURE_ETHERNET
    case LabelType::ETH_IP_ADDRESS:         return formatIP(NetworkLocalIP());
    case LabelType::ETH_IP_SUBNET:          return formatIP(NetworkSubnetMask());
    case LabelType::ETH_IP_ADDRESS_SUBNET:  return strformat(
                                                          F("%s / %s"),
                                                          getValue(LabelType::ETH_IP_ADDRESS).c_str(),
                                                          getValue(LabelType::ETH_IP_SUBNET).c_str());
    case LabelType::ETH_IP_GATEWAY:         return formatIP(NetworkGatewayIP());
    case LabelType::ETH_IP_DNS:             return formatIP(NetworkDnsIP(0));
    case LabelType::ETH_MAC:                return NetworkMacAddress().toString();
    case LabelType::ETH_DUPLEX:             return EthLinkUp() ? (EthFullDuplex() ? F("Full Duplex") : F("Half Duplex")) : F("Link Down");
    case LabelType::ETH_SPEED:              return EthLinkUp() ? getEthSpeed() : F("Link Down");
    case LabelType::ETH_STATE:              return EthLinkUp() ? F("Link Up") : F("Link Down");
    case LabelType::ETH_SPEED_STATE:        return EthLinkUp() ? getEthLinkSpeedState() : F("Link Down");
    case LabelType::ETH_CONNECTED:          return ETHConnected() ? F("CONNECTED") : F("DISCONNECTED"); // 0=disconnected, 1=connected
    case LabelType::ETH_CHIP:               return toString(Settings.ETH_Phy_Type);
#endif // if FEATURE_ETHERNET
# if FEATURE_ETHERNET || defined(USES_ESPEASY_NOW)
    case LabelType::ETH_WIFI_MODE:          return toString(active_network_medium);
#endif
    case LabelType::SKT:                    return node_time.getDateStringPlusDays(urun_skt[sec_URUN_buton], '-');
    case LabelType::SUNRISE:                return node_time.getSunriseTimeString(':');
    case LabelType::SUNSET:                 return node_time.getSunsetTimeString(':');
    case LabelType::SUNRISE_S:              retval = node_time.sunRise.tm_hour * 3600 + node_time.sunRise.tm_min * 60 + node_time.sunRise.tm_sec; break;
    case LabelType::SUNSET_S:               retval = node_time.sunSet.tm_hour * 3600 + node_time.sunSet.tm_min * 60 + node_time.sunSet.tm_sec; break;
    case LabelType::SUNRISE_M:              retval = node_time.sunRise.tm_hour * 60 + node_time.sunRise.tm_min; break;
    case LabelType::SUNSET_M:               retval = node_time.sunSet.tm_hour * 60 + node_time.sunSet.tm_min; break;
    case LabelType::ISNTP:                  return jsonBool(Settings.UseNTP());
    case LabelType::UPTIME_MS:              return ull2String(getMicros64() / 1000);
    case LabelType::TIMEZONE_OFFSET:        retval = Settings.TimeZone; break;
    case LabelType::LATITUDE:               return toString(Settings.Latitude, 6);
    case LabelType::LONGITUDE:              return toString(Settings.Longitude, 6);

    case LabelType::XML_TARIH_V:            return String(XML_TARIH_V);
    case LabelType::XML_SAAT_V:             return String(XML_SAAT_V);
    case LabelType::XML_NET_C:              return String(XML_NET_C);
    case LabelType::XML_NET_S:              return String(XML_NET_S);
    case LabelType::XML_DARA_C:             return String(XML_DARA_C);
    case LabelType::XML_DARA_S:             return String(XML_DARA_S);
    case LabelType::XML_BRUT_C:             return String(XML_BRUT_C);
    case LabelType::XML_BRUT_S:             return String(XML_BRUT_S);
    case LabelType::XML_ADET:               return String(XML_ADET_S);
    case LabelType::XML_NET_2:              return String(XML_NET_S_2);
    case LabelType::XML_DARA_2:             return String(XML_DARA_S_2);
    case LabelType::XML_BRUT_2:             return String(XML_BRUT_S_2);
    case LabelType::XML_ADET_GRAMAJ:        return String(XML_ADET_GRAMAJ_S);
    case LabelType::XML_URUN_NO:            return String(XML_URUN_NO_S);
    case LabelType::XML_URUN_ISMI:          return String(XML_URUN_ISMI_S);
    case LabelType::XML_URUN_KOD:           return String(XML_URUN_KOD_S);
    case LabelType::XML_URUN_MESAJ:         return String(XML_URUN_MESAJ_S);
    case LabelType::XML_BARKOD:             return String(XML_BARKOD_S);
    case LabelType::XML_BIRIM_FIYAT:        return String(XML_BIRIM_FIYAT_S);
    case LabelType::XML_TUTAR:              return String(XML_TUTAR_S);
    case LabelType::XML_SNO:                return String(XML_SNO_S);
    case LabelType::XML_SAYAC_1:            return String(XML_SAYAC_1_S);
    case LabelType::XML_SAYAC_2:            return String(XML_SAYAC_2_S);
    case LabelType::XML_SAYAC_3:            return String(XML_SAYAC_3_S);
    case LabelType::XML_SAYAC_4:            return String(XML_SAYAC_4_S);
    case LabelType::XML_SAYAC_1_C:          return String(XML_SAYAC_1_C);
    case LabelType::XML_SAYAC_2_C:          return String(XML_SAYAC_2_C);
    case LabelType::XML_SAYAC_3_C:          return String(XML_SAYAC_3_C);
    case LabelType::XML_SAYAC_4_C:          return String(XML_SAYAC_4_C);
    case LabelType::XML_SERI_NO:            return String(XML_SERI_NO_S);
    case LabelType::XML_PARTI_NO:           return node_time.getDateString('\0');//String(XML_PARTI_NO_S);
    case LabelType::XML_FIS_NO:             return String(XML_FIS_NO_S);
    case LabelType::XML_TOP_NET:            return String(XML_TOP_NET_C);//String(top_net, int(ExtraTaskSettings.TaskDeviceValueDecimals[0]));
    case LabelType::XML_TOP_DARA:           return String(XML_TOP_DARA_C);//String(top_dara, int(ExtraTaskSettings.TaskDeviceValueDecimals[1]));
    case LabelType::XML_TOP_BRUT:           return String(XML_TOP_BRUT_C);//String(top_brut, int(ExtraTaskSettings.TaskDeviceValueDecimals[2]));
    case LabelType::XML_TOP_ADET:           return String(XML_TOP_ADET_S);//String(top_adet, int(ExtraTaskSettings.TaskDeviceValueDecimals[3]));
    case LabelType::XML_EAN8:               return String(XML_EAN8_S);
    case LabelType::XML_EAN13:              return String(XML_EAN13_S);
    case LabelType::XML_QRKOD:              return String(XML_QRKOD_S);
    case LabelType::XML_STABIL:             return String(XML_STABIL_S);
    case LabelType::XML_MESAJ1:             return String(XML_MESAJ1_S);
    case LabelType::XML_MESAJ2:             return String(XML_MESAJ2_S);
    case LabelType::XML_MESAJ3:             return String(XML_MESAJ3_S);
    case LabelType::XML_MESAJ4:             return String(XML_MESAJ4_S); 
    case LabelType::XML_MESAJ5:             return String(XML_MESAJ5_S); 
    case LabelType::XML_MESAJ6:             return String(XML_MESAJ6_S);
    case LabelType::XML_MESAJ7:             return String(XML_MESAJ7_S); 
    case LabelType::XML_MESAJ8:             return String(XML_MESAJ8_S);
    case LabelType::XML_MESAJ9:             return String(XML_MESAJ9_S);
    case LabelType::XML_FISBAS1:            return String(XML_FIS_BASLIK1_S);
    case LabelType::XML_FISBAS2:            return String(XML_FIS_BASLIK2_S);
    case LabelType::XML_FISBAS3:            return String(XML_FIS_BASLIK3_S);
    case LabelType::XML_FISBAS4:            return String(XML_FIS_BASLIK4_S);

    case LabelType::XML_V0:                 return String(XML_V0);
    case LabelType::XML_V1:                 return String(XML_V1);
    case LabelType::XML_V2:                 return String(XML_V2);
    case LabelType::XML_V3:                 return String(XML_V3);
    case LabelType::XML_V4:                 return String(XML_V4);
    case LabelType::XML_V5:                 return String(XML_V5);
    case LabelType::XML_V6:                 return String(XML_V6);
    case LabelType::XML_V7:                 return String(XML_V7);
    case LabelType::XML_V8:                 return String(XML_V8);
    case LabelType::XML_V9:                 return String(XML_V9);
    case LabelType::XML_V10:                return String(XML_V10);
    case LabelType::XML_V11:                return String(XML_V11);
    case LabelType::XML_V12:                return String(XML_V12);
    case LabelType::XML_V13:                return String(XML_V13);
    case LabelType::XML_V14:                return String(XML_V14);
    case LabelType::XML_V15:                return String(XML_V15);
    case LabelType::XML_V16:                return String(XML_V16);
    case LabelType::XML_V17:                return String(XML_V17);
    case LabelType::XML_V18:                return String(XML_V18);
    case LabelType::XML_V19:                return String(XML_V19);
    case LabelType::XML_V20:                return String(XML_V20);
    case LabelType::XML_V21:                return String(XML_V21);
    case LabelType::XML_V22:                return String(XML_V22);
    case LabelType::XML_V23:                return String(XML_V23);
    case LabelType::XML_V24:                return String(XML_V24);
    case LabelType::XML_V25:                return String(XML_V25);
    case LabelType::XML_V26:                return String(XML_V26);
    case LabelType::XML_V27:                return String(XML_V27);
    case LabelType::XML_V28:                return String(XML_V28);
    case LabelType::XML_V29:                return String(XML_V29);

    case LabelType::KFONT1:                 return String(kfont1);
    case LabelType::KFONT2:                 return String(kfont2);
    case LabelType::KFONT3:                 return String(kfont3);
    case LabelType::KFONT4:                 return String(kfont4);
    case LabelType::KFONT5:                 return String(kfont5);
    case LabelType::KFONT6:                 return String(kfont6);

    case LabelType::FONT1:                  return String(font1);
    case LabelType::FONT2:                  return String(font2);
    case LabelType::FONT3:                  return String(font3);
    case LabelType::FONT4:                  return String(font4);
    case LabelType::FONT5:                  return String(font5);
    case LabelType::FONT6:                  return String(font6);

    case LabelType::LOGO:                   return String(logo);
    case LabelType::SOL:                    return String(sol);
    case LabelType::ORTA:                   return String(orta);
    case LabelType::SAG:                    return String(sag);
    case LabelType::BEYAZ:                  return String(beyaz);
    case LabelType::SIYAH:                  return String(siyah);
    case LabelType::KOYU:                   return String(koyu);
    case LabelType::ACIK:                   return String(acik);
    case LabelType::KES:                    return String(kes);
    case LabelType::CEKMECE:                return String(cekmece);
    //case LabelType::ALTCIZGIPASIF:          return String(altcizgipasif);
    //case LabelType::ALTCIZGIAKTIF:          return String(altcizgiaktif);
    //case LabelType::QRKODBAS:               return String(qrkodbas);
    //case LabelType::QRKODSON:               return String(qrkodson);
    
    case LabelType::XML_FIRMA_ISMI:          return String(XML_FIRMA_ISMI_S);
    case LabelType::XML_MUSTERI_ISMI:        return String(XML_MUSTERI_ISMI_S);
    case LabelType::XML_PLAKA_NO:           return String(XML_PLAKA_NO_S);
    case LabelType::XML_OPERATOR:           return String(XML_OPERATOR_ISMI_S);
    case LabelType::XML_NET_V:              return String(XML_NET_V);
    case LabelType::XML_DARA_V:             return String(XML_DARA_V);
    case LabelType::XML_BRUT_V:             return String(XML_BRUT_V);

    case LabelType::IRDA_DATA:              return String(IRDA_DATA_S);

    case LabelType::XML_TOPLAM_DETAY:       return String(toplam_detay);

    case LabelType::MAX_LABEL:
      break;
  }
  if (retval != INT_MAX) return String(retval);
  return F("MissingString");
}

#if FEATURE_ETHERNET
String getEthSpeed() {
  return strformat(F("%d [Mbps]"), EthLinkSpeed());
}

String getEthLinkSpeedState() {
  if (EthLinkUp()) {
    return strformat(F("%s %s %s"), 
    getValue(LabelType::ETH_STATE).c_str(), 
    getValue(LabelType::ETH_DUPLEX).c_str(), 
    getEthSpeed().c_str());
  }
  return getValue(LabelType::ETH_STATE);
}

#endif // if FEATURE_ETHERNET

String getExtendedValue(LabelType::Enum label) {
  switch (label)
  {
    case LabelType::UPTIME:
    {
      return minutesToDayHourMinute(getUptimeMinutes());
    }

    default:
      break;
  }
  return EMPTY_STRING;
}

String getFormNote(LabelType::Enum label)
{
  // Keep flash string till the end of the function, to reduce build size
  // Otherwise lots of calls to String() constructor are included.
  const __FlashStringHelper *flash_str = F("");

  switch (label) {
#ifndef MINIMAL_OTA
    case LabelType::CONNECT_HIDDEN_SSID:
      flash_str = F("Must be checked to connect to a hidden SSID");
      break;
#ifdef ESP32
    case LabelType::WIFI_PASSIVE_SCAN:
      flash_str = F("Passive scan listens for WiFi beacons, Active scan probes for AP. Passive scan is typically faster.");
      break;
#endif // ifdef ESP32
    case LabelType::HIDDEN_SSID_SLOW_CONNECT:
      flash_str = F("Required for some AP brands like Mikrotik to connect to hidden SSID");
      break;
#if FEATURE_USE_IPV6
    case LabelType::ENABLE_IPV6:
      flash_str = F("Toggling IPv6 requires reboot");
      break;
#endif // if FEATURE_USE_IPV6
#ifndef NO_HTTP_UPDATER
    case LabelType::ALLOW_OTA_UNLIMITED:
      flash_str = F("When enabled, OTA updating can overwrite the filesystem and settings!<br>Requires reboot to activate");
      break;
#endif // ifndef NO_HTTP_UPDATER
#if FEATURE_RULES_EASY_COLOR_CODE
    case LabelType::DISABLE_RULES_AUTOCOMPLETE:
      flash_str = F("Also disables Rules syntax highlighting!");
      break;
#endif // if FEATURE_RULES_EASY_COLOR_CODE

    case LabelType::FORCE_WIFI_NOSLEEP:
      flash_str = F("Change WiFi sleep settings requires reboot to activate");
      break;

    case LabelType::CPU_ECO_MODE:
      flash_str = F("Node may miss receiving packets with Eco mode enabled");
      break;

    case LabelType::WIFI_NR_EXTRA_SCANS:
      flash_str = F("Number of extra times to scan all channels to have higher chance of finding the desired AP");
      break;
#ifndef ESP32
    case LabelType::WAIT_WIFI_CONNECT:
      flash_str = F("Wait for 1000 msec right after connecting to WiFi.<BR>May improve success on some APs like Fritz!Box");
      break;
#endif

#endif

#if FEATURE_SET_WIFI_TX_PWR
    case LabelType::WIFI_TX_MAX_PWR:
    case LabelType::WIFI_SENS_MARGIN:
    {
      float maxTXpwr;
      float sensitivity = GetRSSIthreshold(maxTXpwr);
      if (LabelType::WIFI_TX_MAX_PWR == label) {
        return strformat(
          F("Current max: %.2f dBm"), maxTXpwr);
      }
      return strformat(
        F("Adjust TX power to target the AP with (sensitivity + margin) dBm signal strength. Current sensitivity: %.2f dBm"),
        sensitivity);
    }
#endif // if FEATURE_SET_WIFI_TX_PWR

    default:
      return EMPTY_STRING;
  }

  return flash_str;
}


String getFormUnit(LabelType::Enum label)
{
    const __FlashStringHelper *flash_str = F("");

  switch (label) {
#if FEATURE_SET_WIFI_TX_PWR
    case LabelType::WIFI_TX_MAX_PWR:
    case LabelType::WIFI_CUR_TX_PWR:
    case LabelType::WIFI_RSSI:
      flash_str = F("dBm");
      break;
    case LabelType::WIFI_SENS_MARGIN:
      flash_str = F("dB");
      break;
#endif
    case LabelType::TIME_WANDER:
      flash_str = F("ppm");
      break;
#ifdef ESP32
    case LabelType::HEAP_SIZE:
    case LabelType::HEAP_MIN_FREE:
    #ifdef BOARD_HAS_PSRAM
    case LabelType::PSRAM_SIZE:
    case LabelType::PSRAM_FREE:
    case LabelType::PSRAM_MIN_FREE:
    case LabelType::PSRAM_MAX_FREE_BLOCK:
    #endif // BOARD_HAS_PSRAM
#endif // ifdef ESP32
    case LabelType::FREE_MEM:
    case LabelType::FREE_STACK:
#ifdef USE_SECOND_HEAP
    case LabelType::FREE_HEAP_IRAM:
#endif
#if defined(CORE_POST_2_5_0) || defined(ESP32)
  #ifndef LIMIT_BUILD_SIZE
    case LabelType::HEAP_MAX_FREE_BLOCK:
  #endif
#endif // if defined(CORE_POST_2_5_0) || defined(ESP32)

      flash_str = F("byte");
      break;
    case LabelType::FLASH_CHIP_REAL_SIZE:
    case LabelType::FLASH_IDE_SIZE:
      flash_str = F("kB");
      break;
/*
    case LabelType::UPTIME:
      flash_str = F("min");
      break;
*/
    case LabelType::LOAD_PCT:
#if defined(CORE_POST_2_5_0)
  #ifndef LIMIT_BUILD_SIZE
    case LabelType::HEAP_FRAGMENTATION:
  #endif
#endif // if defined(CORE_POST_2_5_0)

      flash_str = F("%");
      break;

    case LabelType::ESP_CHIP_FREQ:
#ifdef ESP32
    case LabelType::ESP_CHIP_XTAL_FREQ:
    case LabelType::ESP_CHIP_APB_FREQ:
#endif
    case LabelType::FLASH_CHIP_SPEED:
    case LabelType::FLASH_IDE_SPEED:
      flash_str = F("MHz");
      break;
#if FEATURE_INTERNAL_TEMPERATURE
    case LabelType::INTERNAL_TEMPERATURE:
      flash_str = F("&deg;C");
      break;
#endif // if FEATURE_INTERNAL_TEMPERATURE



    default:
      return EMPTY_STRING;
  }

  return flash_str;
}