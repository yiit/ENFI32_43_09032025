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



void setup_scr_scr_fis(lv_ui *ui)
{
    //Write codes scr_fis
    ui->scr_fis = lv_obj_create(NULL);
    lv_obj_set_size(ui->scr_fis, 480, 272);
    lv_obj_set_scrollbar_mode(ui->scr_fis, LV_SCROLLBAR_MODE_OFF);

    //Write style for scr_fis, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_fis, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_fis, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_fis, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_fis_geri_btn
    ui->scr_fis_geri_btn = lv_button_create(ui->scr_fis);
    lv_obj_set_pos(ui->scr_fis_geri_btn, 380, 215);
    lv_obj_set_size(ui->scr_fis_geri_btn, 96, 52);
    ui->scr_fis_geri_btn_label = lv_label_create(ui->scr_fis_geri_btn);
    lv_label_set_text(ui->scr_fis_geri_btn_label, "");
    lv_label_set_long_mode(ui->scr_fis_geri_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_fis_geri_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_fis_geri_btn, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_fis_geri_btn_label, LV_PCT(100));

    //Write style for scr_fis_geri_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_fis_geri_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_fis_geri_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_fis_geri_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_fis_geri_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_src(ui->scr_fis_geri_btn, &_geri_RGB565A8_96x52, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_opa(ui->scr_fis_geri_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_recolor_opa(ui->scr_fis_geri_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_fis_geri_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_fis_geri_btn, &lv_font_Oswald_Reg_12, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_fis_geri_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_fis_geri_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_fis_geri_btn, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_fis_geri_btn, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_fis_geri_btn, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_fis_geri_btn, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_fis_geri_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_fis_geri_btn, 5, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_fis_geri_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_fis_geri_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_fis_geri_btn, &lv_font_Oswald_Reg_12, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_fis_geri_btn, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);

    //Write codes scr_fis_duzenle_btn
    ui->scr_fis_duzenle_btn = lv_button_create(ui->scr_fis);
    lv_obj_set_pos(ui->scr_fis_duzenle_btn, 380, 151);
    lv_obj_set_size(ui->scr_fis_duzenle_btn, 96, 52);
    ui->scr_fis_duzenle_btn_label = lv_label_create(ui->scr_fis_duzenle_btn);
    lv_label_set_text(ui->scr_fis_duzenle_btn_label, "");
    lv_label_set_long_mode(ui->scr_fis_duzenle_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_fis_duzenle_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_fis_duzenle_btn, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_fis_duzenle_btn_label, LV_PCT(100));

    //Write style for scr_fis_duzenle_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_text_color(ui->scr_fis_duzenle_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_fis_duzenle_btn, &lv_font_Oswald_Reg_12, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_fis_duzenle_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_fis_duzenle_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_fis_duzenle_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_fis_duzenle_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_fis_duzenle_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_fis_duzenle_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_src(ui->scr_fis_duzenle_btn, &_duzenle_RGB565A8_96x52, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_opa(ui->scr_fis_duzenle_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_recolor_opa(ui->scr_fis_duzenle_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_fis_duzenle_btn, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_fis_duzenle_btn, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_fis_duzenle_btn, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_fis_duzenle_btn, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_fis_duzenle_btn, 5, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_fis_duzenle_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_fis_duzenle_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_fis_duzenle_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_fis_duzenle_btn, &lv_font_Oswald_Reg_12, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_fis_duzenle_btn, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);

    //Write codes scr_fis_sec_btn
    ui->scr_fis_sec_btn = lv_button_create(ui->scr_fis);
    lv_obj_set_pos(ui->scr_fis_sec_btn, 380, 90);
    lv_obj_set_size(ui->scr_fis_sec_btn, 96, 52);
    ui->scr_fis_sec_btn_label = lv_label_create(ui->scr_fis_sec_btn);
    lv_label_set_text(ui->scr_fis_sec_btn_label, "");
    lv_label_set_long_mode(ui->scr_fis_sec_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_fis_sec_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_fis_sec_btn, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_fis_sec_btn_label, LV_PCT(100));

    //Write style for scr_fis_sec_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_fis_sec_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_fis_sec_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_fis_sec_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_fis_sec_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_src(ui->scr_fis_sec_btn, &_sec_RGB565A8_96x52, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_opa(ui->scr_fis_sec_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_recolor_opa(ui->scr_fis_sec_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_fis_sec_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_fis_sec_btn, &lv_font_Oswald_Reg_12, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_fis_sec_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_fis_sec_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_fis_sec_btn, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_fis_sec_btn, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_fis_sec_btn, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_fis_sec_btn, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_fis_sec_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_fis_sec_btn, 5, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_fis_sec_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_fis_sec_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_fis_sec_btn, &lv_font_Oswald_Reg_12, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_fis_sec_btn, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);

    //Write codes scr_fis_kaydet_btn
    ui->scr_fis_kaydet_btn = lv_button_create(ui->scr_fis);
    lv_obj_set_pos(ui->scr_fis_kaydet_btn, 380, 28);
    lv_obj_set_size(ui->scr_fis_kaydet_btn, 96, 52);
    ui->scr_fis_kaydet_btn_label = lv_label_create(ui->scr_fis_kaydet_btn);
    lv_label_set_text(ui->scr_fis_kaydet_btn_label, "");
    lv_label_set_long_mode(ui->scr_fis_kaydet_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_fis_kaydet_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_fis_kaydet_btn, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_fis_kaydet_btn_label, LV_PCT(100));

    //Write style for scr_fis_kaydet_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_fis_kaydet_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_fis_kaydet_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_fis_kaydet_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_fis_kaydet_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_src(ui->scr_fis_kaydet_btn, &_saved_RGB565A8_96x52, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_opa(ui->scr_fis_kaydet_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_recolor_opa(ui->scr_fis_kaydet_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_fis_kaydet_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_fis_kaydet_btn, &lv_font_Oswald_Reg_12, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_fis_kaydet_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_fis_kaydet_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_fis_kaydet_btn, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_fis_kaydet_btn, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_fis_kaydet_btn, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_fis_kaydet_btn, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_fis_kaydet_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_fis_kaydet_btn, 5, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_fis_kaydet_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_fis_kaydet_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_fis_kaydet_btn, &lv_font_Oswald_Reg_12, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_fis_kaydet_btn, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);

    //Write codes scr_fis_ta_5
    ui->scr_fis_ta_5 = lv_textarea_create(ui->scr_fis);
    lv_obj_set_pos(ui->scr_fis_ta_5, 0, 191);
    lv_obj_set_size(ui->scr_fis_ta_5, 370, 39);
    lv_textarea_set_text(ui->scr_fis_ta_5, "");
    lv_textarea_set_placeholder_text(ui->scr_fis_ta_5, "FİŞ BAŞLIĞI 5");
    lv_textarea_set_password_bullet(ui->scr_fis_ta_5, "*");
    lv_textarea_set_password_mode(ui->scr_fis_ta_5, false);
    lv_textarea_set_one_line(ui->scr_fis_ta_5, true);
    lv_textarea_set_accepted_chars(ui->scr_fis_ta_5, "");
    lv_textarea_set_max_length(ui->scr_fis_ta_5, 60);
#if LV_USE_KEYBOARD
    lv_obj_add_event_cb(ui->scr_fis_ta_5, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif

    //Write style for scr_fis_ta_5, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_text_color(ui->scr_fis_ta_5, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_fis_ta_5, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_fis_ta_5, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_letter_space(ui->scr_fis_ta_5, 1, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_fis_ta_5, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_fis_ta_5, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_fis_ta_5, 2, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_opa(ui->scr_fis_ta_5, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_color(ui->scr_fis_ta_5, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_side(ui->scr_fis_ta_5, LV_BORDER_SIDE_FULL, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_fis_ta_5, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_fis_ta_5, 11, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_fis_ta_5, 4, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_fis_ta_5, 4, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_fis_ta_5, 4, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_fis_ta_5, Part: LV_PART_SCROLLBAR, State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_fis_ta_5, 255, LV_PART_SCROLLBAR|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_fis_ta_5, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_fis_ta_5, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_fis_ta_5, 0, LV_PART_SCROLLBAR|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_fis_ta_4
    ui->scr_fis_ta_4 = lv_textarea_create(ui->scr_fis);
    lv_obj_set_pos(ui->scr_fis_ta_4, 0, 150);
    lv_obj_set_size(ui->scr_fis_ta_4, 370, 39);
    lv_textarea_set_text(ui->scr_fis_ta_4, "");
    lv_textarea_set_placeholder_text(ui->scr_fis_ta_4, "FİŞ BAŞLIĞI 4");
    lv_textarea_set_password_bullet(ui->scr_fis_ta_4, "*");
    lv_textarea_set_password_mode(ui->scr_fis_ta_4, false);
    lv_textarea_set_one_line(ui->scr_fis_ta_4, true);
    lv_textarea_set_accepted_chars(ui->scr_fis_ta_4, "");
    lv_textarea_set_max_length(ui->scr_fis_ta_4, 60);
#if LV_USE_KEYBOARD
    lv_obj_add_event_cb(ui->scr_fis_ta_4, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif

    //Write style for scr_fis_ta_4, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_text_color(ui->scr_fis_ta_4, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_fis_ta_4, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_fis_ta_4, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_letter_space(ui->scr_fis_ta_4, 1, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_fis_ta_4, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_fis_ta_4, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_fis_ta_4, 2, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_opa(ui->scr_fis_ta_4, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_color(ui->scr_fis_ta_4, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_side(ui->scr_fis_ta_4, LV_BORDER_SIDE_FULL, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_fis_ta_4, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_fis_ta_4, 11, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_fis_ta_4, 4, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_fis_ta_4, 4, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_fis_ta_4, 4, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_fis_ta_4, Part: LV_PART_SCROLLBAR, State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_fis_ta_4, 255, LV_PART_SCROLLBAR|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_fis_ta_4, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_fis_ta_4, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_fis_ta_4, 0, LV_PART_SCROLLBAR|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_fis_ta_3
    ui->scr_fis_ta_3 = lv_textarea_create(ui->scr_fis);
    lv_obj_set_pos(ui->scr_fis_ta_3, 0, 109);
    lv_obj_set_size(ui->scr_fis_ta_3, 370, 39);
    lv_textarea_set_text(ui->scr_fis_ta_3, "");
    lv_textarea_set_placeholder_text(ui->scr_fis_ta_3, "FİŞ BAŞLIĞI 3");
    lv_textarea_set_password_bullet(ui->scr_fis_ta_3, "*");
    lv_textarea_set_password_mode(ui->scr_fis_ta_3, false);
    lv_textarea_set_one_line(ui->scr_fis_ta_3, true);
    lv_textarea_set_accepted_chars(ui->scr_fis_ta_3, "");
    lv_textarea_set_max_length(ui->scr_fis_ta_3, 60);
#if LV_USE_KEYBOARD
    lv_obj_add_event_cb(ui->scr_fis_ta_3, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif

    //Write style for scr_fis_ta_3, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_text_color(ui->scr_fis_ta_3, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_fis_ta_3, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_fis_ta_3, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_letter_space(ui->scr_fis_ta_3, 1, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_fis_ta_3, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_fis_ta_3, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_fis_ta_3, 2, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_opa(ui->scr_fis_ta_3, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_color(ui->scr_fis_ta_3, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_side(ui->scr_fis_ta_3, LV_BORDER_SIDE_FULL, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_fis_ta_3, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_fis_ta_3, 11, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_fis_ta_3, 4, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_fis_ta_3, 4, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_fis_ta_3, 4, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_fis_ta_3, Part: LV_PART_SCROLLBAR, State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_fis_ta_3, 255, LV_PART_SCROLLBAR|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_fis_ta_3, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_fis_ta_3, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_fis_ta_3, 0, LV_PART_SCROLLBAR|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_fis_ta_2
    ui->scr_fis_ta_2 = lv_textarea_create(ui->scr_fis);
    lv_obj_set_pos(ui->scr_fis_ta_2, 0, 68);
    lv_obj_set_size(ui->scr_fis_ta_2, 370, 39);
    lv_textarea_set_text(ui->scr_fis_ta_2, "");
    lv_textarea_set_placeholder_text(ui->scr_fis_ta_2, "FİŞ BAŞLIĞI 2");
    lv_textarea_set_password_bullet(ui->scr_fis_ta_2, "*");
    lv_textarea_set_password_mode(ui->scr_fis_ta_2, false);
    lv_textarea_set_one_line(ui->scr_fis_ta_2, true);
    lv_textarea_set_accepted_chars(ui->scr_fis_ta_2, "");
    lv_textarea_set_max_length(ui->scr_fis_ta_2, 60);
#if LV_USE_KEYBOARD
    lv_obj_add_event_cb(ui->scr_fis_ta_2, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif

    //Write style for scr_fis_ta_2, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_text_color(ui->scr_fis_ta_2, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_fis_ta_2, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_fis_ta_2, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_letter_space(ui->scr_fis_ta_2, 1, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_fis_ta_2, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_fis_ta_2, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_fis_ta_2, 2, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_opa(ui->scr_fis_ta_2, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_color(ui->scr_fis_ta_2, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_side(ui->scr_fis_ta_2, LV_BORDER_SIDE_FULL, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_fis_ta_2, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_fis_ta_2, 11, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_fis_ta_2, 4, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_fis_ta_2, 4, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_fis_ta_2, 4, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_fis_ta_2, Part: LV_PART_SCROLLBAR, State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_fis_ta_2, 255, LV_PART_SCROLLBAR|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_fis_ta_2, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_fis_ta_2, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_fis_ta_2, 0, LV_PART_SCROLLBAR|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_fis_ta_1
    ui->scr_fis_ta_1 = lv_textarea_create(ui->scr_fis);
    lv_obj_set_pos(ui->scr_fis_ta_1, 0, 27);
    lv_obj_set_size(ui->scr_fis_ta_1, 370, 39);
    lv_textarea_set_text(ui->scr_fis_ta_1, "");
    lv_textarea_set_placeholder_text(ui->scr_fis_ta_1, "FİŞ BAŞLIĞI 1");
    lv_textarea_set_password_bullet(ui->scr_fis_ta_1, "*");
    lv_textarea_set_password_mode(ui->scr_fis_ta_1, false);
    lv_textarea_set_one_line(ui->scr_fis_ta_1, true);
    lv_textarea_set_accepted_chars(ui->scr_fis_ta_1, "");
    lv_textarea_set_max_length(ui->scr_fis_ta_1, 48);
#if LV_USE_KEYBOARD
    lv_obj_add_event_cb(ui->scr_fis_ta_1, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif

    //Write style for scr_fis_ta_1, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_fis_ta_1, 2, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_opa(ui->scr_fis_ta_1, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_color(ui->scr_fis_ta_1, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_side(ui->scr_fis_ta_1, LV_BORDER_SIDE_FULL, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_fis_ta_1, 4, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_fis_ta_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_fis_ta_1, 11, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_fis_ta_1, 4, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_fis_ta_1, 4, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_fis_ta_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_fis_ta_1, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_fis_ta_1, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_fis_ta_1, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_letter_space(ui->scr_fis_ta_1, 1, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_fis_ta_1, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_fis_ta_1, Part: LV_PART_SCROLLBAR, State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_fis_ta_1, 255, LV_PART_SCROLLBAR|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_fis_ta_1, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_fis_ta_1, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_fis_ta_1, 0, LV_PART_SCROLLBAR|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_fis_cont_1
    ui->scr_fis_cont_1 = lv_obj_create(ui->scr_fis);
    lv_obj_set_pos(ui->scr_fis_cont_1, 0, 0);
    lv_obj_set_size(ui->scr_fis_cont_1, 480, 25);
    lv_obj_set_scrollbar_mode(ui->scr_fis_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for scr_fis_cont_1, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_fis_cont_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_fis_cont_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_fis_cont_1, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_fis_cont_1, lv_color_hex(0x0023F5), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_fis_cont_1, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_fis_cont_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_bottom(ui->scr_fis_cont_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_fis_cont_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_fis_cont_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_fis_cont_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //The custom code of scr_fis.


    //Update current screen layout.
    lv_obj_update_layout(ui->scr_fis);

    //Init events for screen.
    events_init_scr_fis(ui);
}
