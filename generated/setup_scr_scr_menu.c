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



void setup_scr_scr_menu(lv_ui *ui)
{
    //Write codes scr_menu
    ui->scr_menu = lv_obj_create(NULL);
    lv_obj_set_size(ui->scr_menu, 480, 272);
    lv_obj_set_scrollbar_mode(ui->scr_menu, LV_SCROLLBAR_MODE_OFF);

    //Write style for scr_menu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_menu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_menu, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_menu, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_menu_ekran_btn
    ui->scr_menu_ekran_btn = lv_button_create(ui->scr_menu);
    lv_obj_set_pos(ui->scr_menu_ekran_btn, 20, 17);
    lv_obj_set_size(ui->scr_menu_ekran_btn, 105, 52);
    ui->scr_menu_ekran_btn_label = lv_label_create(ui->scr_menu_ekran_btn);
    lv_label_set_text(ui->scr_menu_ekran_btn_label, "EKRAN");
    lv_label_set_long_mode(ui->scr_menu_ekran_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_menu_ekran_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_menu_ekran_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_menu_ekran_btn_label, LV_PCT(100));

    //Write style for scr_menu_ekran_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_menu_ekran_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_menu_ekran_btn, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_menu_ekran_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_menu_ekran_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_menu_ekran_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_menu_ekran_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_menu_ekran_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_menu_ekran_btn, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_menu_ekran_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_menu_ekran_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_menu_wsta_btn
    ui->scr_menu_wsta_btn = lv_button_create(ui->scr_menu);
    lv_obj_set_pos(ui->scr_menu_wsta_btn, 135, 17);
    lv_obj_set_size(ui->scr_menu_wsta_btn, 105, 52);
    ui->scr_menu_wsta_btn_label = lv_label_create(ui->scr_menu_wsta_btn);
    lv_label_set_text(ui->scr_menu_wsta_btn_label, "WİFİ STA");
    lv_label_set_long_mode(ui->scr_menu_wsta_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_menu_wsta_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_menu_wsta_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_menu_wsta_btn_label, LV_PCT(100));

    //Write style for scr_menu_wsta_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_menu_wsta_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_menu_wsta_btn, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_menu_wsta_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_menu_wsta_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_menu_wsta_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_menu_wsta_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_menu_wsta_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_menu_wsta_btn, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_menu_wsta_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_menu_wsta_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_menu_wifiap_btn_1
    ui->scr_menu_wifiap_btn_1 = lv_button_create(ui->scr_menu);
    lv_obj_set_pos(ui->scr_menu_wifiap_btn_1, 250, 17);
    lv_obj_set_size(ui->scr_menu_wifiap_btn_1, 105, 52);
    ui->scr_menu_wifiap_btn_1_label = lv_label_create(ui->scr_menu_wifiap_btn_1);
    lv_label_set_text(ui->scr_menu_wifiap_btn_1_label, "WİFİ AP");
    lv_label_set_long_mode(ui->scr_menu_wifiap_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_menu_wifiap_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_menu_wifiap_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_menu_wifiap_btn_1_label, LV_PCT(100));

    //Write style for scr_menu_wifiap_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_menu_wifiap_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_menu_wifiap_btn_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_menu_wifiap_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_menu_wifiap_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_menu_wifiap_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_menu_wifiap_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_menu_wifiap_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_menu_wifiap_btn_1, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_menu_wifiap_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_menu_wifiap_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_menu_yazici_btn
    ui->scr_menu_yazici_btn = lv_button_create(ui->scr_menu);
    lv_obj_set_pos(ui->scr_menu_yazici_btn, 20, 85);
    lv_obj_set_size(ui->scr_menu_yazici_btn, 105, 52);
    ui->scr_menu_yazici_btn_label = lv_label_create(ui->scr_menu_yazici_btn);
    lv_label_set_text(ui->scr_menu_yazici_btn_label, "YAZICI AYARLARI\n");
    lv_label_set_long_mode(ui->scr_menu_yazici_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_menu_yazici_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_menu_yazici_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_menu_yazici_btn_label, LV_PCT(100));

    //Write style for scr_menu_yazici_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_menu_yazici_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_menu_yazici_btn, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_menu_yazici_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_menu_yazici_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_menu_yazici_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_menu_yazici_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_menu_yazici_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_menu_yazici_btn, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_menu_yazici_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_menu_yazici_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_menu_terazi_btn
    ui->scr_menu_terazi_btn = lv_button_create(ui->scr_menu);
    lv_obj_set_pos(ui->scr_menu_terazi_btn, 135, 85);
    lv_obj_set_size(ui->scr_menu_terazi_btn, 105, 52);
    ui->scr_menu_terazi_btn_label = lv_label_create(ui->scr_menu_terazi_btn);
    lv_label_set_text(ui->scr_menu_terazi_btn_label, "TERAZİ AYARLARI\n");
    lv_label_set_long_mode(ui->scr_menu_terazi_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_menu_terazi_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_menu_terazi_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_menu_terazi_btn_label, LV_PCT(100));

    //Write style for scr_menu_terazi_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_menu_terazi_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_menu_terazi_btn, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_menu_terazi_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_menu_terazi_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_menu_terazi_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_menu_terazi_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_menu_terazi_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_menu_terazi_btn, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_menu_terazi_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_menu_terazi_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_menu_fis_dizayn_btn
    ui->scr_menu_fis_dizayn_btn = lv_button_create(ui->scr_menu);
    lv_obj_set_pos(ui->scr_menu_fis_dizayn_btn, 250, 85);
    lv_obj_set_size(ui->scr_menu_fis_dizayn_btn, 105, 52);
    ui->scr_menu_fis_dizayn_btn_label = lv_label_create(ui->scr_menu_fis_dizayn_btn);
    lv_label_set_text(ui->scr_menu_fis_dizayn_btn_label, "FİŞ DİZAYNI");
    lv_label_set_long_mode(ui->scr_menu_fis_dizayn_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_menu_fis_dizayn_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_menu_fis_dizayn_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_menu_fis_dizayn_btn_label, LV_PCT(100));

    //Write style for scr_menu_fis_dizayn_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_menu_fis_dizayn_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_menu_fis_dizayn_btn, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_menu_fis_dizayn_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_menu_fis_dizayn_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_menu_fis_dizayn_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_menu_fis_dizayn_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_menu_fis_dizayn_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_menu_fis_dizayn_btn, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_menu_fis_dizayn_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_menu_fis_dizayn_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_menu_wifiap_btn_2
    ui->scr_menu_wifiap_btn_2 = lv_button_create(ui->scr_menu);
    lv_obj_set_pos(ui->scr_menu_wifiap_btn_2, 365, 17);
    lv_obj_set_size(ui->scr_menu_wifiap_btn_2, 105, 52);
    ui->scr_menu_wifiap_btn_2_label = lv_label_create(ui->scr_menu_wifiap_btn_2);
    lv_label_set_text(ui->scr_menu_wifiap_btn_2_label, "WİFİ AP");
    lv_label_set_long_mode(ui->scr_menu_wifiap_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_menu_wifiap_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_menu_wifiap_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_menu_wifiap_btn_2_label, LV_PCT(100));

    //Write style for scr_menu_wifiap_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_menu_wifiap_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_menu_wifiap_btn_2, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_menu_wifiap_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_menu_wifiap_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_menu_wifiap_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_menu_wifiap_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_menu_wifiap_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_menu_wifiap_btn_2, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_menu_wifiap_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_menu_wifiap_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_menu_etiket_dizayn_btn
    ui->scr_menu_etiket_dizayn_btn = lv_button_create(ui->scr_menu);
    lv_obj_set_pos(ui->scr_menu_etiket_dizayn_btn, 365, 85);
    lv_obj_set_size(ui->scr_menu_etiket_dizayn_btn, 105, 52);
    ui->scr_menu_etiket_dizayn_btn_label = lv_label_create(ui->scr_menu_etiket_dizayn_btn);
    lv_label_set_text(ui->scr_menu_etiket_dizayn_btn_label, "ETİKET DİZAYNI");
    lv_label_set_long_mode(ui->scr_menu_etiket_dizayn_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_menu_etiket_dizayn_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_menu_etiket_dizayn_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_menu_etiket_dizayn_btn_label, LV_PCT(100));

    //Write style for scr_menu_etiket_dizayn_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_menu_etiket_dizayn_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_menu_etiket_dizayn_btn, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_menu_etiket_dizayn_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_menu_etiket_dizayn_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_menu_etiket_dizayn_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_menu_etiket_dizayn_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_menu_etiket_dizayn_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_menu_etiket_dizayn_btn, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_menu_etiket_dizayn_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_menu_etiket_dizayn_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_menu_geri_btn
    ui->scr_menu_geri_btn = lv_button_create(ui->scr_menu);
    lv_obj_set_pos(ui->scr_menu_geri_btn, 375, 210);
    lv_obj_set_size(ui->scr_menu_geri_btn, 96, 52);
    ui->scr_menu_geri_btn_label = lv_label_create(ui->scr_menu_geri_btn);
    lv_label_set_text(ui->scr_menu_geri_btn_label, "");
    lv_label_set_long_mode(ui->scr_menu_geri_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_menu_geri_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_menu_geri_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_menu_geri_btn_label, LV_PCT(100));

    //Write style for scr_menu_geri_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_menu_geri_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_menu_geri_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_menu_geri_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_menu_geri_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(ui->scr_menu_geri_btn, &_geri_RGB565A8_96x52, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_opa(ui->scr_menu_geri_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_recolor_opa(ui->scr_menu_geri_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_menu_geri_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_menu_geri_btn, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_menu_geri_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_menu_geri_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_menu_geri_btn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_menu_geri_btn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_menu_geri_btn, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_menu_geri_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_menu_geri_btn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_menu_geri_btn, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_menu_geri_btn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_menu_geri_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_menu_geri_btn, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_menu_geri_btn, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //The custom code of scr_menu.


    //Update current screen layout.
    lv_obj_update_layout(ui->scr_menu);

    //Init events for screen.
    events_init_scr_menu(ui);
}
