#include "ESPEasy-Globals.h"

boolean printToWeb = false;
String printWebString;
boolean printToWebJSON = false;

unsigned long timermqtt_interval = 100;
unsigned long lastSend = 0;
unsigned long lastWeb = 0;

unsigned long wdcounter = 0;
unsigned long timerAwakeFromDeepSleep = 0;

#if FEATURE_ADC_VCC
float vcc = -1.0f;
#endif

bool shouldReboot(false);
bool firstLoop(true);

boolean UseRTOSMultitasking(false);

#include "HX711.h"
HX711 scale;

#include <MD5Builder.h>
MD5Builder _md5;

bool WebLisansIn = false;
int WebLisansInTimer = 300;
int WebLisanseyzInTimer = 300;

unsigned long randomNumber = 0;
double timeunix = 0;

const char kfont1[] PROGMEM = { 27, 87, 1 };             //32
const char kfont2[] PROGMEM = { 27, 87, 1, 27, 86, 2 };  //32
const char kfont3[] PROGMEM = { 27, 87, 2 };             //32
const char kfont4[] PROGMEM = { 27, 87, 1, 27, 86, 3 };  //16
const char kfont5[] PROGMEM = { 27, 87, 3 };             //10
const char kfont6[] PROGMEM = { 27, 87, 4 };             //8

const char font1[]   PROGMEM = { 27, 77, 49, 29, 33, 01 };  //64
const char font2[]   PROGMEM = { 27, 77, 48, 29, 33, 01 };  //48
const char font3[]   PROGMEM = { 27, 77, 49, 29, 33, 17 };  //32
const char font4[]   PROGMEM = { 27, 77, 48, 29, 33, 17 };  //24
const char font5[]   PROGMEM = { 27, 77, 48, 29, 33, 33 };  //16
const char font6[]   PROGMEM = { 27, 77, 48, 29, 33, 49 };  //12
const char sol[]     PROGMEM = { 27, 97, 94 };
const char orta[]    PROGMEM = { 27, 97, 01 };
const char sag[]     PROGMEM = { 27, 97, 02 };
const char beyaz[]   PROGMEM = { 29, 66, 94 };
const char siyah[]   PROGMEM = { 29, 66, 01 };
const char acik[]    PROGMEM = { 27, 69, 94 };
const char koyu[]    PROGMEM = { 27, 69, 01 };
const char kes[]     PROGMEM = { 29, 86, 49 }; //{ 29, 86, 49 };
const char logo[]    PROGMEM = { 27, 64, 27, 97,  01, 29, 84, 28, 112, 01, 48, 27, 64, 94, 94 };
const char cekmece[] PROGMEM = { 27, 112, 0, 30, 255,  0 };//{ 16, 20, 1, 1, 5 };

const char hata_beep[] PROGMEM = { 27, 66, 03, 04 };
const char okey_beep[] PROGMEM = { 27, 66, 01, 02 };

const char qrkodbas[] PROGMEM = { 27, 64, 10, 29, 40, 107, 48, 103, 4, 29, 40, 107, 48, 105, 72, 29, 40, 107, 48, 128, 254, 94 };
//const const char qrkodbas[24]  = {27, 64, 10,  29, 40, 107, 48, 103,  7, 29, 40, 107, 48, 105, 72, 29, 40, 107, 48, 128, 254, 94};
const char qrkodson[] PROGMEM = { 94, 29, 40, 107, 48, 129, 27, 74, 200 };
const char CR[]       PROGMEM = { 13 };
const char LF[]       PROGMEM = { 10 };
const char etiketcal[] PROGMEM = { 31, 27, 26, 3, 1, 94, 13, 10};

/*u char qrkodbas[36]  = {27, 64, 29, 40, 107,  4, 94, 49, 65, 50, 94, 29, 40, 107,  3, 94, 49, 67,  4, 29, 40, 107,  3, 94, 49, 69, 48, 29, 40, 107, 253, 254, 49, 80, 48};
uchar qrkodson[18]  = {29, 40, 107,  3, 94,  49, 81, 48, 29, 40, 107,  3, 94,  49, 82, 48};*/

