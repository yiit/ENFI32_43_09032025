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


void setup_scr_scr_logo(lv_ui *ui)
{
    //Write codes scr_logo
    ui->scr_logo = lv_obj_create(NULL);
    lv_obj_set_size(ui->scr_logo, 480, 272);
    lv_obj_set_scrollbar_mode(ui->scr_logo, LV_SCROLLBAR_MODE_OFF);

    //Write style for scr_logo, Part: LV_PART_MAIN, State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_logo, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_logo, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_logo, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_logo_label_1
    ui->scr_logo_label_1 = lv_label_create(ui->scr_logo);
    lv_obj_set_pos(ui->scr_logo_label_1, 356, 251);
    lv_obj_set_size(ui->scr_logo_label_1, 120, 17);
    lv_label_set_text(ui->scr_logo_label_1, "Version : 1.0.1 ");
    lv_label_set_long_mode(ui->scr_logo_label_1, LV_LABEL_LONG_WRAP);

    //Write style for scr_logo_label_1, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_logo_label_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_logo_label_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_logo_label_1, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_logo_label_1, &lv_font_Oswald_Reg_12, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_logo_label_1, 179, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_letter_space(ui->scr_logo_label_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_line_space(ui->scr_logo_label_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_logo_label_1, LV_TEXT_ALIGN_RIGHT, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_logo_label_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_logo_label_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_logo_label_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_bottom(ui->scr_logo_label_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_logo_label_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_logo_label_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_logo_bar_1
    ui->scr_logo_bar_1 = lv_bar_create(ui->scr_logo);
    lv_obj_set_pos(ui->scr_logo_bar_1, 90, 195);
    lv_obj_set_size(ui->scr_logo_bar_1, 300, 6);
    lv_obj_set_style_anim_duration(ui->scr_logo_bar_1, 1000, 0);
    lv_bar_set_mode(ui->scr_logo_bar_1, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->scr_logo_bar_1, 0, 100);
    lv_bar_set_value(ui->scr_logo_bar_1, 0, LV_ANIM_ON);

    //Write style for scr_logo_bar_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scr_logo_bar_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_logo_bar_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_logo_bar_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_logo_bar_1, Part: LV_PART_INDICATOR, State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_logo_bar_1, 255, static_cast<int>(LV_PART_INDICATOR)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_logo_bar_1, lv_color_hex(0x0023F5), static_cast<int>(LV_PART_INDICATOR)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_logo_bar_1, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_INDICATOR)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_logo_bar_1, 10, static_cast<int>(LV_PART_INDICATOR)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_logo_img_1
    ui->scr_logo_img_1 = lv_image_create(ui->scr_logo);
    lv_obj_set_pos(ui->scr_logo_img_1, 100, 93);
    lv_obj_set_size(ui->scr_logo_img_1, 280, 68);
    lv_obj_add_flag(ui->scr_logo_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->scr_logo_img_1, &_endutek_logo_RGB565A8_280x68);
    lv_image_set_pivot(ui->scr_logo_img_1, 50,50);
    lv_image_set_rotation(ui->scr_logo_img_1, 0);

    //Write style for scr_logo_img_1, Part: LV_PART_MAIN, State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_image_recolor_opa(ui->scr_logo_img_1, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_image_opa(ui->scr_logo_img_1, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //The custom code of scr_logo.


    //Update current screen layout.
    lv_obj_update_layout(ui->scr_logo);

    //Init events for screen.
    events_init_scr_logo(ui);
}
