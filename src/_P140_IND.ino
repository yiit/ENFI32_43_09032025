#include "_Plugin_Helper.h"
#include "src/Helpers/Misc.h"
#include "src/DataTypes/SensorVType.h"

#include "ESPEasy_common.h"
#include "ESPEasy-Globals.h"

#ifdef USES_P140

#include "src/Commands/InternalCommands.h"
#include "src/ESPEasyCore/ESPEasyNetwork.h"
#include "src/ESPEasyCore/Controller.h"

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

#include "src/Helpers/ESPEasy_Storage.h"
#include "src/Helpers/Memory.h"
#include "src/Helpers/StringConverter.h"
#include "src/Helpers/StringParser.h"
#include "src/Helpers/Networking.h"

#include "src/ESPEasyCore/ESPEasy_Log.h"

#include <Wire.h>

#define RS232Baud 115200
#define RS232Format SERIAL_8N1

//#######################################################################################################
//#################################### Plugin 140: SCALE IND  #######################################
//#######################################################################################################

#define PLUGIN_140
#define PLUGIN_ID_140 140
#define PLUGIN_NAME_140 "Scale - IND"
#define PLUGIN_VALUENAME1_140 "NET"
#define PLUGIN_VALUENAME2_140 "DARA"
#define PLUGIN_VALUENAME3_140 "BRUT"

//const uint8_t LOADCELL_DOUT_PIN = 11;
//const uint8_t LOADCELL_SCK_PIN  = 10;

const uint8_t LOADCELL_DOUT_PIN = 1;
const uint8_t LOADCELL_SCK_PIN  = 2;

bool indkaydet = true;

#define CUSTOMTASK_STR_SIZE_P140 40

#define IND_SIFIR_KAL_DEGERI_ADDR_SIZE_P140 9
#define IND_YUK_KAL_DEGERI_ADDR_SIZE_P140 9
#define IND_KAPASITE_DEGERI_ADDR_SIZE_P140 9

#define IND_SIFIR_KAL_DEGERI_BUFF_SIZE_P140 9
#define IND_YUK_KAL_DEGERI_BUFF_SIZE_P140 9
#define IND_KAPASITE_DEGERI_BUFF_SIZE_P140 9

#define IND_SIFIR_KAL_DEGERI PCONFIG_FLOAT(0)
#define IND_YUK_KAL_DEGERI PCONFIG_FLOAT(1)
#define IND_KAPASITE PCONFIG_FLOAT(2)

#define IND_EKRAN_MOD PCONFIG(0)
#define IND_TAKSIMAT PCONFIG(1)
#define IND_NOKTA PCONFIG(2)
#define IND_FILTRE PCONFIG(3)
#define IND_HIZ PCONFIG(4)
#define IND_UDP_AKTiF PCONFIG(5)
#define IND_TCP_AKTiF PCONFIG(6)
#define IND_TCP_PORT PCONFIG(7)
#define IND_TCPMODBUS_AKTiF PCONFIG(8)

#define IND_Bartender ExtraTaskSettings.TaskPrintBartender

char goster_net_c[10];
char goster_dara_c[10];
char goster_brut_c[10];

int    ind_stabil_sayisi = 0;
float  bol = 0;
float  ind_tartim_degeri_son = 0;
float  ind_tartim_degeri_son1 = 0;
String file_data = "";

bool output_1_aktif = true;
bool output_2_aktif = true;
bool output_3_aktif = true;
bool output_4_aktif = true;

WiFiServer *sernetServer_140;
WiFiClient sernetClients_140;  //[MAX_SRV_CLIENTS];

const int fifoSize = 255;        // FIFO boyutu
float fifoBuffer[fifoSize];     // FIFO tampon
int fifoIndex = 0;              // FIFO tamponundaki mevcut indeks
int numValues = 0;              // FIFO içindeki toplam değer sayısı
float fifoSum = 0;              // FIFO'daki değerlerin toplamı

const int trendBufferSize = 5; // Kısa süreli tampon boyutu
float trendBuffer[trendBufferSize] = {0}; // Trend verileri için tampon
int trendIndex = 0; // Trend tamponu için indeks
int trendCount = 0; // Trend tamponundaki toplam değer sayısı


