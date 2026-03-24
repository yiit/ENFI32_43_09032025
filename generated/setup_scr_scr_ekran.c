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



void setup_scr_scr_ekran(lv_ui *ui)
{
    //Write codes scr_ekran
    ui->scr_ekran = lv_obj_create(NULL);
    lv_obj_set_size(ui->scr_ekran, 480, 272);
    lv_obj_set_scrollbar_mode(ui->scr_ekran, LV_SCROLLBAR_MODE_OFF);

    //Write style for scr_ekran, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_ekran, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_ekran, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_ekran, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_ekran_btn_1
    ui->scr_ekran_btn_1 = lv_button_create(ui->scr_ekran);
    lv_obj_set_pos(ui->scr_ekran_btn_1, 20, 17);
    lv_obj_set_size(ui->scr_ekran_btn_1, 140, 68);
    ui->scr_ekran_btn_1_label = lv_label_create(ui->scr_ekran_btn_1);
    lv_label_set_text(ui->scr_ekran_btn_1_label, "" LV_SYMBOL_REFRESH "  \n\nEKRAN YÖNÜNÜ ÇEVİR\n");
    lv_label_set_long_mode(ui->scr_ekran_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_ekran_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_ekran_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scr_ekran_btn_1_label, LV_PCT(100));

    //Write style for scr_ekran_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_ekran_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_ekran_btn_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_ekran_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_ekran_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_ekran_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_ekran_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_ekran_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_ekran_btn_1, &lv_font_Oswald_Reg_13, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_ekran_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_ekran_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scr_ekran_slider_1
    ui->scr_ekran_slider_1 = lv_slider_create(ui->scr_ekran);
    lv_obj_set_pos(ui->scr_ekran_slider_1, 20, 136);
    lv_obj_set_size(ui->scr_ekran_slider_1, 300, 8);
    lv_slider_set_range(ui->scr_ekran_slider_1, 0, 100);
    lv_slider_set_mode(ui->scr_ekran_slider_1, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->scr_ekran_slider_1, 50, LV_ANIM_OFF);

    //Write style for scr_ekran_slider_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_ekran_slider_1, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_ekran_slider_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_ekran_slider_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_ekran_slider_1, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->scr_ekran_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_ekran_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scr_ekran_slider_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_ekran_slider_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_ekran_slider_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_ekran_slider_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_ekran_slider_1, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for scr_ekran_slider_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_ekran_slider_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_ekran_slider_1, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_ekran_slider_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_ekran_slider_1, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes scr_ekran_label_1
    ui->scr_ekran_label_1 = lv_label_create(ui->scr_ekran);
    lv_obj_set_pos(ui->scr_ekran_label_1, 75, 102);
    lv_obj_set_size(ui->scr_ekran_label_1, 180, 23);
    lv_label_set_text(ui->scr_ekran_label_1, "EKRAN PARLAKLIĞI");
    lv_label_set_long_mode(ui->scr_ekran_label_1, LV_LABEL_LONG_WRAP);

    //Write style for scr_ekran_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scr_ekran_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_ekran_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_ekran_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_ekran_label_1, &lv_font_Oswald_Reg_13, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_ekran_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scr_ekran_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scr_ekran_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scr_ekran_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_ekran_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scr_ekran_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_ekran_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scr_ekran_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_ekran_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_ekran_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of scr_ekran.


    //Update current screen layout.
    lv_obj_update_layout(ui->scr_ekran);

}
