#ifdef CONTINUOUS_INTEGRATION
# pragma GCC diagnostic error "-Wall"
#else // ifdef CONTINUOUS_INTEGRATION
# pragma GCC diagnostic warning "-Wall"
#endif // ifdef CONTINUOUS_INTEGRATION

#include <Arduino.h>      // 📌 Arduino framework desteği

// Include this as first, to make sure all defines are active during the entire compile.
// See: https://www.letscontrolit.com/forum/viewtopic.php?f=4&t=7980
// If Custom.h build from Arduino IDE is needed, uncomment #define USE_CUSTOM_H in ESPEasy_common.h
#include "ESPEasy_common.h"
#include "ESPEasy-Globals.h"
#include "src/Globals/Settings.h"

#include "Custom.h"

// Global variables
struct EventStruct TempEvent;
const uint16_t MIN_FREE_MEMORY = 2048; // Minimum free memory in bytes

//#define USB_ACTIVE
//define LVGL_ACTIVE

//#define ESP_NOW_ACTIVE

#ifdef ESP_NOW_ACTIVE
#include "src/Globals/Settings.h"
#include <ctype.h> // isdigit fonksiyonu için

void updatePeerStatus(const uint8_t *mac_addr, bool active) {
  for (int i = 0; i < peerStatusCount; i++) {
    if (memcmp(peerStatusList[i].mac, mac_addr, 6) == 0) {
      peerStatusList[i].active = active;
      return;
    }
  }

  if (peerStatusCount < MAX_PAIRED_DEVICES) {
    memcpy(peerStatusList[peerStatusCount].mac, mac_addr, 6);
    peerStatusList[peerStatusCount].active = active;
    peerStatusCount++;
  }
}

void LoadPairedMac() {
  preferences.begin("espnow", true);
  int macDataLength = preferences.getBytesLength("paired_mac");
  pairedDeviceCount = macDataLength / 6;
  if (pairedDeviceCount > MAX_PAIRED_DEVICES) pairedDeviceCount = MAX_PAIRED_DEVICES;
  if (pairedDeviceCount > 0) {
    preferences.getBytes("paired_mac", pairedMacList, macDataLength);
    isPaired = true;
    for (int i = 0; i < pairedDeviceCount; i++) {
      esp_now_peer_info_t peerInfo = {};
      memcpy(peerInfo.peer_addr, pairedMacList[i], 6);
      peerInfo.channel = 0;
      peerInfo.encrypt = false;
      esp_now_add_peer(&peerInfo);
      updatePeerStatus(pairedMacList[i], false);
    }
  } else {
    isPaired = false;
  }
  preferences.end();
}

void RemovePairedMac(const char* macStr) {
  uint8_t mac[6];
  sscanf(macStr, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
         &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]);

  int index = -1;
  for (int i = 0; i < pairedDeviceCount; i++) {
    if (memcmp(pairedMacList[i], mac, 6) == 0) {
      index = i;
      break;
    }
  }

  if (index >= 0) {
    // listedeki öğeyi kaydırarak sil
    for (int i = index; i < pairedDeviceCount - 1; i++) {
      memcpy(pairedMacList[i], pairedMacList[i + 1], 6);
    }
    pairedDeviceCount--;

    // preferences’a gerçekten yaz
    preferences.begin("espnow", false);
    if (pairedDeviceCount > 0) {
      preferences.putBytes("paired_mac", pairedMacList, pairedDeviceCount * 6);
    } else {
      preferences.remove("paired_mac");  // hepsi silindiyse key'i kaldır
    }
    preferences.end();

    // RAM'den ve esp-now'dan da çıkar
    esp_now_del_peer(mac);
    Serial.println("🧹 MAC başarıyla silindi.");
  } else {
    Serial.println("⚠️ MAC adresi listede bulunamadı.");
  }
}