String tartimString_s    = "";
String XML_TARIH_S       = "ERROR";
String XML_SAAT_S        = "ERROR";
String XML_TARIH_V       = "ERROR";
String XML_SAAT_V        = "ERROR";
String XML_NET_S         = "ERROR";
String XML_NET_V         = "ERROR";
String XML_DARA_S        = "ERROR";
String XML_DARA_V        = "ERROR";
String XML_BRUT_S        = "ERROR";
String XML_BRUT_V        = "ERROR";
String XML_NET_S_2       = "ERROR";
String XML_DARA_S_2      = "ERROR";
String XML_BRUT_S_2       = "ERROR";
String XML_ADET_S         = "ADET";
String XML_ADET_GRAMAJ_S  = "ERROR";
String XML_URUN_NO_S      = "ERROR";
String XML_URUN_ISMI_S    = "ERROR";
String XML_URUN_KOD_S     = "ERROR";
String XML_URUN_MESAJ_S   = "ERROR";
String XML_BARKOD_S       = "ERROR";
String XML_BIRIM_FIYAT_S  = "ERROR";
String XML_TUTAR_S        = "ERROR";
String XML_SNO_S          = "ERROR";
String XML_DURUS_ZAMANI_S = "ERROR";

String XML_SAYAC_1_S         = "0";
String XML_SAYAC_1_SONSUZ_S  = "0";
String XML_SAYAC_1_GECIKME_S = "0";
String XML_SAYAC_2_S         = "0";
String XML_SAYAC_2_SONSUZ_S  = "0";
String XML_SAYAC_2_GECIKME_S = "0";
String XML_SAYAC_3_S         = "0";
String XML_SAYAC_3_SONSUZ_S  = "0";
String XML_SAYAC_3_GECIKME_S = "0";
String XML_SAYAC_4_S         = "0";
String XML_SAYAC_4_SONSUZ_S  = "0";
String XML_SAYAC_4_GECIKME_S = "0";
String XML_SICAKLIK_S        = "0";

String XML_SERI_NO_S     = "0";
String XML_PARTI_NO_S    = "0";
String XML_FIS_NO_S      = "ERROR";
String XML_STABIL_S      = "ST";
String XML_TOP_NET_S     = "ERROR";
String XML_TOP_DARA_S    = "ERROR";
String XML_TOP_BRUT_S    = "ERROR";
String XML_TOP_ADET_S    = "ERROR";
String XML_RFIDKOD_S     = "ERROR";
String XML_EAN8_S        = "ERROR";
String XML_EAN13_S       = "ERROR";
String XML_QRKOD_S       = "ERROR";


//String XML_DATA[30];

String XML_V0  = "V0";
String XML_V1  = "V1";
String XML_V2  = "V2";
String XML_V3  = "V3";
String XML_V4  = "V4";
String XML_V5  = "V5";
String XML_V6  = "V6";
String XML_V7  = "V7";
String XML_V8  = "V8";
String XML_V9  = "V9";
String XML_V10 = "V10";
String XML_V11 = "V11";
String XML_V12 = "V12";
String XML_V13 = "V13";
String XML_V14 = "V14";
String XML_V15 = "V15";
String XML_V16 = "V16";
String XML_V17 = "V17";
String XML_V18 = "V18";
String XML_V19 = "V19";
String XML_V20 = "V20";
String XML_V21 = "V21";
String XML_V22 = "V22";
String XML_V23 = "V23";
String XML_V24 = "V24";
String XML_V25 = "V25";
String XML_V26 = "V26";
String XML_V27 = "V27";
String XML_V28 = "V28";
String XML_V29 = "V29";