float filterFactor = 0.7;       // Dinamik olarak değişecek başlangıç filtre katsayısı

// Önceki değerler
long lastWeight = 0;            // Bir önceki ölçülen ağırlık
unsigned long lastTime = 0;     // Bir önceki ölçüm zamanı

#include "ModbusTCPSlave.h"
ModbusTCPSlave Mb_140;

// Function to determine stable or unstable state
String weightState(float currentWeight, int stable) {
  static float lastWeight = 0;
  static unsigned long stableCounter = 0;
  
  if (currentWeight == lastWeight) {
    stableCounter++;
    if (stableCounter >= stable) {
      if (indkaydet) {
        ExecuteCommand_all({EventValueSource::Enum::VALUE_SOURCE_WEB_FRONTEND, "indkaydet"});
        indkaydet = false;
      }
      return "ST"; // Weight is stable
    }
  } else {
    stableCounter = 0; // Reset stability counter on change
    indkaydet = true;
  }
  lastWeight = currentWeight;
  return "US"; // Weight is changing
}

float adjustDynamicFilterFactor(float currentWeight, float lastWeight, unsigned long currentTime, unsigned long lastTime, int taksimatStep) {
    float weightChange = abs(currentWeight - lastWeight); // Ağırlık değişimi
    unsigned long timeElapsed = currentTime - lastTime; // Geçen süre
    float changeRate = (timeElapsed > 0) ? float(weightChange) / timeElapsed : 0;

    if (changeRate > (2 * taksimatStep)) { // Çok hızlı değişim
        return 0.3; }  // Düşük filtreleme
    else if (weightChange <= taksimatStep) { // Çok az değişim
        return 0.95; }  // Stabil sonuçlar için yüksek filtreleme
    else if (timeElapsed > 1000) {// Uzun süre sabit ölçüm
        return 0.85; }
    else { // Normal değişim
        return 0.7; }
}

float applyTaksimat(float rawWeight, int taksimatStep, int decimalPlaces) {
    // 1. Ağırlığı tam sayıya çevirmek için ölçekleme
    float scaleFactor = pow(10, decimalPlaces);
    long scaledWeight = round(rawWeight * scaleFactor);

    // 2. Taksimat adımını ölçeklemek
    long scaledTaksimat = round(taksimatStep * scaleFactor);

    // 3. Taksimat adımına yuvarlama
    long roundedScaledWeight = (scaledWeight / scaledTaksimat) * scaledTaksimat;

    // 4. Sonucu tekrar orijinal ölçeğe geri dönüştürmek
    return float(roundedScaledWeight) / scaleFactor;
}

bool isStable(float currentWeight, float average, float stabilityThreshold) {
  // Ağırlığın stabil olup olmadığını kontrol et
  return abs(currentWeight - average) <= (float)stabilityThreshold;
}