void addToDiscoveredList(const uint8_t *mac_addr) {
  for (int i = 0; i < pairedDeviceCount; i++) {
    if (memcmp(pairedMacList[i], mac_addr, 6) == 0) return;
  }
  for (int i = 0; i < discoveredCount; i++) {
    if (memcmp(discoveredMacList[i], mac_addr, 6) == 0) return;
  }
  if (discoveredCount < MAX_PAIRED_DEVICES) {
    memcpy(discoveredMacList[discoveredCount], mac_addr, 6);
    discoveredCount++;
  }
}

void SavePairedMac(const uint8_t *newMac) {
  preferences.begin("espnow", false);
  pairedDeviceCount = preferences.getBytesLength("paired_mac") / 6;
  if (pairedDeviceCount > MAX_PAIRED_DEVICES) pairedDeviceCount = MAX_PAIRED_DEVICES;
  preferences.getBytes("paired_mac", pairedMacList, pairedDeviceCount * 6);

  bool alreadyExists = false;
  for (int i = 0; i < pairedDeviceCount; i++) {
    if (memcmp(pairedMacList[i], newMac, 6) == 0) {
      alreadyExists = true;
      break;
    }
  }

  if (!alreadyExists) {
    if (pairedDeviceCount < MAX_PAIRED_DEVICES) {
      memcpy(pairedMacList[pairedDeviceCount], newMac, 6);
      pairedDeviceCount++;
    } else {
      for (int i = 0; i < MAX_PAIRED_DEVICES - 1; i++) {
        memcpy(pairedMacList[i], pairedMacList[i + 1], 6);
      }
      memcpy(pairedMacList[MAX_PAIRED_DEVICES - 1], newMac, 6);
    }
  }

  preferences.putBytes("paired_mac", pairedMacList, pairedDeviceCount * 6);
  preferences.end();

  updatePeerStatus(newMac, true);
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, newMac, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if (!esp_now_is_peer_exist(newMac)) {
    esp_now_add_peer(&peerInfo);
  }

  Serial.println("✅ Eşleşmiş MAC adresi kaydedildi.");
}

void PrintMacAddress(const uint8_t *mac) {
  Serial.print("MAC Adresi: ");
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02X", mac[i]);
    if (i < 5) Serial.print(":");
  }
  Serial.println();
}

String macToStr(const uint8_t *mac) {
  char buf[18];
  snprintf(buf, sizeof(buf), "%02X:%02X:%02X:%02X:%02X:%02X",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(buf);
}

void AddPeer(const uint8_t *mac_addr) {
  if (esp_now_is_peer_exist(mac_addr)) {
    Serial.println("ℹ️ Peer zaten kayıtlı.");
    return;
  }

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, mac_addr, 6);
  peerInfo.channel = 0;         // aynı kanal
  peerInfo.encrypt = false;     // şifreleme kullanmıyoruz

  esp_err_t result = esp_now_add_peer(&peerInfo);
  if (result == ESP_OK) {
    Serial.print("✅ Peer eklendi: ");
    PrintMacAddress(mac_addr);
  } else {
    Serial.printf("❌ Peer eklenemedi! Hata kodu: %d\n", result);
  }
}


