/*#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

#define OLED_RESET -1     // Reset pin # (or -1 if sharing Arduino reset pin)
#define i2c_Address 0x3c  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
*/
#include "_Plugin_Helper.h"
#include "src/Helpers/Misc.h"
#include "src/DataTypes/SensorVType.h"

#ifdef USES_P130

#include "src/Commands/InternalCommands.h"
#include "src/ESPEasyCore/ESPEasyNetwork.h"
#include "src/ESPEasyCore/Controller.h"
#include "src/ESPEasyCore/ESPEasy_Log.h"

#include "src/WebServer/ESPEasy_WebServer.h"
#include "src/WebServer/HTML_wrappers.h"
#include "src/WebServer/Markup.h"
#include "src/WebServer/Markup_Buttons.h"
#include "src/WebServer/Markup_Forms.h"
#include "src/WebServer/Lisans.h"
#include "src/WebServer/ToolsPage.h"
#include "src/WebServer/Rules.h"
#include "src/WebServer/LoadFromFS.h"

#include "src/Globals/CPlugins.h"
#include "src/Globals/Device.h"
#include "src/Globals/ExtraTaskSettings.h"
#include "src/Globals/Nodes.h"
#include "src/Globals/Plugins.h"
#include "src/Globals/Settings.h"
#include "src/Globals/Plugins.h"

#include "src/Helpers/ESPEasy_Storage.h"
#include "src/Helpers/Memory.h"
#include "src/Helpers/StringConverter.h"
#include "src/Helpers/StringParser.h"
#include "src/Helpers/Networking.h"

#include "src/PluginStructs/P130_data_struct.h"

#include "ESPEasy_common.h"
#include "ESPEasy-Globals.h"

//#######################################################################################################
//##################################### Plugin 130: EYZ #################################################
//#######################################################################################################

#define PLUGIN_130
#define PLUGIN_ID_130 130
#define PLUGIN_NAME_130 "Printer - EYZ"
#define PLUGIN_VALUENAME1_130 "NET"
#define PLUGIN_VALUENAME2_130 "DARA"
#define PLUGIN_VALUENAME3_130 "BRUT"
#define PLUGIN_VALUENAME4_130 "ADET"
#define PLUGIN_VALUENAME5_130 "ADETGR"
#define PLUGIN_VALUENAME6_130 "QRKOD"
#define PLUGIN_VALUENAME7_130 "PLUNO"//B.FIYAT"
#define PLUGIN_VALUENAME8_130 "URUNISMI"
#define PLUGIN_VALUENAME9_130 "NET_2"
#define PLUGIN_VALUENAME10_130 "DARA_2"
#define MAX_SRV_CLIENTS 5

#define CUSTOMTASK_STR_SIZE_P130 20

#define HEDEF_ADDR_SIZE_P130 8

#define MES_BUFF_SIZE_P130 19
#define HEDEF_BUFF_SIZE_P130 9

#define EYZ_Model     ExtraTaskSettings.TaskDevicePluginConfigLong[0]
#define EYZ_Indikator ExtraTaskSettings.TaskDevicePluginConfigLong[1]
#define EYZ_Mod       ExtraTaskSettings.TaskDevicePluginConfigLong[2]
#define EYZ_Gecikme   ExtraTaskSettings.TaskDevicePluginConfigLong[3]
#define EYZ_Sayac     ExtraTaskSettings.TaskDevicePluginConfigLong[4]

#define EYZ_Bartender ExtraTaskSettings.TaskPrintBartender

#define EYZ_art_komut ExtraTaskSettings.TaskDeviceMesage[0]
#define EYZ_tek_komut ExtraTaskSettings.TaskDeviceMesage[1]
#define EYZ_top_komut ExtraTaskSettings.TaskDeviceMesage[2]

#define EYZ_Hedef PCONFIG_FLOAT(0)


