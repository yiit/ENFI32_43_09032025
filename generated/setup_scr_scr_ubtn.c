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


void setup_scr_scr_ubtn(lv_ui *ui)
{
    //Write codes scr_ubtn
    ui->scr_ubtn = lv_obj_create(NULL);
    lv_obj_set_size(ui->scr_ubtn, 480, 272);
    lv_obj_set_scrollbar_mode(ui->scr_ubtn, LV_SCROLLBAR_MODE_OFF);

    //Write style for scr_ubtn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_ubtn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_ubtn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_ubtn_u_ta
    ui->scr_ubtn_u_ta = lv_textarea_create(ui->scr_ubtn);
    lv_obj_set_pos(ui->scr_ubtn_u_ta, 60, 28);
    lv_obj_set_size(ui->scr_ubtn_u_ta, 300, 39);
    lv_textarea_set_text(ui->scr_ubtn_u_ta, "");
    lv_textarea_set_placeholder_text(ui->scr_ubtn_u_ta, "ÜRÜN İSMİ GİRİNİZ");
    lv_textarea_set_password_bullet(ui->scr_ubtn_u_ta, "*");
    lv_textarea_set_password_mode(ui->scr_ubtn_u_ta, false);
    lv_textarea_set_one_line(ui->scr_ubtn_u_ta, true);
    lv_textarea_set_accepted_chars(ui->scr_ubtn_u_ta, "");
    lv_textarea_set_max_length(ui->scr_ubtn_u_ta, 32);
#if LV_USE_KEYBOARD
    lv_obj_add_event_cb(ui->scr_ubtn_u_ta, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif

    //Write style for scr_ubtn_u_ta, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->scr_ubtn_u_ta, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_ubtn_u_ta, &lv_font_Oswald_Reg_15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_ta, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scr_ubtn_u_ta, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_ubtn_u_ta, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_ta, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_ubtn_u_ta, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn_u_ta, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_ubtn_u_ta, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scr_ubtn_u_ta, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scr_ubtn_u_ta, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scr_ubtn_u_ta, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_ta, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scr_ubtn_u_ta, 9, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_ubtn_u_ta, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_ubtn_u_ta, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_ubtn_u_ta, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_ubtn_u_ta, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_ta, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_ubtn_u_ta, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn_u_ta, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_ubtn_u_ta, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes scr_ubtn_u_cont
    ui->scr_ubtn_u_cont = lv_obj_create(ui->scr_ubtn);
    lv_obj_set_pos(ui->scr_ubtn_u_cont, 0, 76);
    lv_obj_set_size(ui->scr_ubtn_u_cont, 365, 195);
    lv_obj_set_scrollbar_mode(ui->scr_ubtn_u_cont, LV_SCROLLBAR_MODE_AUTO);
    lv_obj_add_flag(ui->scr_ubtn_u_cont, LV_OBJ_FLAG_SCROLLABLE);

    //Write style for scr_ubtn_u_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scr_ubtn_u_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_ubtn_u_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_ubtn_u_cont, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn_u_cont, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scr_ubtn_u_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scr_ubtn_u_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_ubtn_u_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_ubtn_u_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_ubtn_u_name_btn_0
    ui->scr_ubtn_u_name_btn_0 = lv_button_create(ui->scr_ubtn_u_cont);
    lv_obj_set_pos(ui->scr_ubtn_u_name_btn_0, 60, 0);
    lv_obj_set_size(ui->scr_ubtn_u_name_btn_0, 280, 46);
    ui->scr_ubtn_u_name_btn_0_label = lv_label_create(ui->scr_ubtn_u_name_btn_0);
    lv_label_set_text(ui->scr_ubtn_u_name_btn_0_label, "ÜRÜN İSMİ");
    lv_label_set_long_mode(ui->scr_ubtn_u_name_btn_0_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_ubtn_u_name_btn_0_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_ubtn_u_name_btn_0, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_ubtn_u_name_btn_0_label, LV_PCT(100));

    //Write style for scr_ubtn_u_name_btn_0, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_name_btn_0, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_ubtn_u_name_btn_0, lv_color_hex(0x2F92DA), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn_u_name_btn_0, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_ubtn_u_name_btn_0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_ubtn_u_name_btn_0, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_name_btn_0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_ubtn_u_name_btn_0, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_ubtn_u_name_btn_0, &lv_font_Oswald_Reg_15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_name_btn_0, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_ubtn_u_name_btn_0, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_ubtn_u_name_btn_0, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_name_btn_0, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_ubtn_u_name_btn_0, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn_u_name_btn_0, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_ubtn_u_name_btn_0, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_ubtn_u_name_btn_0, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_name_btn_0, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_ubtn_u_name_btn_0, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_ubtn_u_name_btn_0, &lv_font_Oswald_Reg_17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_name_btn_0, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes scr_ubtn_u_name_btn_2
    ui->scr_ubtn_u_name_btn_2 = lv_button_create(ui->scr_ubtn_u_cont);
    lv_obj_set_pos(ui->scr_ubtn_u_name_btn_2, 60, 102);
    lv_obj_set_size(ui->scr_ubtn_u_name_btn_2, 280, 46);
    ui->scr_ubtn_u_name_btn_2_label = lv_label_create(ui->scr_ubtn_u_name_btn_2);
    lv_label_set_text(ui->scr_ubtn_u_name_btn_2_label, "U2");
    lv_label_set_long_mode(ui->scr_ubtn_u_name_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_ubtn_u_name_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_ubtn_u_name_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_ubtn_u_name_btn_2_label, LV_PCT(100));

    //Write style for scr_ubtn_u_name_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_name_btn_2, 150, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_ubtn_u_name_btn_2, lv_color_hex(0xff0000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn_u_name_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_ubtn_u_name_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_ubtn_u_name_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_name_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_ubtn_u_name_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_ubtn_u_name_btn_2, &lv_font_Oswald_Reg_15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_name_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_ubtn_u_name_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_ubtn_u_name_btn_2, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_name_btn_2, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_ubtn_u_name_btn_2, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn_u_name_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_ubtn_u_name_btn_2, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_ubtn_u_name_btn_2, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_name_btn_2, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_ubtn_u_name_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_ubtn_u_name_btn_2, &lv_font_Oswald_Reg_17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_name_btn_2, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes scr_ubtn_u_name_btn_1
    ui->scr_ubtn_u_name_btn_1 = lv_button_create(ui->scr_ubtn_u_cont);
    lv_obj_set_pos(ui->scr_ubtn_u_name_btn_1, 60, 51);
    lv_obj_set_size(ui->scr_ubtn_u_name_btn_1, 280, 46);
    ui->scr_ubtn_u_name_btn_1_label = lv_label_create(ui->scr_ubtn_u_name_btn_1);
    lv_label_set_text(ui->scr_ubtn_u_name_btn_1_label, "U1");
    lv_label_set_long_mode(ui->scr_ubtn_u_name_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_ubtn_u_name_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_ubtn_u_name_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_ubtn_u_name_btn_1_label, LV_PCT(100));

    //Write style for scr_ubtn_u_name_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_name_btn_1, 150, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_ubtn_u_name_btn_1, lv_color_hex(0xff0000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn_u_name_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_ubtn_u_name_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_ubtn_u_name_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_name_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_ubtn_u_name_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_ubtn_u_name_btn_1, &lv_font_Oswald_Reg_15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_name_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_ubtn_u_name_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_ubtn_u_name_btn_1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_name_btn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_ubtn_u_name_btn_1, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn_u_name_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_ubtn_u_name_btn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_ubtn_u_name_btn_1, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_name_btn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_ubtn_u_name_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_ubtn_u_name_btn_1, &lv_font_Oswald_Reg_17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_name_btn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes scr_ubtn_u_no_label_2
    ui->scr_ubtn_u_no_label_2 = lv_label_create(ui->scr_ubtn_u_cont);
    lv_obj_set_pos(ui->scr_ubtn_u_no_label_2, 2, 106);
    lv_obj_set_size(ui->scr_ubtn_u_no_label_2, 50, 38);
    lv_label_set_text(ui->scr_ubtn_u_no_label_2, "2.");
    lv_label_set_long_mode(ui->scr_ubtn_u_no_label_2, LV_LABEL_LONG_WRAP);

    //Write style for scr_ubtn_u_no_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scr_ubtn_u_no_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_ubtn_u_no_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_ubtn_u_no_label_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_ubtn_u_no_label_2, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_no_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scr_ubtn_u_no_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scr_ubtn_u_no_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_ubtn_u_no_label_2, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_no_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scr_ubtn_u_no_label_2, 11, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_ubtn_u_no_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scr_ubtn_u_no_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_ubtn_u_no_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_no_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_ubtn_u_no_label_1
    ui->scr_ubtn_u_no_label_1 = lv_label_create(ui->scr_ubtn_u_cont);
    lv_obj_set_pos(ui->scr_ubtn_u_no_label_1, 2, 56);
    lv_obj_set_size(ui->scr_ubtn_u_no_label_1, 50, 38);
    lv_label_set_text(ui->scr_ubtn_u_no_label_1, "1.");
    lv_label_set_long_mode(ui->scr_ubtn_u_no_label_1, LV_LABEL_LONG_WRAP);

    //Write style for scr_ubtn_u_no_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scr_ubtn_u_no_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_ubtn_u_no_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_ubtn_u_no_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_ubtn_u_no_label_1, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_no_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scr_ubtn_u_no_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scr_ubtn_u_no_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_ubtn_u_no_label_1, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_no_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scr_ubtn_u_no_label_1, 11, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_ubtn_u_no_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scr_ubtn_u_no_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_ubtn_u_no_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_no_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_ubtn_label_1
    ui->scr_ubtn_label_1 = lv_label_create(ui->scr_ubtn_u_cont);
    lv_obj_set_pos(ui->scr_ubtn_label_1, 2, 4);
    lv_obj_set_size(ui->scr_ubtn_label_1, 50, 38);
    lv_label_set_text(ui->scr_ubtn_label_1, "KOD NO");
    lv_label_set_long_mode(ui->scr_ubtn_label_1, LV_LABEL_LONG_WRAP);

    //Write style for scr_ubtn_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scr_ubtn_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_ubtn_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_ubtn_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_ubtn_label_1, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_ubtn_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scr_ubtn_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scr_ubtn_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_ubtn_label_1, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_ubtn_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scr_ubtn_label_1, 11, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_ubtn_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scr_ubtn_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_ubtn_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_ubtn_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_ubtn_u_bar_cont
    ui->scr_ubtn_u_bar_cont = lv_obj_create(ui->scr_ubtn);
    lv_obj_set_pos(ui->scr_ubtn_u_bar_cont, 0, 0);
    lv_obj_set_size(ui->scr_ubtn_u_bar_cont, 480, 25);
    lv_obj_set_scrollbar_mode(ui->scr_ubtn_u_bar_cont, LV_SCROLLBAR_MODE_OFF);

    //Write style for scr_ubtn_u_bar_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scr_ubtn_u_bar_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_ubtn_u_bar_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_bar_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_ubtn_u_bar_cont, lv_color_hex(0x2F35DA), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn_u_bar_cont, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scr_ubtn_u_bar_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scr_ubtn_u_bar_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_ubtn_u_bar_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_ubtn_u_bar_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_bar_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_ubtn_u_label
    ui->scr_ubtn_u_label = lv_label_create(ui->scr_ubtn_u_bar_cont);
    lv_obj_set_pos(ui->scr_ubtn_u_label, 60, 0);
    lv_obj_set_size(ui->scr_ubtn_u_label, 142, 21);
    lv_label_set_text(ui->scr_ubtn_u_label, "ÜRÜN SEÇİM EKRANI");
    lv_label_set_long_mode(ui->scr_ubtn_u_label, LV_LABEL_LONG_WRAP);

    //Write style for scr_ubtn_u_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scr_ubtn_u_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_ubtn_u_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_ubtn_u_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_ubtn_u_label, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scr_ubtn_u_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scr_ubtn_u_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_ubtn_u_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scr_ubtn_u_label, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_ubtn_u_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scr_ubtn_u_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_ubtn_u_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_ubtn_u_geri_btn
    ui->scr_ubtn_u_geri_btn = lv_button_create(ui->scr_ubtn);
    lv_obj_set_pos(ui->scr_ubtn_u_geri_btn, 380, 215);
    lv_obj_set_size(ui->scr_ubtn_u_geri_btn, 96, 52);
    ui->scr_ubtn_u_geri_btn_label = lv_label_create(ui->scr_ubtn_u_geri_btn);
    lv_label_set_text(ui->scr_ubtn_u_geri_btn_label, "");
    lv_label_set_long_mode(ui->scr_ubtn_u_geri_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_ubtn_u_geri_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_ubtn_u_geri_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_ubtn_u_geri_btn_label, LV_PCT(100));

    //Write style for scr_ubtn_u_geri_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_geri_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_ubtn_u_geri_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_ubtn_u_geri_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_geri_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(ui->scr_ubtn_u_geri_btn, &_geri_RGB565A8_96x52, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_opa(ui->scr_ubtn_u_geri_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_recolor_opa(ui->scr_ubtn_u_geri_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_ubtn_u_geri_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_ubtn_u_geri_btn, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_geri_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_ubtn_u_geri_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_ubtn_u_geri_btn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_geri_btn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_ubtn_u_geri_btn, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn_u_geri_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_ubtn_u_geri_btn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_ubtn_u_geri_btn, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_geri_btn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_ubtn_u_geri_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_ubtn_u_geri_btn, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_geri_btn, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes scr_ubtn_u_kaydet_btn
    ui->scr_ubtn_u_kaydet_btn = lv_button_create(ui->scr_ubtn);
    lv_obj_set_pos(ui->scr_ubtn_u_kaydet_btn, 380, 28);
    lv_obj_set_size(ui->scr_ubtn_u_kaydet_btn, 96, 52);
    ui->scr_ubtn_u_kaydet_btn_label = lv_label_create(ui->scr_ubtn_u_kaydet_btn);
    lv_label_set_text(ui->scr_ubtn_u_kaydet_btn_label, "");
    lv_label_set_long_mode(ui->scr_ubtn_u_kaydet_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_ubtn_u_kaydet_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_ubtn_u_kaydet_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_ubtn_u_kaydet_btn_label, LV_PCT(100));

    //Write style for scr_ubtn_u_kaydet_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_kaydet_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_ubtn_u_kaydet_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_ubtn_u_kaydet_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_kaydet_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(ui->scr_ubtn_u_kaydet_btn, &_saved_RGB565A8_96x52, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_opa(ui->scr_ubtn_u_kaydet_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_recolor_opa(ui->scr_ubtn_u_kaydet_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_ubtn_u_kaydet_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_ubtn_u_kaydet_btn, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_kaydet_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_ubtn_u_kaydet_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_ubtn_u_kaydet_btn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_kaydet_btn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_ubtn_u_kaydet_btn, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn_u_kaydet_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_ubtn_u_kaydet_btn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_ubtn_u_kaydet_btn, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_kaydet_btn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_ubtn_u_kaydet_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_ubtn_u_kaydet_btn, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_kaydet_btn, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes scr_ubtn_u_duzenle_btn
    ui->scr_ubtn_u_duzenle_btn = lv_button_create(ui->scr_ubtn);
    lv_obj_set_pos(ui->scr_ubtn_u_duzenle_btn, 380, 151);
    lv_obj_set_size(ui->scr_ubtn_u_duzenle_btn, 96, 52);
    ui->scr_ubtn_u_duzenle_btn_label = lv_label_create(ui->scr_ubtn_u_duzenle_btn);
    lv_label_set_text(ui->scr_ubtn_u_duzenle_btn_label, "");
    lv_label_set_long_mode(ui->scr_ubtn_u_duzenle_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_ubtn_u_duzenle_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_ubtn_u_duzenle_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_ubtn_u_duzenle_btn_label, LV_PCT(100));

    //Write style for scr_ubtn_u_duzenle_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_duzenle_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_ubtn_u_duzenle_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_ubtn_u_duzenle_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_duzenle_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(ui->scr_ubtn_u_duzenle_btn, &_duzenle_RGB565A8_96x52, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_opa(ui->scr_ubtn_u_duzenle_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_recolor_opa(ui->scr_ubtn_u_duzenle_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_ubtn_u_duzenle_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_ubtn_u_duzenle_btn, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_duzenle_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_ubtn_u_duzenle_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_ubtn_u_duzenle_btn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_duzenle_btn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_ubtn_u_duzenle_btn, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn_u_duzenle_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_ubtn_u_duzenle_btn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_ubtn_u_duzenle_btn, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_duzenle_btn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_ubtn_u_duzenle_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_ubtn_u_duzenle_btn, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_duzenle_btn, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes scr_ubtn_u_sec_btn
    ui->scr_ubtn_u_sec_btn = lv_button_create(ui->scr_ubtn);
    lv_obj_set_pos(ui->scr_ubtn_u_sec_btn, 380, 90);
    lv_obj_set_size(ui->scr_ubtn_u_sec_btn, 96, 52);
    ui->scr_ubtn_u_sec_btn_label = lv_label_create(ui->scr_ubtn_u_sec_btn);
    lv_label_set_text(ui->scr_ubtn_u_sec_btn_label, "");
    lv_label_set_long_mode(ui->scr_ubtn_u_sec_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_ubtn_u_sec_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_ubtn_u_sec_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_ubtn_u_sec_btn_label, LV_PCT(100));

    //Write style for scr_ubtn_u_sec_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_sec_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_ubtn_u_sec_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_ubtn_u_sec_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_sec_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(ui->scr_ubtn_u_sec_btn, &_sec_RGB565A8_96x52, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_opa(ui->scr_ubtn_u_sec_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_recolor_opa(ui->scr_ubtn_u_sec_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_ubtn_u_sec_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_ubtn_u_sec_btn, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_sec_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_ubtn_u_sec_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_ubtn_u_sec_btn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_sec_btn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_ubtn_u_sec_btn, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn_u_sec_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_ubtn_u_sec_btn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_ubtn_u_sec_btn, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_sec_btn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_ubtn_u_sec_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_ubtn_u_sec_btn, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_sec_btn, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes scr_ubtn_u_bul_btn
    ui->scr_ubtn_u_bul_btn = lv_button_create(ui->scr_ubtn);
    lv_obj_set_pos(ui->scr_ubtn_u_bul_btn, 380, 28);
    lv_obj_set_size(ui->scr_ubtn_u_bul_btn, 96, 52);
    ui->scr_ubtn_u_bul_btn_label = lv_label_create(ui->scr_ubtn_u_bul_btn);
    lv_label_set_text(ui->scr_ubtn_u_bul_btn_label, "");
    lv_label_set_long_mode(ui->scr_ubtn_u_bul_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_ubtn_u_bul_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_ubtn_u_bul_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_ubtn_u_bul_btn_label, LV_PCT(100));

    //Write style for scr_ubtn_u_bul_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_bul_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_ubtn_u_bul_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_ubtn_u_bul_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_bul_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(ui->scr_ubtn_u_bul_btn, &_bul_RGB565A8_96x52, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_opa(ui->scr_ubtn_u_bul_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_recolor_opa(ui->scr_ubtn_u_bul_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_ubtn_u_bul_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_ubtn_u_bul_btn, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_bul_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_ubtn_u_bul_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_ubtn_u_bul_btn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_bul_btn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_ubtn_u_bul_btn, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn_u_bul_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_ubtn_u_bul_btn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_ubtn_u_bul_btn, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_bul_btn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_ubtn_u_bul_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_ubtn_u_bul_btn, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_bul_btn, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //The custom code of scr_ubtn.


    //Update current screen layout.
    lv_obj_update_layout(ui->scr_ubtn);

    //Init events for screen.
    events_init_scr_ubtn(ui);
}