void OnDataRecv(const esp_now_recv_info_t *esp_now_info, const uint8_t *data, int len) {
  const uint8_t *mac_addr = esp_now_info->src_addr;
  addToDiscoveredList(mac_addr);  
  hataTimer_l = millis();
  char receivedData[len + 1];
  memcpy(receivedData, data, len);
  receivedData[len] = '\0';

  if (strcmp(receivedData, "PAIR_REQUEST") == 0) {
    Serial.println("Eslesme Istegi Alindi!");
    const char *response = "PAIR_RESPONSE";
	  esp_now_send(mac_addr, (uint8_t *)response, strlen(response));
    isPaired = true;
	  SavePairedMac(mac_addr);
	  AddPeer(mac_addr);
    return;
  }

  else if (strcmp(receivedData, "PAIR_DEL") == 0) {
    Serial.println("🧹 Pair silme komutu alındı!");
    String macStr = macToStr(mac_addr);
    RemovePairedMac(macStr.c_str());
  }
  
  else if (strcmp(receivedData, "PAIR_RESPONSE") == 0) {
    Serial.println("Eslesme Yaniti Alindi!");
    isPaired = true;
	  SavePairedMac(mac_addr);
	  PrintMacAddress(mac_addr);
    return;
  }

  else if (strcmp(receivedData, "inddara") == 0) {
    Serial.println("DARA!");
	  digitalWrite(4,LOW);
	  delay(1000);
	  digitalWrite(4,HIGH);
  }
  else {
	  String formattedText = String(receivedData);
	  Serial.print("Gelen veri: ");
	  Serial.println(receivedData);
    //XML_NET_C = formattedText.c_str();
    //dtostrf(XML_NET_S.toFloat(), (ExtraTaskSettings.TaskDeviceValueBit[0] - ExtraTaskSettings.TaskDeviceValueBas[0]), ExtraTaskSettings.TaskDeviceValueDecimals[0], XML_NET_C);
    XML_NET_S = formattedText;
    //strncpy(XML_NET_C, formattedText.c_str(), sizeof(XML_NET_C));
    strlcpy(XML_NET_C, formattedText.c_str(), sizeof(XML_NET_C)); // Espressif destekli

    //XML_NET_C[sizeof(XML_NET_C)-1] = '\0';
	  // Gelen veriyi sabit olarak LED ekrana yazdır
	  // display.displayText(receivedData.c_str(), PA_CENTER, 0, 0, PA_NO_EFFECT, PA_NO_EFFECT); // Sabit pozisyon belirle
  }
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  updatePeerStatus(mac_addr, status == ESP_NOW_SEND_SUCCESS);
}

void SendData(String data) {
  if (!isPaired || pairedDeviceCount == 0) return;

  for (int i = 0; i < pairedDeviceCount; i++) {
    esp_err_t result = esp_now_send(pairedMacList[i], (uint8_t *)data.c_str(), data.length());
    updatePeerStatus(pairedMacList[i], result == ESP_OK);
  }
}
#endif

//#include "ESPEasy-Globals.h"
#include "generated/buton_json_lfs.h"

//#include "gfx_conf.h"

#define TFT_HOR_RES   480
//#define TFT_VER_RES   320
#define TFT_VER_RES   272

//#define TFT_HOR_RES   800
//#define TFT_VER_RES   480

#ifdef USE_CUSTOM_H
// make the compiler show a warning to confirm that this file is inlcuded
  # warning "**** Using Settings from Custom.h File ***"
#endif // ifdef USE_CUSTOM_H

// Needed due to preprocessor issues.
#ifdef PLUGIN_SET_GENERIC_ESP32
  # ifndef ESP32
    #  define ESP32
  # endif // ifndef ESP32
#endif // ifdef PLUGIN_SET_GENERIC_ESP32

/**************** LVGL AKTİF **************/
#ifdef LVGL_ACTIVE
SemaphoreHandle_t gui_mutex = NULL;

/*#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>*/
#include <ArduinoJson.h>
#include "generated/gui_guider.h"
lv_ui guider_ui;

/*#define LV_CANVAS_WIDTH  480
#define LV_CANVAS_HEIGHT 320

lv_obj_t *canvas;
lv_color_t *canvas_buffer;

AsyncWebServer server(81);
AsyncWebSocket ws("/ws");*/

/* Display flushing */
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
  uint32_t w = lv_area_get_width(area);
  uint32_t h = lv_area_get_height(area);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  
  // px_map'ı RGB565 formatına çevir
  uint16_t *buffer = (uint16_t *)px_map;
  tft.pushPixels(buffer, w * h, true);

  tft.endWrite();
  lv_display_flush_ready(disp);
}