String XML_FORMUL1_S         = "ERROR";
String XML_FORMUL2_S         = "ERROR";
String XML_FORMUL1_KATSAYI_S = "ERROR";
String XML_FORMUL2_KATSAYI_S = "ERROR";

String XML_FIRMA_ISMI_S      = "ERROR";
String XML_MUSTERI_ISMI_S    = "ERROR";
String XML_PLAKA_NO_S        = "ERROR";
String XML_OPERATOR_ISMI_S   = "ERROR";

String XML_MESAJ1_S          = "ERROR";
String XML_MESAJ2_S          = "ERROR";
String XML_MESAJ3_S          = "ERROR";
String XML_MESAJ4_S          = "ERROR";
String XML_MESAJ5_S          = "ERROR";
String XML_MESAJ6_S          = "ERROR";
String XML_MESAJ7_S          = "ERROR";
String XML_MESAJ8_S          = "ERROR";
String XML_MESAJ9_S          = "ERROR";

String XML_FIS_BASLIK1_S = "";
String XML_FIS_BASLIK2_S = "";
String XML_FIS_BASLIK3_S = "";
String XML_FIS_BASLIK4_S = "";

String kopya_etiket = "";
String IRDA_DATA_S = "";

char XML_NET_C[9];
char XML_DARA_C[9];
char XML_BRUT_C[9];
char XML_NET_C_2[9];
char XML_DARA_C_2[9];
char XML_BRUT_C_2[9];
char XML_ADET_C[9];
char XML_ADET_GRAMAJ_C[9];
char XML_TOP_NET_C[11];
char XML_TOP_DARA_C[11];
char XML_TOP_BRUT_C[11];
char XML_SNO_C[4];
char XML_SAYAC_1_C[7] = { "0" };
char XML_SAYAC_2_C[7] = { "0" };
char XML_SAYAC_3_C[7] = { "0" };
char XML_SAYAC_4_C[7] = { "0" };
char XML_SIRA_NO_C[9];
char XML_SERI_NO_C[9];
char XML_FIS_NO_C[9];
char XML_BARKOD_C[6];
char XML_FORMUL1_C[7];
char XML_FORMUL2_C[7];
char XML_FORMUL1_KATSAYI_C[9];
char XML_FORMUL2_KATSAYI_C[9];
char yazdir_c[2048];
char yazdir_xml[2048];
char XML_INPUT_PIN_C[4];
char XML_OUTPUT_PIN_C[4];
char XML_webapinettartim_son_C[9];
char XML_webapinettartim_C[9];

float isaret_f = 1;
float isaret_f_2 = 1;
float webapinettartim = 0;
float webapinettartim_son = 0;
float webapidaratartim = 0;
float webapibruttartim = 0;
float webapibruttartim_son = 0;
float webapinettartim_2 = 0;
float webapidaratartim_2 = 0;
float webapibruttartim_2 = 0;
float webapiadet = 0;
float webapiadetgr = 0;
int webapiurunno = 0;
float webapibfiyat = 0;
float webapitutar = 0;
float StabilTartim_f = 0;
float webapikatsayi1 = 0;
float webapikatsayi2 = 0;

uint8_t adet_i = 0;

float ind_sifir_degeri = 0;
float ind_dara_degeri = 0;
float eyz_dara_degeri = 0;

unsigned long hataTimer_l = 0;
unsigned long gosterTimer_l = 0;
unsigned long stabilTimer_l = 0;
unsigned long button_basildi = 0;

bool LisansControl = false;

int bluetooth_mod = 1;
int top_adet = 0;
float top_net = 0;
float top_dara = 0;
float top_brut = 0;
long fis_no = 0;
uint32_t seri_no = 0;
uint32_t sno = 0;

String message0 = "";
String message1 = "";
String message2 = "";
String message3 = "";
String message4 = "";
String message5 = "";
String message6 = "";
String message7 = "";
String message8 = "";
String message9 = "";
String data_s   = "";
String tartimdata_s = "";
String paketVeri_s = "";

