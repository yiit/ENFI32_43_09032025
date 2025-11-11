/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom/custom.h"
#include <string.h>
#include "ESPEasy-Globals.h"

static void kod_girildi_cb(lv_event_t *e) {
    lv_obj_t *ta = (lv_obj_t *)lv_event_get_target(e);  // Event'in tetiklendiği objeyi al
    const char *girilen_kod = lv_textarea_get_text(ta);

    // Label'ı al (void* dönüşümünü açıkça yap)
    lv_obj_t *label = (lv_obj_t *)lv_event_get_user_data(e);

    // Ürün kodlarını ara ve eşleşen ismi bul
    const char *urun_ismi;
    for (uint8_t i = 0; i < 99; i++) {
        if (strcmp(girilen_kod, urun_kod_labels[i]) == 0) {
            urun_ismi = urun_labels[i];
            sec_URUN_buton = (uint8_t)i;
            break;
        }
        else {
            urun_ismi = "ÜRÜN BULUNAMADI";
            sec_URUN_buton = 0;
        }
    }
    // Label'a ürünü yaz
    lv_label_set_text(label, urun_ismi);
}

void setup_scr_scr_kod(lv_ui *ui)
{
    //Write codes scr_kod
    ui->scr_kod = lv_obj_create(NULL);
    lv_obj_set_size(ui->scr_kod, 480, 272);
    lv_obj_set_scrollbar_mode(ui->scr_kod, LV_SCROLLBAR_MODE_OFF);

    //Write style for scr_kod, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_kod, 255, static_cast<int>(static_cast<int>(LV_PART_MAIN))|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_kod, lv_color_hex(0xffffff), static_cast<int>(static_cast<int>(LV_PART_MAIN))|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_kod, LV_GRAD_DIR_NONE, static_cast<int>(static_cast<int>(LV_PART_MAIN))|LV_STATE_DEFAULT);

    //Write codes scr_kod_k_ta
    ui->scr_kod_k_ta = lv_textarea_create(ui->scr_kod);
    lv_obj_set_pos(ui->scr_kod_k_ta, 222, 62);
    lv_obj_set_size(ui->scr_kod_k_ta, 120, 35);
    lv_textarea_set_text(ui->scr_kod_k_ta, "");
    lv_textarea_set_placeholder_text(ui->scr_kod_k_ta, "KOD NO GİRİNİZ");
    lv_textarea_set_password_bullet(ui->scr_kod_k_ta, "*");
    lv_textarea_set_password_mode(ui->scr_kod_k_ta, false);
    lv_textarea_set_one_line(ui->scr_kod_k_ta, true);
    lv_textarea_set_accepted_chars(ui->scr_kod_k_ta, "");
    //lv_textarea_set_accepted_chars(ui->scr_kod_k_ta, ".,0123456789");
    lv_textarea_set_max_length(ui->scr_kod_k_ta, 13);
#if LV_USE_KEYBOARD
    // Klavye oluştur ve sadece numerik moda ayarla
    //ui->g_kb_top_layer = lv_keyboard_create(ui->scr_kod);
    lv_keyboard_set_mode(ui->g_kb_top_layer, LV_KEYBOARD_MODE_NUMBER);
    // Textarea'ya odaklandığında klavyeyi aç
    lv_obj_add_event_cb(ui->scr_kod_k_ta, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);    
    //lv_obj_add_event_cb(ui->scr_kod_k_ta, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
    lv_obj_set_size(ui->g_kb_top_layer, 370, 160); // Özel genişlik ve yükseklik ayarla
    lv_obj_align(ui->g_kb_top_layer, LV_ALIGN_BOTTOM_LEFT, 0, 0); // Alt orta hizala
    lv_keyboard_set_textarea(ui->g_kb_top_layer, ui->scr_kod_k_ta);
    lv_obj_clear_flag(ui->g_kb_top_layer, LV_OBJ_FLAG_HIDDEN);
#endif

    //Write style for scr_kod_k_ta, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->scr_kod_k_ta, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_kod_k_ta, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_kod_k_ta, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scr_kod_k_ta, 0,static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_kod_k_ta, LV_TEXT_ALIGN_RIGHT, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_kod_k_ta, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_kod_k_ta, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_kod_k_ta, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_kod_k_ta, 2, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scr_kod_k_ta, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scr_kod_k_ta, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scr_kod_k_ta, LV_BORDER_SIDE_FULL, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_kod_k_ta, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scr_kod_k_ta, 9, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_kod_k_ta, 4, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_kod_k_ta, 4, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_kod_k_ta, 4, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);

    //Write style for scr_kod_k_ta, Part: static_cast<int>(LV_PART_SCROLLBAR), State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_kod_k_ta, 255, static_cast<int>(LV_PART_SCROLLBAR)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_kod_k_ta, lv_color_hex(0x2195f6), static_cast<int>(LV_PART_SCROLLBAR)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_kod_k_ta, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_SCROLLBAR)|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_kod_k_ta, 0, static_cast<int>(LV_PART_SCROLLBAR)|LV_STATE_DEFAULT);

    //Write codes scr_kod_k_cont
    ui->scr_kod_k_cont = lv_obj_create(ui->scr_kod);
    lv_obj_set_pos(ui->scr_kod_k_cont, 0, 0);
    lv_obj_set_size(ui->scr_kod_k_cont, 480, 25);
    lv_obj_set_scrollbar_mode(ui->scr_kod_k_cont, LV_SCROLLBAR_MODE_OFF);

    //Write style for scr_kod_k_cont, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scr_kod_k_cont, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_kod_k_cont, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_kod_k_cont, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_kod_k_cont, lv_color_hex(0x0023F5), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_kod_k_cont, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scr_kod_k_cont, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scr_kod_k_cont, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_kod_k_cont, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_kod_k_cont, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_kod_k_cont, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);

    //Write codes scr_kod_k_duzen_btn
    ui->scr_kod_k_duzen_btn = lv_button_create(ui->scr_kod);
    lv_obj_set_pos(ui->scr_kod_k_duzen_btn, 375, 147);
    lv_obj_set_size(ui->scr_kod_k_duzen_btn, 96, 52);
    ui->scr_kod_k_duzen_btn_label = lv_label_create(ui->scr_kod_k_duzen_btn);
    lv_label_set_text(ui->scr_kod_k_duzen_btn_label, "");
    lv_label_set_long_mode(ui->scr_kod_k_duzen_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_kod_k_duzen_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_kod_k_duzen_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_kod_k_duzen_btn_label, LV_PCT(100));

    //Write style for scr_kod_k_duzen_btn, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_kod_k_duzen_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_kod_k_duzen_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_kod_k_duzen_btn, 5, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_kod_k_duzen_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(ui->scr_kod_k_duzen_btn, &_duzenle_RGB565A8_96x52, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_opa(ui->scr_kod_k_duzen_btn, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_recolor_opa(ui->scr_kod_k_duzen_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_kod_k_duzen_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_kod_k_duzen_btn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_kod_k_duzen_btn, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_kod_k_duzen_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);

    //Write codes scr_kod_k_bul_btn
    /*ui->scr_kod_k_bul_btn = lv_button_create(ui->scr_kod);
    lv_obj_set_pos(ui->scr_kod_k_bul_btn, 375, 28);
    lv_obj_set_size(ui->scr_kod_k_bul_btn, 96, 52);
    ui->scr_kod_k_bul_btn_label = lv_label_create(ui->scr_kod_k_bul_btn);
    lv_label_set_text(ui->scr_kod_k_bul_btn_label, "");
    lv_label_set_long_mode(ui->scr_kod_k_bul_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_kod_k_bul_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_kod_k_bul_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_kod_k_bul_btn_label, LV_PCT(100));

    //Write style for scr_kod_k_bul_btn, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_kod_k_bul_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_kod_k_bul_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_kod_k_bul_btn, 5, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_kod_k_bul_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(ui->scr_kod_k_bul_btn, &_bul_RGB565A8_96x52, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_opa(ui->scr_kod_k_bul_btn, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_recolor_opa(ui->scr_kod_k_bul_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_kod_k_bul_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_kod_k_bul_btn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_kod_k_bul_btn, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_kod_k_bul_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);*/

    //Write codes scr_kod_k_u_label
    ui->scr_kod_k_u_label = lv_label_create(ui->scr_kod);
    lv_obj_set_pos(ui->scr_kod_k_u_label, 2, 26);
    lv_obj_set_size(ui->scr_kod_k_u_label, 340, 32);
    lv_label_set_text(ui->scr_kod_k_u_label, "ÜRÜN İSMİ");
    lv_label_set_long_mode(ui->scr_kod_k_u_label, LV_LABEL_LONG_WRAP);

    //Write style for scr_kod_k_u_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scr_kod_k_u_label, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_kod_k_u_label, 5, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_kod_k_u_label, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_kod_k_u_label, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_kod_k_u_label, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scr_kod_k_u_label, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scr_kod_k_u_label, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_kod_k_u_label, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_kod_k_u_label, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_kod_k_u_label, lv_color_hex(0xff0000), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_kod_k_u_label, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scr_kod_k_u_label, 9, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_kod_k_u_label, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scr_kod_k_u_label, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_kod_k_u_label, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_kod_k_u_label, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);

    //Write codes scr_kod_k_geri_btn
    ui->scr_kod_k_geri_btn = lv_button_create(ui->scr_kod);
    lv_obj_set_pos(ui->scr_kod_k_geri_btn, 375, 208);
    lv_obj_set_size(ui->scr_kod_k_geri_btn, 96, 52);
    ui->scr_kod_k_geri_btn_label = lv_label_create(ui->scr_kod_k_geri_btn);
    lv_label_set_text(ui->scr_kod_k_geri_btn_label, "");
    lv_label_set_long_mode(ui->scr_kod_k_geri_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_kod_k_geri_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_kod_k_geri_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_kod_k_geri_btn_label, LV_PCT(100));

    //Write style for scr_kod_k_geri_btn, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_kod_k_geri_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_kod_k_geri_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_kod_k_geri_btn, 5, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_kod_k_geri_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(ui->scr_kod_k_geri_btn, &_geri_RGB565A8_96x52, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_opa(ui->scr_kod_k_geri_btn, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_recolor_opa(ui->scr_kod_k_geri_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_kod_k_geri_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_kod_k_geri_btn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_kod_k_geri_btn, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_kod_k_geri_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);

    //Write codes scr_kod_k_sec_btn
    ui->scr_kod_k_sec_btn = lv_button_create(ui->scr_kod);
    //lv_obj_set_pos(ui->scr_kod_k_sec_btn, 375, 88);
    //lv_obj_set_size(ui->scr_kod_k_sec_btn, 96, 52);
    lv_obj_set_pos(ui->scr_kod_k_sec_btn, 375, 30);
    lv_obj_set_size(ui->scr_kod_k_sec_btn, 96, 52);
    ui->scr_kod_k_sec_btn_label = lv_label_create(ui->scr_kod_k_sec_btn);
    lv_label_set_text(ui->scr_kod_k_sec_btn_label, "");
    lv_label_set_long_mode(ui->scr_kod_k_sec_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_kod_k_sec_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_kod_k_sec_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_kod_k_sec_btn_label, LV_PCT(100));

    //Write style for scr_kod_k_sec_btn, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_kod_k_sec_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_kod_k_sec_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_kod_k_sec_btn, 5, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_kod_k_sec_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(ui->scr_kod_k_sec_btn, &_sec_RGB565A8_96x52, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_opa(ui->scr_kod_k_sec_btn, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_recolor_opa(ui->scr_kod_k_sec_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_kod_k_sec_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_kod_k_sec_btn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_kod_k_sec_btn, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_kod_k_sec_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);

    //Update current screen layout.
    lv_obj_update_layout(ui->scr_kod);

    //Init events for screen.
    events_init_scr_kod(ui);

    // Textarea'ya event callback ekleyerek kod girildiğinde ürün adını güncelle
    lv_obj_add_event_cb(ui->scr_kod_k_ta, kod_girildi_cb, LV_EVENT_VALUE_CHANGED, ui->scr_kod_k_u_label);
}