/*unsigned long lastTouchTime = 0;
void adjustScreenBrightness() {
    if (millis() - lastTouchTime > 60000) {  // 60 saniye dokunma yoksa parlaklığı düşür
        tft.setBrightness_lgfx(50);
    } else {
        tft.setBrightness_lgfx(255);
    }
}*/

/*Read the touchpad*/
void my_touchpad_read(lv_indev_t *indev, lv_indev_data_t *data) {
  uint16_t touchX, touchY;
  bool touched = tft.getTouch(&touchX, &touchY);

  if (!touched) {
      data->state = LV_INDEV_STATE_RELEASED;
  } else {
      data->state = LV_INDEV_STATE_PRESSED;
      data->point.x = touchX;
      data->point.y = touchY;
      //lastTouchTime = millis();  // Dokunma algılandı, parlaklığı arttır
  }
  //adjustScreenBrightness();
}

void display_init() {
  // I2C bus reset (soft reset sonrası stuck I2C hatlarını temizle)
  // SC07 kullanıyor: Touch controller I2C üzerinden - reset gerekli
  tft.begin();  // LovyanGFX begin() I2C'yi initialize eder
  
  tft.init();
  tft.initDMA();
  /*if (Settings.WebAPP == 120)
    tft.setRotation(1);
  else if (Settings.WebAPP == 130)
    tft.setRotation(3);
  else
    tft.setRotation(3);*/
  tft.setRotation(2);
  //tft.setBrightness_lgfx(255);
  tft.setBrightness(255);
  tft.fillScreen(TFT_WHITE);
}

// Minimum RAM limiti, 4KB kritik (ESP32 için güvenli alt sınır)
#define CRITICAL_FREE_MEMORY 4096      // 4KB
#define WARNING_FREE_MEMORY  20000     // 20KB (uyarı eşiği)

void optimizeHeap() {
    const size_t freeMem = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    const size_t minMem  = heap_caps_get_minimum_free_size(MALLOC_CAP_8BIT);

    #if CONFIG_SPIRAM
    const size_t freePsram = heap_caps_get_free_size(MALLOC_CAP_SPIRAM);
    const size_t minPsram  = heap_caps_get_minimum_free_size(MALLOC_CAP_SPIRAM);
    #else
    const size_t freePsram = 0, minPsram = 0;
    #endif

    // Log RAM durumu
    Serial.printf("[MEM] Free: %u, Min: %u | PSRAM Free: %u, Min: %u\n",
                  freeMem, minMem, freePsram, minPsram);

    // **KRİTİK RAM OUT DURUMU**: Donma riskinde hemen resetle!
    if (minMem < CRITICAL_FREE_MEMORY || freeMem < CRITICAL_FREE_MEMORY
        #if CONFIG_SPIRAM
        || minPsram < CRITICAL_FREE_MEMORY || freePsram < CRITICAL_FREE_MEMORY
        #endif
        ) {
        Serial.println("‼️ Kritik RAM! Otomatik reset atılıyor...");
        delay(2000); // logun gitmesine izin ver
        ESP.restart();
    }

    // **UYARI EŞİĞİ**: RAM düşüşteyse gizli LVGL objeleri sil
    if (freeMem < WARNING_FREE_MEMORY) {
        if (xSemaphoreTake(gui_mutex, portMAX_DELAY) == pdTRUE) {
            lv_obj_t *scr = lv_scr_act();
            uint32_t child_count = lv_obj_get_child_cnt(scr);
            for (uint32_t i = 0; i < child_count; i++) {
                lv_obj_t *child = lv_obj_get_child(scr, i);
                if (lv_obj_has_flag(child, LV_OBJ_FLAG_HIDDEN)) {
                    lv_obj_del(child); // sadece gizli olanları sil
                    Serial.println("🧹 Gizli LVGL obje silindi.");
                }
            }
            xSemaphoreGive(gui_mutex);
        }
    }
}