String stabilTartim_s = "";

String toplam_detay = "";

int artyaz = 0;
int topyaz = 0;

bool oto_yazdir = false;
bool escpos_mod = false;
unsigned long escpos_time = 0;
bool tspl_mod = false;
unsigned long tspl_time = 0;
bool WifiAPMode;

bool karakter_195 = false;
bool karakter_196 = false;
bool karakter_197 = false;

bool Client_Mod = false;

String options2[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

int hayvan_modu = 2;
uint8_t topla_i = 0;
unsigned long yazdir_iptal = 0;

//LGFX tft;

#ifdef LVGL_ACTIVE
//PanelLan tft(BOARD_SC01_PLUS); // BOARD_SC01_PLUS, BOARD_SC02, BOARD_SC05, BOARD_KC01, BOARD_BC02, BOARD_SC07
PanelLan tft(BOARD_SC07);

/*LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes*/
lv_color_t *draw_buf_1 = NULL;
lv_color_t *draw_buf_2 = NULL;
//***************LVGL***************/

bool bul_buton_aktif = false;
bool edit_buton_aktif = false;
bool kaydet_buton_aktif = false;

bool M_buton_aktif[MAKTIF_BUTTON_COUNT] = {false, false, false, false, false, false, false, false};
bool net_label = false;

uint8_t ADDR_M_BUTON_AKTIF[] = {
    ADDR_M1_BUTON_AKTIF, ADDR_M2_BUTON_AKTIF, ADDR_M3_BUTON_AKTIF, ADDR_M4_BUTON_AKTIF,
    ADDR_M5_BUTON_AKTIF, ADDR_M6_BUTON_AKTIF, ADDR_M7_BUTON_AKTIF, ADDR_M8_BUTON_AKTIF
};

uint8_t sec_M_buton[SEC_M_BUTON_COUNT] = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t sec_F_buton[SEC_F_BUTON_COUNT] = {255, 255, 255, 255, 255, 255, 255, 255};

uint8_t ADDR_SEC_M_BUTON[] = { ADDR_SEC_M1_BUTON, ADDR_SEC_M2_BUTON, ADDR_SEC_M3_BUTON, ADDR_SEC_M4_BUTON, 
                                ADDR_SEC_M5_BUTON, ADDR_SEC_M6_BUTON, ADDR_SEC_M7_BUTON, ADDR_SEC_M8_BUTON };

uint8_t ADDR_SEC_F_BUTON[] = { ADDR_SEC_F1_BUTON, ADDR_SEC_F2_BUTON, ADDR_SEC_F3_BUTON, ADDR_SEC_F4_BUTON, 
                                ADDR_SEC_F5_BUTON, ADDR_SEC_F6_BUTON, ADDR_SEC_F7_BUTON, ADDR_SEC_F8_BUTON };

uint8_t sec_URUN_buton = 0;

// 📌 Seçili buton bilgilerini saklayan değişkenler
uint8_t selected_m_btn_no = 0;
uint8_t selected_i = 0;
uint8_t m_btn_no = 0;
uint8_t f_btn_no = 0;

char mesaj_labels[8][31][33];
char urun_labels[101][49];
float urun_net[255];
uint8_t urun_adet[255];
char urun_kod_labels[101][14];
uint8_t urun_tipi[101];
uint16_t urun_skt[101];
uint8_t urun_etiket_format[101];
float urun_dara[101];
float urun_birim_gramaj[101];
int8_t urun_barkod_format[101];
char urun_msg[101][49];

void beep(uint16_t freq, uint32_t duration) {
    ledcWriteTone(tft.pins.buzzer.buzzer_pin, freq);
    delay(duration);
    ledcWriteTone(tft.pins.buzzer.buzzer_pin, 0);
    ledcWrite(tft.pins.buzzer.buzzer_pin, 0);
}

void writeEEPROM(EEPROM_Address addr, uint8_t value) {
    if (addr < EEPROM_START_ADDR || addr >= ADDR_MAX) {
        return;
    }
    EEPROM.write(addr, value);
    EEPROM.commit();
}

uint8_t readEEPROM(EEPROM_Address addr) {
    if (addr < EEPROM_START_ADDR || addr >= ADDR_MAX) {
        return 0;
    }
    uint8_t value = EEPROM.read(addr);
    return value;
}

char json_temp_buf[64]; // Maks 64 karakterlik geçici kullanım

#endif

#ifdef ESP_NOW_ACTIVE

#include <esp_now.h>
#include "src/Globals/Settings.h"
#include <Preferences.h>

#define espnow_hata "Eslesmis cihaz yok, veri gonderilemiyor."
#define MAX_PAIRED_DEVICES 6

// Degiskenler
Preferences preferences;
uint8_t pairedMacList[MAX_PAIRED_DEVICES][6];  // Eslesmis cihazin MAC adresi
int pairedDeviceCount; // Eslesmis cihaz sayısını tutar

PeerStatus peerStatusList[MAX_PAIRED_DEVICES];
int peerStatusCount = 0;

// Tarama sonucu geçici cihaz listesi
uint8_t discoveredMacList[MAX_PAIRED_DEVICES][6];
int discoveredCount = 0;

// Broadcast adresini belirle
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
esp_now_peer_info_t peerInfo;

unsigned long buttonPressStartTime = 0; // Butona basılma baslangıc zamanı
bool buttonPressed = false;

bool isPaired = false; // Eslesme durumu

void StartPairing() {
  Serial.println("Eslesme Modu Baslatildi...");
  const char *pairMessage = "PAIR_REQUEST";

  // Broadcast adresine mesaj gonder
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)pairMessage, strlen(pairMessage));
  if (result == ESP_OK) {
    Serial.println("Eslesme Istegi Basariyla Gonderildi.");
  } else {
    Serial.println("Eslesme Istegi Gonderilemedi.");
  }
}

