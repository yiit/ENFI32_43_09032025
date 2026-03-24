#include <ArduinoJson.h>
#include <LittleFS.h>
#include "lvgl.h"
#include "gui_guider.h"
#include "../ESPEasy-Globals.h"
#include "buton_json_lfs.h"

// UTF-8 karakteri ortadan kesmemek için bayta göre güvenli kısalt
static inline bool _is_utf8_cont(unsigned char c) { return (c & 0xC0) == 0x80; }

static void utf8_truncate_by_bytes(char* s, size_t max_bytes) {
    size_t len = strlen(s);
    if (len <= max_bytes) return;
    s[max_bytes] = '\0';
    while (max_bytes > 0 && _is_utf8_cont((unsigned char)s[max_bytes])) {
        s[--max_bytes] = '\0';
    }
}

urun_event_data_t* g_urun_event_data = nullptr;
urun_event_data_t urun_event_data_array[101];

// 📌 JSON Dosya Adını Oluştur
String getJsonFileName(uint8_t mbtn_no) {
    return "/mesaj_" + String(mbtn_no) + ".json";
}
String getJsonFileNameUrun() {
    return "/urun.json";
}

// 📌 JSON'dan Belirli Bir Butonun Mesajlarını Yükle
void loadMesajLabels(uint8_t mbtn_no) {
    /*if (!LittleFS.begin()) {
        //Serial.println("LittleFS başlatılamadı!");
        return;
    }*/
    String fileName = getJsonFileName(mbtn_no);
    File file = LittleFS.open(fileName, "r");
    if (!file) {
        //Serial.printf("[HATA] %s bulunamadı, varsayılan mesajlar atanıyor...\r\n", fileName.c_str());
        for (uint8_t i = 0; i < 30; i++) {
            if (i == 0) {
              strcpy(mesaj_labels[mbtn_no][i], "GRUP");
            }
            else {
              String msg = "Mesaj" + String(mbtn_no) + "." + String(i);
              strcpy(mesaj_labels[mbtn_no][i], msg.c_str());
            }
        }
        return;
    }
    //StaticJsonDocument<1024> doc;  // Daha küçük bellek kullanımı
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, file);
    file.close();
    if (error) {
        //Serial.print("[HATA] JSON Okuma Hatası: ");
        //Serial.println(error.c_str());
        return;
    }
    JsonArray group = doc["mesaj"].as<JsonArray>();
    if (!group) {
        //Serial.printf("[HATA] JSON format hatalı! (%s)\r\n", fileName.c_str());
        return;
    }
    for (uint8_t i = 0; i < 30; i++) {
        if (group[i].isNull()) {
            //Serial.printf("Eksik mesaj içeriği: [%d][%d]\r\n", mbtn_no, i);
            continue;
        }
        strlcpy(mesaj_labels[mbtn_no][i], group[i] | "Mesaj", sizeof(mesaj_labels[mbtn_no][i]));
    }
    //Serial.printf("Mesajlar başarıyla yüklendi: %s\r\n", fileName.c_str());
}


// 📌 JSON'dan Belirli Bir Butonun Mesajlarını Yükle
void loadUrunLabels() {
    /*if (!LittleFS.begin()) {
        return;
    }*/
    String fileName = getJsonFileNameUrun();
    File file = LittleFS.open(fileName, "r");
    if (!file) {
        for (uint8_t i = 0; i < 100; i++) {
            snprintf(urun_labels[i], sizeof(urun_labels[i]), "Urun%d", i);
            snprintf(urun_kod_labels[i], sizeof(urun_kod_labels[i]), "%03d", i);
        }        
        // Opsiyonel: eksikse varsayılan dosya oluştur
        File createFile = LittleFS.open(fileName, "w");
        if (createFile) {
            DynamicJsonDocument defaultDoc(16000);
            JsonArray urunArray         = defaultDoc.createNestedArray("urun");
            JsonArray kodArray          = defaultDoc.createNestedArray("kod");  
            JsonArray tipArray          = defaultDoc.createNestedArray("tip");
            JsonArray sktArray          = defaultDoc.createNestedArray("skt");
            JsonArray etiketArray       = defaultDoc.createNestedArray("etiket");
            JsonArray daraArray         = defaultDoc.createNestedArray("dara");
            JsonArray birimGramajArray  = defaultDoc.createNestedArray("birim_gramaj");
            JsonArray barkodFormatArray = defaultDoc.createNestedArray("barkod_format");
            JsonArray mesajArray        = defaultDoc.createNestedArray("msg");

            for (uint8_t i = 0; i < 100; i++) {
                urunArray.add(urun_labels[i]);
                kodArray.add(urun_kod_labels[i]);
                tipArray.add(urun_tipi[i]); // Varsayılan tip değeri
                sktArray.add(0); // Varsayılan son kullanma tarihi
                etiketArray.add(0); // Varsayılan etiket değeri
                daraArray.add(0.0f); // Varsayılan ürün dara değeri
                birimGramajArray.add(0.0f); // Varsayılan birim gramaj değeri
                barkodFormatArray.add(0); // Varsayılan barkod format değeri
                mesajArray.add(""); // Varsayılan msg içeriği
            }        
            serializeJson(defaultDoc, createFile);
            createFile.close();
        }
        return;
    }
    //StaticJsonDocument<16000> doc;
    DynamicJsonDocument doc(96 * 1024);
    DeserializationError error = deserializeJson(doc, file);
    file.close();
    if (error) {
        return;
    }
    if (!doc.containsKey("urun") || !doc.containsKey("kod") || !doc.containsKey("tip") || !doc.containsKey("skt") || !doc.containsKey("etiket") || !doc.containsKey("dara") || !doc.containsKey("birim_gramaj") || !doc.containsKey("barkod_format") || !doc.containsKey("msg")) {
        return;
    }
    JsonArray urunArray         = doc["urun"].as<JsonArray>();
    JsonArray kodArray          = doc["kod"].as<JsonArray>();
    JsonArray tipArray          = doc["tip"].as<JsonArray>();
    JsonArray sktArray          = doc["skt"].as<JsonArray>();
    JsonArray etiketArray       = doc["etiket"].as<JsonArray>();
    JsonArray daraArray         = doc["dara"].as<JsonArray>();
    JsonArray birimGramajArray  = doc["birim_gramaj"].as<JsonArray>();
    JsonArray barkodFormatArray = doc["barkod_format"].as<JsonArray>();
    JsonArray mesajArray        = doc["msg"].as<JsonArray>();

    for (uint8_t i = 0; i < 100; i++) {
        if (i < urunArray.size() && !urunArray[i].isNull()) {
            const char* s = urunArray[i].as<const char*>();
            if (s && s[0] != '\0') strlcpy(urun_labels[i], s, sizeof(urun_labels[i]));
            else snprintf(urun_labels[i], sizeof(urun_labels[i]), "Urun%d", i);
        } else {
            snprintf(urun_labels[i], sizeof(urun_labels[i]), "Urun%d", i);
        }
        utf8_truncate_by_bytes(urun_labels[i], 96); 

        if (i < kodArray.size() && !kodArray[i].isNull()) {
            const char* k = kodArray[i].as<const char*>();
            if (k && k[0] != '\0') strlcpy(urun_kod_labels[i], k, sizeof(urun_kod_labels[i]));
            else snprintf(urun_kod_labels[i], sizeof(urun_kod_labels[i]), "%03d", i);
        } else {
            snprintf(urun_kod_labels[i], sizeof(urun_kod_labels[i]), "%03d", i);
        }

        urun_tipi[i]          = (i < tipArray.size() && !tipArray[i].isNull()) ? tipArray[i].as<uint8_t>()  : 0;
        urun_skt[i]           = (i < sktArray.size() && !sktArray[i].isNull()) ? sktArray[i].as<uint16_t>() : 0;
        urun_etiket_format[i] = (i < etiketArray.size() && !etiketArray[i].isNull()) ? etiketArray[i].as<uint8_t>() : 0;
        urun_dara[i]          = (i < daraArray.size() && !daraArray[i].isNull()) ? daraArray[i].as<float>() : 0.0f;
        urun_birim_gramaj[i]  = (i < birimGramajArray.size() && !birimGramajArray[i].isNull()) ? birimGramajArray[i].as<float>() : 0.0f;
        urun_barkod_format[i] = (i < barkodFormatArray.size() && !barkodFormatArray[i].isNull()) ? barkodFormatArray[i].as<int8_t>() : 0;


        if (i < mesajArray.size() && !mesajArray[i].isNull()) {
            const char* m = mesajArray[i].as<const char*>();
            strlcpy(urun_msg[i], (m && m[0] != '\0') ? m : " ", sizeof(urun_msg[i]));
        } else {
            snprintf(urun_msg[i], sizeof(urun_msg[i]), "Mesaj%d", i);
        }
    }
}