// **RAM Watchdog + Memory Manager Task**
void Task_Memory_Manager(void *pvParameters) {
    while (true) {
        optimizeHeap();
        vTaskDelay(pdMS_TO_TICKS(5000));  // 15 saniyede bir kontrol et
    }
}

/***************** WebSocket Event Handler *****************/
/*void onWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo *)arg;
  if (info->final && info->opcode == WS_TEXT) {
      String message = String((char *)data);
      DynamicJsonDocument doc(256);
      DeserializationError error = deserializeJson(doc, message);

      if (!error) {
          if (doc["type"] == "touch") {
              int touchX = doc["x"];
              int touchY = doc["y"];
              Serial.printf("Web'den Dokunmatik: X=%d, Y=%d\n", touchX, touchY);

              lv_indev_data_t touchData;
              touchData.state = LV_INDEV_STATE_PRESSED;
              touchData.point.x = touchX;
              touchData.point.y = touchY;
              my_touchpad_read(NULL, &touchData);
          }
      }
  }
}

void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_CONNECT) {
      Serial.printf("WebSocket Bağlandı: %d\n", client->id());
  } else if (type == WS_EVT_DISCONNECT) {
      Serial.printf("WebSocket Ayrıldı: %d\n", client->id());
  } else if (type == WS_EVT_DATA) {
      onWebSocketMessage(arg, data, len);
  }
}*/

/************ LVGL UI ve Bellek Yönetimi ************/
/*void setupLVGLCanvas() {
  canvas_buffer = (lv_color_t *)heap_caps_malloc(LV_CANVAS_WIDTH * LV_CANVAS_HEIGHT * sizeof(lv_color_t), MALLOC_CAP_DMA);
  if (!canvas_buffer) {
      Serial.println("HATA: Bellek tahsisi başarısız!");
      return;
  }
  canvas = lv_canvas_create(lv_scr_act());
  lv_canvas_set_buffer(canvas, canvas_buffer, LV_CANVAS_WIDTH, LV_CANVAS_HEIGHT, LV_COLOR_FORMAT_RGB565);
  lv_obj_align(canvas, LV_ALIGN_CENTER, 0, 0);
}

void sendLVGLFrame() {
  if (!canvas_buffer) return;
  lv_refr_now(NULL);
  lv_canvas_fill_bg(canvas, lv_color_black(), LV_OPA_COVER);
  lv_obj_update_layout(canvas);
  lv_obj_invalidate(canvas);
  ws.binaryAll((uint8_t *)canvas_buffer, LV_CANVAS_WIDTH * LV_CANVAS_HEIGHT * sizeof(lv_color_t));
}*/
#endif

/**************** LVGL AKTİF **************/

// Must be included after all the defines, since it is using TASKS_MAX
#include "_Plugin_Helper.h"

// Plugin helper needs the defined controller sets, thus include after 'define_plugin_sets.h'
#include "src/Helpers/_CPlugin_Helper.h"

#include "src/ESPEasyCore/ESPEasy_setup.h"
#include "src/ESPEasyCore/ESPEasy_loop.h"

#ifdef PHASE_LOCKED_WAVEFORM
# include <core_esp8266_waveform.h>
#endif // ifdef PHASE_LOCKED_WAVEFORM

#if FEATURE_ADC_VCC
ADC_MODE(ADC_VCC);
#endif // if FEATURE_ADC_VCC

#ifdef CORE_POST_2_5_0

/*********************************************************************************************\
* Pre-init
\*********************************************************************************************/
void preinit();
void preinit() {
  system_phy_set_powerup_option(3);
  // Global WiFi constructors are not called yet
  // (global class instances like WiFi, Serial... are not yet initialized)..
  // No global object methods or C++ exceptions can be called in here!
  // The below is a static class method, which is similar to a function, so it's ok.
  #ifndef CORE_POST_3_0_0
  //ESP8266WiFiClass::preinitWiFiOff();
  #endif

  // Prevent RF calibration on power up.
  // TD-er: disabled on 2021-06-07 as it may cause several issues with some boards.
  // It cannot be made a setting as we can't read anything of our own settings.
  //system_phy_set_powerup_option(RF_NO_CAL);
}

