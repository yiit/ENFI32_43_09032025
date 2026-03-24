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


void setup_scr_scr_wifi_sta(lv_ui *ui)
{
    //Write codes scr_wifi_sta
    ui->scr_wifi_sta = lv_obj_create(NULL);
    lv_obj_set_size(ui->scr_wifi_sta, 480, 272);
    lv_obj_set_scrollbar_mode(ui->scr_wifi_sta, LV_SCROLLBAR_MODE_OFF);

    //Write style for scr_wifi_sta, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_wifi_sta, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_wifi_sta, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_wifi_sta, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);

    //Write codes scr_wifi_sta_cb_1
    ui->scr_wifi_sta_cb_1 = lv_checkbox_create(ui->scr_wifi_sta);
    lv_obj_set_pos(ui->scr_wifi_sta_cb_1, 66, 69);
    lv_checkbox_set_text(ui->scr_wifi_sta_cb_1, "checkbox");

    //Write style for scr_wifi_sta_cb_1, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_top(ui->scr_wifi_sta_cb_1, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_wifi_sta_cb_1, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_wifi_sta_cb_1, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scr_wifi_sta_cb_1, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_wifi_sta_cb_1, lv_color_hex(0x0D3055), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_wifi_sta_cb_1, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_wifi_sta_cb_1, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scr_wifi_sta_cb_1, 2, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_wifi_sta_cb_1, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_wifi_sta_cb_1, 6, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_wifi_sta_cb_1, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_wifi_sta_cb_1, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_wifi_sta_cb_1, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_wifi_sta_cb_1, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);

    //Write style for scr_wifi_sta_cb_1, Part: static_cast<int>(LV_PART_INDICATOR), State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_all(ui->scr_wifi_sta_cb_1, 3, static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_wifi_sta_cb_1, 2, static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scr_wifi_sta_cb_1, 255, static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scr_wifi_sta_cb_1, lv_color_hex(0x2195f6), static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scr_wifi_sta_cb_1, LV_BORDER_SIDE_FULL, static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_wifi_sta_cb_1, 6, static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_wifi_sta_cb_1, 255, static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_wifi_sta_cb_1, lv_color_hex(0xffffff), static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_wifi_sta_cb_1, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);

    //Write codes scr_wifi_sta_cb_2
    ui->scr_wifi_sta_cb_2 = lv_checkbox_create(ui->scr_wifi_sta);
    lv_obj_set_pos(ui->scr_wifi_sta_cb_2, 66, 107);
    lv_checkbox_set_text(ui->scr_wifi_sta_cb_2, "checkbox");

    //Write style for scr_wifi_sta_cb_2, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_top(ui->scr_wifi_sta_cb_2, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_wifi_sta_cb_2, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_wifi_sta_cb_2, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scr_wifi_sta_cb_2, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_wifi_sta_cb_2, lv_color_hex(0x0D3055), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_wifi_sta_cb_2, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_wifi_sta_cb_2, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scr_wifi_sta_cb_2, 2, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_wifi_sta_cb_2, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_wifi_sta_cb_2, 6, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_wifi_sta_cb_2, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_wifi_sta_cb_2, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_wifi_sta_cb_2, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_wifi_sta_cb_2, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);

    //Write style for scr_wifi_sta_cb_2, Part: static_cast<int>(LV_PART_INDICATOR), State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_all(ui->scr_wifi_sta_cb_2, 3, static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_wifi_sta_cb_2, 2, static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scr_wifi_sta_cb_2, 255, static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scr_wifi_sta_cb_2, lv_color_hex(0x2195f6), static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scr_wifi_sta_cb_2, LV_BORDER_SIDE_FULL, static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_wifi_sta_cb_2, 6, static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_wifi_sta_cb_2, 255, static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_wifi_sta_cb_2, lv_color_hex(0xffffff), static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_wifi_sta_cb_2, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);

    //Write codes scr_wifi_sta_img_1
    ui->scr_wifi_sta_img_1 = lv_image_create(ui->scr_wifi_sta);
    lv_obj_set_pos(ui->scr_wifi_sta_img_1, 222, 69);
    lv_obj_set_size(ui->scr_wifi_sta_img_1, 32, 32);
    lv_obj_add_flag(ui->scr_wifi_sta_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->scr_wifi_sta_img_1, &_wifi_RGB565A8_27x27);
    lv_image_set_pivot(ui->scr_wifi_sta_img_1, 50,50);
    lv_image_set_rotation(ui->scr_wifi_sta_img_1, 0);

    //Write style for scr_wifi_sta_img_1, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->scr_wifi_sta_img_1, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->scr_wifi_sta_img_1, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);

    //Write codes scr_wifi_sta_img_2
    ui->scr_wifi_sta_img_2 = lv_image_create(ui->scr_wifi_sta);
    lv_obj_set_pos(ui->scr_wifi_sta_img_2, 222, 105);
    lv_obj_set_size(ui->scr_wifi_sta_img_2, 32, 32);
    lv_obj_add_flag(ui->scr_wifi_sta_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->scr_wifi_sta_img_2, &_wifi_RGB565A8_27x27);
    lv_image_set_pivot(ui->scr_wifi_sta_img_2, 50,50);
    lv_image_set_rotation(ui->scr_wifi_sta_img_2, 0);

    //Write style for scr_wifi_sta_img_2, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->scr_wifi_sta_img_2, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->scr_wifi_sta_img_2, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);

    //Write codes scr_wifi_sta_w_img
    ui->scr_wifi_sta_w_img = lv_image_create(ui->scr_wifi_sta);
    lv_obj_set_pos(ui->scr_wifi_sta_w_img, 222, 144);
    lv_obj_set_size(ui->scr_wifi_sta_w_img, 32, 32);
    lv_obj_add_flag(ui->scr_wifi_sta_w_img, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->scr_wifi_sta_w_img, &_wifi_RGB565A8_27x27);
    lv_image_set_pivot(ui->scr_wifi_sta_w_img, 50,50);
    lv_image_set_rotation(ui->scr_wifi_sta_w_img, 0);

    //Write style for scr_wifi_sta_w_img, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->scr_wifi_sta_w_img, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->scr_wifi_sta_w_img, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);

    //Write codes scr_wifi_sta_w_cb
    ui->scr_wifi_sta_w_cb = lv_checkbox_create(ui->scr_wifi_sta);
    lv_obj_set_pos(ui->scr_wifi_sta_w_cb, 66, 145);
    lv_checkbox_set_text(ui->scr_wifi_sta_w_cb, "checkbox");

    //Write style for scr_wifi_sta_w_cb, Part: static_cast<int>(LV_PART_MAIN), State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_top(ui->scr_wifi_sta_w_cb, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scr_wifi_sta_w_cb, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scr_wifi_sta_w_cb, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scr_wifi_sta_w_cb, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scr_wifi_sta_w_cb, lv_color_hex(0x0D3055), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scr_wifi_sta_w_cb, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scr_wifi_sta_w_cb, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scr_wifi_sta_w_cb, 2, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_wifi_sta_w_cb, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_wifi_sta_w_cb, 6, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_wifi_sta_w_cb, 255, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_wifi_sta_w_cb, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_wifi_sta_w_cb, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scr_wifi_sta_w_cb, 0, static_cast<int>(LV_PART_MAIN)|LV_STATE_DEFAULT);

    //Write style for scr_wifi_sta_w_cb, Part: static_cast<int>(LV_PART_INDICATOR), State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_all(ui->scr_wifi_sta_w_cb, 3, static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scr_wifi_sta_w_cb, 2, static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scr_wifi_sta_w_cb, 255, static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scr_wifi_sta_w_cb, lv_color_hex(0x2195f6), static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scr_wifi_sta_w_cb, LV_BORDER_SIDE_FULL, static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scr_wifi_sta_w_cb, 6, static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scr_wifi_sta_w_cb, 255, static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scr_wifi_sta_w_cb, lv_color_hex(0xffffff), static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scr_wifi_sta_w_cb, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_INDICATOR)|LV_STATE_DEFAULT);

    //The custom code of scr_wifi_sta.


    //Update current screen layout.
    lv_obj_update_layout(ui->scr_wifi_sta);

}