void EspnowSendKomut(const char *komut) {
  /*if (!isPaired) {
    Serial.println("❌ Eşleşmiş cihaz yok, gönderilemiyor.");
    return;
  }*/

  esp_err_t result = esp_now_send(Settings.espnow_mac_address, (uint8_t *)komut, strlen(komut));

  if (result == ESP_OK) {
    Serial.printf("✅ '%s' komutu gönderildi.\n", komut);
  } else {
    Serial.printf("❌ '%s' komutu gönderilemedi! Hata kodu: %d (0x%X)\n", komut, result, result);
  }
}

void EspnowSendData(String data) {
	if (!isPaired) {
	  Serial.println(espnow_hata);
	  return;
	}
  
	if (pairedDeviceCount == 0) {
	  Serial.println(espnow_hata);
	  return;
	}
	
	for (int i = 0; i < pairedDeviceCount; i++) { // Sadece kayıtlı cihazlar kadar dongu
	  if (pairedMacList[i] != nullptr) { // MAC adresi gecerli mi kontrol et
		  esp_err_t result = esp_now_send(pairedMacList[i], (uint8_t *)data.c_str(), data.length());
		  if (result != ESP_OK) {
		    Serial.printf("Veri gonderme hatası: Cihaz %d\n", i);
		  }
	  } else {
		  Serial.printf("Gecersiz MAC adresi: Cihaz %d\n", i);
	  }
	}
}  
#endif


#ifdef USB_ACTIVE
// ========== Global Değişkenlerin Tanımı ==========
// (Header'da extern olarak ilan edilmişti)
usb_host_client_handle_t client_hdl = NULL;
usb_device_handle_t dev_hdl        = NULL;
uint8_t out_ep                     = 0x01;  // Varsayılan OUT endpoint
bool printer_ready                 = false;