float updateMovingAverageWithStability(
  float newValue, float* buffer, int& index, int& numValues, 
  int fifoSize, float& sum, float deviationThreshold, 
  int stabilityThreshold, int taksimatStep, int consecutiveThreshold
) {
  // Mevcut ortalamayı hesapla
  float average = (numValues > 0) ? sum / numValues : 0;

  // Aykırı değer kontrolü: Değerler trend kontrolü için kullanılacak
  static int outlierCount = 0;
  static bool lastWasHigh = false;

  // Yeni değer ve ortalama farkını kontrol et
  float deviation = abs(newValue - average);

  if (deviation > deviationThreshold && deviation < taksimatStep * 3) {
      // Eğer iki ardışık yüksek/düşük değer varsa, yok say
      if ((newValue > average && lastWasHigh) || (newValue < average && !lastWasHigh)) {
          outlierCount++;
          if (outlierCount >= consecutiveThreshold) {
              Serial.println("Sürekli yüksek/düşük trend algılandı, dikkate alınıyor.");
              outlierCount = 0; // Reset
              lastWasHigh = newValue > average;
              //XML_STABIL_S = "US"; // Unstabil durum
          } else {
              Serial.println("Yüksek/düşük aykırı değer yok sayılıyor.");
              //XML_STABIL_S = "US"; // Unstabil durum
              return average;
          }
      } else {
          outlierCount = 1; // Yeni bir trend başlıyor
          lastWasHigh = newValue > average;
          //XML_STABIL_S = "US"; // Unstabil durum
          return average;
      }
  } else {
      outlierCount = 0; // Aykırı değilse sıfırla
  }

  // FIFO tam dolduysa en eski değeri çıkar
  if (numValues == fifoSize) {
      sum -= buffer[index];
  } else {
      numValues++;
  }

  // Yeni değeri FIFO'ya ekle
  buffer[index] = newValue;
  sum += newValue;

  // Döngüsel tampon için indeksi güncelle
  index = (index + 1) % fifoSize;

  // Stabilite kontrolü
  if (isStable(newValue, average, stabilityThreshold)) {
      XML_STABIL_S = "ST"; // Stabil durum
      return sum / numValues;
  } else {
      XML_STABIL_S = "US"; // Unstabil durum
      return average;  // Stabil değilse mevcut ortalamayı döndür
  }
}

float performWeighing(float rawWeight, int taksimatStep, float* buffer, int& index, int& numValues, int fifoSize, float& sum, float deviationThreshold, int stabilityThreshold, int decimalPlaces, int consecutiveThreshold) {
  // Ağırlığı FIFO'ya ekle ve filtrelenmiş ortalama hesapla
  float filteredWeight = updateMovingAverageWithStability(
      rawWeight, buffer, index, numValues, fifoSize, sum, deviationThreshold, stabilityThreshold, taksimatStep, consecutiveThreshold
  );

  // Ham ağırlığı taksimata yuvarla
  float roundedWeight = applyTaksimat(filteredWeight, taksimatStep, decimalPlaces);
  // Stabilize edilmiş ağırlığı döndür
  return roundedWeight;
}