#endif // ifdef CORE_POST_2_5_0

/**************** LVGL AKTİF **************/
#ifdef LVGL_ACTIVE

#define BIT_0 (1 << 0)
#define BIT_1 (1 << 1)

EventGroupHandle_t eventGroup;

void Task_ESPEasy(void *pvParameters) {
  while (true) {
    xEventGroupSetBits(eventGroup, BIT_1);
    ESPEasy_loop();
    vTaskDelay(pdMS_TO_TICKS(20));
  }
  vTaskDelete(NULL);
}

void Task_LVGL(void *pvParameters) {
  unsigned long lastTick = millis();
  const int LVGL_REFRESH_PERIOD_MS = 5;
  while (true) {
    // 🔹 Zamanlayıcı olaylarını bekle
    xEventGroupWaitBits(eventGroup, BIT_1, pdTRUE, pdFALSE, portMAX_DELAY);
    // 🔹 millis() sıfırlanmasını kontrol et
    unsigned long now = millis();
    unsigned long elapsed = now - lastTick;
    if (elapsed >= LVGL_REFRESH_PERIOD_MS) {
      lv_tick_inc(elapsed);
      lastTick = now;
      if (xSemaphoreTake(gui_mutex, portMAX_DELAY) == pdTRUE) {
        lv_timer_handler();
        xSemaphoreGive(gui_mutex);
      }
    }
    // 🔹 Daha uzun gecikme süresi (50~100ms)
    vTaskDelay(pdMS_TO_TICKS(LVGL_REFRESH_PERIOD_MS));
  }
  vTaskDelete(NULL);
}

#include "src/ESPEasyCore/ESPEasyWifi.h"

#endif
/**************** LVGL AKTİF **************/

void loadButtonConfigs() {
  for (uint8_t i = 0; i < SEC_M_BUTON_COUNT; i++) {
      sec_M_buton[i] = readEEPROM(static_cast<EEPROM_Address>(ADDR_SEC_M_BUTON[i]));
      sec_F_buton[i] = readEEPROM(static_cast<EEPROM_Address>(ADDR_SEC_F_BUTON[i]));
  }
}

void loadButtonActiveStates() {
  for (int i = 0; i < MAKTIF_BUTTON_COUNT; i++) {
      //writeEEPROM(static_cast<EEPROM_Address>(ADDR_M_BUTON_AKTIF[i]), M_buton_aktif[i] ? 1 : 0);  // Bool değeri EEPROM'a kaydet
      M_buton_aktif[i] = readEEPROM(static_cast<EEPROM_Address>(ADDR_M_BUTON_AKTIF[i]));
  }
  // net_label daha önce ADDR_MAX hatası nedeniyle hiç erişilemedi; şimdi gerçek EEPROM değerini normalize ediyoruz.
  uint8_t raw_net = readEEPROM(static_cast<EEPROM_Address>(ADDR_NET_LABEL));
  // Geçersiz ya da ilk kullanım (0xFF veya >1) ise varsayılan TRUE yapıp EEPROM'a yaz.
  if (raw_net == 0xFF || raw_net > 1) {
    net_label = true; // Varsayılanı burada değiştirilebilir (false istiyorsan true yerine false yaz)
    writeEEPROM(static_cast<EEPROM_Address>(ADDR_NET_LABEL), net_label ? 1 : 0);
  } else {
    net_label = (raw_net != 0);
  }
}