// 📌 Sadece Bir Mesajı JSON Dosyasında Güncelle
void updateSingleMesaj(uint8_t mbtn_no, uint8_t i, const char *newMessage) {
    /*if (!LittleFS.begin()) {
        //Serial.println("LittleFS başlatılamadı!");
        return;
    }*/

    String fileName = getJsonFileName(mbtn_no);
    File file = LittleFS.open(fileName, "r");
    
    //StaticJsonDocument<1024> doc;
    DynamicJsonDocument doc(1024);
    
    if (file) {
        DeserializationError error = deserializeJson(doc, file);
        file.close();
        if (error) {
            //Serial.print("[HATA] JSON Okuma Hatası: ");
            //Serial.println(error.c_str());
            return;
        }
    } else {
        //Serial.printf("[BİLGİ] %s bulunamadı, yeni oluşturulacak.\r\n", fileName.c_str());
        doc["mesaj"] = JsonArray();
    }

    JsonArray group = doc["mesaj"].as<JsonArray>();
    if (!group) {
        group = doc.createNestedArray("mesaj");
    }

    while (group.size() <= i) {
        group.add("");  // Eksik elemanları tamamla
    }

    // 📌 **Sadece ilgili mesajı değiştiriyoruz**
    //group[i] = newMessage;

    snprintf(json_temp_buf, sizeof(json_temp_buf), "%s", newMessage);
    group[i] = json_temp_buf;

    // 📌 **JSON dosyasını güncelle**
    File writeFile = LittleFS.open(fileName, "w");
    if (!writeFile) {
        //Serial.printf("[HATA] %s yazmak için açılamadı!\r\n", fileName.c_str());
        return;
    }

    serializeJson(doc, writeFile);
    writeFile.close();

    //Serial.printf("[OK] Güncellendi: [%d][%d] -> %s\r\n", mbtn_no, i, newMessage);
}


// 📌 Tek Bir Ürünü JSON'da Güncelle
void updateSingleUrun(uint8_t i, const char *newMessage, const char *newKod, const uint8_t newTip, const uint16_t newSkt, const uint8_t newEtiket, const float newDara, const float newBirimGramaj, const int8_t newBarkodFormat, const char *newMesaj) {
    /*if (!LittleFS.begin()) {
        return;
    }*/

    String fileName = getJsonFileNameUrun();
    File file = LittleFS.open(fileName, "r");

    //StaticJsonDocument<16000> doc;
    DynamicJsonDocument doc(96 * 1024);

    if (file) {
        DeserializationError error = deserializeJson(doc, file);
        file.close();
        if (error) {
            return;
        }
    }

    if (!doc.containsKey("urun")) {
        doc["urun"] = JsonArray();
    }
    if (!doc.containsKey("kod")) {
        doc["kod"] = JsonArray();
    }
    if (!doc.containsKey("tip")) {
        doc["tip"] = JsonArray();
    }
    if (!doc.containsKey("skt")) {
        doc["skt"] = JsonArray();
    }
    if (!doc.containsKey("etiket")) {
        doc["etiket"] = JsonArray();
    }
    if (!doc.containsKey("dara")) {
        doc["dara"] = JsonArray();
    }
    if (!doc.containsKey("birim_gramaj")) {
        doc["birim_gramaj"] = JsonArray();
    }
    if (!doc.containsKey("barkod_format")) {
        doc["barkod_format"] = JsonArray();
    }
    if (!doc.containsKey("msg")) {
        doc["msg"] = JsonArray();
    }

    JsonArray urunArray         = doc["urun"].as<JsonArray>();
    JsonArray kodArray          = doc["kod"].as<JsonArray>();
    JsonArray tipArray          = doc["tip"].as<JsonArray>();
    JsonArray sktArray          = doc["skt"].as<JsonArray>();
    JsonArray etiketArray       = doc["etiket"].as<JsonArray>();
    JsonArray daraArray         = doc["dara"].as<JsonArray>();
    JsonArray birimGramajArray  = doc["birim_gramaj"].as<JsonArray>();
    JsonArray barkodFormatArray = doc["barkod_format"].as<JsonArray>();
    JsonArray mesajArray        = doc["msg"].as<JsonArray>();

    // Dizinin boyutunu uygun hale getir
    while (urunArray.size() <= i) {
        urunArray.add("");
    }
    while (kodArray.size() <= i) {
        kodArray.add("");
    }
    while (tipArray.size() <= i) {
        tipArray.add(0);  // Varsayılan tip değeri
    }
    while (sktArray.size() <= i) {
        sktArray.add(0);  // Varsayılan son kullanma tarihi
    }
    while (etiketArray.size() <= i) {
        etiketArray.add(0);  // Varsayılan etiket değeri
    }
    while (daraArray.size() <= i) {
        daraArray.add(0.0f);  // Varsayılan dara değeri
    }
    while (birimGramajArray.size() <= i) {
        birimGramajArray.add(0.0f);  // Varsayılan birim gramaj değeri
    }
    while (barkodFormatArray.size() <= i) {
        barkodFormatArray.add(0);  // Varsayılan barkod formatı
    }
    while (mesajArray.size() <= i) {
        mesajArray.add("");  // Varsayılan msg içeriği
    }


    // Yeni değerleri ata
    urunArray[i]         = newMessage;
    kodArray[i]          = newKod;
    tipArray[i]          = newTip;  // Yeni tip değerini ata
    sktArray[i]          = newSkt;  // Mevcut son kullanma tarihini koru
    etiketArray[i]       = newEtiket;  // Mevcut etiket değerini koru
    daraArray[i]         = newDara;  // Yeni dara değerini ata
    birimGramajArray[i]  = newBirimGramaj;  // Yeni birim gramaj değerini ata
    barkodFormatArray[i] = newBarkodFormat;  // Yeni barkod formatını ata
    mesajArray[i]        = newMesaj;  // Yeni msg içeriğini ata

    // Güncellenmiş JSON'u dosyaya yaz
    File writeFile = LittleFS.open(fileName, "w");
    if (!writeFile) {
        return;
    }

    serializeJson(doc, writeFile);
    writeFile.close();
}


void save_mesaj_name_event_cb(lv_event_t *e) {
    //Serial.println("[INFO] Kayıt işlemi başlatılıyor...");

    // 📌 **Geçersiz buton seçimi engellendi**
    if (selected_m_btn_no < 0 || selected_m_btn_no >= 8 || selected_i < 0 || selected_i >= 30) {
        //Serial.println("[HATA] Geçersiz buton seçimi!");
        return;
    }

    // 📌 **Text alanından veri al ve NULL kontrolü yap**
    const char *new_message = lv_textarea_get_text(guider_ui.scr_mbtn_m1_ta);
    if (!new_message || strlen(new_message) == 0) {
        //Serial.println("[HATA] Mesaj içeriği boş olamaz!");
        return;
    }

    // 📌 **Maksimum msg uzunluğu kontrolü**
    if (strlen(new_message) >= 32) {
        //Serial.println("[HATA] Mesaj çok uzun!");
        return;
    }

    // 📌 **Label nesnesinin geçerli olup olmadığını kontrol et**
    if (!lv_obj_is_valid(guider_ui.scr_mbtn_m_name_btn_label[selected_m_btn_no][selected_i])) {
        //Serial.println("[HATA] Label geçersiz!");
        return;
    }

    // 📌 **Mesajı güvenli bir şekilde kopyala**
    strlcpy(mesaj_labels[selected_m_btn_no][selected_i], new_message, sizeof(mesaj_labels[selected_m_btn_no][selected_i]));

    // 📌 **Label güncelleme**
    lv_label_set_text(guider_ui.scr_mbtn_m_name_btn_label[selected_m_btn_no][selected_i], new_message);
    //Serial.printf("[OK] Yeni Mesaj [%d][%d]: %s\r\n", selected_m_btn_no, selected_i, new_message);

    // 📌 **JSON Güncellemesi**
    //Serial.println("[INFO] updateSingleMesaj çağrılıyor...");
    delay(10); // **WDT resetlenmesi için bekleme**
    updateSingleMesaj(selected_m_btn_no, selected_i, new_message);
    //Serial.println("[INFO] updateSingleMesaj tamamlandı!");

    // 📌 **Seçili butonu sıfırla**
    selected_m_btn_no = -1;
    selected_i = -1;
    //Serial.println("[OK] Kayıt işlemi başarıyla tamamlandı!");
}

