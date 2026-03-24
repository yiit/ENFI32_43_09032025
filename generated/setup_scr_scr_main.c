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


void setup_scr_scr_main(lv_ui *ui)
{
    //Write codes scr_main
    ui->scr_main = lv_obj_create(NULL);
    lv_obj_set_size(ui->scr_main, 480, 272);
    lv_obj_set_scrollbar_mode(ui->scr_main, LV_SCROLLBAR_MODE_OFF);

    //Write style for scr_main, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_main, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_main, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_main_yazdir_imgbtn
    ui->scr_main_yazdir_imgbtn = lv_imagebutton_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_yazdir_imgbtn, 381, 217);
    lv_obj_set_size(ui->scr_main_yazdir_imgbtn, 96, 54);
    lv_imagebutton_set_src(ui->scr_main_yazdir_imgbtn, LV_IMAGEBUTTON_STATE_RELEASED, &_printing_RGB565A8_96x54, NULL, NULL);
    lv_imagebutton_set_src(ui->scr_main_yazdir_imgbtn, LV_IMAGEBUTTON_STATE_PRESSED, &_printing_RGB565A8_96x54, NULL, NULL);
    ui->scr_main_yazdir_imgbtn_label = lv_label_create(ui->scr_main_yazdir_imgbtn);
    lv_label_set_text(ui->scr_main_yazdir_imgbtn_label, "");
    lv_label_set_long_mode(ui->scr_main_yazdir_imgbtn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_yazdir_imgbtn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_yazdir_imgbtn, 0, LV_STATE_DEFAULT);

    //Write style for scr_main_yazdir_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->scr_main_yazdir_imgbtn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_yazdir_imgbtn, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_yazdir_imgbtn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_yazdir_imgbtn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_yazdir_imgbtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_main_yazdir_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_image_recolor_opa(ui->scr_main_yazdir_imgbtn, 100, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_image_recolor(ui->scr_main_yazdir_imgbtn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_image_opa(ui->scr_main_yazdir_imgbtn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_main_yazdir_imgbtn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_main_yazdir_imgbtn, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_main_yazdir_imgbtn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_main_yazdir_imgbtn, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for scr_main_yazdir_imgbtn, Part: LV_PART_MAIN, State: LV_IMAGEBUTTON_STATE_RELEASED.
    lv_obj_set_style_image_recolor_opa(ui->scr_main_yazdir_imgbtn, 0, LV_PART_MAIN|LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_style_image_opa(ui->scr_main_yazdir_imgbtn, 255, LV_PART_MAIN|LV_IMAGEBUTTON_STATE_RELEASED);

    //Write codes scr_main_topla_imgbtn
    ui->scr_main_topla_imgbtn = lv_imagebutton_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_topla_imgbtn, 381, 161);
    lv_obj_set_size(ui->scr_main_topla_imgbtn, 96, 54);
    lv_imagebutton_set_src(ui->scr_main_topla_imgbtn, LV_IMAGEBUTTON_STATE_RELEASED, &_topla_RGB565A8_96x54, NULL, NULL);
    lv_imagebutton_set_src(ui->scr_main_topla_imgbtn, LV_IMAGEBUTTON_STATE_PRESSED, &_topla_RGB565A8_96x54, NULL, NULL);
    ui->scr_main_topla_imgbtn_label = lv_label_create(ui->scr_main_topla_imgbtn);
    lv_label_set_text(ui->scr_main_topla_imgbtn_label, "");
    lv_label_set_long_mode(ui->scr_main_topla_imgbtn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_topla_imgbtn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_topla_imgbtn, 0, LV_STATE_DEFAULT);

    //Write style for scr_main_topla_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->scr_main_topla_imgbtn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_topla_imgbtn, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_topla_imgbtn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_topla_imgbtn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_topla_imgbtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_main_topla_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_image_recolor_opa(ui->scr_main_topla_imgbtn, 100, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_image_recolor(ui->scr_main_topla_imgbtn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_image_opa(ui->scr_main_topla_imgbtn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_main_topla_imgbtn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_main_topla_imgbtn, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_main_topla_imgbtn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_main_topla_imgbtn, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for scr_main_topla_imgbtn, Part: LV_PART_MAIN, State: LV_IMAGEBUTTON_STATE_RELEASED.
    lv_obj_set_style_image_recolor_opa(ui->scr_main_topla_imgbtn, 0, LV_PART_MAIN|LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_style_image_opa(ui->scr_main_topla_imgbtn, 255, LV_PART_MAIN|LV_IMAGEBUTTON_STATE_RELEASED);

    //Write codes scr_main_m_cont
    ui->scr_main_m_cont = lv_obj_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_m_cont, 34, 114);
    lv_obj_set_size(ui->scr_main_m_cont, 412, 44);
    lv_obj_set_scrollbar_mode(ui->scr_main_m_cont, LV_SCROLLBAR_MODE_AUTO);
    lv_obj_add_flag(ui->scr_main_m_cont, LV_OBJ_FLAG_SCROLL_WITH_ARROW);

    //Write style for scr_main_m_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scr_main_m_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_m_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_main_m_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_main_m_cont, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_cont, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scr_main_m_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scr_main_m_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_main_m_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_main_m_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_m_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_main_m_btn_8
    ui->scr_main_m_btn_8 = lv_button_create(ui->scr_main_m_cont);
    lv_obj_set_pos(ui->scr_main_m_btn_8, 723, 1);
    lv_obj_set_size(ui->scr_main_m_btn_8, 100, 42);
    lv_obj_add_flag(ui->scr_main_m_btn_8, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_m_btn_8_label = lv_label_create(ui->scr_main_m_btn_8);
    lv_label_set_text(ui->scr_main_m_btn_8_label, "M8");
    lv_label_set_long_mode(ui->scr_main_m_btn_8_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_m_btn_8_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_m_btn_8, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_main_m_btn_8_label, LV_PCT(100));

    //Write style for scr_main_m_btn_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main_m_btn_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_8, lv_color_hex(0xff8f00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_main_m_btn_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_m_btn_8, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_m_btn_8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_m_btn_8, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_m_btn_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_main_m_btn_8, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_main_m_btn_8, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_8, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_main_m_btn_8, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_main_m_btn_8, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_8, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_main_m_btn_8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_main_m_btn_8, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_8, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes scr_main_m_btn_7
    ui->scr_main_m_btn_7 = lv_button_create(ui->scr_main_m_cont);
    lv_obj_set_pos(ui->scr_main_m_btn_7, 620, 1);
    lv_obj_set_size(ui->scr_main_m_btn_7, 100, 42);
    lv_obj_add_flag(ui->scr_main_m_btn_7, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_m_btn_7_label = lv_label_create(ui->scr_main_m_btn_7);
    lv_label_set_text(ui->scr_main_m_btn_7_label, "M7");
    lv_label_set_long_mode(ui->scr_main_m_btn_7_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_m_btn_7_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_m_btn_7, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_main_m_btn_7_label, LV_PCT(100));

    //Write style for scr_main_m_btn_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main_m_btn_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_7, lv_color_hex(0xff8f00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_main_m_btn_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_m_btn_7, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_m_btn_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_m_btn_7, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_m_btn_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_main_m_btn_7, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_main_m_btn_7, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_7, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_main_m_btn_7, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_main_m_btn_7, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_7, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_main_m_btn_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_main_m_btn_7, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_7, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes scr_main_m_btn_6
    ui->scr_main_m_btn_6 = lv_button_create(ui->scr_main_m_cont);
    lv_obj_set_pos(ui->scr_main_m_btn_6, 517, 1);
    lv_obj_set_size(ui->scr_main_m_btn_6, 100, 42);
    lv_obj_add_flag(ui->scr_main_m_btn_6, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_m_btn_6_label = lv_label_create(ui->scr_main_m_btn_6);
    lv_label_set_text(ui->scr_main_m_btn_6_label, "M6");
    lv_label_set_long_mode(ui->scr_main_m_btn_6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_m_btn_6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_m_btn_6, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_main_m_btn_6_label, LV_PCT(100));

    //Write style for scr_main_m_btn_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main_m_btn_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_6, lv_color_hex(0xff8f00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_main_m_btn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_m_btn_6, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_m_btn_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_m_btn_6, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_m_btn_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_main_m_btn_6, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_main_m_btn_6, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_6, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_main_m_btn_6, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_main_m_btn_6, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_6, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_main_m_btn_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_main_m_btn_6, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_6, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes scr_main_m_btn_5
    ui->scr_main_m_btn_5 = lv_button_create(ui->scr_main_m_cont);
    lv_obj_set_pos(ui->scr_main_m_btn_5, 414, 1);
    lv_obj_set_size(ui->scr_main_m_btn_5, 100, 42);
    lv_obj_add_flag(ui->scr_main_m_btn_5, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_m_btn_5_label = lv_label_create(ui->scr_main_m_btn_5);
    lv_label_set_text(ui->scr_main_m_btn_5_label, "M5");
    lv_label_set_long_mode(ui->scr_main_m_btn_5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_m_btn_5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_m_btn_5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_main_m_btn_5_label, LV_PCT(100));

    //Write style for scr_main_m_btn_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main_m_btn_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_5, lv_color_hex(0xff8f00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_main_m_btn_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_m_btn_5, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_m_btn_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_m_btn_5, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_m_btn_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_main_m_btn_5, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_main_m_btn_5, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_5, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_main_m_btn_5, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_main_m_btn_5, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_5, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_main_m_btn_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_main_m_btn_5, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_5, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes scr_main_m_btn_4
    ui->scr_main_m_btn_4 = lv_button_create(ui->scr_main_m_cont);
    lv_obj_set_pos(ui->scr_main_m_btn_4, 311, 1);
    lv_obj_set_size(ui->scr_main_m_btn_4, 100, 42);
    lv_obj_add_flag(ui->scr_main_m_btn_4, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_m_btn_4_label = lv_label_create(ui->scr_main_m_btn_4);
    lv_label_set_text(ui->scr_main_m_btn_4_label, "M4");
    lv_label_set_long_mode(ui->scr_main_m_btn_4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_m_btn_4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_m_btn_4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_main_m_btn_4_label, LV_PCT(100));

    //Write style for scr_main_m_btn_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main_m_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_4, lv_color_hex(0xff8f00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_main_m_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_m_btn_4, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_m_btn_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_m_btn_4, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_m_btn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_main_m_btn_4, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_main_m_btn_4, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_4, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_main_m_btn_4, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_main_m_btn_4, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_4, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_main_m_btn_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_main_m_btn_4, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_4, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes scr_main_m_btn_3
    ui->scr_main_m_btn_3 = lv_button_create(ui->scr_main_m_cont);
    lv_obj_set_pos(ui->scr_main_m_btn_3, 208, 1);
    lv_obj_set_size(ui->scr_main_m_btn_3, 100, 42);
    lv_obj_add_flag(ui->scr_main_m_btn_3, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_m_btn_3_label = lv_label_create(ui->scr_main_m_btn_3);
    lv_label_set_text(ui->scr_main_m_btn_3_label, "M3");
    lv_label_set_long_mode(ui->scr_main_m_btn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_m_btn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_m_btn_3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_main_m_btn_3_label, LV_PCT(100));

    //Write style for scr_main_m_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main_m_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_3, lv_color_hex(0xff8f00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_main_m_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_m_btn_3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_m_btn_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_m_btn_3, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_m_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_main_m_btn_3, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_main_m_btn_3, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_3, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_main_m_btn_3, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_main_m_btn_3, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_3, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_main_m_btn_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_main_m_btn_3, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_3, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes scr_main_m_btn_2
    ui->scr_main_m_btn_2 = lv_button_create(ui->scr_main_m_cont);
    lv_obj_set_pos(ui->scr_main_m_btn_2, 105, 1);
    lv_obj_set_size(ui->scr_main_m_btn_2, 100, 42);
    lv_obj_add_flag(ui->scr_main_m_btn_2, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_m_btn_2_label = lv_label_create(ui->scr_main_m_btn_2);
    lv_label_set_text(ui->scr_main_m_btn_2_label, "M2");
    lv_label_set_long_mode(ui->scr_main_m_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_m_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_m_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_main_m_btn_2_label, LV_PCT(100));

    //Write style for scr_main_m_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main_m_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_2, lv_color_hex(0xff8f00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_main_m_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_m_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_m_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_m_btn_2, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_m_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_main_m_btn_2, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_main_m_btn_2, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_2, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_main_m_btn_2, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_main_m_btn_2, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_2, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_main_m_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_main_m_btn_2, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_2, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes scr_main_m_btn_1
    ui->scr_main_m_btn_1 = lv_button_create(ui->scr_main_m_cont);
    lv_obj_set_pos(ui->scr_main_m_btn_1, 2, 1);
    lv_obj_set_size(ui->scr_main_m_btn_1, 100, 42);
    lv_obj_add_flag(ui->scr_main_m_btn_1, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_m_btn_1_label = lv_label_create(ui->scr_main_m_btn_1);
    lv_label_set_text(ui->scr_main_m_btn_1_label, "M1");
    lv_label_set_long_mode(ui->scr_main_m_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_m_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_m_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_main_m_btn_1_label, LV_PCT(100));

    //Write style for scr_main_m_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main_m_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_1, lv_color_hex(0xff8f00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_main_m_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_m_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_m_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_m_btn_1, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_m_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_main_m_btn_1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_main_m_btn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_main_m_btn_1, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_m_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_main_m_btn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_main_m_btn_1, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_main_m_btn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_main_m_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_main_m_btn_1, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_main_m_btn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes scr_main_f_cont
    ui->scr_main_f_cont = lv_obj_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_f_cont, 0, 159);
    lv_obj_set_size(ui->scr_main_f_cont, 378, 110);
    lv_obj_set_scrollbar_mode(ui->scr_main_f_cont, LV_SCROLLBAR_MODE_OFF);

    //Write style for scr_main_f_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scr_main_f_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_f_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_main_f_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_main_f_cont, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_cont, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scr_main_f_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scr_main_f_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_main_f_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_main_f_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_f_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_main_f_btn_8
    ui->scr_main_f_btn_8 = lv_button_create(ui->scr_main_f_cont);
    lv_obj_set_pos(ui->scr_main_f_btn_8, 283, 56);
    lv_obj_set_size(ui->scr_main_f_btn_8, 92, 54);
    lv_obj_add_flag(ui->scr_main_f_btn_8, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_f_btn_8_label = lv_label_create(ui->scr_main_f_btn_8);
    lv_label_set_text(ui->scr_main_f_btn_8_label, "F8");
    lv_label_set_long_mode(ui->scr_main_f_btn_8_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_f_btn_8_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_f_btn_8, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_main_f_btn_8_label, LV_PCT(100));

    //Write style for scr_main_f_btn_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_8, lv_color_hex(0x2F35DA), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_main_f_btn_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_f_btn_8, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_f_btn_8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_f_btn_8, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_f_btn_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_main_f_btn_8, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_8, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_8, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_main_f_btn_8, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_main_f_btn_8, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_8, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_main_f_btn_8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_main_f_btn_8, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_8, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes scr_main_f_btn_7
    ui->scr_main_f_btn_7 = lv_button_create(ui->scr_main_f_cont);
    lv_obj_set_pos(ui->scr_main_f_btn_7, 189, 56);
    lv_obj_set_size(ui->scr_main_f_btn_7, 92, 54);
    lv_obj_add_flag(ui->scr_main_f_btn_7, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_f_btn_7_label = lv_label_create(ui->scr_main_f_btn_7);
    lv_label_set_text(ui->scr_main_f_btn_7_label, "F7");
    lv_label_set_long_mode(ui->scr_main_f_btn_7_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_f_btn_7_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_f_btn_7, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_main_f_btn_7_label, LV_PCT(100));

    //Write style for scr_main_f_btn_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_7, lv_color_hex(0x2F35DA), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_main_f_btn_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_f_btn_7, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_f_btn_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_f_btn_7, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_f_btn_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_main_f_btn_7, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_7, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_7, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_main_f_btn_7, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_main_f_btn_7, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_7, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_main_f_btn_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_main_f_btn_7, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_7, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes scr_main_f_btn_6
    ui->scr_main_f_btn_6 = lv_button_create(ui->scr_main_f_cont);
    lv_obj_set_pos(ui->scr_main_f_btn_6, 95, 56);
    lv_obj_set_size(ui->scr_main_f_btn_6, 92, 54);
    lv_obj_add_flag(ui->scr_main_f_btn_6, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_f_btn_6_label = lv_label_create(ui->scr_main_f_btn_6);
    lv_label_set_text(ui->scr_main_f_btn_6_label, "F6");
    lv_label_set_long_mode(ui->scr_main_f_btn_6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_f_btn_6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_f_btn_6, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_main_f_btn_6_label, LV_PCT(100));

    //Write style for scr_main_f_btn_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_6, lv_color_hex(0x2F35DA), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_main_f_btn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_f_btn_6, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_f_btn_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_f_btn_6, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_f_btn_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_main_f_btn_6, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_6, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_6, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_main_f_btn_6, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_main_f_btn_6, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_6, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_main_f_btn_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_main_f_btn_6, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_6, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes scr_main_f_btn_5
    ui->scr_main_f_btn_5 = lv_button_create(ui->scr_main_f_cont);
    lv_obj_set_pos(ui->scr_main_f_btn_5, 1, 56);
    lv_obj_set_size(ui->scr_main_f_btn_5, 92, 54);
    lv_obj_add_flag(ui->scr_main_f_btn_5, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_f_btn_5_label = lv_label_create(ui->scr_main_f_btn_5);
    lv_label_set_text(ui->scr_main_f_btn_5_label, "F5");
    lv_label_set_long_mode(ui->scr_main_f_btn_5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_f_btn_5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_f_btn_5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_main_f_btn_5_label, LV_PCT(100));

    //Write style for scr_main_f_btn_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_5, lv_color_hex(0x2F35DA), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_main_f_btn_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_f_btn_5, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_f_btn_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_f_btn_5, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_f_btn_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_main_f_btn_5, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_5, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_5, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_main_f_btn_5, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_main_f_btn_5, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_5, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_main_f_btn_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_main_f_btn_5, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_5, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes scr_main_f_btn_4
    ui->scr_main_f_btn_4 = lv_button_create(ui->scr_main_f_cont);
    lv_obj_set_pos(ui->scr_main_f_btn_4, 283, 0);
    lv_obj_set_size(ui->scr_main_f_btn_4, 92, 54);
    lv_obj_add_flag(ui->scr_main_f_btn_4, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_f_btn_4_label = lv_label_create(ui->scr_main_f_btn_4);
    lv_label_set_text(ui->scr_main_f_btn_4_label, "F4");
    lv_label_set_long_mode(ui->scr_main_f_btn_4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_f_btn_4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_f_btn_4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_main_f_btn_4_label, LV_PCT(100));

    //Write style for scr_main_f_btn_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_4, lv_color_hex(0x2F35DA), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_main_f_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_f_btn_4, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_f_btn_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_f_btn_4, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_f_btn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_main_f_btn_4, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_4, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_4, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_main_f_btn_4, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_main_f_btn_4, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_4, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_main_f_btn_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_main_f_btn_4, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_4, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes scr_main_f_btn_3
    ui->scr_main_f_btn_3 = lv_button_create(ui->scr_main_f_cont);
    lv_obj_set_pos(ui->scr_main_f_btn_3, 189, 0);
    lv_obj_set_size(ui->scr_main_f_btn_3, 92, 54);
    lv_obj_add_flag(ui->scr_main_f_btn_3, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_f_btn_3_label = lv_label_create(ui->scr_main_f_btn_3);
    lv_label_set_text(ui->scr_main_f_btn_3_label, "F3");
    lv_label_set_long_mode(ui->scr_main_f_btn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_f_btn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_f_btn_3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_main_f_btn_3_label, LV_PCT(100));

    //Write style for scr_main_f_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_3, lv_color_hex(0x2F35DA), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_main_f_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_f_btn_3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_f_btn_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_f_btn_3, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_f_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_main_f_btn_3, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_3, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_3, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_main_f_btn_3, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_main_f_btn_3, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_3, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_main_f_btn_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_main_f_btn_3, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_3, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes scr_main_f_btn_2
    ui->scr_main_f_btn_2 = lv_button_create(ui->scr_main_f_cont);
    lv_obj_set_pos(ui->scr_main_f_btn_2, 95, 0);
    lv_obj_set_size(ui->scr_main_f_btn_2, 92, 54);
    lv_obj_add_flag(ui->scr_main_f_btn_2, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_f_btn_2_label = lv_label_create(ui->scr_main_f_btn_2);
    lv_label_set_text(ui->scr_main_f_btn_2_label, "F2");
    lv_label_set_long_mode(ui->scr_main_f_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_f_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_f_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_main_f_btn_2_label, LV_PCT(100));

    //Write style for scr_main_f_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_2, lv_color_hex(0x2F35DA), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_main_f_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_f_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_f_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_f_btn_2, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_f_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_main_f_btn_2, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_2, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_2, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_main_f_btn_2, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_main_f_btn_2, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_2, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_main_f_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_main_f_btn_2, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_2, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes scr_main_f_btn_1
    ui->scr_main_f_btn_1 = lv_button_create(ui->scr_main_f_cont);
    lv_obj_set_pos(ui->scr_main_f_btn_1, 1, 0);
    lv_obj_set_size(ui->scr_main_f_btn_1, 92, 54);
    lv_obj_add_flag(ui->scr_main_f_btn_1, LV_OBJ_FLAG_SCROLLABLE);
    ui->scr_main_f_btn_1_label = lv_label_create(ui->scr_main_f_btn_1);
    lv_label_set_text(ui->scr_main_f_btn_1_label, "F1");
    lv_label_set_long_mode(ui->scr_main_f_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_f_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_f_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_main_f_btn_1_label, LV_PCT(100));

    //Write style for scr_main_f_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_1, lv_color_hex(0x2F35DA), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_main_f_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_f_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_f_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_f_btn_1, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_f_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_main_f_btn_1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->scr_main_f_btn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->scr_main_f_btn_1, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_f_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->scr_main_f_btn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->scr_main_f_btn_1, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_main_f_btn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_main_f_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_main_f_btn_1, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_main_f_btn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes scr_main_kg_label
    ui->scr_main_kg_label = lv_label_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_kg_label, 430, 60);
    lv_obj_set_size(ui->scr_main_kg_label, 46, 51);
    lv_label_set_text(ui->scr_main_kg_label, "kg");
    lv_label_set_long_mode(ui->scr_main_kg_label, LV_LABEL_LONG_WRAP);

    //Write style for scr_main_kg_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scr_main_kg_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_kg_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_kg_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_kg_label, &lv_font_Oswald_Reg_40, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_kg_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scr_main_kg_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scr_main_kg_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_kg_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_main_kg_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scr_main_kg_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_main_kg_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scr_main_kg_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_main_kg_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_kg_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_main_knet_data_btn
    ui->scr_main_knet_data_btn = lv_button_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_knet_data_btn, 330, 76);
    lv_obj_set_size(ui->scr_main_knet_data_btn, 150, 39);
    ui->scr_main_knet_data_btn_label = lv_label_create(ui->scr_main_knet_data_btn);
    lv_label_set_text(ui->scr_main_knet_data_btn_label, "-150.000");
    lv_label_set_long_mode(ui->scr_main_knet_data_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_knet_data_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_knet_data_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_main_knet_data_btn_label, LV_PCT(100));

    //Write style for scr_main_knet_data_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main_knet_data_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_main_knet_data_btn, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scr_main_knet_data_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scr_main_knet_data_btn, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scr_main_knet_data_btn, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_knet_data_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_knet_data_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_knet_data_btn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_knet_data_btn, &lv_font_Bebas_40, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_knet_data_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_knet_data_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_main_dara_data_btn
    ui->scr_main_dara_data_btn = lv_button_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_dara_data_btn, 180, 76);
    lv_obj_set_size(ui->scr_main_dara_data_btn, 150, 39);
    ui->scr_main_dara_data_btn_label = lv_label_create(ui->scr_main_dara_data_btn);
    lv_label_set_text(ui->scr_main_dara_data_btn_label, "-150.000");
    lv_label_set_long_mode(ui->scr_main_dara_data_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_dara_data_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_dara_data_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_main_dara_data_btn_label, LV_PCT(100));

    //Write style for scr_main_dara_data_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main_dara_data_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_main_dara_data_btn, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scr_main_dara_data_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scr_main_dara_data_btn, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scr_main_dara_data_btn, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_dara_data_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_dara_data_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_dara_data_btn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_dara_data_btn, &lv_font_Bebas_40, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_dara_data_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_dara_data_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_main_brut_data_btn
    ui->scr_main_brut_data_btn = lv_button_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_brut_data_btn, 30, 76);
    lv_obj_set_size(ui->scr_main_brut_data_btn, 150, 39);
    ui->scr_main_brut_data_btn_label = lv_label_create(ui->scr_main_brut_data_btn);
    lv_label_set_text(ui->scr_main_brut_data_btn_label, "-150.000");
    lv_label_set_long_mode(ui->scr_main_brut_data_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_brut_data_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_brut_data_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_main_brut_data_btn_label, LV_PCT(100));

    //Write style for scr_main_brut_data_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main_brut_data_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_main_brut_data_btn, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scr_main_brut_data_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scr_main_brut_data_btn, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scr_main_brut_data_btn, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_brut_data_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_brut_data_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_brut_data_btn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_brut_data_btn, &lv_font_Bebas_40, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_brut_data_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_brut_data_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_main_sag_label
    ui->scr_main_sag_label = lv_label_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_sag_label, 454, 125);
    lv_obj_set_size(ui->scr_main_sag_label, 25, 26);
    lv_label_set_text(ui->scr_main_sag_label, "" LV_SYMBOL_RIGHT " ");
    lv_label_set_long_mode(ui->scr_main_sag_label, LV_LABEL_LONG_WRAP);

    //Write style for scr_main_sag_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scr_main_sag_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_sag_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_sag_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_sag_label, &lv_font_Bebas_25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_sag_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scr_main_sag_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scr_main_sag_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_sag_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_main_sag_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scr_main_sag_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_main_sag_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scr_main_sag_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_main_sag_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_sag_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_main_sol_label
    ui->scr_main_sol_label = lv_label_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_sol_label, 5, 124);
    lv_obj_set_size(ui->scr_main_sol_label, 25, 25);
    lv_label_set_text(ui->scr_main_sol_label, "" LV_SYMBOL_LEFT " ");
    lv_label_set_long_mode(ui->scr_main_sol_label, LV_LABEL_LONG_WRAP);

    //Write style for scr_main_sol_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scr_main_sol_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_sol_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_sol_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_sol_label, &lv_font_Bebas_25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_sol_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scr_main_sol_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scr_main_sol_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_sol_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_main_sol_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scr_main_sol_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_main_sol_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scr_main_sol_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_main_sol_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_sol_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_main_net_label
    ui->scr_main_net_label = lv_label_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_net_label, 380, 60);
    lv_obj_set_size(ui->scr_main_net_label, 55, 12);
    lv_label_set_text(ui->scr_main_net_label, "NET KG");
    lv_label_set_long_mode(ui->scr_main_net_label, LV_LABEL_LONG_WRAP);

    //Write style for scr_main_net_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scr_main_net_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_net_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_net_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_net_label, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_net_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scr_main_net_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scr_main_net_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_net_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_main_net_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scr_main_net_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_main_net_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scr_main_net_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_main_net_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_net_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_main_dara_label
    ui->scr_main_dara_label = lv_label_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_dara_label, 231, 60);
    lv_obj_set_size(ui->scr_main_dara_label, 55, 12);
    lv_label_set_text(ui->scr_main_dara_label, "DARA KG\n");
    lv_label_set_long_mode(ui->scr_main_dara_label, LV_LABEL_LONG_WRAP);

    //Write style for scr_main_dara_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scr_main_dara_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_dara_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_dara_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_dara_label, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_dara_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scr_main_dara_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scr_main_dara_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_dara_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_main_dara_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scr_main_dara_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_main_dara_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scr_main_dara_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_main_dara_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_dara_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_main_brut_label
    ui->scr_main_brut_label = lv_label_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_brut_label, 80, 60);
    lv_obj_set_size(ui->scr_main_brut_label, 55, 12);
    lv_label_set_text(ui->scr_main_brut_label, "BRÜT KG");
    lv_label_set_long_mode(ui->scr_main_brut_label, LV_LABEL_LONG_WRAP);

    //Write style for scr_main_brut_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scr_main_brut_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_brut_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_brut_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_brut_label, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_brut_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scr_main_brut_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scr_main_brut_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_brut_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_main_brut_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scr_main_brut_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_main_brut_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scr_main_brut_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_main_brut_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_brut_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_main_menu_btn
    ui->scr_main_menu_btn = lv_button_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_menu_btn, 399, 26);
    lv_obj_set_size(ui->scr_main_menu_btn, 80, 32);
    ui->scr_main_menu_btn_label = lv_label_create(ui->scr_main_menu_btn);
    lv_label_set_text(ui->scr_main_menu_btn_label, "MENÜ");
    lv_label_set_long_mode(ui->scr_main_menu_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_menu_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_menu_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_main_menu_btn_label, LV_PCT(100));

    //Write style for scr_main_menu_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main_menu_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_main_menu_btn, lv_color_hex(0x2F35DA), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_menu_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_main_menu_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_menu_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_menu_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_menu_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_menu_btn, &lv_font_Oswald_Reg_15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_menu_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_menu_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_main_urun_btn
    ui->scr_main_urun_btn = lv_button_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_urun_btn, 83, 26);
    lv_obj_set_size(ui->scr_main_urun_btn, 314, 32);
    ui->scr_main_urun_btn_label = lv_label_create(ui->scr_main_urun_btn);
    lv_label_set_text(ui->scr_main_urun_btn_label, "ÜRÜN İSMİ");
    lv_label_set_long_mode(ui->scr_main_urun_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_urun_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_urun_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_main_urun_btn_label, LV_PCT(100));

    //Write style for scr_main_urun_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main_urun_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_main_urun_btn, lv_color_hex(0xff0000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_urun_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_main_urun_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_urun_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_urun_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_urun_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_urun_btn, &lv_font_Oswald_Reg_15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_urun_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_urun_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_main_kod_btn
    ui->scr_main_kod_btn = lv_button_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_kod_btn, 1, 26);
    lv_obj_set_size(ui->scr_main_kod_btn, 80, 32);
    ui->scr_main_kod_btn_label = lv_label_create(ui->scr_main_kod_btn);
    lv_label_set_text(ui->scr_main_kod_btn_label, "2700001");
    lv_label_set_long_mode(ui->scr_main_kod_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_kod_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_kod_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_main_kod_btn_label, LV_PCT(100));

    //Write style for scr_main_kod_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main_kod_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_main_kod_btn, lv_color_hex(0x2F35DA), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_kod_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_main_kod_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_kod_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_kod_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_kod_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_kod_btn, &lv_font_Oswald_Reg_15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_kod_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_kod_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_main_bar_cont
    ui->scr_main_bar_cont = lv_obj_create(ui->scr_main);
    lv_obj_set_pos(ui->scr_main_bar_cont, 0, 0);
    lv_obj_set_size(ui->scr_main_bar_cont, 480, 25);
    lv_obj_set_scrollbar_mode(ui->scr_main_bar_cont, LV_SCROLLBAR_MODE_OFF);

    //Write style for scr_main_bar_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scr_main_bar_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_bar_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_main_bar_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_main_bar_cont, lv_color_hex(0x2F35DA), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_main_bar_cont, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scr_main_bar_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scr_main_bar_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_main_bar_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_main_bar_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_bar_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_main_tarih_btn
    ui->scr_main_tarih_btn = lv_button_create(ui->scr_main_bar_cont);
    lv_obj_set_pos(ui->scr_main_tarih_btn, 405, 0);
    lv_obj_set_size(ui->scr_main_tarih_btn, 70, 25);
    ui->scr_main_tarih_btn_label = lv_label_create(ui->scr_main_tarih_btn);
    lv_label_set_text(ui->scr_main_tarih_btn_label, "12-12-2025");
    lv_label_set_long_mode(ui->scr_main_tarih_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_tarih_btn_label, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_tarih_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_main_tarih_btn_label, LV_PCT(100));

    //Write style for scr_main_tarih_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main_tarih_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_main_tarih_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_tarih_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_tarih_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_tarih_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_tarih_btn, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_tarih_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_tarih_btn, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_main_saat_btn
    ui->scr_main_saat_btn = lv_button_create(ui->scr_main_bar_cont);
    lv_obj_set_pos(ui->scr_main_saat_btn, 340, 0);
    lv_obj_set_size(ui->scr_main_saat_btn, 55, 25);
    ui->scr_main_saat_btn_label = lv_label_create(ui->scr_main_saat_btn);
    lv_label_set_text(ui->scr_main_saat_btn_label, "12:00:00");
    lv_label_set_long_mode(ui->scr_main_saat_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_saat_btn_label, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_saat_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_main_saat_btn_label, LV_PCT(100));

    //Write style for scr_main_saat_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_main_saat_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_main_saat_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_main_saat_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_saat_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_main_saat_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_saat_btn, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_saat_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_saat_btn, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_main_wifi_sta_imgbt
    ui->scr_main_wifi_sta_imgbt = lv_imagebutton_create(ui->scr_main_bar_cont);
    lv_obj_set_pos(ui->scr_main_wifi_sta_imgbt, 5, 0);
    lv_obj_set_size(ui->scr_main_wifi_sta_imgbt, 25, 25);
    lv_obj_add_flag(ui->scr_main_wifi_sta_imgbt, LV_OBJ_FLAG_CHECKABLE);
    lv_imagebutton_set_src(ui->scr_main_wifi_sta_imgbt, LV_IMAGEBUTTON_STATE_RELEASED, &_wifi_lost_RGB565A8_25x25, NULL, NULL);
    ui->scr_main_wifi_sta_imgbt_label = lv_label_create(ui->scr_main_wifi_sta_imgbt);
    lv_label_set_text(ui->scr_main_wifi_sta_imgbt_label, "");
    lv_label_set_long_mode(ui->scr_main_wifi_sta_imgbt_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_main_wifi_sta_imgbt_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_main_wifi_sta_imgbt, 0, LV_STATE_DEFAULT);

    //Write style for scr_main_wifi_sta_imgbt, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->scr_main_wifi_sta_imgbt, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_main_wifi_sta_imgbt, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_main_wifi_sta_imgbt, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_main_wifi_sta_imgbt, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_main_wifi_sta_imgbt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_main_wifi_sta_imgbt, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_image_recolor_opa(ui->scr_main_wifi_sta_imgbt, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_image_opa(ui->scr_main_wifi_sta_imgbt, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->scr_main_wifi_sta_imgbt, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->scr_main_wifi_sta_imgbt, &lv_font_Oswald_Reg_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->scr_main_wifi_sta_imgbt, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->scr_main_wifi_sta_imgbt, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for scr_main_wifi_sta_imgbt, Part: LV_PART_MAIN, State: LV_IMAGEBUTTON_STATE_RELEASED.
    lv_obj_set_style_image_recolor_opa(ui->scr_main_wifi_sta_imgbt, 0, LV_PART_MAIN|LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_style_image_opa(ui->scr_main_wifi_sta_imgbt, 255, LV_PART_MAIN|LV_IMAGEBUTTON_STATE_RELEASED);

    //The custom code of scr_main.


    //Update current screen layout.
    lv_obj_update_layout(ui->scr_main);

    //Init events for screen.
    events_init_scr_main(ui);
}
