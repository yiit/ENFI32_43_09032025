#include <ArduinoJson.h>
#include <LittleFS.h>
#include "lvgl.h"
#include "gui_guider.h"
#include "../ESPEasy-Globals.h"

#define JSON_FILE "/mesaj.json"

//extern lv_ui guider_ui; // LVGL UI değişkeni
typedef struct {
    lv_obj_t **no_label;        // Numara etiketleri
    lv_obj_t **name_btn;        // Butonlar
    lv_obj_t **name_btn_label;  // Buton içi etiketler
    lv_obj_t *parent;
    uint8_t menu;               // Seçili menü
} urun_event_data_t;

// 📌 JSON'dan Buton İsimlerini Yükle
void loadMesajLabels(uint8_t mbtn_no);
void save_mesaj_name_event_cb(lv_event_t *e);
void mesaj_event_cb(lv_event_t *e);
void updateSingleMesaj(uint8_t mbtn_no, uint8_t i, const char *newMessage);
void create_buttons(lv_ui *ui, lv_obj_t *parent, uint8_t mbtn_no);
String getJsonFileName(uint8_t mbtn_no);


// 📌 JSON'dan Ürün Bilgilerini Yükle
void loadUrunLabels();
void save_urun_name_event_cb(lv_event_t *e);
void urun_event_cb(lv_event_t *e);
void updateSingleUrun(uint8_t i, const char *newMessage, const char *newKod, const uint8_t newTipi = 0, const uint16_t newSkt = 0, const uint8_t newEtiket = 0);
//void create_urun_buttons(lv_ui *ui, lv_obj_t *parent);
void create_urun_buttons(
    lv_ui *ui,
    lv_obj_t *parent,
    lv_obj_t **no_label,            // Numara etiketleri için parametre
    lv_obj_t **name_btn,            // Butonlar için parametre
    lv_obj_t **name_btn_label,      // Buton içi etiketler için parametre
    uint8_t menu,                   // Seçili buton için parametre
    const char *filter_text
);
String getJsonFileNameUrun();

void src_main_net_label();