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
#include "custom.h"
#include "custom/custom.h"
#include "../ESPEasy-Globals.h"
#include "buton_json_lfs.h"

// Statik bellek optimizasyonu için değişkenler
static char m1_part1[10], m1_part2[10];
static char m1_char[20];

// Buton olay işleyicisi - Optimize edilmiş versiyon
static void btn_event_cb(lv_event_t *e) {
    lv_obj_t *kb = static_cast<lv_obj_t *>(lv_event_get_user_data(e));
    static lv_obj_t *ta = NULL;

    if(!ta) {
        ta = lv_textarea_create(lv_scr_act());
        lv_obj_set_size(ta, 150, 40);
        lv_obj_align(ta, LV_ALIGN_TOP_MID, 0, 10);
        lv_textarea_set_one_line(ta, true);
        lv_textarea_set_max_length(ta, 13);
    }

    lv_keyboard_set_textarea(kb, ta);
    lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    lv_obj_move_foreground(kb);
    lv_obj_add_flag(ta, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_add_state(ta, LV_STATE_FOCUSED);
}

// Metin ortalamak için optimize edilmiş fonksiyon
void center_text(char *dest, const char *src, int width) {
    int len = strlen(src);
    if (len >= width) {
        snprintf(dest, width + 1, "%.*s", width, src);
        return;
    }
    int pad_left = (width - len) / 2;
    int pad_right = width - len - pad_left;
    snprintf(dest, width + 1, "%*s%s%*s", pad_left, "", src, pad_right, ""); 
}

// Scroll olaylarını dinleyen fonksiyon
static void scroll_event_handler(lv_event_t * e) {
  lv_obj_t * obj = (lv_obj_t *)lv_event_get_target(e);
  lv_event_code_t code = lv_event_get_code(e);

  if (code == LV_EVENT_SCROLL_BEGIN) {
      // Kaydırma başladığında kırmızı yap
      lv_obj_set_style_bg_color(obj, lv_color_hex(0xFF0000), static_cast<int>(LV_PART_SCROLLBAR) | static_cast<int>(LV_STATE_DEFAULT));
      lv_obj_set_style_bg_opa(obj, 255, static_cast<int>(LV_PART_SCROLLBAR) | static_cast<int>(LV_STATE_DEFAULT)); // Görünür yap
  } 
  else if (code == LV_EVENT_SCROLL_END) {
      // Kaydırma bittiğinde saydam yap
      lv_obj_set_style_bg_opa(obj, 0, static_cast<int>(LV_PART_SCROLLBAR) | static_cast<int>(LV_STATE_DEFAULT));
  }
}

// Ana ekran kurulumu - Optimize edilmiş versiyon
void setup_scr_scr_main(lv_ui *ui) {
    //loadUrunLabels();
    // Ana ekran oluştur
    ui->scr_main = lv_obj_create(NULL);
    lv_obj_set_size(ui->scr_main, 480, 272);
    lv_obj_set_scrollbar_mode(ui->scr_main, LV_SCROLLBAR_MODE_OFF);

    //Write style for scr_main, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_main, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_main, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN) | static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    // Ana container oluştur
    ui->scr_main_m_cont = lv_obj_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_m_cont, 34, 114);
    lv_obj_set_size(ui->scr_main_m_cont, 412, 44);
    lv_obj_set_scrollbar_mode(ui->scr_main_m_cont, LV_SCROLLBAR_MODE_AUTO);
    lv_obj_add_flag(ui->scr_main_m_cont, LV_OBJ_FLAG_SCROLL_WITH_ARROW);
    lv_obj_set_style_bg_opa(ui->scr_main_m_cont, 0, static_cast<int>(LV_PART_SCROLLBAR) | static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_m_cont, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_main_m_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_m_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_main_m_cont, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_main_m_cont, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_cont, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_main_m_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_bottom(ui->scr_main_m_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_main_m_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_main_m_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_m_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    // Scroll olaylarını ekle
    lv_obj_add_event_cb(ui->scr_main_m_cont, scroll_event_handler, LV_EVENT_SCROLL_BEGIN, NULL);
    lv_obj_add_event_cb(ui->scr_main_m_cont, scroll_event_handler, LV_EVENT_SCROLL_END, NULL);

    //Write codes scr_main_m_btn_1
    ui->scr_main_m_btn_1 = lv_button_create(ui->scr_main_m_cont);
    lv_obj_set_pos(ui->scr_main_m_btn_1, 2, 2);
    lv_obj_set_size(ui->scr_main_m_btn_1, 100, 42);
    lv_obj_add_flag(ui->scr_main_m_btn_1, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_m_btn_1_label = lv_label_create(ui->scr_main_m_btn_1);

    // İlk ve ikinci stringi 8 karaktere tamamlayarak ortala
    center_text(m1_part1, mesaj_labels[0][0], 9);
    //center_text(m1_part2, mesaj_labels[0][sec_M_buton[0]], 9);
    if (M_buton_aktif[0]) {
      center_text(m1_part2, mesaj_labels[0][sec_M_buton[0]], 9);
      snprintf(m1_char, sizeof(m1_char), "%s%s", m1_part1, m1_part2);
      lv_obj_set_style_bg_opa(ui->scr_main_m_btn_1, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    }
    else {
      snprintf(m1_char, sizeof(m1_char), "%s", m1_part1);
      lv_obj_set_style_bg_opa(ui->scr_main_m_btn_1, 150, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    }
    lv_label_set_text(ui->scr_main_m_btn_1_label, m1_char);
    lv_label_set_long_mode(ui->scr_main_m_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_m_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_m_btn_1, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_m_btn_1_label, LV_PCT(100));

    //Write style for scr_main_m_btn_1, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_1, lv_color_hex(0xff8f00), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_1, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_m_btn_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_m_btn_1, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_m_btn_1, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_m_btn_1, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_1, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_m_btn_1, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_m_btn_1, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_bg_opa(ui->scr_main_m_btn_1, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_1, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_1, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_border_width(ui->scr_main_m_btn_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_radius(ui->scr_main_m_btn_1, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_main_m_btn_1, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_main_m_btn_1, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_1, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    //Write codes scr_main_m_btn_2
    ui->scr_main_m_btn_2 = lv_button_create(ui->scr_main_m_cont);
    lv_obj_set_pos(ui->scr_main_m_btn_2, 105, 2);
    lv_obj_set_size(ui->scr_main_m_btn_2, 100, 42);
    lv_obj_add_flag(ui->scr_main_m_btn_2, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_m_btn_2_label = lv_label_create(ui->scr_main_m_btn_2);
    // İlk ve ikinci stringi 8 karaktere tamamlayarak ortala
    center_text(m1_part1, mesaj_labels[1][0], 9);
    //center_text(m1_part2, mesaj_labels[1][sec_M_buton[1]], 9);
    // İki parçayı birleştir
    if (M_buton_aktif[1]) {
      center_text(m1_part2, mesaj_labels[1][sec_M_buton[1]], 9);
      snprintf(m1_char, sizeof(m1_char), "%s%s", m1_part1, m1_part2);
      lv_obj_set_style_bg_opa(ui->scr_main_m_btn_2, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    }
    else {
      snprintf(m1_char, sizeof(m1_char), "%s", m1_part1);
      lv_obj_set_style_bg_opa(ui->scr_main_m_btn_2, 150, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    }
    lv_label_set_text(ui->scr_main_m_btn_2_label, m1_char);
    lv_label_set_long_mode(ui->scr_main_m_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_m_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_m_btn_2, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_m_btn_2_label, LV_PCT(100));

    //Write style for scr_main_m_btn_2, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_2, lv_color_hex(0xff8f00), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_2, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_m_btn_2, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_m_btn_2, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_2, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_m_btn_2, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_m_btn_2, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_2, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_m_btn_2, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_m_btn_2, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_bg_opa(ui->scr_main_m_btn_2, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_2, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_2, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_border_width(ui->scr_main_m_btn_2, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_radius(ui->scr_main_m_btn_2, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_2, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_main_m_btn_2, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_main_m_btn_2, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_2, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    //Write codes scr_main_m_btn_3
    ui->scr_main_m_btn_3 = lv_button_create(ui->scr_main_m_cont);
    lv_obj_set_pos(ui->scr_main_m_btn_3, 208, 2);
    lv_obj_set_size(ui->scr_main_m_btn_3, 100, 42);
    lv_obj_add_flag(ui->scr_main_m_btn_3, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_m_btn_3_label = lv_label_create(ui->scr_main_m_btn_3);
    // İlk ve ikinci stringi 8 karaktere tamamlayarak ortala
    center_text(m1_part1, mesaj_labels[2][0], 9);
    //center_text(m1_part2, mesaj_labels[2][sec_M_buton[2]], 9);
    if (M_buton_aktif[2]) {
      center_text(m1_part2, mesaj_labels[2][sec_M_buton[2]], 9);
      snprintf(m1_char, sizeof(m1_char), "%s%s", m1_part1, m1_part2);
      lv_obj_set_style_bg_opa(ui->scr_main_m_btn_3, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    }
    else {
      snprintf(m1_char, sizeof(m1_char), "%s", m1_part1);
      lv_obj_set_style_bg_opa(ui->scr_main_m_btn_3, 150, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    }
    lv_label_set_text(ui->scr_main_m_btn_3_label, m1_char);
    lv_label_set_long_mode(ui->scr_main_m_btn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_m_btn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_m_btn_3, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_m_btn_3_label, LV_PCT(100));

    //Write style for scr_main_m_btn_3, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_3, lv_color_hex(0xff8f00), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_3, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_m_btn_3, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_m_btn_3, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_3, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_m_btn_3, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_m_btn_3, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_3, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_m_btn_3, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_m_btn_3, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_bg_opa(ui->scr_main_m_btn_3, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_3, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_3, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_border_width(ui->scr_main_m_btn_3, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_radius(ui->scr_main_m_btn_3, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_3, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_main_m_btn_3, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_main_m_btn_3, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_3, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    //Write codes scr_main_m_btn_4
    ui->scr_main_m_btn_4 = lv_button_create(ui->scr_main_m_cont);
    lv_obj_set_pos(ui->scr_main_m_btn_4, 311, 2);
    lv_obj_set_size(ui->scr_main_m_btn_4, 100, 42);
    lv_obj_add_flag(ui->scr_main_m_btn_4, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_m_btn_4_label = lv_label_create(ui->scr_main_m_btn_4);
    // İlk ve ikinci stringi 8 karaktere tamamlayarak ortala
    center_text(m1_part1, mesaj_labels[3][0], 9);
    //center_text(m1_part2, mesaj_labels[3][sec_M_buton[3]], 9);
    if (M_buton_aktif[3]) {
      center_text(m1_part2, mesaj_labels[3][sec_M_buton[3]], 9);
      snprintf(m1_char, sizeof(m1_char), "%s%s", m1_part1, m1_part2);
      lv_obj_set_style_bg_opa(ui->scr_main_m_btn_4, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    }
    else {
      snprintf(m1_char, sizeof(m1_char), "%s", m1_part1);
      lv_obj_set_style_bg_opa(ui->scr_main_m_btn_4, 150, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    }
    lv_label_set_text(ui->scr_main_m_btn_4_label, m1_char);
    lv_label_set_long_mode(ui->scr_main_m_btn_4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_m_btn_4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_m_btn_4, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_m_btn_4_label, LV_PCT(100));

    //Write style for scr_main_m_btn_4, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_4, lv_color_hex(0xff8f00), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_4, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_m_btn_4, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_m_btn_4, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_4, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_m_btn_4, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_m_btn_4, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_4, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_m_btn_4, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_m_btn_4, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_bg_opa(ui->scr_main_m_btn_4, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_4, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_4, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_border_width(ui->scr_main_m_btn_4, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_radius(ui->scr_main_m_btn_4, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_4, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_main_m_btn_4, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_main_m_btn_4, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_4, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    //Write codes scr_main_m_btn_5
    ui->scr_main_m_btn_5 = lv_button_create(ui->scr_main_m_cont);
    lv_obj_set_pos(ui->scr_main_m_btn_5, 414, 2);
    lv_obj_set_size(ui->scr_main_m_btn_5, 100, 42);
    lv_obj_add_flag(ui->scr_main_m_btn_5, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_m_btn_5_label = lv_label_create(ui->scr_main_m_btn_5);
    // İlk ve ikinci stringi 8 karaktere tamamlayarak ortala
    center_text(m1_part1, mesaj_labels[4][0], 9);
    //center_text(m1_part2, mesaj_labels[4][sec_M_buton[4]], 9);
    if (M_buton_aktif[4]) {
      center_text(m1_part2, mesaj_labels[4][sec_M_buton[4]], 9);
      snprintf(m1_char, sizeof(m1_char), "%s%s", m1_part1, m1_part2);
      lv_obj_set_style_bg_opa(ui->scr_main_m_btn_5, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    }
    else {
      snprintf(m1_char, sizeof(m1_char), "%s", m1_part1);
      lv_obj_set_style_bg_opa(ui->scr_main_m_btn_5, 150, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    }
    lv_label_set_text(ui->scr_main_m_btn_5_label, m1_char);
    lv_label_set_long_mode(ui->scr_main_m_btn_5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_m_btn_5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_m_btn_5, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_m_btn_5_label, LV_PCT(100));

    //Write style for scr_main_m_btn_5, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_5, lv_color_hex(0xff8f00), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_5, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_m_btn_5, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_m_btn_5, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_5, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_m_btn_5, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_m_btn_5, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_5, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_m_btn_5, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_m_btn_5, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_bg_opa(ui->scr_main_m_btn_5, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_5, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_5, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_border_width(ui->scr_main_m_btn_5, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_radius(ui->scr_main_m_btn_5, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_5, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_main_m_btn_5, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_main_m_btn_5, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_5, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    //Write codes scr_main_m_btn_6
    ui->scr_main_m_btn_6 = lv_button_create(ui->scr_main_m_cont);
    lv_obj_set_pos(ui->scr_main_m_btn_6, 517, 2);
    lv_obj_set_size(ui->scr_main_m_btn_6, 100, 42);
    lv_obj_add_flag(ui->scr_main_m_btn_6, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_m_btn_6_label = lv_label_create(ui->scr_main_m_btn_6);
    // İlk ve ikinci stringi 8 karaktere tamamlayarak ortala
    center_text(m1_part1, mesaj_labels[5][0], 9);
    //center_text(m1_part2, mesaj_labels[5][sec_M_buton[5]], 9);
    if (M_buton_aktif[5]) {
      center_text(m1_part2, mesaj_labels[5][sec_M_buton[5]], 9);
      snprintf(m1_char, sizeof(m1_char), "%s%s", m1_part1, m1_part2);
      lv_obj_set_style_bg_opa(ui->scr_main_m_btn_6, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    }
    else {
      snprintf(m1_char, sizeof(m1_char), "%s", m1_part1);
      lv_obj_set_style_bg_opa(ui->scr_main_m_btn_6, 150, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    }
    lv_label_set_text(ui->scr_main_m_btn_6_label, m1_char);
    lv_label_set_long_mode(ui->scr_main_m_btn_6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_m_btn_6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_m_btn_6, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_m_btn_6_label, LV_PCT(100));

    //Write style for scr_main_m_btn_6, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_6, lv_color_hex(0xff8f00), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_6, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_m_btn_6, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_m_btn_6, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_6, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_m_btn_6, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_m_btn_6, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_6, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_m_btn_6, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_m_btn_6, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_bg_opa(ui->scr_main_m_btn_6, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_6, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_6, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_border_width(ui->scr_main_m_btn_6, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_radius(ui->scr_main_m_btn_6, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_6, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_main_m_btn_6, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_main_m_btn_6, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_6, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    //Write codes scr_main_m_btn_7
    ui->scr_main_m_btn_7 = lv_button_create(ui->scr_main_m_cont);
    lv_obj_set_pos(ui->scr_main_m_btn_7, 620, 2);
    lv_obj_set_size(ui->scr_main_m_btn_7, 100, 42);
    lv_obj_add_flag(ui->scr_main_m_btn_7, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_m_btn_7_label = lv_label_create(ui->scr_main_m_btn_7);
    // İlk ve ikinci stringi 8 karaktere tamamlayarak ortala
    center_text(m1_part1, mesaj_labels[6][0], 9);
    //center_text(m1_part2, mesaj_labels[6][sec_M_buton[6]], 9);
    if (M_buton_aktif[6]) {
      center_text(m1_part2, mesaj_labels[6][sec_M_buton[6]], 9);
      snprintf(m1_char, sizeof(m1_char), "%s%s", m1_part1, m1_part2);
      lv_obj_set_style_bg_opa(ui->scr_main_m_btn_7, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    }
    else {
      snprintf(m1_char, sizeof(m1_char), "%s", m1_part1);
      lv_obj_set_style_bg_opa(ui->scr_main_m_btn_7, 150, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    }
    lv_label_set_text(ui->scr_main_m_btn_7_label, m1_char);
    lv_label_set_long_mode(ui->scr_main_m_btn_7_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_m_btn_7_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_m_btn_7, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_m_btn_7_label, LV_PCT(100));

    //Write style for scr_main_m_btn_7, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_7, lv_color_hex(0xff8f00), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_7, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_m_btn_7, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_m_btn_7, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_7, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_m_btn_7, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_m_btn_7, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_7, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_m_btn_7, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_m_btn_7, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_bg_opa(ui->scr_main_m_btn_7, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_7, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_7, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_border_width(ui->scr_main_m_btn_7, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_radius(ui->scr_main_m_btn_7, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_7, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_main_m_btn_7, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_main_m_btn_7, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_7, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    //Write codes scr_main_m_btn_8
    ui->scr_main_m_btn_8 = lv_button_create(ui->scr_main_m_cont);
    lv_obj_set_pos(ui->scr_main_m_btn_8, 723, 2);
    lv_obj_set_size(ui->scr_main_m_btn_8, 100, 42);
    lv_obj_add_flag(ui->scr_main_m_btn_8, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_m_btn_8_label = lv_label_create(ui->scr_main_m_btn_8);
    // İlk ve ikinci stringi 8 karaktere tamamlayarak ortala
    center_text(m1_part1, mesaj_labels[7][0], 9);
    //center_text(m1_part2, mesaj_labels[7][sec_M_buton[7]], 9);
    if (M_buton_aktif[7]) {
      center_text(m1_part2, mesaj_labels[7][sec_M_buton[7]], 9);
      snprintf(m1_char, sizeof(m1_char), "%s%s", m1_part1, m1_part2);
      lv_obj_set_style_bg_opa(ui->scr_main_m_btn_8, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    }
    else {
      snprintf(m1_char, sizeof(m1_char), "%s", m1_part1);
      lv_obj_set_style_bg_opa(ui->scr_main_m_btn_8, 150, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    }
    lv_label_set_text(ui->scr_main_m_btn_8_label, m1_char);
    lv_label_set_long_mode(ui->scr_main_m_btn_8_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_m_btn_8_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_m_btn_8, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_m_btn_8_label, LV_PCT(100));

    //Write style for scr_main_m_btn_8, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_8, lv_color_hex(0xff8f00), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_8, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_m_btn_8, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_m_btn_8, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_8, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_m_btn_8, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_m_btn_8, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_8, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_m_btn_8, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_m_btn_8, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_bg_opa(ui->scr_main_m_btn_8, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_8, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_8, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_border_width(ui->scr_main_m_btn_8, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_radius(ui->scr_main_m_btn_8, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_8, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_main_m_btn_8, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_main_m_btn_8, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_8, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    //Write codes scr_main_f_cont
    ui->scr_main_f_cont = lv_obj_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_f_cont, 0, 160);
    lv_obj_set_size(ui->scr_main_f_cont, 380, 112);
    lv_obj_set_scrollbar_mode(ui->scr_main_f_cont, LV_SCROLLBAR_MODE_OFF);

    //Write style for scr_main_f_cont, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_main_f_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_f_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_main_f_cont, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_main_f_cont, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_cont, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_main_f_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_bottom(ui->scr_main_f_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_main_f_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_main_f_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_f_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_main_f_btn_1
    ui->scr_main_f_btn_1 = lv_button_create(ui->scr_main_f_cont);
    lv_obj_set_pos(ui->scr_main_f_btn_1, 1, 0);
    lv_obj_set_size(ui->scr_main_f_btn_1, 92, 54);
    lv_obj_add_flag(ui->scr_main_f_btn_1, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_f_btn_1_label = lv_label_create(ui->scr_main_f_btn_1);
    if (sec_F_buton[0] <= 0) 
      lv_label_set_text(ui->scr_main_f_btn_1_label, "F1");
    else
      lv_label_set_text(ui->scr_main_f_btn_1_label, urun_labels[sec_F_buton[0]]);
    lv_label_set_long_mode(ui->scr_main_f_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_f_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_f_btn_1, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_f_btn_1_label, LV_PCT(100));

    //Write style for scr_main_f_btn_1, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_1, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_1, lv_color_hex(0x0023F5), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_1, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_f_btn_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_f_btn_1, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_f_btn_1, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_f_btn_1, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_1, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_f_btn_1, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_f_btn_1, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_1, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_1, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_1, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_border_width(ui->scr_main_f_btn_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_radius(ui->scr_main_f_btn_1, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_main_f_btn_1, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_main_f_btn_1, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_1, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    //Write codes scr_main_f_btn_2
    ui->scr_main_f_btn_2 = lv_button_create(ui->scr_main_f_cont);
    lv_obj_set_pos(ui->scr_main_f_btn_2, 95, 0);
    lv_obj_set_size(ui->scr_main_f_btn_2, 92, 54);
    lv_obj_add_flag(ui->scr_main_f_btn_2, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_f_btn_2_label = lv_label_create(ui->scr_main_f_btn_2);
    if (sec_F_buton[1] <= 0) 
      lv_label_set_text(ui->scr_main_f_btn_2_label, "F2");
    else
      lv_label_set_text(ui->scr_main_f_btn_2_label, urun_labels[sec_F_buton[1]]);
    lv_label_set_long_mode(ui->scr_main_f_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_f_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_f_btn_2, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_f_btn_2_label, LV_PCT(100));

    //Write style for scr_main_f_btn_2, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_2, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_2, lv_color_hex(0x0023F5), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_2, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_f_btn_2, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_f_btn_2, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_2, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_f_btn_2, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_f_btn_2, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_2, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_f_btn_2, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_f_btn_2, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_2, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_2, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_2, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_border_width(ui->scr_main_f_btn_2, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_radius(ui->scr_main_f_btn_2, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_2, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_main_f_btn_2, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_main_f_btn_2, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_2, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    //Write codes scr_main_f_btn_3
    ui->scr_main_f_btn_3 = lv_button_create(ui->scr_main_f_cont);
    lv_obj_set_pos(ui->scr_main_f_btn_3, 189, 0);
    lv_obj_set_size(ui->scr_main_f_btn_3, 92, 54);
    lv_obj_add_flag(ui->scr_main_f_btn_3, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_f_btn_3_label = lv_label_create(ui->scr_main_f_btn_3);
    if (sec_F_buton[2] <= 0) 
      lv_label_set_text(ui->scr_main_f_btn_3_label, "F3");
    else
      lv_label_set_text(ui->scr_main_f_btn_3_label, urun_labels[sec_F_buton[2]]);
    lv_label_set_long_mode(ui->scr_main_f_btn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_f_btn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_f_btn_3, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_f_btn_3_label, LV_PCT(100));

    //Write style for scr_main_f_btn_3, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_3, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_3, lv_color_hex(0x0023F5), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_3, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_f_btn_3, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_f_btn_3, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_3, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_f_btn_3, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_f_btn_3, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_3, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_f_btn_3, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_f_btn_3, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_3, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_3, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_3, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_border_width(ui->scr_main_f_btn_3, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_radius(ui->scr_main_f_btn_3, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_3, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_main_f_btn_3, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_main_f_btn_3, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_3, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    //Write codes scr_main_f_btn_4
    /*ui->scr_main_f_btn_4 = lv_button_create(ui->scr_main_f_cont);
    lv_obj_set_pos(ui->scr_main_f_btn_4, 283, 0);
    lv_obj_set_size(ui->scr_main_f_btn_4, 92, 54);
    lv_obj_add_flag(ui->scr_main_f_btn_4, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_f_btn_4_label = lv_label_create(ui->scr_main_f_btn_4);
    if (sec_F_buton[3] <= 0) 
      lv_label_set_text(ui->scr_main_f_btn_4_label, "F4");
    else
      lv_label_set_text(ui->scr_main_f_btn_4_label, urun_labels[sec_F_buton[3]]);
    lv_label_set_long_mode(ui->scr_main_f_btn_4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_f_btn_4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_f_btn_4, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_f_btn_4_label, LV_PCT(100));

    //Write style for scr_main_f_btn_4, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_4, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_4, lv_color_hex(0x0023F5), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_4, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_f_btn_4, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_f_btn_4, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_4, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_f_btn_4, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_f_btn_4, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_4, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_f_btn_4, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_f_btn_4, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_4, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_4, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_4, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_border_width(ui->scr_main_f_btn_4, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_radius(ui->scr_main_f_btn_4, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_4, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_main_f_btn_4, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_main_f_btn_4, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_4, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));*/

    //Write codes scr_main_f_btn_5
    ui->scr_main_f_btn_5 = lv_button_create(ui->scr_main_f_cont);
    lv_obj_set_pos(ui->scr_main_f_btn_5, 1, 56);
    lv_obj_set_size(ui->scr_main_f_btn_5, 92, 54);
    lv_obj_add_flag(ui->scr_main_f_btn_5, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_f_btn_5_label = lv_label_create(ui->scr_main_f_btn_5);
    if (sec_F_buton[4] <= 0) 
      lv_label_set_text(ui->scr_main_f_btn_5_label, "F5");
    else
      lv_label_set_text(ui->scr_main_f_btn_5_label, urun_labels[sec_F_buton[4]]);
    lv_label_set_long_mode(ui->scr_main_f_btn_5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_f_btn_5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_f_btn_5, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_f_btn_5_label, LV_PCT(100));

    //Write style for scr_main_f_btn_5, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_5, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_5, lv_color_hex(0x0023F5), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_5, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_f_btn_5, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_f_btn_5, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_5, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_f_btn_5, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_f_btn_5, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_5, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_f_btn_5, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_f_btn_5, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_5, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_5, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_5, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_border_width(ui->scr_main_f_btn_5, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_radius(ui->scr_main_f_btn_5, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_5, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_main_f_btn_5, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_main_f_btn_5, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_5, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    //Write codes scr_main_f_btn_6
    ui->scr_main_f_btn_6 = lv_button_create(ui->scr_main_f_cont);
    lv_obj_set_pos(ui->scr_main_f_btn_6, 95, 56);
    lv_obj_set_size(ui->scr_main_f_btn_6, 92, 54);
    lv_obj_add_flag(ui->scr_main_f_btn_6, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_f_btn_6_label = lv_label_create(ui->scr_main_f_btn_6);
    if (sec_F_buton[5] <= 0) 
      lv_label_set_text(ui->scr_main_f_btn_6_label, "F6");
    else
      lv_label_set_text(ui->scr_main_f_btn_6_label, urun_labels[sec_F_buton[5]]);
    lv_label_set_long_mode(ui->scr_main_f_btn_6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_f_btn_6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_f_btn_6, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_f_btn_6_label, LV_PCT(100));

    //Write style for scr_main_f_btn_6, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_6, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_6, lv_color_hex(0x0023F5), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_6, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_f_btn_6, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_f_btn_6, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_6, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_f_btn_6, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_f_btn_6, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_6, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_f_btn_6, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_f_btn_6, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_6, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_6, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_6, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_border_width(ui->scr_main_f_btn_6, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_radius(ui->scr_main_f_btn_6, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_6, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_main_f_btn_6, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_main_f_btn_6, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_6, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    //Write codes scr_main_f_btn_7
    ui->scr_main_f_btn_7 = lv_button_create(ui->scr_main_f_cont);
    lv_obj_set_pos(ui->scr_main_f_btn_7, 189, 56);
    lv_obj_set_size(ui->scr_main_f_btn_7, 92, 54);
    lv_obj_add_flag(ui->scr_main_f_btn_7, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_f_btn_7_label = lv_label_create(ui->scr_main_f_btn_7);
    if (sec_F_buton[6] <= 0) 
      lv_label_set_text(ui->scr_main_f_btn_7_label, "F7");
    else
      lv_label_set_text(ui->scr_main_f_btn_7_label, urun_labels[sec_F_buton[6]]);
    lv_label_set_long_mode(ui->scr_main_f_btn_7_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_f_btn_7_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_f_btn_7, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_f_btn_7_label, LV_PCT(100));

    //Write style for scr_main_f_btn_7, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_7, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_7, lv_color_hex(0x0023F5), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_7, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_f_btn_7, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_f_btn_7, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_7, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_f_btn_7, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_f_btn_7, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_7, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_f_btn_7, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_f_btn_7, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_7, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_7, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_7, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_border_width(ui->scr_main_f_btn_7, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_radius(ui->scr_main_f_btn_7, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_7, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_main_f_btn_7, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_main_f_btn_7, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_7, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    //Write codes scr_main_f_btn_8
    /*ui->scr_main_f_btn_8 = lv_button_create(ui->scr_main_f_cont);
    lv_obj_set_pos(ui->scr_main_f_btn_8, 283, 56);
    lv_obj_set_size(ui->scr_main_f_btn_8, 92, 54);
    lv_obj_add_flag(ui->scr_main_f_btn_8, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_f_btn_8_label = lv_label_create(ui->scr_main_f_btn_8);
    if (sec_F_buton[7] <= 0) 
      lv_label_set_text(ui->scr_main_f_btn_8_label, "F8");
    else
      lv_label_set_text(ui->scr_main_f_btn_8_label, urun_labels[sec_F_buton[7]]);
    lv_label_set_long_mode(ui->scr_main_f_btn_8_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_f_btn_8_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_f_btn_8, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_f_btn_8_label, LV_PCT(100));

    //Write style for scr_main_f_btn_8, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_8, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_8, lv_color_hex(0x0023F5), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_8, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_f_btn_8, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_f_btn_8, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_8, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_f_btn_8, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_f_btn_8, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_8, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_f_btn_8, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_f_btn_8, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_8, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_8, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_8, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_border_width(ui->scr_main_f_btn_8, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_radius(ui->scr_main_f_btn_8, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_8, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_main_f_btn_8, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_main_f_btn_8, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_8, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));*/

    ui->scr_main_daraekle_btn = lv_button_create(ui->scr_main_f_cont);
    lv_obj_set_pos(ui->scr_main_daraekle_btn, 283, 0);
    lv_obj_set_size(ui->scr_main_daraekle_btn, 92, 54);
    lv_obj_add_flag(ui->scr_main_daraekle_btn, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_daraekle_btn_label = lv_label_create(ui->scr_main_daraekle_btn);
    if (eyz_dara_degeri == 0)
      lv_label_set_text(ui->scr_main_daraekle_btn_label, "DARA AL");
    else
      lv_label_set_text(ui->scr_main_daraekle_btn_label, "DARA EKLE");
    lv_label_set_long_mode(ui->scr_main_daraekle_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_daraekle_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_daraekle_btn, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_daraekle_btn_label, LV_PCT(100));

    //Write style for scr_main_daraekle_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_main_daraekle_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_main_daraekle_btn, lv_color_hex(0x732BF5), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_daraekle_btn, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_daraekle_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_daraekle_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_daraekle_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_daraekle_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_daraekle_btn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_daraekle_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_daraekle_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_daraekle_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_bg_opa(ui->scr_main_daraekle_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_color(ui->scr_main_daraekle_btn, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_daraekle_btn, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_border_width(ui->scr_main_daraekle_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_radius(ui->scr_main_daraekle_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_main_daraekle_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_main_daraekle_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_main_daraekle_btn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_main_daraekle_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    ui->scr_main_darasil_btn = lv_button_create(ui->scr_main_f_cont);
    lv_obj_set_pos(ui->scr_main_darasil_btn, 283, 56);
    lv_obj_set_size(ui->scr_main_darasil_btn, 92, 54);
    lv_obj_add_flag(ui->scr_main_darasil_btn, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_darasil_btn_label = lv_label_create(ui->scr_main_darasil_btn);
    lv_label_set_text(ui->scr_main_darasil_btn_label, "DARA SİL");
    lv_label_set_long_mode(ui->scr_main_darasil_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_darasil_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_darasil_btn, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_darasil_btn_label, LV_PCT(100));

    //Write style for scr_main_darasil_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_main_darasil_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_main_darasil_btn, lv_color_hex(0x3A083E), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_darasil_btn, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_darasil_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_darasil_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_darasil_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_darasil_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_darasil_btn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_darasil_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_darasil_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_darasil_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_bg_opa(ui->scr_main_darasil_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_color(ui->scr_main_darasil_btn, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_darasil_btn, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_border_width(ui->scr_main_darasil_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_radius(ui->scr_main_darasil_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_main_darasil_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_main_darasil_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_main_darasil_btn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_main_darasil_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    //Write codes scr_main_bar_cont
    ui->scr_main_bar_cont = lv_obj_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_bar_cont, 0, 0);
    lv_obj_set_size(ui->scr_main_bar_cont, 480, 25);
    lv_obj_set_scrollbar_mode(ui->scr_main_bar_cont, LV_SCROLLBAR_MODE_OFF);

    //Write style for scr_main_bar_cont, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_main_bar_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_bar_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_main_bar_cont, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_main_bar_cont, lv_color_hex(0x0023F5), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_bar_cont, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_main_bar_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_bottom(ui->scr_main_bar_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_main_bar_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_main_bar_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_bar_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_main_tarih_btn
    ui->scr_main_tarih_btn = lv_button_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_tarih_btn, 405, 0);
    lv_obj_set_size(ui->scr_main_tarih_btn, 70, 25);
    ui->scr_main_tarih_btn_label = lv_label_create(ui->scr_main_tarih_btn);
    lv_label_set_text(ui->scr_main_tarih_btn_label, "12-12-2025");
    lv_label_set_long_mode(ui->scr_main_tarih_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_tarih_btn_label, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_tarih_btn, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_tarih_btn_label, LV_PCT(100));

    //Write style for scr_main_tarih_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_main_tarih_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_tarih_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_tarih_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_tarih_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_tarih_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_tarih_btn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_tarih_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_tarih_btn, LV_TEXT_ALIGN_RIGHT, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_main_saat_btn
    ui->scr_main_saat_btn = lv_button_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_saat_btn, 340, 0);
    lv_obj_set_size(ui->scr_main_saat_btn, 55, 25);
    ui->scr_main_saat_btn_label = lv_label_create(ui->scr_main_saat_btn);
    lv_label_set_text(ui->scr_main_saat_btn_label, "12:00:00");
    lv_label_set_long_mode(ui->scr_main_saat_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_saat_btn_label, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_saat_btn, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_saat_btn_label, LV_PCT(100));

    //Write style for scr_main_saat_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_main_saat_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_saat_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_saat_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_saat_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_saat_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_saat_btn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_saat_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_saat_btn, LV_TEXT_ALIGN_RIGHT, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_main_wifi_sta_imgbt
    ui->scr_main_wifi_sta_imgbt = lv_imagebutton_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_wifi_sta_imgbt, 5, 0);
    lv_obj_set_size(ui->scr_main_wifi_sta_imgbt, 25, 25);
    lv_obj_add_flag(ui->scr_main_wifi_sta_imgbt, LV_OBJ_FLAG_CHECKABLE);
    lv_imagebutton_set_src(ui->scr_main_wifi_sta_imgbt, LV_IMAGEBUTTON_STATE_RELEASED, &_wifi_lost_RGB565A8_25x25, NULL, NULL);
    ui->scr_main_wifi_sta_imgbt_label = lv_label_create(ui->scr_main_wifi_sta_imgbt);
    lv_label_set_text(ui->scr_main_wifi_sta_imgbt_label, "");
    lv_label_set_long_mode(ui->scr_main_wifi_sta_imgbt_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_wifi_sta_imgbt_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_wifi_sta_imgbt, 0, static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_wifi_sta_imgbt, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_text_color(ui->scr_main_wifi_sta_imgbt, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_wifi_sta_imgbt, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_wifi_sta_imgbt, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_wifi_sta_imgbt, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_wifi_sta_imgbt, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_wifi_sta_imgbt, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_image_recolor_opa(ui->scr_main_wifi_sta_imgbt, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_image_opa(ui->scr_main_wifi_sta_imgbt, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_main_wifi_sta_imgbt, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_main_wifi_sta_imgbt, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_main_wifi_sta_imgbt, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_main_wifi_sta_imgbt, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    //Write style for scr_main_wifi_sta_imgbt, Part: static_cast<int>(LV_PART_MAIN), State: LV_IMAGEBUTTON_STATE_RELEASED.
    lv_obj_set_style_image_recolor_opa(ui->scr_main_wifi_sta_imgbt, 0, static_cast<int>(LV_PART_MAIN)|LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_style_image_opa(ui->scr_main_wifi_sta_imgbt, 255, static_cast<int>(LV_PART_MAIN)|LV_IMAGEBUTTON_STATE_RELEASED);

    //Write codes scr_main_net_label
    ui->scr_main_net_label = lv_label_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_net_label, 380, 58);
    lv_obj_set_size(ui->scr_main_net_label, 55, 12);
    lv_label_set_text(ui->scr_main_net_label, "NET KG");
    lv_label_set_long_mode(ui->scr_main_net_label, LV_LABEL_LONG_WRAP);

    //Write style for scr_main_net_label, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_main_net_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_net_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_net_label, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_net_label, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_net_label, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_letter_space(ui->scr_main_net_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_line_space(ui->scr_main_net_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_net_label, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_main_net_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_main_net_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_main_net_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_bottom(ui->scr_main_net_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_main_net_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_net_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_main_dara_label
    ui->scr_main_dara_label = lv_label_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_dara_label, 231, 58);
    lv_obj_set_size(ui->scr_main_dara_label, 55, 12);
    lv_label_set_text(ui->scr_main_dara_label, "DARA KG");
    lv_label_set_long_mode(ui->scr_main_dara_label, LV_LABEL_LONG_WRAP);

    //Write style for scr_main_dara_label, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_main_dara_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_dara_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_dara_label, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_dara_label, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_dara_label, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_letter_space(ui->scr_main_dara_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_line_space(ui->scr_main_dara_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_dara_label, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_main_dara_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_main_dara_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_main_dara_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_bottom(ui->scr_main_dara_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_main_dara_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_dara_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_main_birimgr_label
    /*ui->scr_main_birimgr_label = lv_label_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_birimgr_label, 231, 58);
    lv_obj_set_size(ui->scr_main_birimgr_label, 55, 12);
    lv_label_set_text(ui->scr_main_birimgr_label, "BİRİM GR");
    lv_label_set_long_mode(ui->scr_main_birimgr_label, LV_LABEL_LONG_WRAP);

    //Write style for scr_main_birimgr_label, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_main_birimgr_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_birimgr_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_birimgr_label, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_birimgr_label, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_birimgr_label, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_letter_space(ui->scr_main_birimgr_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_line_space(ui->scr_main_birimgr_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_birimgr_label, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_main_birimgr_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_main_birimgr_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_main_birimgr_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_bottom(ui->scr_main_birimgr_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_main_birimgr_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_birimgr_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));*/

    //Write codes scr_main_brut_label
    ui->scr_main_brut_label = lv_label_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_brut_label, 80, 58);
    lv_obj_set_size(ui->scr_main_brut_label, 55, 12);
    lv_label_set_text(ui->scr_main_brut_label, "BRÜT KG");
    lv_label_set_long_mode(ui->scr_main_brut_label, LV_LABEL_LONG_WRAP);

    //Write style for scr_main_brut_label, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_main_brut_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_brut_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_brut_label, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_brut_label, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_brut_label, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_letter_space(ui->scr_main_brut_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_line_space(ui->scr_main_brut_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_brut_label, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_main_brut_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_main_brut_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_main_brut_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_bottom(ui->scr_main_brut_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_main_brut_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_brut_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_main_adet_label
    /*ui->scr_main_adet_label = lv_label_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_adet_label, 80, 58);
    lv_obj_set_size(ui->scr_main_adet_label, 55, 12);
    lv_label_set_text(ui->scr_main_adet_label, "ADET");
    lv_label_set_long_mode(ui->scr_main_adet_label, LV_LABEL_LONG_WRAP);

    //Write style for scr_main_adet_label, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_main_adet_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_adet_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_adet_label, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_adet_label, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_adet_label, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_letter_space(ui->scr_main_adet_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_line_space(ui->scr_main_adet_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_adet_label, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_main_adet_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_main_adet_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_main_adet_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_bottom(ui->scr_main_adet_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_main_adet_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_adet_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));*/

    //Write codes scr_main_yazdir_imgbtn
    ui->scr_main_yazdir_imgbtn = lv_imagebutton_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_yazdir_imgbtn, 380, 217);
    lv_obj_set_size(ui->scr_main_yazdir_imgbtn, 96, 52);
    lv_imagebutton_set_src(ui->scr_main_yazdir_imgbtn, LV_IMAGEBUTTON_STATE_RELEASED, &_printing_RGB565A8_96x52, NULL, NULL);
    lv_imagebutton_set_src(ui->scr_main_yazdir_imgbtn, LV_IMAGEBUTTON_STATE_PRESSED, &_printing_RGB565A8_96x52, NULL, NULL);
    ui->scr_main_yazdir_imgbtn_label = lv_label_create(ui->scr_main_yazdir_imgbtn);
    lv_obj_set_pos(ui->scr_main_yazdir_imgbtn_label, 380, 256);
    lv_obj_set_size(ui->scr_main_yazdir_imgbtn_label, 96, 62);
    lv_obj_set_style_text_color(ui->scr_main_yazdir_imgbtn_label, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_yazdir_imgbtn_label, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_label_set_text(ui->scr_main_yazdir_imgbtn_label, "");
    lv_obj_set_style_pad_top(ui->scr_main_yazdir_imgbtn_label, 4, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    //lv_obj_set_style_bg_color(ui->scr_main_yazdir_imgbtn_label, lv_color_hex(0xFF0000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_label_set_long_mode(ui->scr_main_yazdir_imgbtn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_yazdir_imgbtn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_yazdir_imgbtn, 0, static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_yazdir_imgbtn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_main_yazdir_imgbtn, 2, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_yazdir_imgbtn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_yazdir_imgbtn, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_yazdir_imgbtn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_yazdir_imgbtn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_yazdir_imgbtn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_yazdir_imgbtn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_yazdir_imgbtn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_image_recolor_opa(ui->scr_main_yazdir_imgbtn, 100, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_image_recolor(ui->scr_main_yazdir_imgbtn, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_image_opa(ui->scr_main_yazdir_imgbtn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_main_yazdir_imgbtn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_main_yazdir_imgbtn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_main_yazdir_imgbtn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_main_yazdir_imgbtn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    //Write style for scr_main_yazdir_imgbtn, Part: static_cast<int>(LV_PART_MAIN), State: LV_IMAGEBUTTON_STATE_RELEASED.
    lv_obj_set_style_image_recolor_opa(ui->scr_main_yazdir_imgbtn, 0, static_cast<int>(LV_PART_MAIN)|LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_style_image_opa(ui->scr_main_yazdir_imgbtn, 255, static_cast<int>(LV_PART_MAIN)|LV_IMAGEBUTTON_STATE_RELEASED);

    //Write codes scr_main_topla_imgbtn
    ui->scr_main_topla_imgbtn = lv_imagebutton_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_topla_imgbtn, 380, 161);
    lv_obj_set_size(ui->scr_main_topla_imgbtn, 96, 52);
    lv_imagebutton_set_src(ui->scr_main_topla_imgbtn, LV_IMAGEBUTTON_STATE_RELEASED, &_topla_RGB565A8_96x52, NULL, NULL);
    lv_imagebutton_set_src(ui->scr_main_topla_imgbtn, LV_IMAGEBUTTON_STATE_PRESSED, &_topla_RGB565A8_96x52, NULL, NULL);
    ui->scr_main_topla_imgbtn_label = lv_label_create(ui->scr_main_topla_imgbtn);
    lv_obj_set_pos(ui->scr_main_topla_imgbtn_label, 380, 191);
    lv_obj_set_size(ui->scr_main_topla_imgbtn_label, 96, 62);
    lv_obj_set_style_text_color(ui->scr_main_topla_imgbtn_label, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_topla_imgbtn_label, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    //lv_obj_set_style_bg_color(ui->scr_main_topla_imgbtn_label, lv_color_hex(0xCCCCCC), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_label_set_text(ui->scr_main_topla_imgbtn_label, "");
    lv_obj_set_style_pad_top(ui->scr_main_topla_imgbtn_label, 4, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_label_set_long_mode(ui->scr_main_topla_imgbtn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_topla_imgbtn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_topla_imgbtn, 0, static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_topla_imgbtn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_main_topla_imgbtn, 2, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_topla_imgbtn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_topla_imgbtn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_topla_imgbtn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_topla_imgbtn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_topla_imgbtn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_topla_imgbtn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_main_topla_imgbtn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_image_recolor_opa(ui->scr_main_topla_imgbtn, 100, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_image_recolor(ui->scr_main_topla_imgbtn, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_image_opa(ui->scr_main_topla_imgbtn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_main_topla_imgbtn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_main_topla_imgbtn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_main_topla_imgbtn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_main_topla_imgbtn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    //Write style for scr_main_topla_imgbtn, Part: static_cast<int>(LV_PART_MAIN), State: LV_IMAGEBUTTON_STATE_RELEASED.
    lv_obj_set_style_image_recolor_opa(ui->scr_main_topla_imgbtn, 0, static_cast<int>(LV_PART_MAIN)|LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_style_image_opa(ui->scr_main_topla_imgbtn, 255, static_cast<int>(LV_PART_MAIN)|LV_IMAGEBUTTON_STATE_RELEASED);

    //Write codes scr_main_urun_btn
    ui->scr_main_urun_btn = lv_button_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_urun_btn, 83, 26);
    lv_obj_set_size(ui->scr_main_urun_btn, 314, 32);
    ui->scr_main_urun_btn_label = lv_label_create(ui->scr_main_urun_btn);
    if (sec_URUN_buton <= 0) 
      lv_label_set_text(ui->scr_main_urun_btn_label, "ÜRÜN SEÇİNİZ");
    else {
      char limited_text[29]; // 28 karakter + null terminator
      strncpy(limited_text, urun_labels[sec_URUN_buton], 28);
      limited_text[28] = '\0'; // Sonuna null karakter koy (önemli!)

      lv_label_set_text(ui->scr_main_urun_btn_label, limited_text);
    }
    lv_label_set_long_mode(ui->scr_main_urun_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_urun_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_urun_btn, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_urun_btn_label, LV_PCT(100));

    //Write style for scr_main_urun_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_main_urun_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_main_urun_btn, lv_color_hex(0xff0000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_urun_btn, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_urun_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_urun_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_urun_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_urun_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_urun_btn, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_urun_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_urun_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_main_menu_btn
    ui->scr_main_menu_btn = lv_button_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_menu_btn, 399, 26);
    lv_obj_set_size(ui->scr_main_menu_btn, 80, 32);
    ui->scr_main_menu_btn_label = lv_label_create(ui->scr_main_menu_btn);
    lv_label_set_text(ui->scr_main_menu_btn_label, "MENÜ");
    lv_label_set_long_mode(ui->scr_main_menu_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_menu_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_menu_btn, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_menu_btn_label, LV_PCT(100));

    //Write style for scr_main_menu_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_main_menu_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_main_menu_btn, lv_color_hex(0x0023F5), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_menu_btn, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_menu_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_menu_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_menu_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_menu_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_menu_btn, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_menu_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_menu_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_main_kod_btn
    ui->scr_main_kod_btn = lv_button_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_kod_btn, 1, 26);
    lv_obj_set_size(ui->scr_main_kod_btn, 80, 32);
    ui->scr_main_kod_btn_label = lv_label_create(ui->scr_main_kod_btn);
    if (sec_URUN_buton <= 0) 
      lv_label_set_text(ui->scr_main_kod_btn_label, "KOD NO");
    else
      lv_label_set_text(ui->scr_main_kod_btn_label, urun_kod_labels[sec_URUN_buton]);
    lv_label_set_long_mode(ui->scr_main_kod_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_kod_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_kod_btn, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_kod_btn_label, LV_PCT(100));

    //Write style for scr_main_kod_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_main_kod_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_main_kod_btn, lv_color_hex(0x0023F5), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_main_kod_btn, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_kod_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_kod_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_kod_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_kod_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_kod_btn, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_kod_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_kod_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_main_knet_data_btn
    ui->scr_main_knet_data_btn = lv_button_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_knet_data_btn, 330, 76);
    lv_obj_set_size(ui->scr_main_knet_data_btn, 150, 39);
    ui->scr_main_knet_data_btn_label = lv_label_create(ui->scr_main_knet_data_btn);
    lv_label_set_text(ui->scr_main_knet_data_btn_label, XML_NET_C);
    lv_label_set_long_mode(ui->scr_main_knet_data_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_knet_data_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_knet_data_btn, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_knet_data_btn_label, LV_PCT(100));

    //Write style for scr_main_knet_data_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_main_knet_data_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_knet_data_btn, 2, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_opa(ui->scr_main_knet_data_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_color(ui->scr_main_knet_data_btn, lv_color_hex(0x2195f6), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_side(ui->scr_main_knet_data_btn, LV_BORDER_SIDE_FULL, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_knet_data_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_knet_data_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_knet_data_btn, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_knet_data_btn, &lv_font_Bebas_48, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_knet_data_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_knet_data_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_knet_data_ta
    ui->scr_knet_data_ta = lv_textarea_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_knet_data_ta, 150, 26);
    lv_obj_set_size(ui->scr_knet_data_ta, 290, 88);
    lv_textarea_set_text(ui->scr_knet_data_ta, "");
    lv_textarea_set_placeholder_text(ui->scr_knet_data_ta, "ADET ?");
    lv_textarea_set_password_bullet(ui->scr_knet_data_ta, "*");
    lv_textarea_set_password_mode(ui->scr_knet_data_ta, false);
    lv_textarea_set_one_line(ui->scr_knet_data_ta, true);
    lv_textarea_set_accepted_chars(ui->scr_knet_data_ta, "0123456789");  // Sadece rakam
    lv_textarea_set_max_length(ui->scr_knet_data_ta, 8); // "0.0000" = 7+1 güvenlik
#if LV_USE_KEYBOARD
    // Klavye oluştur ve sadece numerik moda ayarla
    //ui->g_kb_top_layer = lv_keyboard_create(ui->scr_kod);
    lv_keyboard_set_mode(ui->g_kb_top_layer, LV_KEYBOARD_MODE_NUMBER);
    // Textarea'ya odaklandığında klavyeyi aç
    lv_obj_add_event_cb(ui->scr_knet_data_ta, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);    
    //lv_obj_add_event_cb(ui->scr_knet_data_ta, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
    lv_obj_set_size(ui->g_kb_top_layer, 375, 157); // Özel genişlik ve yükseklik ayarla
    lv_obj_align(ui->g_kb_top_layer, LV_ALIGN_BOTTOM_LEFT, 0, 0); // Alt orta hizala
    lv_keyboard_set_textarea(ui->g_kb_top_layer, ui->scr_knet_data_ta);
#endif

    //Write style for scr_knet_data_ta, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->scr_knet_data_ta, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_knet_data_ta, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_knet_data_ta, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scr_knet_data_ta, 0,static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_knet_data_ta, LV_TEXT_ALIGN_RIGHT, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_knet_data_ta, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_knet_data_ta, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_knet_data_ta, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_knet_data_ta, 2, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scr_knet_data_ta, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scr_knet_data_ta, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scr_knet_data_ta, LV_BORDER_SIDE_FULL, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_knet_data_ta, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scr_knet_data_ta, 9, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_knet_data_ta, 4, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_knet_data_ta, 4, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_knet_data_ta, 4, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);

    //Write style for scr_knet_data_ta, Part: static_cast<int>(LV_PART_SCROLLBAR), State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_knet_data_ta, 255, static_cast<int>(LV_PART_SCROLLBAR)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_knet_data_ta, lv_color_hex(0x2195f6), static_cast<int>(LV_PART_SCROLLBAR)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_knet_data_ta, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_SCROLLBAR)|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_knet_data_ta, 0, static_cast<int>(LV_PART_SCROLLBAR)|LV_STATE_DEFAULT);

    

    //Write codes scr_main_dara_data_btn
    ui->scr_main_dara_data_btn = lv_button_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_dara_data_btn, 180, 76);
    lv_obj_set_size(ui->scr_main_dara_data_btn, 150, 39);
    ui->scr_main_dara_data_btn_label = lv_label_create(ui->scr_main_dara_data_btn);
    lv_label_set_text(ui->scr_main_dara_data_btn_label, XML_DARA_C);
    lv_label_set_long_mode(ui->scr_main_dara_data_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_dara_data_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_dara_data_btn, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_dara_data_btn_label, LV_PCT(100));

    //Write style for scr_main_dara_data_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_main_dara_data_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_dara_data_btn, 2, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_opa(ui->scr_main_dara_data_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_color(ui->scr_main_dara_data_btn, lv_color_hex(0x2195f6), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_side(ui->scr_main_dara_data_btn, LV_BORDER_SIDE_FULL, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_dara_data_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_dara_data_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_dara_data_btn, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_dara_data_btn, &lv_font_Bebas_48, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_dara_data_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_dara_data_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_dara_data_ta
    ui->scr_dara_data_ta = lv_textarea_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_dara_data_ta, 180, 76);
    lv_obj_set_size(ui->scr_dara_data_ta, 150, 37);
    lv_textarea_set_text(ui->scr_dara_data_ta, "");
    lv_textarea_set_placeholder_text(ui->scr_dara_data_ta, "DARA ?");
    lv_textarea_set_password_bullet(ui->scr_dara_data_ta, "*");
    lv_textarea_set_password_mode(ui->scr_dara_data_ta, false);
    lv_textarea_set_one_line(ui->scr_dara_data_ta, true);
    lv_textarea_set_accepted_chars(ui->scr_dara_data_ta, ".0123456789");  // Sadece rakam
    lv_textarea_set_max_length(ui->scr_dara_data_ta, 8); // "0.0000" = 7+1 güvenlik
#if LV_USE_KEYBOARD
    // Klavye oluştur ve sadece numerik moda ayarla
    //ui->g_kb_top_layer = lv_keyboard_create(ui->scr_kod);
    lv_keyboard_set_mode(ui->g_kb_top_layer, LV_KEYBOARD_MODE_NUMBER);
    // Textarea'ya odaklandığında klavyeyi aç
    lv_obj_add_event_cb(ui->scr_dara_data_ta, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);    
    //lv_obj_add_event_cb(ui->scr_dara_data_ta, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
    lv_obj_set_size(ui->g_kb_top_layer, 375, 157); // Özel genişlik ve yükseklik ayarla
    lv_obj_align(ui->g_kb_top_layer, LV_ALIGN_BOTTOM_LEFT, 0, 0); // Alt orta hizala
    lv_keyboard_set_textarea(ui->g_kb_top_layer, ui->scr_dara_data_ta);
#endif

    //Write style for scr_dara_data_ta, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->scr_dara_data_ta, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_dara_data_ta, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_dara_data_ta, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scr_dara_data_ta, 0,static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_dara_data_ta, LV_TEXT_ALIGN_RIGHT, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_dara_data_ta, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_dara_data_ta, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_dara_data_ta, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_dara_data_ta, 2, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scr_dara_data_ta, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scr_dara_data_ta, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scr_dara_data_ta, LV_BORDER_SIDE_FULL, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_dara_data_ta, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scr_dara_data_ta, 9, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_dara_data_ta, 4, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_dara_data_ta, 4, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_dara_data_ta, 4, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);

    //Write style for scr_dara_data_ta, Part: static_cast<int>(LV_PART_SCROLLBAR), State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_dara_data_ta, 255, static_cast<int>(LV_PART_SCROLLBAR)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_dara_data_ta, lv_color_hex(0x2195f6), static_cast<int>(LV_PART_SCROLLBAR)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_dara_data_ta, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_SCROLLBAR)|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_dara_data_ta, 0, static_cast<int>(LV_PART_SCROLLBAR)|LV_STATE_DEFAULT);

    //Write codes scr_main_birimgr_data_btn
    /*ui->scr_main_birimgr_data_btn = lv_button_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_birimgr_data_btn, 180, 76);
    lv_obj_set_size(ui->scr_main_birimgr_data_btn, 150, 39);
    ui->scr_main_birimgr_data_btn_label = lv_label_create(ui->scr_main_birimgr_data_btn);
    lv_label_set_text(ui->scr_main_birimgr_data_btn_label, XML_ADET_GRAMAJ_C);
    lv_label_set_long_mode(ui->scr_main_birimgr_data_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_birimgr_data_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_birimgr_data_btn, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_birimgr_data_btn_label, LV_PCT(100));

    //Write style for scr_main_birimgr_data_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_main_birimgr_data_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_birimgr_data_btn, 2, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_opa(ui->scr_main_birimgr_data_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_color(ui->scr_main_birimgr_data_btn, lv_color_hex(0x2195f6), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_side(ui->scr_main_birimgr_data_btn, LV_BORDER_SIDE_FULL, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_birimgr_data_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_birimgr_data_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_birimgr_data_btn, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_birimgr_data_btn, &lv_font_Bebas_48, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_birimgr_data_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_birimgr_data_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_birimgr_data_ta
    ui->scr_birimgr_data_ta = lv_textarea_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_birimgr_data_ta, 180, 76);
    lv_obj_set_size(ui->scr_birimgr_data_ta, 150, 37);
    lv_textarea_set_text(ui->scr_birimgr_data_ta, "");
    lv_textarea_set_placeholder_text(ui->scr_birimgr_data_ta, "BİRİM GR ?");
    lv_textarea_set_password_bullet(ui->scr_birimgr_data_ta, "*");
    lv_textarea_set_password_mode(ui->scr_birimgr_data_ta, false);
    lv_textarea_set_one_line(ui->scr_birimgr_data_ta, true);
    lv_textarea_set_accepted_chars(ui->scr_birimgr_data_ta, ".0123456789");  // Sadece rakam
    lv_textarea_set_max_length(ui->scr_birimgr_data_ta, 8); // "0.0000" = 7+1 güvenlik
#if LV_USE_KEYBOARD
    // Klavye oluştur ve sadece numerik moda ayarla
    //ui->g_kb_top_layer = lv_keyboard_create(ui->scr_kod);
    lv_keyboard_set_mode(ui->g_kb_top_layer, LV_KEYBOARD_MODE_NUMBER);
    // Textarea'ya odaklandığında klavyeyi aç
    lv_obj_add_event_cb(ui->scr_birimgr_data_ta, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);    
    //lv_obj_add_event_cb(ui->scr_birimgr_data_ta, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
    lv_obj_set_size(ui->g_kb_top_layer, 375, 157); // Özel genişlik ve yükseklik ayarla
    lv_obj_align(ui->g_kb_top_layer, LV_ALIGN_BOTTOM_LEFT, 0, 0); // Alt orta hizala
    lv_keyboard_set_textarea(ui->g_kb_top_layer, ui->scr_birimgr_data_ta);
#endif

    //Write style for scr_birimgr_data_ta, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->scr_birimgr_data_ta, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_birimgr_data_ta, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_birimgr_data_ta, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scr_birimgr_data_ta, 0,static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_birimgr_data_ta, LV_TEXT_ALIGN_RIGHT, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_birimgr_data_ta, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_birimgr_data_ta, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_birimgr_data_ta, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_birimgr_data_ta, 2, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scr_birimgr_data_ta, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scr_birimgr_data_ta, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scr_birimgr_data_ta, LV_BORDER_SIDE_FULL, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_birimgr_data_ta, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scr_birimgr_data_ta, 9, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_birimgr_data_ta, 4, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_birimgr_data_ta, 4, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_birimgr_data_ta, 4, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);

    //Write style for scr_birimgr_data_ta, Part: static_cast<int>(LV_PART_SCROLLBAR), State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_birimgr_data_ta, 255, static_cast<int>(LV_PART_SCROLLBAR)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_birimgr_data_ta, lv_color_hex(0x2195f6), static_cast<int>(LV_PART_SCROLLBAR)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_birimgr_data_ta, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_SCROLLBAR)|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_birimgr_data_ta, 0, static_cast<int>(LV_PART_SCROLLBAR)|LV_STATE_DEFAULT);*/

    //Write codes scr_main_brut_data_btn
    ui->scr_main_brut_data_btn = lv_button_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_brut_data_btn, 30, 76);
    lv_obj_set_size(ui->scr_main_brut_data_btn, 150, 39);
    ui->scr_main_brut_data_btn_label = lv_label_create(ui->scr_main_brut_data_btn);
    lv_label_set_text(ui->scr_main_brut_data_btn_label, XML_BRUT_C);
    lv_label_set_long_mode(ui->scr_main_brut_data_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_brut_data_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_brut_data_btn, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_brut_data_btn_label, LV_PCT(100));

    //Write style for scr_main_brut_data_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_main_brut_data_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_brut_data_btn, 2, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_opa(ui->scr_main_brut_data_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_color(ui->scr_main_brut_data_btn, lv_color_hex(0x2195f6), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_side(ui->scr_main_brut_data_btn, LV_BORDER_SIDE_FULL, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_brut_data_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_brut_data_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_brut_data_btn, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_brut_data_btn, &lv_font_Bebas_48, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_brut_data_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_brut_data_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));


    //Write codes scr_main_adet_data_btn
    /*ui->scr_main_adet_data_btn = lv_button_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_adet_data_btn, 30, 76);
    lv_obj_set_size(ui->scr_main_adet_data_btn, 150, 39);
    ui->scr_main_adet_data_btn_label = lv_label_create(ui->scr_main_adet_data_btn);
    lv_label_set_text(ui->scr_main_adet_data_btn_label, XML_ADET_C);
    lv_label_set_long_mode(ui->scr_main_adet_data_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_adet_data_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_adet_data_btn, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_main_adet_data_btn_label, LV_PCT(100));

    //Write style for scr_main_adet_data_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_main_adet_data_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_main_adet_data_btn, 2, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_opa(ui->scr_main_adet_data_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_color(ui->scr_main_adet_data_btn, lv_color_hex(0x2195f6), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_side(ui->scr_main_adet_data_btn, LV_BORDER_SIDE_FULL, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_adet_data_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_adet_data_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_adet_data_btn, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_adet_data_btn, &lv_font_Bebas_48, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_adet_data_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_adet_data_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_adet_data_ta
    ui->scr_adet_data_ta = lv_textarea_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_adet_data_ta, 30, 76);
    lv_obj_set_size(ui->scr_adet_data_ta, 150, 37);
    lv_textarea_set_text(ui->scr_adet_data_ta, "");
    lv_textarea_set_placeholder_text(ui->scr_adet_data_ta, "ADET ?");
    lv_textarea_set_password_bullet(ui->scr_adet_data_ta, "*");
    lv_textarea_set_password_mode(ui->scr_adet_data_ta, false);
    lv_textarea_set_one_line(ui->scr_adet_data_ta, true);
    lv_textarea_set_accepted_chars(ui->scr_adet_data_ta, "0123456789");  // Sadece rakam
    lv_textarea_set_max_length(ui->scr_adet_data_ta, 8); // "0.0000" = 7+1 güvenlik
#if LV_USE_KEYBOARD
    // Klavye oluştur ve sadece numerik moda ayarla
    //ui->g_kb_top_layer = lv_keyboard_create(ui->scr_kod);
    lv_keyboard_set_mode(ui->g_kb_top_layer, LV_KEYBOARD_MODE_NUMBER);
    // Textarea'ya odaklandığında klavyeyi aç
    lv_obj_add_event_cb(ui->scr_adet_data_ta, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);    
    //lv_obj_add_event_cb(ui->scr_adet_data_ta, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
    lv_obj_set_size(ui->g_kb_top_layer, 375, 157); // Özel genişlik ve yükseklik ayarla
    lv_obj_align(ui->g_kb_top_layer, LV_ALIGN_BOTTOM_LEFT, 0, 0); // Alt orta hizala
    lv_keyboard_set_textarea(ui->g_kb_top_layer, ui->scr_adet_data_ta);
#endif

    //Write style for scr_adet_data_ta, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->scr_adet_data_ta, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_adet_data_ta, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_adet_data_ta, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scr_adet_data_ta, 0,static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_adet_data_ta, LV_TEXT_ALIGN_RIGHT, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_adet_data_ta, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_adet_data_ta, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_adet_data_ta, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_adet_data_ta, 2, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scr_adet_data_ta, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scr_adet_data_ta, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scr_adet_data_ta, LV_BORDER_SIDE_FULL, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_adet_data_ta, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scr_adet_data_ta, 9, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_adet_data_ta, 4, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_adet_data_ta, 4, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_adet_data_ta, 4, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);

    //Write style for scr_adet_data_ta, Part: static_cast<int>(LV_PART_SCROLLBAR), State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_adet_data_ta, 255, static_cast<int>(LV_PART_SCROLLBAR)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_adet_data_ta, lv_color_hex(0x2195f6), static_cast<int>(LV_PART_SCROLLBAR)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_adet_data_ta, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_SCROLLBAR)|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_adet_data_ta, 0, static_cast<int>(LV_PART_SCROLLBAR)|LV_STATE_DEFAULT);*/

    //Write codes scr_main_kg_label
    ui->scr_main_kg_label = lv_label_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_kg_label, 427, 60);
    lv_obj_set_size(ui->scr_main_kg_label, 50, 51);
    lv_label_set_text(ui->scr_main_kg_label, "kg");
    lv_label_set_long_mode(ui->scr_main_kg_label, LV_LABEL_LONG_WRAP);

    //Write style for scr_main_kg_label, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_main_kg_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_kg_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_kg_label, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_kg_label, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_kg_label, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_letter_space(ui->scr_main_kg_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_line_space(ui->scr_main_kg_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_kg_label, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_main_kg_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_main_kg_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_main_kg_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_bottom(ui->scr_main_kg_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_main_kg_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_kg_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_main_sol_label
    ui->scr_main_sol_label = lv_label_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_sol_label, 5, 124);
    lv_obj_set_size(ui->scr_main_sol_label, 25, 25);
    lv_label_set_text(ui->scr_main_sol_label, "" LV_SYMBOL_LEFT " ");
    lv_label_set_long_mode(ui->scr_main_sol_label, LV_LABEL_LONG_WRAP);

    //Write style for scr_main_sol_label, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_main_sol_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_sol_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_sol_label, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_sol_label, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_sol_label, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_letter_space(ui->scr_main_sol_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_line_space(ui->scr_main_sol_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_sol_label, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_main_sol_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_main_sol_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_main_sol_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_bottom(ui->scr_main_sol_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_main_sol_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_sol_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_main_sag_label
    ui->scr_main_sag_label = lv_label_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_sag_label, 454, 125);
    lv_obj_set_size(ui->scr_main_sag_label, 25, 26);
    lv_label_set_text(ui->scr_main_sag_label, "" LV_SYMBOL_RIGHT " ");
    lv_label_set_long_mode(ui->scr_main_sag_label, LV_LABEL_LONG_WRAP);

    //Write style for scr_main_sag_label, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_main_sag_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_main_sag_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_main_sag_label, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_main_sag_label, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_main_sag_label, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_letter_space(ui->scr_main_sag_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_line_space(ui->scr_main_sag_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_main_sag_label, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_main_sag_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_main_sag_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_main_sag_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_bottom(ui->scr_main_sag_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_main_sag_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_main_sag_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    src_main_net_label();
    
    //The custom code of scr_main.


    //Update current screen layout.
    lv_obj_update_layout(ui->scr_main);

    //Init events for screen.
    events_init_scr_main(ui);
}