void loadeeprom() {
  randomNumber = random(1000, 9999);
  String fisno = node_time.getTimeString('0');
  fis_no = fisno.toInt();
  int address = 0;
  seri_no = EEPROM.readLong(address);
  address += sizeof(uint32_t);
  sno = EEPROM.readLong(address);
  XML_SNO_S = String(sno);
  address += sizeof(uint32_t);
  top_net = EEPROM.readFloat(address);
  XML_TOP_NET_S = String(top_net);
  address += sizeof(float);
  top_adet = EEPROM.readLong(address);
  XML_TOP_ADET_S = String(top_adet);

  XML_SAYAC_1_S = String(EEPROM.readLong(100));
  dtostrf(XML_SAYAC_1_S.toInt(), 4, 0, XML_SAYAC_1_C);
  XML_SAYAC_1_SONSUZ_S = String(EEPROM.readLong(110));
  XML_SAYAC_2_S = String(EEPROM.readLong(104));
  dtostrf(XML_SAYAC_2_S.toInt(), 4, 0, XML_SAYAC_2_C);
  XML_SAYAC_3_S = String(EEPROM.readLong(118));
  dtostrf(XML_SAYAC_3_S.toInt(), 4, 0, XML_SAYAC_3_C);
  XML_SAYAC_4_S = String(EEPROM.readLong(126));
  dtostrf(XML_SAYAC_4_S.toInt(), 4, 0, XML_SAYAC_4_C);
}

#ifdef ESP_NOW_ACTIVE
void ESP_NOW() {

esp_now_register_send_cb(OnDataSent);

LoadPairedMac();

if (!isPaired && !preferences.getBytesLength("paired_mac")) {
    Serial.println("Eslesmis Cihaz Yok. Eslesme Bekleniyor."); 
} else {
    Serial.println("Eslesmis cihaz bulundu:");
    
    // 'i' degiskenini 0 olarak baslat ve kayıtlı cihaz sayısına gore dongu yap
    int maxDeviceCount = sizeof(pairedMacList) / sizeof(pairedMacList[0]);
    for (int i = 0; i < pairedDeviceCount && i < maxDeviceCount; i++) {
        if (pairedMacList[i] != nullptr) { // Gecerli MAC adresi kontrolu
            AddPeer(pairedMacList[i]); // Eslesmis cihazı peer olarak ekle
            Serial.printf("Peer eklendi: Cihaz %d\n", i);
        } else {
            Serial.printf("Gecersiz MAC adresi: Cihaz %d\n", i);
        }
    }
  }
  
    // Gelen veri için callback fonksiyonu
    esp_now_register_recv_cb(OnDataRecv);
  
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    // esp_now_add_peer çağrısını değişkene ata
    esp_err_t err = esp_now_add_peer(&peerInfo);

    if (esp_now_add_peer(&peerInfo) == ESP_OK) {
        Serial.println("Eslesme Istegi Basariyla Gonderildi.");
    } else {
        Serial.printf("Eslesme Istegi Gonderilemedi. Hata: %d (0x%X)\n", (int)err, (unsigned)err);
    }
}
#endif

// Task stack boyutları için sabitler
#define TASK_LVGL_STACK_SIZE (1024 * 32)
#define TASK_ESPEASY_STACK_SIZE (1024 * 8)
#define TASK_MEMORY_STACK_SIZE 4096

// Task öncelikleri
#define TASK_LVGL_PRIORITY 2
#define TASK_ESPEASY_PRIORITY 3
#define TASK_MEMORY_PRIORITY 1