// Yerel (static) fonksiyonlar:
static void client_event_cb(const usb_host_client_event_msg_t *event_msg, void *arg);
static esp_err_t parse_config_and_claim_interface(usb_device_handle_t new_dev_hdl);
static void transfer_cb(usb_transfer_t *transfer);

/**
 * @brief USB Host'i başlatır ve client_event_cb'yi kaydeder.
 */
void usb_host_setup() {
    usb_host_config_t host_cfg = {
        .skip_phy_setup = false,
        .intr_flags = ESP_INTR_FLAG_LEVEL1
    };

    // Asenkron kullanım için callback'li yapı
    usb_host_client_config_t client_cfg = {
        .is_synchronous = false,
        .max_num_event_msg = 10,
        .async = {
            .client_event_callback = client_event_cb,
            .callback_arg = NULL,
        }
    };

    if (usb_host_install(&host_cfg) == ESP_OK &&
        usb_host_client_register(&client_cfg, &client_hdl) == ESP_OK) {
        Serial.println("✅ USB Host hazır, yazıcı bekleniyor...");
    } else {
        Serial.println("❌ USB Host başlatılamadı!");
    }
}

/**
 * @brief USB Host client event callback.
 *        Yeni cihaz takıldığında veya çıkarıldığında tetiklenir.
 */
static void client_event_cb(const usb_host_client_event_msg_t *event_msg, void *arg) {
    if (event_msg->event == USB_HOST_CLIENT_EVENT_NEW_DEV) {
        Serial.println("🔌 USB cihaz bağlandı");

        usb_device_handle_t new_dev_hdl;
        if (usb_host_device_open(client_hdl, event_msg->new_dev.address, &new_dev_hdl) != ESP_OK) {
            Serial.println("❌ Cihaz açılamadı.");
            return;
        }

        // Cihazın descriptor'ına bakalım (VID/PID gibi)
        const usb_device_desc_t *desc;
        if (usb_host_get_device_descriptor(new_dev_hdl, &desc) == ESP_OK) {
            Serial.printf("📎 VID: 0x%04X, PID: 0x%04X\n", desc->idVendor, desc->idProduct);
            // Eğer belirli bir yazıcıya kilitlenmek isterseniz:
            // if (desc->idVendor != PRINTER_VID || desc->idProduct != PRINTER_PID) ...
        }

        // Config descriptor'ı parse ederek printer interface'i claim etmeyi deneyelim
        if (parse_config_and_claim_interface(new_dev_hdl) == ESP_OK) {
            dev_hdl = new_dev_hdl;
            printer_ready = true;
            Serial.println("✅ Interface claim edildi, yazıcı hazır.");

            // Donanımın tam hazır olması için kısa gecikme (bazı yazıcılarda gerekiyor)
            delay(500);

            // Örnek olarak hemen etiket basalım
            // yazdirEtiket();
        } else {
            Serial.println("❌ Desteklenmeyen yazıcı veya interface claim başarısız.");
            // Eğer claim edilemezse device handle'ı kapatmayı unutmayın
            usb_host_device_close(client_hdl, new_dev_hdl);
        }
    }
    else if (event_msg->event == USB_HOST_CLIENT_EVENT_DEV_GONE) {
        Serial.println("🛑 USB cihaz çıkarıldı.");
        dev_hdl = NULL;
        printer_ready = false;
        out_ep = 0x01;  // Varsayılanı geri al
    }
}

/**
 * @brief Config descriptor içindeki Interface ve Endpoint'leri tarayarak
 *        Printer Class (0x07) bulur ve interface claim eder.
 *        Bulk OUT endpoint adresini de `out_ep` değişkenine atar.
 *
 * @param new_dev_hdl  usb_device_handle_t
 * @return ESP_OK başarılı claim edildiyse, aksi halde ESP_FAIL veya başka bir hata
 */