#include "OneButton.h"
//OneButton eyz_button2(12, false, false); //denedik
#ifdef ESP8266
//OneButton eyz_button2(14, false, false);  //RONGTA
OneButton eyz_button2(12, false, false);  //RONGTA
//OneButton eyz_button2(12, true, true); //HPRT
#endif
#ifdef ESP32_CLASSIC
#ifdef ESP32
#if FEATURE_ETHERNET
OneButton eyz_button1(14, false, false);  //RONGTA
OneButton eyz_button2(15, false, false);  //RONGTA
//OneButton eyz_button2(22, true, true);  //HPRT
#endif
#ifdef HAS_WIFI
OneButton eyz_button1(21, false, false);  //RONGTA
OneButton eyz_button2(22, false, false);  //RONGTA
//OneButton eyz_button1(21, true, true);  //SK330
//OneButton eyz_button2(22, true, true);  //SK330
#endif
#endif
//OneButton eyz_button1(12, false, false);  //SAYAC

#ifdef HAS_BLUETOOTH
OneButton eyz_button1(21, false, false);  //RONGTA
OneButton eyz_button2(22, false, false);  //RONGTA
#endif
//OneButton eyz_button2(12, true, true); //HPRT
//OneButton eyz_button2(13, true, true); //HPRT
//OneButton eyz_button2(15, true, true); //HPRT
//OneButton eyz_button2(2, true, true);  //SD KARD AKTİF

/*uint8_t broadcastAddress_rcv[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
esp_now_peer_info_t peerInfo_rcv;*/

void eyz_click1() {
  ExecuteCommand_all({EventValueSource::Enum::VALUE_SOURCE_WEB_FRONTEND, "eyzart"});
  /*//ExecuteCommand_all(EventValueSource::Enum::VALUE_SOURCE_WEB_FRONTEND, "eyztek");
  int sayac = XML_SAYAC_S.toInt();
  sayac = sayac + 1;
  XML_SAYAC_S = String(sayac);
  dtostrf(XML_SAYAC_S.toInt(), 5, 0, XML_SAYAC_C);*/
}
/*void eyz_longPressStart1() {
  ExecuteCommand_all(EventValueSource::Enum::VALUE_SOURCE_WEB_FRONTEND, "eyzsensor");
  //Settings.UseSerial = true;
}
void eyz_longPressStop1() {
  //Settings.UseSerial = false;
  int sayac = XML_SAYAC_S.toInt();
  sayac = sayac + 1;
  XML_SAYAC_S = String(sayac);
  dtostrf(XML_SAYAC_S.toInt(), 5, 0, XML_SAYAC_C);
}*/
void eyz_click2() {
  //ExecuteCommand_all(EventValueSource::Enum::VALUE_SOURCE_WEB_FRONTEND, "eyzart");
  ExecuteCommand_all({EventValueSource::Enum::VALUE_SOURCE_WEB_FRONTEND, "eyztek"});
  //XML_SAYAC_S = "0";
  //dtostrf(XML_SAYAC_S.toInt(), 5, 0, XML_SAYAC_C);
}
void eyz_longPressStart2() {
  //Settings.UseSerial = true;
  //ExecuteCommand_all(EventValueSource::Enum::VALUE_SOURCE_WEB_FRONTEND, "eyztek");
  //ExecuteCommand_all(EventValueSource::Enum::VALUE_SOURCE_WEB_FRONTEND, "eyzart");
  ExecuteCommand_all({EventValueSource::Enum::VALUE_SOURCE_WEB_FRONTEND, "eyzsensor"});
}
/*
void eyz_longPressStop2() {
  ExecuteCommand_all(EventValueSource::Enum::VALUE_SOURCE_WEB_FRONTEND, "eyztek");
}*/  

#endif

bool internet_p130 = false;

float sum_f_d_130[128];
float sum_f_130 = 0;
uint8_t i_130 = 0;

int eyzurun_stabil_sayisi = 0;