void setup()
{
  ESPEasy_setup();
  #ifdef USB_ACTIVE
  usb_host_setup();
  #endif
  //detect_and_print_tspl();  // 🔍 otomatik tarama + yazdırm

  EEPROM.begin(1024); // EEPROM Başlat

  /**************** LVGL AKTİF **************/
  #ifdef LVGL_ACTIVE

  loadeeprom();
  loadButtonConfigs();
  loadButtonActiveStates();

  gui_mutex = xSemaphoreCreateMutex();
  if (!gui_mutex) { Serial.println("Mutex fail!"); ESP.restart(); }

  // LVGL başlat
  display_init();
  lv_init();

  draw_buf_1 = (lv_color_t *)heap_caps_malloc(DRAW_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_SPIRAM | MALLOC_CAP_DMA);
  draw_buf_2 = (lv_color_t *)heap_caps_malloc(DRAW_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_SPIRAM | MALLOC_CAP_DMA);

  if (!draw_buf_1 || !draw_buf_2) {
      Serial.println("❌ LVGL Buffer allocation FAILED. Restarting...");
      delay(1000);
      ESP.restart();
  }

  // Ekran tanımlama
  lv_display_t *disp = lv_display_create(TFT_HOR_RES, TFT_VER_RES);
  lv_display_set_flush_cb(disp, my_disp_flush);
  lv_display_set_buffers(disp, draw_buf_1, draw_buf_2, DRAW_BUF_SIZE, LV_DISPLAY_RENDER_MODE_PARTIAL);
  //lv_display_set_buffers(disp, draw_buf_1, NULL, DRAW_BUF_SIZE, LV_DISPLAY_RENDER_MODE_PARTIAL);
  
  // Dokunmatik girişini tanımla
  lv_indev_t *indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, my_touchpad_read);
  lv_indev_set_disp(indev, disp); // dokunmatik giriş doğru ekranla eşleştirilsin

  setup_ui(&guider_ui);
  
  loadUrunLabels();

  for (uint8_t i = 0; i < 8; i++) {
    loadMesajLabels(i);  
  }
  
  /*setupLVGLCanvas();
  // WebSockets Başlat
  ws.onEvent(onWebSocketEvent);
  server.addHandler(&ws);
  server.begin();*/

  eventGroup = xEventGroupCreate();
  if (eventGroup == nullptr) {
    printf("Event group creation failed\n");
    return; // Bellek yetersizse çıkış yap
  }

  if (xTaskCreatePinnedToCore(Task_LVGL,    // Pointer to the task entry function.
                          "Task_LVGL",  // A descriptive name for the task.
                          1024 * 32,    // The size of the task stack specified as the number of bytes
                          NULL,         // Pointer that will be used as the parameter for the task being created.
                          1,            // The priority at which the task should run.
                          NULL,         // Used to pass back a handle by which the created task can be referenced.
                          1)           // The core to which the task is pinned to, or tskNO_AFFINITY if the task has no core affinity.
                          !=pdPASS) {
                          Serial.println("Failed to create LVGL Loop task");
                          ESP.restart();
  }

  if (xTaskCreatePinnedToCore(Task_ESPEasy,
                          "Task_ESPEasy",
                          1024 * 8,
                          NULL,
                          2,
                          NULL,
                          0)
                          != pdPASS) {
                          Serial.println("Failed to create ESP Easy task");
                          ESP.restart();
  }

  if (xTaskCreatePinnedToCore(Task_Memory_Manager,
                          "Task_Memory_Manager",
                          4096,
                          NULL,
                          1,
                          NULL,
                          0) != pdPASS) {
                          Serial.println("Failed to create Memory Manager task");
                          ESP.restart();
  }

  ledcAttachChannel(tft.pins.buzzer.buzzer_pin, 2000, 10, 3);
  ledcWriteChannel(3, 0);

  //ESP-NOW başlat
#ifdef ESP_NOW_ACTIVE
  setWifiMode(WIFI_AP_STA);
  esp_now_init();
  ESP_NOW();
#endif
  #endif
  /**************** LVGL AKTİF **************/
}

bool yazici_bulundu = false;

void loop() {
  #ifndef LVGL_ACTIVE
    ESPEasy_loop();
  #endif

  #ifdef USB_ACTIVE
  usb_host_lib_handle_events(0, NULL);

  static unsigned long lastCheck = 0;
  if (millis() - lastCheck > 5000) {
    lastCheck = millis();

    // Eğer printer_ready değilse tarayalım:
    if (!printer_ready) {
      detect_and_print_tspl();
    }
  }
  #endif
}