// 📌 ÜRÜN KAYDET Buton Olayı
void save_urun_name_event_cb(lv_event_t *e) {
    if (selected_i < 0 || selected_i >= 100) {
        //Serial.println("[HATA] Geçersiz buton seçimi!");
        return;
    }

    const char *new_message = lv_textarea_get_text(guider_ui.scr_ubtn_u_ta);
    if (!new_message || strlen(new_message) == 0) {
        //Serial.println("Hata: Ürün içeriği boş olamaz!");
        return;
    }

    if (strlen(new_message) >= 48) {
        //Serial.println("[HATA] Mesaj çok uzun!");
        return;
    }

    if (!lv_obj_is_valid(guider_ui.scr_ubtn_u_name_btn_label[selected_i])) {
        //Serial.println("[HATA] Label geçersiz!");
        return;
    }

    strlcpy(urun_labels[selected_i], new_message, sizeof(urun_labels[selected_i])+1);
    lv_label_set_text(guider_ui.scr_ubtn_u_name_btn_label[selected_i], new_message);

    // Güncellenmesi gereken ürün kodunu belirle (Mevcut kodu koruyalım)
    const char *current_kod = urun_kod_labels[selected_i];
    const uint8_t current_tipi = urun_tipi[selected_i];
    const uint16_t current_skt = urun_skt[selected_i];
    const uint8_t current_etiket = urun_etiket_format[selected_i];
    const float current_urun_dara = urun_dara[selected_i];
    const float current_urun_birim_gramaj = urun_birim_gramaj[selected_i];
    const int8_t current_urun_barkod_format = urun_barkod_format[selected_i];
    const char *current_mesaj = urun_msg[selected_i];

    //Serial.printf("Yeni Ürün [%d]: %s\n", selected_i, new_message);

    delay(10); // **WDT resetlenmesi için bekleme**
    updateSingleUrun(selected_i, new_message, current_kod, current_tipi, current_skt, current_etiket, current_urun_dara, current_urun_birim_gramaj, current_urun_barkod_format, current_mesaj);
    selected_i = -1;
}