boolean Plugin_130(byte function, struct EventStruct *event, String &string) {
  boolean success = false;
  switch (function) {
    case PLUGIN_DEVICE_ADD:
      {
        Device[++deviceCount].Number = PLUGIN_ID_130;
        Device[deviceCount].Type = DEVICE_TYPE_SERIAL;
        Device[deviceCount].FormulaOption = true;
        Device[deviceCount].ValueCount = 10;
        Device[deviceCount].SendDataOption = false;
        Device[deviceCount].TimerOption = false;
        Device[deviceCount].GlobalSyncOption = false;
        break;
      }
    case PLUGIN_GET_DEVICENAME:
      {
        string = F(PLUGIN_NAME_130);
        break;
      }
    case PLUGIN_GET_DEVICEVALUENAMES:
      {
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[0], PSTR(PLUGIN_VALUENAME1_130));
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[1], PSTR(PLUGIN_VALUENAME2_130));
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[2], PSTR(PLUGIN_VALUENAME3_130));
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[3], PSTR(PLUGIN_VALUENAME4_130));
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[4], PSTR(PLUGIN_VALUENAME5_130));
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[5], PSTR(PLUGIN_VALUENAME6_130));
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[6], PSTR(PLUGIN_VALUENAME7_130));
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[7], PSTR(PLUGIN_VALUENAME8_130));
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[8], PSTR(PLUGIN_VALUENAME9_130));
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[9], PSTR(PLUGIN_VALUENAME10_130));
        break;
      }
    
    case PLUGIN_GET_DEVICEGPIONAMES:
      {
        event->String1 = formatGpioName_RX(false);
        event->String2 = formatGpioName_TX(false);
        break;
      }
    
    case PLUGIN_WEBFORM_SHOW_GPIO_DESCR:
      {
        string  = F("TX/RX");
        success = true;
        break;
      }
    case PLUGIN_WEBFORM_LOAD:
      {
#ifdef CAS_VERSION
        addFormSubHeader(F("Yazıcı Ayarları"));
#else
        addFormSubHeader(F("EYZ Ayarları"));
#endif
        
        // Serial Port Configuration - Simple like P020
        unsigned long currentBaud = PCONFIG_LONG(2);
        if (currentBaud == 0) {
          currentBaud = 9600;  // Default baud rate for web form
        }
        addFormNumericBox(F("Baud Rate"), F("plugin_130_baudrate"), currentBaud, 1200, 115200);
        addFormNote(F("Serial configuration 8N1 by default"));
        
        byte choice0 = EYZ_Model;
        const __FlashStringHelper *options0[] = {
          F("EYZ72R"),
          F("EYZ100"),
          F("EYZ100R"),
          F("EYZ72Mobil"),
          F("EYZ100Mobil")
        };
        constexpr int optionCount0 = NR_ELEMENTS(options0);
        const FormSelectorOptions selector130model(optionCount0, options0);
        selector130model.addFormSelector(F("Model"), F("plugin_130_model"), choice0);
        
        byte choice1 = EYZ_Mod;
        const __FlashStringHelper *options1[] = {
          F("SÜREKLi VERi (TEK SATIRLI VERi)"),
          F("TERAZiDEN OTOMATiK (TEK SATIRLI VERi)"),
          F("DENGELi OTOMATiK (TEK SATIRLI VERi)"),
          F("TERAZiDEN TUŞ iLE (ÇOK SATIRLI VERi)"),
          F("YAZICIDAN TUŞ iLE KONTROL(ÇOK SATIRLI VERi)"),
          F("KUMANDA"),
          F("VERi PAKETi")
        };
        constexpr int optionCount1 = NR_ELEMENTS(options1);
        const FormSelectorOptions selector130mod(optionCount1, options1);
        selector130mod.addFormSelector(F("Yazdırma Modu"), F("plugin_130_mod"), choice1);
        
        addFormCheckBox(F("Bartender prn"), F("plugin_130_bartender"), EYZ_Bartender);

        fs::File root = ESPEASY_FS.open(F("/")); //rules"));
        fs::File file = root.openNextFile();
        int fileno = 0;

        while (file && fileno < 10) {
          if (!file.isDirectory()) {
            const String fname(file.name());
            if (fname.startsWith(F("/eyz")) || fname.startsWith(F("eyz"))) {
              options2[fileno] = file.name();
              fileno++;
            }
          }
          file = root.openNextFile();
        }
        byte choice2 = ExtraTaskSettings.TaskDevicePrint[0];  
        const FormSelectorOptions selector130prn(fileno, options2);             
        selector130prn.addFormSelector(F("Tek Etiket"),           F("plugin_130_tek_prn"), choice2);
        addButton(options2[ExtraTaskSettings.TaskDevicePrint[0]], F("Etiket Dizayn Menüsüne Git"));

        byte choice3 = ExtraTaskSettings.TaskDevicePrint[1];
        selector130prn.addFormSelector(F("Artı Etiket"),          F("plugin_130_art_prn"), choice3);
        addButton(options2[ExtraTaskSettings.TaskDevicePrint[1]], F("Etiket Dizayn Menüsüne Git"));

        byte choice4 = ExtraTaskSettings.TaskDevicePrint[2];
        selector130prn.addFormSelector(F("Toplam Etiket"),        F("plugin_130_top_prn"), choice4);
        addButton(options2[ExtraTaskSettings.TaskDevicePrint[2]], F("Etiket Dizayn Menüsüne Git"));
#if FEATURE_SD
        byte choice5 = ExtraTaskSettings.TaskDevicePrint[3];
        selector130prn.addFormSelector(F("SD data"),              F("plugin_130_sd_prn"), choice5);
        addButton(options2[ExtraTaskSettings.TaskDevicePrint[3]], F("SD Data Dizayn Menüsüne Git"));
#endif
        byte choice6 = ExtraTaskSettings.TaskDevicePrint[4];
        selector130prn.addFormSelector(F("Adet Tek Etiket"),      F("plugin_130_urun_adet_tek_prn"), choice6);
        addButton(options2[ExtraTaskSettings.TaskDevicePrint[4]], F("Etiket Dizayn Menüsüne Git"));

        byte choice7 = ExtraTaskSettings.TaskDevicePrint[5];
        selector130prn.addFormSelector(F("Adet Artı Etiket"),     F("plugin_130_urun_adet_art_prn"), choice7);
        addButton(options2[ExtraTaskSettings.TaskDevicePrint[5]], F("Etiket Dizayn Menüsüne Git"));
        
        byte choice8 = ExtraTaskSettings.TaskDevicePrint[6];
        selector130prn.addFormSelector(F("Adet Ek Etiket"),       F("plugin_130_urun_adet_ek_prn"), choice8);
        addButton(options2[ExtraTaskSettings.TaskDevicePrint[6]], F("Etiket Dizayn Menüsüne Git"));
        
        byte choice9 = ExtraTaskSettings.TaskDevicePrint[7];
        selector130prn.addFormSelector(F("Adet Toplam Etiket"),   F("plugin_130_urun_adet_top_prn"), choice9);
        addButton(options2[ExtraTaskSettings.TaskDevicePrint[7]], F("Etiket Dizayn Menüsüne Git"));

        addFormTextBox(F("Hedef Kilogram"), F("plugin_130_hedef"), String(EYZ_Hedef, 3), HEDEF_BUFF_SIZE_P130);
        addFormNumericBox(F("Gecikme Saniyesi"), F("plugin_130_gecikme"), EYZ_Gecikme, 0, 999999);
        addFormNumericBox(F("Veri Sayaç"), F("plugin_130_sayac"), EYZ_Sayac, 2, 129);
        if (EYZ_Mod == 5) {
          addFormTextBox(F("Artı Komutu"), getPluginCustomArgName(0),   EYZ_art_komut, MES_BUFF_SIZE_P130);
          addFormTextBox(F("Toplam Komutu"), getPluginCustomArgName(1), EYZ_top_komut, MES_BUFF_SIZE_P130);
          addFormTextBox(F("Tek Komutu"), getPluginCustomArgName(2),    EYZ_tek_komut, MES_BUFF_SIZE_P130);
        }
        addFormSubHeader(F("İndikatör Ayarları"));
        indikator_secimi(event, EYZ_Indikator, F("plugin_130_indikator"));
        addFormCheckBox(F("İndikatör Data Düzenleme"), F("duzenle"), PCONFIG(4));
        addFormNote(F("<font color='red'>Başlangıç-Bitiş Datasının Değişimine İzin Verir.</font>"));
        success = true;
        break;
      }

    case PLUGIN_WEBFORM_SAVE:
      {
        PCONFIG_LONG(2) = getFormItemInt(F("plugin_130_baudrate"));
        PCONFIG(0) = 0x1C;  // 8N1 serial config
        
        EYZ_Model = getFormItemInt(F("plugin_130_model"));
        EYZ_Indikator = getFormItemInt(F("plugin_130_indikator"));
        EYZ_Mod = getFormItemInt(F("plugin_130_mod"));
        EYZ_Gecikme = getFormItemInt(F("plugin_130_gecikme"));
        EYZ_Bartender = isFormItemChecked(F("plugin_130_bartender"));
        EYZ_Sayac = getFormItemInt(F("plugin_130_sayac"));
        ExtraTaskSettings.TaskDeviceIsaretByte = getFormItemInt(F("isaret_byte"));
        ExtraTaskSettings.TaskDeviceSonByte = getFormItemInt(F("son_byte"));
        PCONFIG_FLOAT(0) = getFormItemFloat(F("plugin_130_hedef"));
        if (EYZ_Mod == 5) {
          strncpy_webserver_arg(EYZ_art_komut, getPluginCustomArgName(0));
          strncpy_webserver_arg(EYZ_top_komut, getPluginCustomArgName(1));
          strncpy_webserver_arg(EYZ_tek_komut, getPluginCustomArgName(2));
        }
        PCONFIG(4) = isFormItemChecked(F("duzenle"));
        indikator_secimi_kaydet(event, EYZ_Indikator, PCONFIG(4));
        ExtraTaskSettings.TaskDevicePrint[0] = getFormItemInt(F("plugin_130_tek_prn"));
        ExtraTaskSettings.TaskDevicePrint[1] = getFormItemInt(F("plugin_130_art_prn"));
        ExtraTaskSettings.TaskDevicePrint[2] = getFormItemInt(F("plugin_130_top_prn"));
        ExtraTaskSettings.TaskDevicePrint[3] = getFormItemInt(F("plugin_130_sd_prn"));
        ExtraTaskSettings.TaskDevicePrint[4] = getFormItemInt(F("plugin_130_urun_adet_tek_prn"));
        ExtraTaskSettings.TaskDevicePrint[5] = getFormItemInt(F("plugin_130_urun_adet_art_prn"));
        ExtraTaskSettings.TaskDevicePrint[6] = getFormItemInt(F("plugin_130_urun_adet_ek_prn"));
        ExtraTaskSettings.TaskDevicePrint[7] = getFormItemInt(F("plugin_130_urun_adet_top_prn"));
        options2[ExtraTaskSettings.TaskDevicePrint[0]].toCharArray(Settings.urun_tek_prn,      options2[ExtraTaskSettings.TaskDevicePrint[0]].length() + 1);
        options2[ExtraTaskSettings.TaskDevicePrint[1]].toCharArray(Settings.urun_art_prn,      options2[ExtraTaskSettings.TaskDevicePrint[1]].length() + 1);
        options2[ExtraTaskSettings.TaskDevicePrint[2]].toCharArray(Settings.urun_top_prn,      options2[ExtraTaskSettings.TaskDevicePrint[2]].length() + 1);
        options2[ExtraTaskSettings.TaskDevicePrint[3]].toCharArray(Settings.sd_prn,            options2[ExtraTaskSettings.TaskDevicePrint[3]].length() + 1);
        options2[ExtraTaskSettings.TaskDevicePrint[4]].toCharArray(Settings.urun_adet_tek_prn, options2[ExtraTaskSettings.TaskDevicePrint[4]].length() + 1);
        options2[ExtraTaskSettings.TaskDevicePrint[5]].toCharArray(Settings.urun_adet_art_prn, options2[ExtraTaskSettings.TaskDevicePrint[5]].length() + 1);
        options2[ExtraTaskSettings.TaskDevicePrint[6]].toCharArray(Settings.urun_adet_ek_prn,  options2[ExtraTaskSettings.TaskDevicePrint[6]].length() + 1);
        options2[ExtraTaskSettings.TaskDevicePrint[7]].toCharArray(Settings.urun_adet_top_prn, options2[ExtraTaskSettings.TaskDevicePrint[7]].length() + 1);
        success = true;
        break;
      }

    case PLUGIN_INIT:
      {
        if (!PCONFIG(4)) {
          switch (EYZ_Indikator) {
            case 26:
              strcpy_P(ExtraTaskSettings.TaskDeviceFormula[0], PSTR("NW"));
              strcpy_P(ExtraTaskSettings.TaskDeviceFormula[1], PSTR("TW"));
              strcpy_P(ExtraTaskSettings.TaskDeviceFormula[2], PSTR("GW"));
              strcpy_P(ExtraTaskSettings.TaskDeviceFormula[3], PSTR("QTY"));
              strcpy_P(ExtraTaskSettings.TaskDeviceFormula[4], PSTR("APW"));
              break;
            case 27:
              strcpy_P(ExtraTaskSettings.TaskDeviceFormula[0], PSTR("NET"));
              strcpy_P(ExtraTaskSettings.TaskDeviceFormula[1], PSTR("Tare"));
              strcpy_P(ExtraTaskSettings.TaskDeviceFormula[2], PSTR("Gross"));
              strcpy_P(ExtraTaskSettings.TaskDeviceFormula[3], PSTR("PCS"));
              strcpy_P(ExtraTaskSettings.TaskDeviceFormula[4], PSTR("U/W"));
              break;
          }
        }
        
        // Initialize P130 Task with ESPeasySerial (reuse existing if already initialized)
        P130_Task *task = static_cast<P130_Task *>(getPluginTaskData(event->TaskIndex));
        
        addLog(LOG_LEVEL_INFO, F("P130 PLUGIN_INIT: Starting initialization"));
        
        if ((nullptr != task) && task->isInit()) {
          // Task already exists and is initialized, reuse it
          addLog(LOG_LEVEL_INFO, F("P130 PLUGIN_INIT: Reusing existing task"));
        } else {
          initPluginTaskData(event->TaskIndex, new (std::nothrow) P130_Task(event));
          task = static_cast<P130_Task *>(getPluginTaskData(event->TaskIndex));
          addLog(LOG_LEVEL_INFO, F("P130 PLUGIN_INIT: Created new task"));
        }
        
        if (nullptr == task) {
          addLog(LOG_LEVEL_ERROR, F("P130 PLUGIN_INIT: Task creation failed!"));
          break;
        }
        
        // Get serial port and pins from settings (like P020)
        int rxPin = CONFIG_PIN1;
        int txPin = CONFIG_PIN2;
        const ESPEasySerialPort port = static_cast<ESPEasySerialPort>(CONFIG_PORT);
        
        // İlk yüklemede pinler -1 olabilir, ESPeasySerialType'dan default al
        if ((rxPin < 0) && (txPin < 0)) {
          ESPeasySerialType::getSerialTypePins(port, rxPin, txPin);
          CONFIG_PIN1 = rxPin;
          CONFIG_PIN2 = txPin;
          addLog(LOG_LEVEL_INFO, strformat(F("P130 PLUGIN_INIT: Pinler ayarlanmamış, port %d için default: RX=%d TX=%d"), 
                                           static_cast<int>(port), rxPin, txPin));
        }
        
        unsigned long baudrate = PCONFIG_LONG(2);
        if (baudrate == 0) {
          baudrate = 9600;  // Default baud rate
          addLog(LOG_LEVEL_INFO, F("P130 PLUGIN_INIT: Baudrate ayarlanmamış, default 9600 kullanılıyor"));
        }
        
        uint8_t serialconfig = PCONFIG(0);
        if (serialconfig == 0) {
          serialconfig = 0x1C;  // 8N1
        }
        
        // Open serial port (otomatik seçim: Serial0/1/2 CONFIG_PORT'a göre)
        task->serialBegin(port, rxPin, txPin, baudrate, serialconfig);
        
        addLog(LOG_LEVEL_INFO, strformat(F("P130 PLUGIN_INIT: Serial port %d opened - RX=%d TX=%d BAUD=%lu"), 
                                         static_cast<int>(port), rxPin, txPin, baudrate));
        
        if (!task->isInit()) {
          addLog(LOG_LEVEL_ERROR, F("P130 PLUGIN_INIT: Task init check failed!"));
          clearPluginTaskData(event->TaskIndex);
          break;
        }
        
        Settings.WebAPP = 130;
        success = true;
        break;
      }

    case PLUGIN_FIFTY_PER_SECOND:
      {
        // Handle serial data (like P020)
        P130_Task *task = static_cast<P130_Task *>(getPluginTaskData(event->TaskIndex));
        
        // Auto-initialize if task doesn't exist (lazy init)
        if (nullptr == task) {
          // Try to initialize task
          initPluginTaskData(event->TaskIndex, new (std::nothrow) P130_Task(event));
          task = static_cast<P130_Task *>(getPluginTaskData(event->TaskIndex));
          
          if (nullptr != task) {
            // Initialize serial port with saved settings (same as PLUGIN_INIT)
            int rxPin = CONFIG_PIN1;
            int txPin = CONFIG_PIN2;
            const ESPEasySerialPort port = static_cast<ESPEasySerialPort>(CONFIG_PORT);
            
            if ((rxPin < 0) && (txPin < 0)) {
              ESPeasySerialType::getSerialTypePins(port, rxPin, txPin);
            }
            
            unsigned long baudrate = PCONFIG_LONG(2);
            if (baudrate == 0) {
              baudrate = 9600;
            }
            
            uint8_t serialconfig = PCONFIG(0);
            if (serialconfig == 0) {
              serialconfig = 0x1C;  // 8N1
            }
            
            task->serialBegin(port, rxPin, txPin, baudrate, serialconfig);
            addLog(LOG_LEVEL_INFO, strformat(F("P130: Auto-initialized port %d RX=%d TX=%d"), 
                                             static_cast<int>(port), rxPin, txPin));
          }
        }
        
        if (nullptr != task) {
          task->handleSerialIn(event);
        }
        
        if (yazdir_iptal < millis()) {
          hayvan_modu = 2;
        }
        dtostrf(webapinettartim, 8, ExtraTaskSettings.TaskDeviceValueDecimals[0], XML_webapinettartim_C);
        dtostrf(webapinettartim_son, 8, ExtraTaskSettings.TaskDeviceValueDecimals[0], XML_webapinettartim_son_C);
        if (String(webapinettartim_son,int(ExtraTaskSettings.TaskDeviceValueDecimals[0])) == String(webapinettartim,int(ExtraTaskSettings.TaskDeviceValueDecimals[0])))
          eyzurun_stabil_sayisi++;
        else
          eyzurun_stabil_sayisi = 0;
        if (eyzurun_stabil_sayisi >= EYZ_Gecikme) {
          XML_STABIL_S = "ST";
          if ((webapinettartim_son > EYZ_Hedef) || (topla_i == 1) || (topla_i == 2) || (urun_adet[sec_URUN_buton] == 1)) {
            if (hayvan_modu == 0) {
              String eyz_data = "";
              if (topla_i == 1)
                eyz_data += "eyzurunart&";
              else if (topla_i == 2)
                eyz_data += "eyzuruntek&";            
              //String eyz_data = "fyzplutop&";
              eyz_data += String(sec_URUN_buton);
              eyz_data += "&0&0&0";
              eyz_data += "&" + String(sec_M_buton[0]);
              eyz_data += "&" + String(sec_M_buton[1]);
              eyz_data += "&" + String(sec_M_buton[2]);
              eyz_data += "&" + String(sec_M_buton[3]);
              eyz_data += "&" + String(sec_M_buton[4]);
              eyz_data += "&" + String(sec_M_buton[5]);
              eyz_data += "&" + String(sec_M_buton[6]);
              eyz_data += "&" + String(sec_M_buton[7]);
              ExecuteCommand_all({EventValueSource::Enum::VALUE_SOURCE_WEB_FRONTEND, eyz_data.c_str()});
              addLog(LOG_LEVEL_INFO, eyz_data);
              hayvan_modu = 2;
            }
          }
        }
        else {
          XML_STABIL_S = "US";
          if ((webapinettartim_son < EYZ_Hedef) && (hayvan_modu == 2) && (EYZ_Mod == 2)) {
            hayvan_modu = 0;
            topla_i = 1;
            addLog(LOG_LEVEL_INFO, F("TOPLA AKTİF"));
          }
        }
        success = true;
        break;
      }

    case PLUGIN_WRITE:
      {
        /*if (Settings.UDPPort > 0) {
          hataTimer_l = millis();
          //Serial.print(string);
          if ((String(EYZ_art_komut).length() > 0) && (string.substring(ExtraTaskSettings.TaskDeviceValueBas[0]+2, (String(EYZ_art_komut).length() + ExtraTaskSettings.TaskDeviceValueBas[0]+2)) == String(EYZ_art_komut)))
            ExecuteCommand_all({EventValueSource::Enum::VALUE_SOURCE_WEB_FRONTEND, "eyzart"}, false);
          else if ((String(EYZ_top_komut).length() > 0) && (string.substring(ExtraTaskSettings.TaskDeviceValueBas[0]+2, (String(EYZ_top_komut).length() + ExtraTaskSettings.TaskDeviceValueBas[0]+2)) == String(EYZ_top_komut)))
            ExecuteCommand_all({EventValueSource::Enum::VALUE_SOURCE_WEB_FRONTEND, "eyztop"}, false);
          else if ((String(EYZ_tek_komut).length() > 0) && (string.substring(ExtraTaskSettings.TaskDeviceValueBas[0]+2, (String(EYZ_tek_komut).length() + ExtraTaskSettings.TaskDeviceValueBas[0]+2)) == String(EYZ_tek_komut)))
            ExecuteCommand_all({EventValueSource::Enum::VALUE_SOURCE_WEB_FRONTEND, "eyztop"}, false);
          else {
            if (Settings.Tersle)
              tersle(event, string);
            isaret(event, EYZ_Indikator, string);
            if ((EYZ_Mod == 3) || (EYZ_Mod == 4))
              formul_kontrol(event, string, EYZ_Mod, true);
            else
              udp_client(event, EYZ_Indikator, string, EYZ_Mod);
          }
          string = "";          
        }*/
        success = true;
        break;
      }
      
    case PLUGIN_ONCE_A_SECOND:
      {
        // Serial timeout check removed - using lazy init in FIFTY_PER_SECOND instead
        //serial_error(event, EYZ_Mod, "eyztek");
        success = true;
        break;
      }

#if defined(HAS_WIFI) || defined(HAS_BLE) || defined(HAS_BLUETOOTH)
    case PLUGIN_SERIAL_IN:
      {
        P130_Task *task = static_cast<P130_Task *>(getPluginTaskData(event->TaskIndex));
        
        if (nullptr != task) {
          task->handleSerialIn(event);
        }
        success = true;
        break;
      }
#endif
  }
  return success;
}
#endif

//Dikomsan
//ETXSTXadd:       01   CRLF
//n/w:      0.09 gCRLF
//u/w:       0    CRLF
//pcs:       0   CRLF