static esp_err_t parse_config_and_claim_interface(usb_device_handle_t new_dev_hdl) {
    const usb_config_desc_t *cfg;
    esp_err_t ret = usb_host_get_active_config_descriptor(new_dev_hdl, &cfg);
    if (ret != ESP_OK) {
        return ret;
    }

    const uint8_t *p = (const uint8_t *)cfg;
    const uint8_t *end = p + cfg->wTotalLength;

    // Öncelikle config descriptor'ı atla
    p += cfg->bLength;

    bool claimed = false;

    while (p < end) {
        if (p[1] == USB_B_DESCRIPTOR_TYPE_INTERFACE) {
            const usb_intf_desc_t *intf = (const usb_intf_desc_t *)p;

            // Printer Class? (bInterfaceClass == 0x07)
            if (intf->bInterfaceClass == 0x07) {
                // Bu interface'i claim etmeyi deneyelim
                esp_err_t claim = usb_host_interface_claim(client_hdl, new_dev_hdl, intf->bInterfaceNumber, 0);
                if (claim == ESP_OK) {
                    // Endpoint descriptor'ları oku
                    const uint8_t *ep_ptr = p + p[0];
                    for (int i = 0; i < intf->bNumEndpoints; i++) {
                        if (ep_ptr[1] == USB_B_DESCRIPTOR_TYPE_ENDPOINT) {
                            const usb_ep_desc_t *ep_desc = (const usb_ep_desc_t *)ep_ptr;

                            // OUT endpoint mi? (0x80 bit'i setli değilse)
                            if ((ep_desc->bEndpointAddress & 0x80) == 0) {
                                out_ep = ep_desc->bEndpointAddress;
                                Serial.printf("Bulunan OUT endpoint: 0x%02X\n", out_ep);
                            }
                            ep_ptr += ep_desc->bLength;
                        } else {
                            // Başka descriptor ise boyutu kadar ilerle
                            ep_ptr += ep_ptr[0];
                        }
                    }

                    claimed = true;
                    break; // Hedef interface bulundu ve claim edildi, çıkıyoruz
                }
            }
        }
        p += p[0];  // Sonraki descriptor'a geç
    }

    free((void*)cfg);

    if (!claimed) {
        return ESP_FAIL;
    }
    return ESP_OK;
}

/**
 * @brief Yazıcıya TSPL (veya benzer) komutu göndermek için asenkron transfer.
 *        Transfer bittiğinde transfer_cb() fonksiyonu çağrılır.
 */
/*void send_tspl_command(const char *cmd) {
    if (!printer_ready || dev_hdl == NULL) {
        Serial.println("❌ Yazıcı bağlı değil veya hazır değil.");
        return;
    }

    size_t len = strlen(cmd);
    usb_transfer_t *transfer;
    if (usb_host_transfer_alloc(len, 0, &transfer) != ESP_OK) {
        Serial.println("❌ Transfer alloc hatası!");
        return;
    }

    memcpy(transfer->data_buffer, cmd, len);

    // Transfer parametreleri
    transfer->device_handle    = dev_hdl;
    transfer->bEndpointAddress = out_ep;       // Örneğin 0x01
    transfer->num_bytes        = len;
    transfer->timeout_ms       = 1000;         // Gerekirse
    transfer->callback         = transfer_cb;  // Transfer bitince çağrılacak fonksiyon
    transfer->context          = NULL;

    // Asenkron submit
    esp_err_t err = usb_host_transfer_submit(transfer);
    if (err == ESP_OK) {
        // Burada başarı ile submit kuyruğa alındı demektir.
        Serial.println("✅ TSPL komutu transfer kuyruğuna alındı.");
    } else {
        // Submit başarısızsa, allocated yapıyı hemen burada serbest bırakalım.
        Serial.printf("❌ Transfer gönderilemedi. Kod: 0x%X\n", err);
        usb_host_transfer_free(transfer);
    }
}*/