void mesaj_event_cb(lv_event_t *e) {
    lv_obj_t *btn = static_cast<lv_obj_t *>(lv_event_get_target(e));
    lv_event_code_t code = lv_event_get_code(e);
    
    static lv_obj_t *prev_selected_btn = NULL; // Önceki seçili butonun referansı
    static lv_obj_t *prev_selected_label = NULL; // Önceki seçili label referansı
    static lv_color_t prev_btn_color;  // Önceki butonun rengini saklamak için
    static lv_color_t prev_label_color;  // Önceki label rengini saklamak için

        if (code == LV_EVENT_LONG_PRESSED)
        {
            beep(2000, 300);
            lv_obj_remove_flag(guider_ui.scr_mbtn_m_duzenle_label, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(guider_ui.scr_mbtn_m_sec_label, LV_OBJ_FLAG_HIDDEN);
            lv_obj_remove_flag(guider_ui.scr_mbtn_m_kaydet_btn, LV_OBJ_FLAG_HIDDEN);
            lv_obj_remove_flag(guider_ui.scr_mbtn_m1_ta, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(guider_ui.scr_mbtn_m_sec_btn, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(guider_ui.scr_mbtn_m_bul_btn, LV_OBJ_FLAG_HIDDEN);   
        for (uint8_t i = 0; i < 30; i++) {
            if (btn == guider_ui.scr_mbtn_m_name_btn[m_btn_no][i]) {
                selected_m_btn_no = m_btn_no;
                selected_i = i;

                // 🔹 **İlgili JSON dosyasını yükle (sadece bir butonun mesajlarını çekiyoruz)**
                loadMesajLabels(m_btn_no);

                // 🔴 **Önceki seçili butonun rengini sıfırla**
                if (prev_selected_btn) {
                    if (lv_obj_is_valid(prev_selected_btn)) {
                        lv_obj_set_style_bg_color(prev_selected_btn, prev_btn_color, static_cast<int>(LV_PART_MAIN));
                        //Serial.println("Önceki butonun rengi sıfırlandı.");
                    } else {
                        //Serial.println("Önceki buton geçersiz! NULL yapıldı.");
                        prev_selected_btn = NULL; // Geçersiz butonu sıfırla
                    }
                }

                if (prev_selected_label) {
                    if (lv_obj_is_valid(prev_selected_label)) {
                        lv_obj_set_style_text_color(prev_selected_label, prev_label_color, static_cast<int>(LV_PART_MAIN));
                        //Serial.println("Önceki butonun rengi sıfırlandı.");
                    } else {
                        //Serial.println("Önceki buton geçersiz! NULL yapıldı.");
                        prev_selected_label = NULL; // Geçersiz butonu sıfırla
                    }
                }

                // 🔴 **Yeni seçili butonu kırmızı yap**
                prev_btn_color = lv_obj_get_style_bg_color(btn, static_cast<int>(LV_PART_MAIN));  // Önceki rengi sakla
                prev_label_color = lv_obj_get_style_text_color(guider_ui.scr_mbtn_m_no_label[i], static_cast<int>(LV_PART_MAIN)); // Önceki label rengi sakla

                lv_obj_set_style_bg_color(btn, lv_color_hex(0xFF0000), static_cast<int>(LV_PART_MAIN));
                lv_obj_set_style_text_color(guider_ui.scr_mbtn_m_no_label[i], lv_color_hex(0xFF0000), static_cast<int>(LV_PART_MAIN));

                prev_selected_btn = btn;
                prev_selected_label = guider_ui.scr_mbtn_m_no_label[i];

                // 📌 **Seçili butonu içeren container'ı yukarı kaydır**
                lv_coord_t btn_y = lv_obj_get_y(btn); // Seçili butonun Y konumu
                lv_obj_t *container = lv_obj_get_parent(btn); // Butonun bağlı olduğu container

                if (container) {
                    lv_obj_scroll_to_y(container, btn_y, LV_ANIM_ON); // Container'ı butonun olduğu yere kaydır
                }

                // 📌 **Seçilen mesajı textarea'ya yaz**
                lv_textarea_set_text(guider_ui.scr_mbtn_m1_ta, mesaj_labels[m_btn_no][i]);

                // 📌 **Textarea'yı ekranda görünür hale getir ve yukarı kaydır**
                lv_obj_scroll_to_view(guider_ui.scr_mbtn_m1_ta, LV_ANIM_ON);

                // 📌 **Eğer LVGL klavye aktif olarak kullanılıyorsa, onu aç ve textarea ile ilişkilendir**
                #if LV_USE_KEYBOARD
                    lv_keyboard_set_textarea(guider_ui.g_kb_top_layer, guider_ui.scr_mbtn_m1_ta);
                    lv_obj_remove_flag(guider_ui.g_kb_top_layer, LV_OBJ_FLAG_HIDDEN); // Klavyeyi göster
                    lv_obj_scroll_to_view(guider_ui.g_kb_top_layer, LV_ANIM_ON); // Klavyeyi görünür hale getir
                #endif

                //Serial.printf("Mesaj Seçildi ve Sabitlendi: [%d][%d] - %s\r\n", m_btn_no, i, mesaj_labels[m_btn_no][i]);
                return;
            }
          }
        }
        else if (code == LV_EVENT_SHORT_CLICKED)
        {
            beep(2000, 300);
            lv_obj_add_flag(guider_ui.scr_mbtn_m_duzenle_label, LV_OBJ_FLAG_HIDDEN);
            lv_obj_remove_flag(guider_ui.scr_mbtn_m_sec_btn, LV_OBJ_FLAG_HIDDEN);
            lv_obj_remove_flag(guider_ui.scr_mbtn_m_sec_label, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(guider_ui.scr_mbtn_m_kaydet_btn, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(guider_ui.scr_mbtn_m1_ta, LV_OBJ_FLAG_HIDDEN);
            lv_obj_remove_flag(guider_ui.scr_mbtn_m_bul_btn, LV_OBJ_FLAG_HIDDEN); 
            for (uint8_t i = 0; i < 30; i++) {
            if (btn == guider_ui.scr_mbtn_m_name_btn[m_btn_no][i]) {
                selected_m_btn_no = m_btn_no;
                selected_i = i;
                switch (m_btn_no) {
                    case 0:
                        if (sec_M_buton[0] != i) {
                            sec_M_buton[0] = i;
                            writeEEPROM(ADDR_SEC_M1_BUTON, sec_M_buton[0]);
                        }
                        break;
                    case 1:
                        if (sec_M_buton[1] != i) {
                            sec_M_buton[1] = i;
                            writeEEPROM(ADDR_SEC_M2_BUTON, sec_M_buton[1]);
                        }
                        break;
                    case 2:
                        if (sec_M_buton[2] != i) {
                            sec_M_buton[2] = i;
                            writeEEPROM(ADDR_SEC_M3_BUTON, sec_M_buton[2]);
                        }
                        break;
                    case 3:
                        if (sec_M_buton[3] != i) {
                            sec_M_buton[3] = i;
                            writeEEPROM(ADDR_SEC_M4_BUTON, sec_M_buton[3]);
                        }
                        break;
                    case 4:
                        if (sec_M_buton[4] != i) {
                            sec_M_buton[4] = i;
                            writeEEPROM(ADDR_SEC_M5_BUTON, sec_M_buton[4]);
                        }
                        break;
                    case 5:
                        if (sec_M_buton[5] != i) {
                            sec_M_buton[5] = i;
                            writeEEPROM(ADDR_SEC_M6_BUTON, sec_M_buton[5]);
                        }
                        break;
                    case 6:
                        if (sec_M_buton[6] != i) {
                            sec_M_buton[6] = i;
                            writeEEPROM(ADDR_SEC_M7_BUTON, sec_M_buton[6]);
                        }
                        break;
                    case 7:
                        if (sec_M_buton[7] != i) {
                            sec_M_buton[7] = i;
                            writeEEPROM(ADDR_SEC_M8_BUTON, sec_M_buton[7]);
                        }
                        break;
                    }
        // 🔴 **Önceki seçili butonun rengini sıfırla**
        if (prev_selected_btn) {
            if (lv_obj_is_valid(prev_selected_btn)) {
                lv_obj_set_style_text_color(prev_selected_btn, prev_btn_color, static_cast<int>(LV_PART_MAIN));
                //Serial.println("Önceki butonun rengi sıfırlandı.");
            } else {
                //Serial.println("Önceki buton geçersiz! NULL yapıldı.");
                prev_selected_btn = NULL; // Geçersiz butonu sıfırla
            }
        }

        if (prev_selected_label) {
            if (lv_obj_is_valid(prev_selected_label)) {
                lv_obj_set_style_text_color(prev_selected_label, prev_label_color, static_cast<int>(LV_PART_MAIN));
                //Serial.println("Önceki butonun rengi sıfırlandı.");
            } else {
                //Serial.println("Önceki buton geçersiz! NULL yapıldı.");
                prev_selected_label = NULL; // Geçersiz butonu sıfırla
            }
          }
          // 🔴 **Yeni seçili butonu kırmızı yap**
          prev_btn_color = lv_obj_get_style_bg_color(btn, static_cast<int>(LV_PART_MAIN));  // Önceki rengi sakla
          prev_label_color = lv_obj_get_style_text_color(guider_ui.scr_mbtn_m_no_label[i], static_cast<int>(LV_PART_MAIN)); // Önceki label rengi sakla

          lv_obj_set_style_bg_color(btn, lv_color_hex(0xFF0000), static_cast<int>(LV_PART_MAIN));
          lv_obj_set_style_text_color(guider_ui.scr_mbtn_m_no_label[i], lv_color_hex(0xFF0000), static_cast<int>(LV_PART_MAIN));

          prev_selected_btn = btn;
          prev_selected_label = guider_ui.scr_mbtn_m_no_label[i];

          // 📌 **Seçili butonu içeren container'ı yukarı kaydır**
          lv_coord_t btn_y = lv_obj_get_y(btn); // Seçili butonun Y konumu
          lv_obj_t *container = lv_obj_get_parent(btn); // Butonun bağlı olduğu container

          if (container) {
              lv_obj_scroll_to_y(container, btn_y, LV_ANIM_ON); // Container'ı butonun olduğu yere kaydır
          }
                 // 📌 **Eğer LVGL klavye aktif olarak kullanılıyorsa, onu gizle**
          #if LV_USE_KEYBOARD
            lv_obj_add_flag(guider_ui.g_kb_top_layer, LV_OBJ_FLAG_HIDDEN); // Klavyeyi gizle
          #endif
         }
        }
    }
}


void urun_event_cb(lv_event_t *e) {
    lv_obj_t *btn = static_cast<lv_obj_t *>(lv_event_get_target(e));
    lv_event_code_t code = lv_event_get_code(e);

        // 📌 Kullanıcı verisini al
        urun_event_data_t *data = static_cast<urun_event_data_t *>(lv_event_get_user_data(e));

        if (!data) return;  // Eğer veri yoksa işlemi iptal et
    
        lv_obj_t **no_label = data->no_label;
        lv_obj_t **name_btn = data->name_btn;
        lv_obj_t **name_btn_label = data->name_btn_label;
        lv_obj_t *parent = data->parent;
        uint8_t menu = data->menu;
    
        static lv_obj_t *prev_selected_btn = NULL; // Önceki seçili butonun referansı
        static lv_obj_t *prev_selected_label = NULL; // Önceki seçili label referansı
        static lv_color_t prev_btn_color;  // Önceki butonun rengini saklamak için
        static lv_color_t prev_label_color;  // Önceki label rengini saklamak için

        if (code == LV_EVENT_LONG_PRESSED) {
            if (menu == 2) {
                beep(2000, 300);
                lv_obj_remove_flag(guider_ui.scr_ubtn_u_ta, LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(guider_ui.scr_ubtn_u_duzenle_label, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(guider_ui.scr_ubtn_u_sec_label, LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(guider_ui.scr_ubtn_u_kaydet_btn, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(guider_ui.scr_ubtn_u_sec_btn, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(guider_ui.scr_ubtn_u_bul_btn, LV_OBJ_FLAG_HIDDEN);
        
                for (uint8_t i = 0; i < 100; i++) {
                    if (btn == name_btn[i]) {
                        selected_i = i;
        
                        // 🔹 Önceki seçili butonu sıfırla
                        if (prev_selected_btn) {
                            if (lv_obj_is_valid(prev_selected_btn)) {
                                lv_obj_set_style_bg_color(prev_selected_btn, prev_btn_color, static_cast<int>(LV_PART_MAIN));
                                lv_obj_set_style_bg_color(prev_selected_btn, prev_btn_color, static_cast<int>(LV_STATE_DEFAULT));
                                lv_obj_refresh_style(prev_selected_btn, static_cast<int>(LV_PART_MAIN), LV_STYLE_PROP_ANY);
                            }
                            else {
                                //Serial.println("Önceki buton geçersiz! NULL yapıldı.");
                                prev_selected_btn = NULL; // Geçersiz butonu sıfırla
                            }
                        }
        
                        if (prev_selected_label) {
                            if (lv_obj_is_valid(prev_selected_label)) {
                                lv_obj_set_style_text_color(prev_selected_label, prev_label_color, static_cast<int>(LV_PART_MAIN));
                                lv_obj_refresh_style(prev_selected_btn, static_cast<int>(LV_PART_MAIN), LV_STYLE_PROP_ANY);
                            }
                            else {
                                prev_selected_label = NULL;
                            }
                        }
        
                        // 🔴 **Yeni seçili butonu ve label'ı işaretle**
                        prev_btn_color = lv_obj_get_style_bg_color(btn, static_cast<int>(LV_PART_MAIN));  
                        prev_label_color = lv_obj_get_style_text_color(no_label[i], static_cast<int>(LV_PART_MAIN)); 
        
                        lv_obj_set_style_bg_color(btn, lv_color_hex(0x00FF00), LV_PART_MAIN); // Yeterli
                        lv_obj_refresh_style(btn, LV_PART_MAIN, LV_STYLE_PROP_ANY);
                        
                        // Label için de doğru olanı yeşil yap
                        lv_obj_set_style_text_color(no_label[i], lv_color_hex(0x00FF00), LV_PART_MAIN);
                        lv_obj_refresh_style(no_label[i], LV_PART_MAIN, LV_STYLE_PROP_ANY);                       
        
                        prev_selected_btn = btn;
                        prev_selected_label = no_label[i];
        
                        // 📌 **Seçili butonu içeren container'ı yukarı kaydır**
                        lv_coord_t btn_y = lv_obj_get_y(btn);
                        lv_obj_t *container = lv_obj_get_parent(btn);
                        if (container) {
                            lv_obj_scroll_to_y(container, btn_y, LV_ANIM_ON);
                        }
        
                        // 📌 **Seçilen mesajı textarea'ya yaz**
                        lv_textarea_set_text(guider_ui.scr_ubtn_u_ta, urun_labels[i]);
        
                        // 📌 **Klavyeyi aç**
                        #if LV_USE_KEYBOARD
                            lv_keyboard_set_textarea(guider_ui.g_kb_top_layer, guider_ui.scr_ubtn_u_ta);
                            lv_obj_remove_flag(guider_ui.g_kb_top_layer, LV_OBJ_FLAG_HIDDEN);
                            lv_obj_scroll_to_view(guider_ui.g_kb_top_layer, LV_ANIM_ON);
                        #endif
        
                        return;
                    }
                }
            }
        }
        else if (code == LV_EVENT_SHORT_CLICKED)
        {
            beep(2000, 300);
            if (menu == 1) {
                lv_obj_remove_flag(guider_ui.scr_fbtn_f_sec_btn, LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(guider_ui.scr_fbtn_f_sec_btn_label, LV_OBJ_FLAG_HIDDEN);
                }   
            if (menu == 2) {
                lv_obj_add_flag(guider_ui.scr_ubtn_u_duzenle_label, LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(guider_ui.scr_ubtn_u_sec_btn, LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(guider_ui.scr_ubtn_u_sec_label, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(guider_ui.scr_ubtn_u_kaydet_btn, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(guider_ui.scr_ubtn_u_ta, LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(guider_ui.scr_ubtn_u_bul_btn, LV_OBJ_FLAG_HIDDEN); 
            }
            for (uint8_t i = 0; i < 100; i++) {
                if (btn == name_btn[i]) {
                    selected_i = i;
                    sec_URUN_buton = i;
                    writeEEPROM(ADDR_SEC_URUN_BUTON, sec_URUN_buton);
            
                    if (f_btn_no >= 1 && f_btn_no <= 8) {  // Geçerli buton numarası kontrolü
                        // Değişiklik varsa yaz
                        if (sec_F_buton[f_btn_no - 1] != sec_URUN_buton) {
                            sec_F_buton[f_btn_no - 1] = sec_URUN_buton;
                            writeEEPROM(static_cast<EEPROM_Address>(ADDR_SEC_F_BUTON[f_btn_no - 1]), sec_F_buton[f_btn_no - 1]);
                        }
                    }
                    break;  // Eşleşme bulunduğunda döngüden çık
            
        // 🔴 **Önceki seçili butonun rengini sıfırla**
        if (prev_selected_btn) {
            if (lv_obj_is_valid(prev_selected_btn)) {
                lv_obj_set_style_bg_color(prev_selected_btn, prev_btn_color, static_cast<int>(LV_PART_MAIN));
                lv_obj_set_style_bg_color(prev_selected_btn, prev_btn_color, static_cast<int>(LV_STATE_DEFAULT));
                lv_obj_refresh_style(prev_selected_btn, static_cast<int>(LV_PART_MAIN), LV_STYLE_PROP_ANY);
            } else {
                //Serial.println("Önceki buton geçersiz! NULL yapıldı.");
                prev_selected_btn = NULL; // Geçersiz butonu sıfırla
            }
        }

        if (prev_selected_label) {
            if (lv_obj_is_valid(prev_selected_label)) {
                lv_obj_set_style_bg_color(prev_selected_label, prev_btn_color, static_cast<int>(LV_PART_MAIN));
                lv_obj_set_style_bg_color(prev_selected_label, prev_btn_color, static_cast<int>(LV_STATE_DEFAULT));
                lv_obj_refresh_style(prev_selected_label, static_cast<int>(LV_PART_MAIN), LV_STYLE_PROP_ANY);
            } else {
                //Serial.println("Önceki buton geçersiz! NULL yapıldı.");
                prev_selected_label = NULL; // Geçersiz butonu sıfırla
            }
          }

            // 🔴 **Yeni seçili butonu ve label'ı işaretle**
            prev_btn_color = lv_obj_get_style_bg_color(btn, static_cast<int>(LV_PART_MAIN));  
            prev_label_color = lv_obj_get_style_text_color(no_label[i], static_cast<int>(LV_PART_MAIN)); 
            
            lv_obj_set_style_bg_color(btn, lv_color_hex(0x00FF00), static_cast<int>(LV_PART_MAIN));
            lv_obj_set_style_bg_color(btn, lv_color_hex(0x00FF00), LV_STATE_CHECKED);
            lv_obj_refresh_style(btn, static_cast<int>(LV_PART_MAIN), LV_STYLE_PROP_ANY);
                 
            lv_obj_set_style_text_color(no_label[i], lv_color_hex(0x00FF00), static_cast<int>(LV_PART_MAIN));
            lv_obj_refresh_style(no_label[i], static_cast<int>(LV_PART_MAIN), LV_STYLE_PROP_ANY);
                  
            prev_selected_btn = btn;
            prev_selected_label = no_label[i];
                  
            // 📌 **Seçili butonu içeren container'ı yukarı kaydır**
            lv_coord_t btn_y = lv_obj_get_y(btn);
            lv_obj_t *container = lv_obj_get_parent(btn);
            if (container) {
                lv_obj_scroll_to_y(container, btn_y, LV_ANIM_ON);
            }
        // 📌 **Eğer LVGL klavye aktif olarak kullanılıyorsa, onu gizle**
        if (menu == 2) {
        #if LV_USE_KEYBOARD
            lv_obj_add_flag(guider_ui.g_kb_top_layer, LV_OBJ_FLAG_HIDDEN); // Klavyeyi gizle
        #endif
        }
      }
    }
  }
}

static void src_mbtn_m_sw_event_handler (lv_event_t *e)
{
    lv_obj_t * obj = (lv_obj_t *)lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        bool state = lv_obj_has_state(obj, LV_STATE_CHECKED);
        if (state) {
            M_buton_aktif[m_btn_no] = true;
            beep(2000, 300);  // Switch açıldığında bip sesi
        } else {
            M_buton_aktif[m_btn_no] = false;
            beep(1000, 300);  // Switch kapandığında farklı bir bip sesi
        }        
        writeEEPROM(static_cast<EEPROM_Address>(ADDR_M_BUTON_AKTIF[m_btn_no]), M_buton_aktif[m_btn_no] ? 1 : 0);
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_kaydedildi, guider_ui.scr_kaydedildi_del, &guider_ui.scr_mbtn_del, setup_scr_scr_kaydedildi, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 1000, 500, true, true);
        break;
    }
    default:
        break;
    }
}

void src_main_net_label() { 
    if (net_label) {
      lv_obj_remove_flag(guider_ui.scr_main_brut_data_btn, LV_OBJ_FLAG_HIDDEN);
      //lv_obj_remove_flag(guider_ui.scr_main_adet_data_btn, LV_OBJ_FLAG_HIDDEN);
      lv_obj_remove_flag(guider_ui.scr_main_dara_data_btn, LV_OBJ_FLAG_HIDDEN);      
      //lv_obj_remove_flag(guider_ui.scr_main_birimgr_data_btn, LV_OBJ_FLAG_HIDDEN);
      lv_obj_set_pos(guider_ui.scr_main_knet_data_btn, 330, 76);
      lv_obj_set_size(guider_ui.scr_main_knet_data_btn, 150, 39);
      lv_obj_set_style_text_font(guider_ui.scr_main_knet_data_btn, &lv_font_Bebas_48, 0);
      lv_obj_remove_flag(guider_ui.scr_main_brut_label, LV_OBJ_FLAG_HIDDEN);
      //lv_obj_remove_flag(guider_ui.scr_main_adet_label, LV_OBJ_FLAG_HIDDEN);
      lv_obj_remove_flag(guider_ui.scr_main_dara_label, LV_OBJ_FLAG_HIDDEN);
      //lv_obj_remove_flag(guider_ui.scr_main_birimgr_label, LV_OBJ_FLAG_HIDDEN);
      lv_obj_remove_flag(guider_ui.scr_main_net_label, LV_OBJ_FLAG_HIDDEN);
      lv_obj_remove_flag(guider_ui.scr_main_menu_btn, LV_OBJ_FLAG_HIDDEN);
      lv_obj_set_pos(guider_ui.scr_main_urun_btn, 83, 26);
      lv_obj_set_size(guider_ui.scr_main_urun_btn, 314, 32);
      lv_obj_add_flag(guider_ui.scr_main_kg_label, LV_OBJ_FLAG_HIDDEN);
      lv_obj_set_width(guider_ui.scr_main_kod_btn, 80);
      //lv_obj_set_width(guider_ui.scr_main_t_ta, 80);
    } else {
      lv_obj_add_flag(guider_ui.scr_main_brut_data_btn, LV_OBJ_FLAG_HIDDEN);
      //lv_obj_add_flag(guider_ui.scr_main_adet_data_btn, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(guider_ui.scr_main_dara_data_btn, LV_OBJ_FLAG_HIDDEN);
      //lv_obj_add_flag(guider_ui.scr_main_birimgr_data_btn, LV_OBJ_FLAG_HIDDEN);
      lv_obj_set_pos(guider_ui.scr_main_knet_data_btn, 150, 26);
      lv_obj_set_size(guider_ui.scr_main_knet_data_btn, 290, 88);
      lv_obj_set_style_text_font(guider_ui.scr_main_knet_data_btn, &lv_font_Bebas_100, 0);
      lv_obj_add_flag(guider_ui.scr_main_brut_label, LV_OBJ_FLAG_HIDDEN);
      //lv_obj_add_flag(guider_ui.scr_main_adet_label, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(guider_ui.scr_main_dara_label, LV_OBJ_FLAG_HIDDEN);
      //lv_obj_add_flag(guider_ui.scr_main_birimgr_label, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(guider_ui.scr_main_net_label, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(guider_ui.scr_main_menu_btn, LV_OBJ_FLAG_HIDDEN);
      lv_obj_set_pos(guider_ui.scr_main_urun_btn, 1, 60);
      lv_obj_set_size(guider_ui.scr_main_urun_btn, 148, 54);
      lv_obj_remove_flag(guider_ui.scr_main_kg_label, LV_OBJ_FLAG_HIDDEN);
      lv_obj_set_width(guider_ui.scr_main_kod_btn, 148);
      //lv_obj_set_width(guider_ui.scr_main_t_ta, 80);
    }
}

static char tolower_tr(unsigned char c) {
    switch (c) {
        case 0xC7: return 0xE7;  // Ç -> ç
        case 0xD0: return 0xF0;  // Ğ -> ğ
        case 0xDD: return 'i';   // İ -> i
        case 'I':  return 0xFD;  // I -> ı
        case 0xD6: return 0xF6;  // Ö -> ö
        case 0xDE: return 0xFE;  // Ş -> ş
        case 0xDC: return 0xFC;  // Ü -> ü
        default: return tolower(c);
    }
}

static bool strcasestr_like(const char *haystack, const char *needle)
{
    if (!haystack || !needle) return false;

    size_t len_h = strlen(haystack);
    size_t len_n = strlen(needle);

    if (len_n == 0) return true; // boş arama her zaman eşleşir
    if (len_n > len_h) return false; // needle haystack'ten uzun olamaz

    for (size_t i = 0; i <= len_h - len_n; i++) {
        size_t j = 0;
        while (j < len_n &&
               tolower_tr((unsigned char)haystack[i + j]) == tolower((unsigned char)needle[j])) {
            j++;
        }
        if (j == len_n) return true; // tüm needle karakterleri eşleşti
    }
    return false;
}

void create_buttons(lv_ui *ui, lv_obj_t *parent, uint8_t mbtn_no) {
// Butonları oluşturmak için bir döngü kullanıyoruz
loadMesajLabels(mbtn_no);

lv_obj_set_style_bg_color(ui->scr_mbtn_m_cont, lv_color_hex(0x0000FF), static_cast<int>(LV_PART_SCROLLBAR) | static_cast<int>(LV_STATE_DEFAULT)); // Mavi renk
lv_obj_set_style_width(ui->scr_mbtn_m_cont, 8, static_cast<int>(LV_PART_SCROLLBAR) | static_cast<int>(LV_STATE_DEFAULT));  // Scrollbar genişliği 8 px
lv_obj_set_style_bg_opa(ui->scr_mbtn_m_cont, LV_OPA_50, static_cast<int>(LV_PART_SCROLLBAR) | static_cast<int>(LV_STATE_DEFAULT)); // %80 opaklık
lv_obj_set_style_radius(ui->scr_mbtn_m_cont, 10, static_cast<int>(LV_PART_SCROLLBAR) | static_cast<int>(LV_STATE_DEFAULT)); // 10 px köşe yuvarlaklığı

lv_obj_set_style_bg_color(ui->scr_mbtn_m_cont, lv_color_hex(0x00FF00), static_cast<int>(LV_PART_SCROLLBAR) | static_cast<int>(LV_STATE_SCROLLED)); // Mavi renk
lv_obj_set_style_width(ui->scr_mbtn_m_cont, 8, static_cast<int>(LV_PART_SCROLLBAR) | static_cast<int>(LV_STATE_SCROLLED));  // Scrollbar genişliği 8 px
lv_obj_set_style_bg_opa(ui->scr_mbtn_m_cont, LV_OPA_10, static_cast<int>(LV_PART_SCROLLBAR) | static_cast<int>(LV_STATE_SCROLLED)); // %80 opaklık
lv_obj_set_style_radius(ui->scr_mbtn_m_cont, 10, static_cast<int>(LV_PART_SCROLLBAR) | static_cast<int>(LV_STATE_SCROLLED)); // 10 px köşe yuvarlaklığı

//Write codes scr_mbtn_m_sw
ui->scr_mbtn_m_sw[mbtn_no] = lv_switch_create(ui->scr_mbtn);
lv_obj_set_pos(ui->scr_mbtn_m_sw[mbtn_no], 5, 30);
lv_obj_set_size(ui->scr_mbtn_m_sw[mbtn_no], 45, 25);
if (M_buton_aktif[mbtn_no]) {
    lv_obj_add_state(ui->scr_mbtn_m_sw[mbtn_no], LV_STATE_CHECKED);
} else {
    lv_obj_clear_state(ui->scr_mbtn_m_sw[mbtn_no], LV_STATE_CHECKED);
}

//Write style for scr_mbtn_m_sw, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
lv_obj_set_style_bg_opa(ui->scr_mbtn_m_sw[mbtn_no], 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
lv_obj_set_style_bg_color(ui->scr_mbtn_m_sw[mbtn_no], lv_color_hex(0xe6e2e6), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
lv_obj_set_style_bg_grad_dir(ui->scr_mbtn_m_sw[mbtn_no], LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
lv_obj_set_style_border_width(ui->scr_mbtn_m_sw[mbtn_no], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
lv_obj_set_style_radius(ui->scr_mbtn_m_sw[mbtn_no], 10, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
lv_obj_set_style_shadow_width(ui->scr_mbtn_m_sw[mbtn_no], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

//Write style for scr_mbtn_m_sw, Part: static_cast<int>(LV_PART_INDICATOR), State: static_cast<int>(LV_STATE_CHECKED).
lv_obj_set_style_bg_opa(ui->scr_mbtn_m_sw[mbtn_no], 255, static_cast<int>(LV_PART_INDICATOR)|static_cast<int>(LV_STATE_CHECKED));
lv_obj_set_style_bg_color(ui->scr_mbtn_m_sw[mbtn_no], lv_color_hex(0x2195f6), static_cast<int>(LV_PART_INDICATOR)|static_cast<int>(LV_STATE_CHECKED));
lv_obj_set_style_bg_grad_dir(ui->scr_mbtn_m_sw[mbtn_no], LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_INDICATOR)|static_cast<int>(LV_STATE_CHECKED));
lv_obj_set_style_border_width(ui->scr_mbtn_m_sw[mbtn_no], 0, static_cast<int>(LV_PART_INDICATOR)|static_cast<int>(LV_STATE_CHECKED));

//Write style for scr_mbtn_m_sw, Part: LV_PART_KNOB, State: static_cast<int>(LV_STATE_DEFAULT).
lv_obj_set_style_bg_opa(ui->scr_mbtn_m_sw[mbtn_no], 255, LV_PART_KNOB|static_cast<int>(LV_STATE_DEFAULT));
lv_obj_set_style_bg_color(ui->scr_mbtn_m_sw[mbtn_no], lv_color_hex(0xffffff), LV_PART_KNOB|static_cast<int>(LV_STATE_DEFAULT));
lv_obj_set_style_bg_grad_dir(ui->scr_mbtn_m_sw[mbtn_no], LV_GRAD_DIR_NONE, LV_PART_KNOB|static_cast<int>(LV_STATE_DEFAULT));
lv_obj_set_style_border_width(ui->scr_mbtn_m_sw[mbtn_no], 0, LV_PART_KNOB|static_cast<int>(LV_STATE_DEFAULT));
lv_obj_set_style_radius(ui->scr_mbtn_m_sw[mbtn_no], 10, LV_PART_KNOB|static_cast<int>(LV_STATE_DEFAULT));

lv_obj_add_event_cb(ui->scr_mbtn_m_sw[mbtn_no], src_mbtn_m_sw_event_handler, LV_EVENT_ALL, NULL);

for (uint8_t i = 0; i < 30; i++) {

    if ((!M_buton_aktif[m_btn_no]) && (i > 0)) {
        break;
    }    
    //Write codes scr_mbtn_m_no_label[i]
    ui->scr_mbtn_m_no_label[i] = lv_label_create(ui->scr_mbtn_m_cont);
    lv_obj_set_pos(ui->scr_mbtn_m_no_label[i], 2, i * 55);
    lv_obj_set_size(ui->scr_mbtn_m_no_label[i], 50, 50);
    if (i == 0)
      lv_label_set_text(ui->scr_mbtn_m_no_label[i], "GRUP ADI");
    else
      lv_label_set_text_fmt(ui->scr_mbtn_m_no_label[i], "%d.", i);
    lv_label_set_long_mode(ui->scr_mbtn_m_no_label[i], LV_LABEL_LONG_WRAP);

    //Write style for scr_mbtn_m_no_label[i], Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_mbtn_m_no_label[i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_mbtn_m_no_label[i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_mbtn_m_no_label[i], lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_mbtn_m_no_label[i], &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_mbtn_m_no_label[i], 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_letter_space(ui->scr_mbtn_m_no_label[i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_line_space(ui->scr_mbtn_m_no_label[i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_mbtn_m_no_label[i], LV_TEXT_ALIGN_RIGHT, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_mbtn_m_no_label[i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_mbtn_m_no_label[i], 11, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_mbtn_m_no_label[i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_bottom(ui->scr_mbtn_m_no_label[i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_mbtn_m_no_label[i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_mbtn_m_no_label[i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_mbtn_m_name_btn
    ui->scr_mbtn_m_name_btn[mbtn_no][i] = lv_button_create(ui->scr_mbtn_m_cont);
    lv_obj_set_pos(ui->scr_mbtn_m_name_btn[mbtn_no][i], 60, i * 55);
    lv_obj_set_size(ui->scr_mbtn_m_name_btn[mbtn_no][i], 280, 50);
    ui->scr_mbtn_m_name_btn_label[mbtn_no][i] = lv_label_create(ui->scr_mbtn_m_name_btn[mbtn_no][i]);
    lv_label_set_text(ui->scr_mbtn_m_name_btn_label[mbtn_no][i], mesaj_labels[mbtn_no][i]);
    //lv_label_set_long_mode(ui->scr_mbtn_m_name_btn_label[mbtn_no][i], LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_mbtn_m_name_btn_label[mbtn_no][i], LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_mbtn_m_name_btn[mbtn_no][i], 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_mbtn_m_name_btn_label[mbtn_no][i], LV_PCT(100));

    //Write style for scr_mbtn_m_name_btn[mbtn_no][i], Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_mbtn_m_name_btn[mbtn_no][i], 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    if (i == 0)
        lv_obj_set_style_bg_color(ui->scr_mbtn_m_name_btn[mbtn_no][i], lv_color_hex(0x2F92DA), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    else 
        lv_obj_set_style_bg_color(ui->scr_mbtn_m_name_btn[mbtn_no][i], lv_color_hex(0xff8f00), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_mbtn_m_name_btn[mbtn_no][i], LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_mbtn_m_name_btn[mbtn_no][i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_mbtn_m_name_btn[mbtn_no][i], 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_mbtn_m_name_btn[mbtn_no][i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_mbtn_m_name_btn[mbtn_no][i], lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_mbtn_m_name_btn[mbtn_no][i], &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_mbtn_m_name_btn[mbtn_no][i], 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_mbtn_m_name_btn[mbtn_no][i], Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_bg_opa(ui->scr_mbtn_m_name_btn[mbtn_no][i], 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_color(ui->scr_mbtn_m_name_btn[mbtn_no][i], lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_grad_dir(ui->scr_mbtn_m_name_btn[mbtn_no][i], LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_border_width(ui->scr_mbtn_m_name_btn[mbtn_no][i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_radius(ui->scr_mbtn_m_name_btn[mbtn_no][i], 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_mbtn_m_name_btn[mbtn_no][i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_mbtn_m_name_btn[mbtn_no][i], lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_mbtn_m_name_btn[mbtn_no][i], &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_mbtn_m_name_btn[mbtn_no][i], 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    lv_obj_add_event_cb(ui->scr_mbtn_m_name_btn[mbtn_no][i], mesaj_event_cb, LV_EVENT_ALL, NULL);
  }
}

//void create_urun_buttons(lv_ui *ui, lv_obj_t *parent) {
void create_urun_buttons(
        lv_ui *ui,
        lv_obj_t *parent,
        lv_obj_t **no_label,            // Numara etiketleri için parametre
        lv_obj_t **name_btn,            // Butonlar için parametre
        lv_obj_t **name_btn_label,      // Buton içi etiketler için parametre
        uint8_t menu,                   // Seçili buton için parametre
        const char *filter_text // 🔍 Eklenen filtre parametresi
    ) {
    // Butonları oluşturmak için bir döngü kullanıyoruz
    loadUrunLabels();
    
    lv_obj_set_style_bg_color(parent, lv_color_hex(0x0000FF), static_cast<int>(LV_PART_SCROLLBAR) | static_cast<int>(LV_STATE_DEFAULT)); // Mavi renk
    lv_obj_set_style_width(parent, 10, static_cast<int>(LV_PART_SCROLLBAR) | static_cast<int>(LV_STATE_DEFAULT));  // Scrollbar genişliği 8 px
    lv_obj_set_style_height(parent, 20, static_cast<int>(LV_PART_SCROLLBAR) | static_cast<int>(LV_STATE_DEFAULT));  // Scrollbar genişliği 8 px
    lv_obj_set_style_bg_opa(parent, LV_OPA_80, static_cast<int>(LV_PART_SCROLLBAR) | static_cast<int>(LV_STATE_DEFAULT)); // %80 opaklık
    lv_obj_set_style_radius(parent, 10, static_cast<int>(LV_PART_SCROLLBAR) | static_cast<int>(LV_STATE_DEFAULT)); // 10 px köşe yuvarlaklığı
    
    lv_obj_set_style_bg_color(parent, lv_color_hex(0x00FF00), static_cast<int>(LV_PART_SCROLLBAR) | static_cast<int>(LV_STATE_SCROLLED)); // Mavi renk
    lv_obj_set_style_width(parent, 10, static_cast<int>(LV_PART_SCROLLBAR) | static_cast<int>(LV_STATE_SCROLLED));  // Scrollbar genişliği 8 px
    lv_obj_set_style_height(parent, 20, static_cast<int>(LV_PART_SCROLLBAR) | static_cast<int>(LV_STATE_SCROLLED));  // Scrollbar genişliği 8 px
    lv_obj_set_style_bg_opa(parent, LV_OPA_50, static_cast<int>(LV_PART_SCROLLBAR) | static_cast<int>(LV_STATE_SCROLLED)); // %80 opaklık
    lv_obj_set_style_radius(parent, 10, static_cast<int>(LV_PART_SCROLLBAR) | static_cast<int>(LV_STATE_SCROLLED)); // 10 px köşe yuvarlaklığı 

    uint8_t aktif_urun_no = 0;
    const size_t filter_len = filter_text ? strlen(filter_text) : 0;
    const bool has_filter = filter_len > 0;

    for (uint8_t i = 0; i < 100; i++) {
        // Filtre varsa, boş isimlileri ve eşleşmeyenleri atla
        if (has_filter) {
            const char* current_label = urun_labels[i];
            if (!current_label || current_label[0] == '\0' || !strcasestr_like(current_label, filter_text)) {
                continue;
            }
        }
        
        //Write codes scr_ubtn_u_no_label[i]
        no_label[i]= lv_label_create(parent);
        lv_obj_set_pos(no_label[i], 2, aktif_urun_no * 55);
        lv_obj_set_size(no_label[i], 50, 50);
        if (i == 0) {
            lv_label_set_text(no_label[i], "KOD NO");                 // sabit literal, normal set
        } else {
            lv_label_set_text_static(no_label[i], urun_kod_labels[i]); // dizi içeriği -> static
        }

        lv_label_set_long_mode(no_label[i], LV_LABEL_LONG_WRAP);
        
        //Write style for scr_ubtn_u_no_label[i], Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
        lv_obj_set_style_border_width(no_label[i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
        lv_obj_set_style_radius(no_label[i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
        lv_obj_set_style_text_color(no_label[i], lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
        lv_obj_set_style_text_font(no_label[i], &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
        lv_obj_set_style_text_opa(no_label[i], 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
        lv_obj_set_style_text_letter_space(no_label[i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
        lv_obj_set_style_text_line_space(no_label[i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
        lv_obj_set_style_text_align(no_label[i], LV_TEXT_ALIGN_RIGHT, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
        lv_obj_set_style_bg_opa(no_label[i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
        lv_obj_set_style_pad_top(no_label[i], 11, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
        lv_obj_set_style_pad_right(no_label[i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
        lv_obj_set_style_pad_bottom(no_label[i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
        lv_obj_set_style_pad_left(no_label[i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
        lv_obj_set_style_shadow_width(no_label[i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));  

        name_btn[i] = lv_button_create(parent);
        lv_obj_set_pos(name_btn[i], 60, aktif_urun_no * 55);
        lv_obj_set_size(name_btn[i], 280, 50);
        name_btn_label[i] = lv_label_create(name_btn[i]);
        lv_label_set_long_mode(name_btn_label[i], LV_LABEL_LONG_DOT);  // taşma: ...
        lv_obj_set_width(name_btn_label[i], LV_PCT(100));              // genişlik sabit
        lv_label_set_text_static(name_btn_label[i], urun_labels[i]);   // KOPYASIZ, RAM dostu

        //lv_label_set_long_mode(name_btn_label[i], LV_LABEL_LONG_WRAP);
        lv_obj_align(name_btn_label[i], LV_ALIGN_CENTER, 0, 0);
        lv_obj_set_style_pad_all(name_btn[i], 0, static_cast<int>(LV_STATE_DEFAULT));
        lv_obj_set_width(name_btn_label[i], LV_PCT(100));

        //Write style for scr_ubtn_u_name_btn[i], Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
        //lv_obj_set_style_bg_opa(name_btn[i], 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
        if (i == 0)
          lv_obj_set_style_bg_color(name_btn[i], lv_color_hex(0x2F92DA), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
        else 
          lv_obj_set_style_bg_color(name_btn[i], lv_color_hex(0xFF0000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
        lv_obj_set_style_bg_grad_dir(name_btn[i], LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
        lv_obj_set_style_border_width(name_btn[i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
        lv_obj_set_style_radius(name_btn[i], 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
        lv_obj_set_style_shadow_width(name_btn[i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
        lv_obj_set_style_text_color(name_btn[i], lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
        lv_obj_set_style_text_font(name_btn[i], &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
        lv_obj_set_style_text_opa(name_btn[i], 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
        //lv_obj_set_style_text_align(name_btn[i], LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

        //Write style for scr_ubtn_u_name_btn[i], Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
        lv_obj_set_style_bg_opa(name_btn[i], 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
        lv_obj_set_style_bg_color(name_btn[i], lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
        lv_obj_set_style_bg_grad_dir(name_btn[i], LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
        lv_obj_set_style_border_width(name_btn[i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
        lv_obj_set_style_radius(name_btn[i], 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
        lv_obj_set_style_shadow_width(name_btn[i], 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
        lv_obj_set_style_text_color(name_btn[i], lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
        lv_obj_set_style_text_font(name_btn[i], &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
        lv_obj_set_style_text_opa(name_btn[i], 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

        // 📌 Kullanıcı verisini oluştur
        /*urun_event_data_t *urun_event_data = new urun_event_data_t{
            no_label,
            name_btn,
            name_btn_label,
            parent,
            menu
        };*/
        /*g_urun_event_data = &urun_event_data_array[i];
        *g_urun_event_data = new urun_event_data_t{
            no_label,
            name_btn,
            name_btn_label,
            parent,
            menu
        };*/

        g_urun_event_data = &urun_event_data_array[i];  // i: aktif ürünün indexi

        *g_urun_event_data = {
            no_label,
            name_btn,
            name_btn_label,
            parent,
            menu
        };       

        lv_obj_add_event_cb(name_btn[i], urun_event_cb, LV_EVENT_ALL, g_urun_event_data);
        
        aktif_urun_no++;
    }
    if (aktif_urun_no == 0) {
        // 📌 Eğer hiç ürün yoksa, bir etiket oluştur ve "Ürün Bulunamadı" yaz
        lv_obj_t *no_urun_label = lv_label_create(parent);
        lv_obj_set_pos(no_urun_label, 0, 0);
        lv_obj_set_size(no_urun_label, 320, 240);
        lv_label_set_text(no_urun_label, "Ürün Bulunamadı");
        //lv_label_set_long_mode(no_urun_label, LV_LABEL_LONG_WRAP);
        lv_obj_set_style_text_font(no_urun_label, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN) | static_cast<int>(LV_STATE_DEFAULT));
        lv_obj_set_style_text_color(no_urun_label, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN) | static_cast<int>(LV_STATE_DEFAULT));
        lv_obj_set_style_text_align(no_urun_label, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN) | static_cast<int>(LV_STATE_DEFAULT));
    }
}