boolean Plugin_140(byte function, struct EventStruct *event, String &string) {
  boolean success = false;
  //static byte connectionState = 0;

  switch (function) {

    case PLUGIN_DEVICE_ADD:
      {
        Device[++deviceCount].Number = PLUGIN_ID_140;

        Device[deviceCount].Type = DEVICE_TYPE_DUMMY;
        //Device[deviceCount].VType = SENSOR_TYPE_SINGLE;
        Device[deviceCount].VType = Sensor_VType::SENSOR_TYPE_SINGLE;
        Device[deviceCount].FormulaOption = true;
        Device[deviceCount].ValueCount = 3;
        Device[deviceCount].SendDataOption = false;
        Device[deviceCount].TimerOption = false;
        Device[deviceCount].GlobalSyncOption = false;
        break;
      }

    case PLUGIN_GET_DEVICENAME:
      {
        string = F(PLUGIN_NAME_140);
        break;
      }

    case PLUGIN_GET_DEVICEVALUENAMES:
      {
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[0], PSTR(PLUGIN_VALUENAME1_140));
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[1], PSTR(PLUGIN_VALUENAME2_140));
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[2], PSTR(PLUGIN_VALUENAME3_140));
        break;
      }

    case PLUGIN_WEBFORM_LOAD:
      {
        //String strings[3];
        //LoadCustomTaskSettings(event->TaskIndex, strings, 3, CUSTOMTASK_STR_SIZE_P140);

        byte choice0 = IND_EKRAN_MOD;
        const __FlashStringHelper *options0[] = {
          F("TARTIM"),
          F("URUN HAFIZASI"),
        };
        constexpr int optionCount0 = NR_ELEMENTS(options0);
        const FormSelectorOptions selector140ekranmod(optionCount0, options0);
        selector140ekranmod.addFormSelector(F("EKRAN MODU"), F("plugin_140_ekran_mod"), choice0);
        IND_SIFIR_KAL_DEGERI = Settings.ind_sifir_kal_degeri;
        addFormTextBox(F("SIFIR KALIBRASYON DEGERI"), F("plugin_140_sifir_kal_deg"), String(IND_SIFIR_KAL_DEGERI, 0), IND_SIFIR_KAL_DEGERI_BUFF_SIZE_P140);
        IND_YUK_KAL_DEGERI = float(Settings.ind_yuk_kal_degeri);
        addFormTextBox(F("YUK KALIBRASYON DEGERI"), F("plugin_140_yuk_kal_deg"), String(IND_YUK_KAL_DEGERI, 8), IND_YUK_KAL_DEGERI_BUFF_SIZE_P140);

        addFormTextBox(F("YUK KAPASITE DEGERI"), F("plugin_140_kapasite_deg"), String(IND_KAPASITE, 8), IND_KAPASITE_DEGERI_BUFF_SIZE_P140);

        byte choice6 = IND_TAKSIMAT;
        const __FlashStringHelper *options6[] = { F("1"),F("2"),F("5"),F("10"),F("20"),F("50"),F("100"),F("200"),F("500")};
        constexpr int optionValues6[] = {1,2,5,10,20,50,100,200,500};
        const FormSelectorOptions selector140taksimat(NR_ELEMENTS(options6), options6, optionValues6);
        selector140taksimat.addFormSelector(F("TAKSİMAT"), F("plugin_140_taksimat_deg"), choice6);

        byte choice7 = IND_NOKTA;
        const __FlashStringHelper *options7[] = {F("0"),F("0.0"),F("0.00"),F("0.000"),F("0.0000")};
        constexpr int optionCount7 = NR_ELEMENTS(options7);
        const FormSelectorOptions selector140nokta(optionCount7, options7);
        selector140nokta.addFormSelector(F("NOKTA"), F("plugin_140_nokta_deg"), choice7);

        addFormNumericBox(F("FILTRE"), F("plugin_140_filtre_deg"), IND_FILTRE, 1, 65535);
        addFormNumericBox(F("HIZ"), F("plugin_140_hiz_deg"), IND_HIZ, 1, 65535);

        addFormCheckBox(F("Bartender prn"), F("plugin_140_bartender"), IND_Bartender);

#ifdef ESP32
        fs::File root = ESPEASY_FS.open(F("/"));
        fs::File file = root.openNextFile();
        int fileno = 0;
        while (file && fileno < 10) {
          if (!file.isDirectory()) {
            const String fname(file.name());
            if (fname.startsWith(F("/ind")) || fname.startsWith(F("ind"))) {
              //int count = getCacheFileCountFromFilename(fname);
              options2[fileno] += file.name();
              fileno++;
            }
          }
          file = root.openNextFile();
        }
#endif

        byte choice2 = ExtraTaskSettings.TaskDevicePrint[0];
        const FormSelectorOptions selector120prn(fileno, options2);
        selector120prn.addFormSelector(F("Tek Etiket"), F("plugin_140_tek_prn"), choice2);
        addButton(options2[ExtraTaskSettings.TaskDevicePrint[0]], F("Etiket Dizayn Menüsüne Git"));

        byte choice3 = ExtraTaskSettings.TaskDevicePrint[1];
        selector120prn.addFormSelector(F("Artı Etiket"), F("plugin_140_art_prn"), choice3);
        addButton(options2[ExtraTaskSettings.TaskDevicePrint[1]], F("Etiket Dizayn Menüsüne Git"));

        byte choice4 = ExtraTaskSettings.TaskDevicePrint[2];
        selector120prn.addFormSelector(F("Toplam Etiket"), F("plugin_140_top_prn"), choice4);
        addButton(options2[ExtraTaskSettings.TaskDevicePrint[2]], F("Etiket Dizayn Menüsüne Git"));

#if FEATURE_SD
        byte choice5 = ExtraTaskSettings.TaskDevicePrint[3];
        selector120prn.addFormSelector(F("SD data"), F("plugin_140_sd_prn"), choice5);
        addButton(options2[ExtraTaskSettings.TaskDevicePrint[3]], F("SD Data Dizayn Menüsüne Git"));
#endif

        addFormCheckBox(F("TCP/MODBUS AKTİF"), F("plugin_140_tcpmodbus_aktif"), IND_TCPMODBUS_AKTiF);
        addFormCheckBox(F("UDP AKTiF"), F("plugin_140_udp_aktif"), IND_UDP_AKTiF);
        addFormCheckBox(F("TCP AKTiF"), F("plugin_140_tcp_aktif"), IND_TCP_AKTiF);
        addFormNumericBox(F("TCP PORT"), F("plugin_140_tcp_port"), IND_TCP_PORT, 1, 65535);

        success = true;
        break;
      }

    case PLUGIN_WEBFORM_SAVE:
      {
        //char deviceTemplate[0][CUSTOMTASK_STR_SIZE_P140];

        //LoadTaskSettings(event->TaskIndex);
        IND_EKRAN_MOD = getFormItemInt(F("plugin_140_ekran_mod"));
        IND_SIFIR_KAL_DEGERI = getFormItemFloat(F("plugin_140_sifir_kal_deg"));
        Settings.ind_sifir_kal_degeri = IND_SIFIR_KAL_DEGERI;
        IND_YUK_KAL_DEGERI = getFormItemFloat(F("plugin_140_yuk_kal_deg"));
        Settings.ind_yuk_kal_degeri = IND_YUK_KAL_DEGERI;

        IND_KAPASITE = getFormItemFloat(F("plugin_140_kapasite_deg"));
        IND_TAKSIMAT = getFormItemInt(F("plugin_140_taksimat_deg"));
        IND_NOKTA = getFormItemInt(F("plugin_140_nokta_deg"));
        IND_FILTRE = getFormItemInt(F("plugin_140_filtre_deg"));
        IND_HIZ = getFormItemInt(F("plugin_140_hiz_deg"));
        IND_TCPMODBUS_AKTiF = isFormItemChecked(F("plugin_140_tcpmodbus_aktif"));
        IND_UDP_AKTiF = isFormItemChecked(F("plugin_140_udp_aktif"));
        IND_TCP_AKTiF = isFormItemChecked(F("plugin_140_tcp_aktif"));
        IND_TCP_PORT = getFormItemInt(F("plugin_140_tcp_port"));

        IND_Bartender = isFormItemChecked(F("plugin_140_bartender"));

        ExtraTaskSettings.TaskDevicePrint[0] = getFormItemInt(F("plugin_140_tek_prn"));
        ExtraTaskSettings.TaskDevicePrint[1] = getFormItemInt(F("plugin_140_art_prn"));
        ExtraTaskSettings.TaskDevicePrint[2] = getFormItemInt(F("plugin_140_top_prn"));
        ExtraTaskSettings.TaskDevicePrint[3] = getFormItemInt(F("plugin_140_sd_prn"));
        options2[ExtraTaskSettings.TaskDevicePrint[0]].toCharArray(Settings.tek_prn, options2[ExtraTaskSettings.TaskDevicePrint[0]].length() + 1);
        options2[ExtraTaskSettings.TaskDevicePrint[1]].toCharArray(Settings.art_prn, options2[ExtraTaskSettings.TaskDevicePrint[1]].length() + 1);
        options2[ExtraTaskSettings.TaskDevicePrint[2]].toCharArray(Settings.top_prn, options2[ExtraTaskSettings.TaskDevicePrint[2]].length() + 1);
        options2[ExtraTaskSettings.TaskDevicePrint[3]].toCharArray(Settings.sd_prn, options2[ExtraTaskSettings.TaskDevicePrint[3]].length() + 1);

        //SaveCustomTaskSettings(event->TaskIndex, (byte *)&deviceTemplate, sizeof(deviceTemplate));
        //SaveSettings();
        success = true;        
        break;
      }

    case PLUGIN_INIT:
      {
        scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
        switch (IND_NOKTA) {
          case 0: bol = 1; break;
          case 1: bol = 10; break;
          case 2: bol = 100; break;
          case 3: bol = 1000; break;
          case 4: bol = 10000; break;
        }
        if (fileExists(SERIDATA_IND)) {
          fs::File form = tryOpenFile(SERIDATA_IND, "r");
          tartimString_s = "";
          while (form.position() < form.size()) {
            tartimString_s += form.readStringUntil('\r');
            tartimString_s.trim();
          }
          form.close();
        }
        if (IND_TCP_PORT != 0) {
          sernetServer_140 = new WiFiServer(IND_TCP_PORT);
          sernetServer_140->begin();
          sernetServer_140->setNoDelay(true);
        }
        if (IND_TCPMODBUS_AKTiF)
          Mb_140.begin();

        fifoBuffer[fifoSize] = {};     // FIFO tampon
        fifoIndex = 0;              // FIFO tamponundaki mevcut indeks
        numValues = 0;              // FIFO içindeki toplam değer sayısı
        fifoSum = 0;              // FIFO'daki değerlerin toplamı
        filterFactor = 0.7;       // Dinamik olarak değişecek başlangıç filtre katsayısı
        lastWeight = 0;            // Bir önceki ölçülen ağırlık
        lastTime = 0;     // Bir önceki ölçüm zamanı
        Settings.WebAPP = 140;
        success = true;
        break;
      } 

      case PLUGIN_FIFTY_PER_SECOND:
      {
        // Ham ağırlık değerini al
        float rawWeight = float(float((scale.read() - (Settings.ind_sifir_kal_degeri + ind_sifir_degeri)) * Settings.ind_yuk_kal_degeri) + (XML_DARA_S.toFloat() * bol));

        // Ağırlığı stabilize et
        float stabilizedWeight = performWeighing(
           rawWeight, int(IND_TAKSIMAT), fifoBuffer, fifoIndex, numValues, float(IND_FILTRE), fifoSum, float(IND_FILTRE), int(IND_HIZ), int(IND_NOKTA), int(IND_HIZ)
        );

        dtostrf((float(stabilizedWeight) / float(bol)), 8, IND_NOKTA, goster_net_c);
        dtostrf((float(ind_dara_degeri)), 8, IND_NOKTA, goster_dara_c);
        //addLog(LOG_LEVEL_INFO, String(F("Taksimat: ")) + IND_TAKSIMAT + F(" rawData: ") + rawWeight + F(" filteredWeight: ") + stabilizedWeight);
        if (stabilizedWeight < 0)
          dtostrf(((stabilizedWeight / bol) + (-1 * ind_dara_degeri)), 8, IND_NOKTA, goster_brut_c);
        else
          dtostrf(((stabilizedWeight / bol) + ind_dara_degeri), 8, IND_NOKTA, goster_brut_c);
        XML_NET_S  = String(goster_net_c);
        XML_DARA_S = String(goster_dara_c);
        XML_BRUT_S = String(goster_brut_c);
        if ((indkaydet) && (XML_STABIL_S == "ST")) {
          ExecuteCommand_all({EventValueSource::Enum::VALUE_SOURCE_WEB_FRONTEND, "indkaydet"});
          indkaydet = false;
        }
        else if ((!indkaydet) && (XML_STABIL_S == "US")) {
          indkaydet = true;
        }
        success = true;
        break;
      }

      case PLUGIN_ONCE_A_SECOND:
      {
        serialPrintln(String(F("ST,GS,")) + XML_NET_S + F(" kg"));
        success = true;
        break;
      }

      case PLUGIN_WRITE:
      {
        if (Settings.UDPPort > 0) {
          //Serial1.println("BARKOD OKUNDU");
          //Serial.println("BARKOD OKUNDU");
          string.replace("\r","");
          string.replace("\n","");
          XML_QRKOD_S = string;
          String barkod = "scan";
          barkod += XML_QRKOD_S;
          barkod +="\r\n";
          //Serial1.print(barkod);
          //ExecuteCommand_all({EventValueSource::Enum::VALUE_SOURCE_WEB_FRONTEND, "eyztek"});
          string = "";
        }
        success = true;
        break;
      }
  }
  return success;
}

/*void addSelector(const String& label, const String& name, const String options[], const int optionValues[], int choice, int count) {
    addFormSelector(label, name, count, options, optionValues, choice);
}*/

#endif  // USES_P140