void send_tspl_command(const char *cmd) {
    if (!printer_ready || dev_hdl == NULL || cmd == NULL) {
        Serial.println("❌ Yazıcı hazır değil ya da geçersiz komut.");
        return;
    }

    size_t len = strlen(cmd);
    if (len == 0 || len > 512) {
        Serial.printf("⚠️ TSPL komutu geçersiz uzunlukta (%d byte).\n", (int)len);
        return;
    }

    usb_transfer_t *transfer = NULL;
    if (usb_host_transfer_alloc(len, 0, &transfer) != ESP_OK || transfer == NULL) {
        Serial.println("❌ Transfer alloc hatası!");
        return;
    }

    if (transfer->data_buffer == NULL) {
        Serial.println("❌ Transfer buffer NULL!");
        usb_host_transfer_free(transfer);
        return;
    }

    memcpy(transfer->data_buffer, cmd, len);

    transfer->device_handle    = dev_hdl;
    transfer->bEndpointAddress = out_ep;
    transfer->num_bytes        = len;
    transfer->timeout_ms       = 1000;
    transfer->callback         = transfer_cb;
    transfer->context          = NULL;

    esp_err_t err = usb_host_transfer_submit(transfer);
    if (err != ESP_OK) {
        Serial.printf("❌ Transfer gönderilemedi. Kod: 0x%X\n", err);
        usb_host_transfer_free(transfer);
    } else {
        Serial.println("✅ TSPL transfer kuyruğa alındı.");
    }
}


/**
 * @brief Transfer işlemi bittiğinde (başarılı ya da başarısız) otomatik çağrılan callback.
 */
static void transfer_cb(usb_transfer_t *transfer) {
    if (transfer->status == USB_TRANSFER_STATUS_COMPLETED) {
        Serial.println("✅ Transfer başarıyla tamamlandı.");
    } else {
        Serial.printf("❌ Transfer hata. Status: %d\n", transfer->status);
    }
    // Transfer yapısı artık işimiz bitti, serbest bırakabiliriz.
    usb_host_transfer_free(transfer);
}

/**
 * @brief Örnek TSPL komutları ile basit bir etiket basar
 */
void yazdirEtiket() {
    const char *tspl =
        "SIZE 60 mm,40 mm\r\n"
        "GAP 2 mm,0 mm\r\n"
        "CLS\r\n"
        "TEXT 100,100,\"3\",0,1,1,\"Merhaba Yiğit\"\r\n"
        "PRINT 1\r\n";

    send_tspl_command(tspl);
}

/**
 * @brief Manuel olarak [1..127] adreslerini tarar,
 *        RONGTA yazıcı (örnek VID/PID) bulunursa interface claim eder ve etiket basar.
 */
void detect_and_print_tspl() {
    for (uint8_t addr = 1; addr < 128; addr++) {
        usb_device_handle_t temp;
        // Adres mevcut mu?
        if (usb_host_device_open(client_hdl, addr, &temp) == ESP_OK) {
            const usb_device_desc_t *desc;
            if (usb_host_get_device_descriptor(temp, &desc) == ESP_OK) {
                // Örnek: ICS Advent / RONGTA => 0x0FE6:0x8800
                if (desc->idVendor == 0x0FE6 && desc->idProduct == 0x8800) {
                    Serial.println("🔍 Manuel olarak yazıcı bulundu.");

                    // Bu yazıcıya ait interface'i parse/claim
                    if (parse_config_and_claim_interface(temp) == ESP_OK) {
                        dev_hdl = temp;
                        printer_ready = true;

                        // Örnek baskı
                        //yazdirEtiket();
                        return; // Yazıcıyı bulunca fonksiyondan çıkıyoruz
                    } else {
                        // Claim edilemezse kapat
                        usb_host_device_close(client_hdl, temp);
                    }
                }
            }
            // Farklı cihaz ya da mismatch => kapat
            usb_host_device_close(client_hdl, temp);
        }
    }
}
#endif