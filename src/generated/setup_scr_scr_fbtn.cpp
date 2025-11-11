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

void setup_scr_scr_fbtn(lv_ui *ui)
{
    //Write codes scr_fbtn
    ui->scr_fbtn = lv_obj_create(NULL);
    lv_obj_set_size(ui->scr_fbtn, 480, 272);
    lv_obj_set_scrollbar_mode(ui->scr_fbtn, LV_SCROLLBAR_MODE_OFF);

    //Write style for scr_fbtn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_fbtn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_fbtn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_fbtn, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_fbtn_f_btn_cont
    ui->scr_fbtn_f_btn_cont = lv_obj_create(ui->scr_fbtn);
    lv_obj_set_pos(ui->scr_fbtn_f_btn_cont, 0, 90);
    lv_obj_set_size(ui->scr_fbtn_f_btn_cont, 365, 230);
    lv_obj_set_scrollbar_mode(ui->scr_fbtn_f_btn_cont, LV_SCROLLBAR_MODE_OFF);

    //Write style for scr_fbtn_f_btn_cont, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_fbtn_f_btn_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_fbtn_f_btn_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_fbtn_f_btn_cont, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_fbtn_f_btn_cont, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_fbtn_f_btn_cont, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_fbtn_f_btn_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_bottom(ui->scr_fbtn_f_btn_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_fbtn_f_btn_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_fbtn_f_btn_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_fbtn_f_btn_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    create_urun_buttons(ui, ui->scr_fbtn_f_btn_cont, ui->scr_fbtn_f_no_label, ui->scr_fbtn_f_name_btn, ui->scr_fbtn_f_name_btn_label, 1, NULL); // 📌 Ürün butonlarını oluştur

/*    //Write codes scr_fbtn_f_name_btn_2
    ui->scr_fbtn_f_name_btn_2 = lv_button_create(ui->scr_fbtn_f_btn_cont);
    lv_obj_set_pos(ui->scr_fbtn_f_name_btn_2, 60, 60);
    lv_obj_set_size(ui->scr_fbtn_f_name_btn_2, 290, 55);
    ui->scr_fbtn_f_name_btn_2_label = lv_label_create(ui->scr_fbtn_f_name_btn_2);
    lv_label_set_text(ui->scr_fbtn_f_name_btn_2_label, "ÜRÜN İSMİ");
    lv_label_set_long_mode(ui->scr_fbtn_f_name_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_fbtn_f_name_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_fbtn_f_name_btn_2, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_fbtn_f_name_btn_2_label, LV_PCT(100));

    //Write style for scr_fbtn_f_name_btn_2, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_fbtn_f_name_btn_2, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_fbtn_f_name_btn_2, lv_color_hex(0x0023F5), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_fbtn_f_name_btn_2, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_fbtn_f_name_btn_2, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_fbtn_f_name_btn_2, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_fbtn_f_name_btn_2, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_fbtn_f_name_btn_2, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_fbtn_f_name_btn_2, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_fbtn_f_name_btn_2, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_fbtn_f_name_btn_2, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_fbtn_f_name_btn_2, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_fbtn_f_name_btn_2, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_fbtn_f_name_btn_2, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_fbtn_f_name_btn_2, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_fbtn_f_name_btn_2, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_fbtn_f_name_btn_2, 5, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_fbtn_f_name_btn_2, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_fbtn_f_name_btn_2, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_fbtn_f_name_btn_2, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_fbtn_f_name_btn_2, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);

    //Write codes scr_fbtn_f_no_label_2
    ui->scr_fbtn_f_no_label_2 = lv_label_create(ui->scr_fbtn_f_btn_cont);
    lv_obj_set_pos(ui->scr_fbtn_f_no_label_2, 3, 65);
    lv_obj_set_size(ui->scr_fbtn_f_no_label_2, 50, 45);
    lv_label_set_text(ui->scr_fbtn_f_no_label_2, "2.");
    lv_label_set_long_mode(ui->scr_fbtn_f_no_label_2, LV_LABEL_LONG_WRAP);

    //Write style for scr_fbtn_f_no_label_2, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_fbtn_f_no_label_2, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_fbtn_f_no_label_2, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_fbtn_f_no_label_2, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_fbtn_f_no_label_2, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_fbtn_f_no_label_2, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_letter_space(ui->scr_fbtn_f_no_label_2, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_line_space(ui->scr_fbtn_f_no_label_2, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_fbtn_f_no_label_2, LV_TEXT_ALIGN_RIGHT, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_fbtn_f_no_label_2, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_fbtn_f_no_label_2, 11, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_fbtn_f_no_label_2, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_bottom(ui->scr_fbtn_f_no_label_2, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_fbtn_f_no_label_2, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_fbtn_f_no_label_2, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_fbtn_f_name_btn_1
    ui->scr_fbtn_f_name_btn_1 = lv_button_create(ui->scr_fbtn_f_btn_cont);
    lv_obj_set_pos(ui->scr_fbtn_f_name_btn_1, 60, 0);
    lv_obj_set_size(ui->scr_fbtn_f_name_btn_1, 290, 55);
    ui->scr_fbtn_f_name_btn_1_label = lv_label_create(ui->scr_fbtn_f_name_btn_1);
    lv_label_set_text(ui->scr_fbtn_f_name_btn_1_label, "ÜRÜN İSMİ");
    lv_label_set_long_mode(ui->scr_fbtn_f_name_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_fbtn_f_name_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_fbtn_f_name_btn_1, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_fbtn_f_name_btn_1_label, LV_PCT(100));

    //Write style for scr_fbtn_f_name_btn_1, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_fbtn_f_name_btn_1, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_fbtn_f_name_btn_1, lv_color_hex(0x0023F5), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_fbtn_f_name_btn_1, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_fbtn_f_name_btn_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_fbtn_f_name_btn_1, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_fbtn_f_name_btn_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_fbtn_f_name_btn_1, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_fbtn_f_name_btn_1, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_fbtn_f_name_btn_1, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_fbtn_f_name_btn_1, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_fbtn_f_name_btn_1, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_fbtn_f_name_btn_1, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_fbtn_f_name_btn_1, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_fbtn_f_name_btn_1, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_fbtn_f_name_btn_1, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_fbtn_f_name_btn_1, 5, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_fbtn_f_name_btn_1, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_fbtn_f_name_btn_1, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_fbtn_f_name_btn_1, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_fbtn_f_name_btn_1, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);

    //Write codes scr_fbtn_f_no_label_1
    ui->scr_fbtn_f_no_label_1 = lv_label_create(ui->scr_fbtn_f_btn_cont);
    lv_obj_set_pos(ui->scr_fbtn_f_no_label_1, 3, 5);
    lv_obj_set_size(ui->scr_fbtn_f_no_label_1, 50, 45);
    lv_label_set_text(ui->scr_fbtn_f_no_label_1, "1.");
    lv_label_set_long_mode(ui->scr_fbtn_f_no_label_1, LV_LABEL_LONG_WRAP);

    //Write style for scr_fbtn_f_no_label_1, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_fbtn_f_no_label_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_fbtn_f_no_label_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_fbtn_f_no_label_1, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_fbtn_f_no_label_1, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_fbtn_f_no_label_1, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_letter_space(ui->scr_fbtn_f_no_label_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_line_space(ui->scr_fbtn_f_no_label_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_fbtn_f_no_label_1, LV_TEXT_ALIGN_RIGHT, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_fbtn_f_no_label_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_fbtn_f_no_label_1, 11, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_fbtn_f_no_label_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_bottom(ui->scr_fbtn_f_no_label_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_fbtn_f_no_label_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_fbtn_f_no_label_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    //Write codes scr_fbtn_f_btn_0
    ui->scr_fbtn_f_btn_0 = lv_button_create(ui->scr_fbtn);
    lv_obj_set_pos(ui->scr_fbtn_f_btn_0, 60, 34);
    lv_obj_set_size(ui->scr_fbtn_f_btn_0, 290, 45);
    ui->scr_fbtn_f_btn_0_label = lv_label_create(ui->scr_fbtn_f_btn_0);
    lv_label_set_text(ui->scr_fbtn_f_btn_0_label, "F1 ÜRÜN SEÇİMİ");
    lv_label_set_long_mode(ui->scr_fbtn_f_btn_0_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_fbtn_f_btn_0_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_fbtn_f_btn_0, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_fbtn_f_btn_0_label, LV_PCT(100));

    //Write style for scr_fbtn_f_btn_0, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_fbtn_f_btn_0, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_fbtn_f_btn_0, lv_color_hex(0xD01FBB), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_fbtn_f_btn_0, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_fbtn_f_btn_0, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_fbtn_f_btn_0, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_fbtn_f_btn_0, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_fbtn_f_btn_0, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_fbtn_f_btn_0, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_fbtn_f_btn_0, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_fbtn_f_btn_0, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_fbtn_f_btn_0, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_fbtn_f_btn_0, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_fbtn_f_btn_0, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_fbtn_f_btn_0, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_fbtn_f_btn_0, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_fbtn_f_btn_0, 5, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_fbtn_f_btn_0, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_fbtn_f_btn_0, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_fbtn_f_btn_0, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_fbtn_f_btn_0, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);*/

    //Write codes scr_fbtn_f_geri_btn
    ui->scr_fbtn_f_geri_btn = lv_button_create(ui->scr_fbtn);
    lv_obj_set_pos(ui->scr_fbtn_f_geri_btn, 380, 110);
    lv_obj_set_size(ui->scr_fbtn_f_geri_btn, 96, 62);
    ui->scr_fbtn_f_geri_btn_label = lv_label_create(ui->scr_fbtn_f_geri_btn);
    lv_label_set_text(ui->scr_fbtn_f_geri_btn_label, "");
    lv_label_set_long_mode(ui->scr_fbtn_f_geri_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_fbtn_f_geri_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_fbtn_f_geri_btn, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_fbtn_f_geri_btn_label, LV_PCT(100));

    //Write style for scr_fbtn_f_geri_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_fbtn_f_geri_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_fbtn_f_geri_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_fbtn_f_geri_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_fbtn_f_geri_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_src(ui->scr_fbtn_f_geri_btn, &_geri_RGB565A8_96x52, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_opa(ui->scr_fbtn_f_geri_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_recolor_opa(ui->scr_fbtn_f_geri_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_fbtn_f_geri_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_fbtn_f_geri_btn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_fbtn_f_geri_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_fbtn_f_geri_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_fbtn_f_geri_btn, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_fbtn_f_geri_btn, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_fbtn_f_geri_btn, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_fbtn_f_geri_btn, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_fbtn_f_geri_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_fbtn_f_geri_btn, 5, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_fbtn_f_geri_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_fbtn_f_geri_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_fbtn_f_geri_btn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_fbtn_f_geri_btn, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);

    //Write codes scr_fbtn_f_sec_btn
    ui->scr_fbtn_f_sec_btn = lv_button_create(ui->scr_fbtn);
    lv_obj_set_pos(ui->scr_fbtn_f_sec_btn, 380, 34);
    lv_obj_set_size(ui->scr_fbtn_f_sec_btn, 96, 62);
    ui->scr_fbtn_f_sec_btn_label = lv_label_create(ui->scr_fbtn_f_sec_btn);
    lv_label_set_text(ui->scr_fbtn_f_sec_btn_label, "");
    lv_label_set_long_mode(ui->scr_fbtn_f_sec_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_fbtn_f_sec_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_fbtn_f_sec_btn, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_fbtn_f_sec_btn_label, LV_PCT(100));

    //Write style for scr_fbtn_f_sec_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_fbtn_f_sec_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_fbtn_f_sec_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_fbtn_f_sec_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_fbtn_f_sec_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_src(ui->scr_fbtn_f_sec_btn, &_sec_RGB565A8_96x52, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_opa(ui->scr_fbtn_f_sec_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_recolor_opa(ui->scr_fbtn_f_sec_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_fbtn_f_sec_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_fbtn_f_sec_btn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_fbtn_f_sec_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_fbtn_f_sec_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_fbtn_f_sec_btn, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_fbtn_f_sec_btn, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_fbtn_f_sec_btn, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_fbtn_f_sec_btn, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_fbtn_f_sec_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_fbtn_f_sec_btn, 5, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_fbtn_f_sec_btn, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_fbtn_f_sec_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_fbtn_f_sec_btn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_fbtn_f_sec_btn, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_PRESSED);

    //Write codes scr_fbtn_f_bar_cont
    ui->scr_fbtn_f_bar_cont = lv_obj_create(ui->scr_fbtn);
    lv_obj_set_pos(ui->scr_fbtn_f_bar_cont, 0, 0);
    lv_obj_set_size(ui->scr_fbtn_f_bar_cont, 480, 30);
    lv_obj_set_scrollbar_mode(ui->scr_fbtn_f_bar_cont, LV_SCROLLBAR_MODE_OFF);

    //Write style for scr_fbtn_f_bar_cont, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_fbtn_f_bar_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_fbtn_f_bar_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_fbtn_f_bar_cont, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_fbtn_f_bar_cont, lv_color_hex(0x0023F5), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_fbtn_f_bar_cont, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_fbtn_f_bar_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_bottom(ui->scr_fbtn_f_bar_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_fbtn_f_bar_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_fbtn_f_bar_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_fbtn_f_bar_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //The custom code of scr_fbtn.


    //Update current screen layout.
    lv_obj_update_layout(ui->scr_fbtn);

    //Init events for screen.
    events_init_scr_fbtn(ui);
}
