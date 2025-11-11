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

static void urun_bul_cb(lv_event_t *e)
{
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    const char *arama = lv_textarea_get_text(ui->scr_ubtn_u_ta);

    // Önce önceki butonları temizle
    lv_obj_clean(ui->scr_ubtn_u_cont);

    // Yeniden oluştur - arama filtresiyle
    create_urun_buttons(ui, ui->scr_ubtn_u_cont,
                        ui->scr_ubtn_u_no_label,
                        ui->scr_ubtn_u_name_btn,
                        ui->scr_ubtn_u_name_btn_label,
                        2,
                        arama);
}


void setup_scr_scr_ubtn(lv_ui *ui)
{
    //Write codes scr_ubtn
    ui->scr_ubtn = lv_obj_create(NULL);
    lv_obj_set_size(ui->scr_ubtn, 480, 272);
    lv_obj_set_scrollbar_mode(ui->scr_ubtn, LV_SCROLLBAR_MODE_OFF);

    //Write style for scr_ubtn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_ubtn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_ubtn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_ubtn_u_ta
    ui->scr_ubtn_u_ta = lv_textarea_create(ui->scr_ubtn);
    lv_obj_set_pos(ui->scr_ubtn_u_ta, 60, 28);
    lv_obj_set_size(ui->scr_ubtn_u_ta, 300, 30);
    lv_textarea_set_text(ui->scr_ubtn_u_ta, "");
    lv_textarea_set_placeholder_text(ui->scr_ubtn_u_ta, "ÜRÜN İSMİ GİRİNİZ");
    lv_textarea_set_password_bullet(ui->scr_ubtn_u_ta, "*");
    lv_textarea_set_password_mode(ui->scr_ubtn_u_ta, false);
    lv_textarea_set_one_line(ui->scr_ubtn_u_ta, true);
    lv_textarea_set_accepted_chars(ui->scr_ubtn_u_ta, "");
    lv_textarea_set_max_length(ui->scr_ubtn_u_ta, 48);
#if LV_USE_KEYBOARD
    // Klavye oluştur ve sadece text moda ayarla
    //ui->g_kb_top_layer = lv_keyboard_create(ui->scr_ubtn);
    lv_keyboard_set_mode(ui->g_kb_top_layer, LV_KEYBOARD_MODE_TEXT_UPPER);
    lv_obj_set_size(ui->g_kb_top_layer, 480, 148); // Özel genişlik ve yükseklik ayarla
    lv_obj_align(ui->g_kb_top_layer, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    lv_keyboard_set_textarea(ui->g_kb_top_layer, ui->scr_ubtn_u_ta);
    lv_obj_add_event_cb(ui->scr_ubtn_u_ta, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif

    //Write style for scr_ubtn_u_ta, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_text_color(ui->scr_ubtn_u_ta, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_ubtn_u_ta, &lv_font_Oswald_Reg_20, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_ta, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_letter_space(ui->scr_ubtn_u_ta, 1, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_ubtn_u_ta, LV_TEXT_ALIGN_LEFT, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_ta, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_ubtn_u_ta, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn_u_ta, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_ubtn_u_ta, 2, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_opa(ui->scr_ubtn_u_ta, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_color(ui->scr_ubtn_u_ta, lv_color_hex(0x000000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_side(ui->scr_ubtn_u_ta, LV_BORDER_SIDE_FULL, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_ta, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_ubtn_u_ta, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_ubtn_u_ta, 4, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_ubtn_u_ta, 4, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_ubtn_u_ta, 4, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_ubtn_u_ta, Part: LV_PART_SCROLLBAR, State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_ta, 255, LV_PART_SCROLLBAR|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_ubtn_u_ta, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn_u_ta, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_ubtn_u_ta, 0, LV_PART_SCROLLBAR|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_ubtn_u_cont
    ui->scr_ubtn_u_cont = lv_obj_create(ui->scr_ubtn);
    lv_obj_set_pos(ui->scr_ubtn_u_cont, 0, 76);
    lv_obj_set_size(ui->scr_ubtn_u_cont, 365, 195);
    lv_obj_set_scrollbar_mode(ui->scr_ubtn_u_cont, LV_SCROLLBAR_MODE_AUTO);
    lv_obj_add_flag(ui->scr_ubtn_u_cont, LV_OBJ_FLAG_SCROLLABLE);

    //Write style for scr_ubtn_u_cont, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_ubtn_u_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_ubtn_u_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_cont, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_ubtn_u_cont, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn_u_cont, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_ubtn_u_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_ubtn_u_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_ubtn_u_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_bottom(ui->scr_ubtn_u_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //create_urun_buttons(ui, ui->scr_ubtn_u_cont);
    //create_urun_buttons(ui, ui->scr_ubtn_u_cont, ui->scr_ubtn_u_no_label, ui->scr_ubtn_u_name_btn, ui->scr_ubtn_u_name_btn_label, 2); // 📌 Ürün butonlarını oluştur

    create_urun_buttons(ui, ui->scr_ubtn_u_cont,
        ui->scr_ubtn_u_no_label,
        ui->scr_ubtn_u_name_btn,
        ui->scr_ubtn_u_name_btn_label,
        2,
        NULL); // NULL: Tüm ürünleri göster


    //Write codes scr_ubtn_u_bar_cont
    ui->scr_ubtn_u_bar_cont = lv_obj_create(ui->scr_ubtn);
    lv_obj_set_pos(ui->scr_ubtn_u_bar_cont, 0, 0);
    lv_obj_set_size(ui->scr_ubtn_u_bar_cont, 480, 25);
    lv_obj_set_scrollbar_mode(ui->scr_ubtn_u_bar_cont, LV_SCROLLBAR_MODE_OFF);

    //Write style for scr_ubtn_u_bar_cont, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_ubtn_u_bar_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_ubtn_u_bar_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_bar_cont, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_color(ui->scr_ubtn_u_bar_cont, lv_color_hex(0x0023F5), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn_u_bar_cont, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_ubtn_u_bar_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_bottom(ui->scr_ubtn_u_bar_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_ubtn_u_bar_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_ubtn_u_bar_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_bar_cont, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_ubtn_u_duzenle_label
    ui->scr_ubtn_u_duzenle_label = lv_label_create(ui->scr_ubtn_u_bar_cont);
    lv_obj_set_pos(ui->scr_ubtn_u_duzenle_label, 60, 0);
    lv_obj_set_size(ui->scr_ubtn_u_duzenle_label, 130, 21);
    lv_label_set_text(ui->scr_ubtn_u_duzenle_label, "DÜZENLEME EKRANI");
    lv_label_set_long_mode(ui->scr_ubtn_u_duzenle_label, LV_LABEL_LONG_WRAP);

    //Write style for scr_ubtn_u_duzenle_label, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_ubtn_u_duzenle_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_ubtn_u_duzenle_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_ubtn_u_duzenle_label, lv_color_hex(0xFFFFFF), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_ubtn_u_duzenle_label, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_duzenle_label, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_letter_space(ui->scr_ubtn_u_duzenle_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_line_space(ui->scr_ubtn_u_duzenle_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_ubtn_u_duzenle_label, LV_TEXT_ALIGN_LEFT, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_duzenle_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_ubtn_u_duzenle_label, 7, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_ubtn_u_duzenle_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_bottom(ui->scr_ubtn_u_duzenle_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_ubtn_u_duzenle_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_duzenle_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_ubtn_u_sec_label
    ui->scr_ubtn_u_sec_label = lv_label_create(ui->scr_ubtn_u_bar_cont);
    lv_obj_set_pos(ui->scr_ubtn_u_sec_label, 60, 0);
    lv_obj_set_size(ui->scr_ubtn_u_sec_label, 130, 25);
    lv_label_set_text(ui->scr_ubtn_u_sec_label, "ÜRÜN SEÇİM EKRANI");
    lv_label_set_long_mode(ui->scr_ubtn_u_sec_label, LV_LABEL_LONG_WRAP);
    
    //Write style for scr_ubtn_u_sec_label, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_border_width(ui->scr_ubtn_u_sec_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_ubtn_u_sec_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_ubtn_u_sec_label, lv_color_hex(0xFFFFFF), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_ubtn_u_sec_label, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_sec_label, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_letter_space(ui->scr_ubtn_u_sec_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_line_space(ui->scr_ubtn_u_sec_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_ubtn_u_sec_label, LV_TEXT_ALIGN_LEFT, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_sec_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_top(ui->scr_ubtn_u_sec_label, 2, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_right(ui->scr_ubtn_u_sec_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_bottom(ui->scr_ubtn_u_sec_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_pad_left(ui->scr_ubtn_u_sec_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_sec_label, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write codes scr_ubtn_u_geri_btn
    ui->scr_ubtn_u_geri_btn = lv_button_create(ui->scr_ubtn);
    lv_obj_set_pos(ui->scr_ubtn_u_geri_btn, 380, 215);
    lv_obj_set_size(ui->scr_ubtn_u_geri_btn, 96, 52);
    ui->scr_ubtn_u_geri_btn_label = lv_label_create(ui->scr_ubtn_u_geri_btn);
    lv_label_set_text(ui->scr_ubtn_u_geri_btn_label, "");
    lv_label_set_long_mode(ui->scr_ubtn_u_geri_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_ubtn_u_geri_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_ubtn_u_geri_btn, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_ubtn_u_geri_btn_label, LV_PCT(100));

    //Write style for scr_ubtn_u_geri_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_geri_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_ubtn_u_geri_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_ubtn_u_geri_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_geri_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_src(ui->scr_ubtn_u_geri_btn, &_geri_RGB565A8_96x52, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_opa(ui->scr_ubtn_u_geri_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_recolor_opa(ui->scr_ubtn_u_geri_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_ubtn_u_geri_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_ubtn_u_geri_btn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_geri_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_ubtn_u_geri_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_ubtn_u_geri_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_geri_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_color(ui->scr_ubtn_u_geri_btn, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn_u_geri_btn, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_border_width(ui->scr_ubtn_u_geri_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_radius(ui->scr_ubtn_u_geri_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_geri_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_ubtn_u_geri_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_ubtn_u_geri_btn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_geri_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    //Write codes scr_ubtn_u_kaydet_btn
    ui->scr_ubtn_u_kaydet_btn = lv_button_create(ui->scr_ubtn);
    lv_obj_set_pos(ui->scr_ubtn_u_kaydet_btn, 380, 28);
    lv_obj_set_size(ui->scr_ubtn_u_kaydet_btn, 96, 52);
    ui->scr_ubtn_u_kaydet_btn_label = lv_label_create(ui->scr_ubtn_u_kaydet_btn);
    lv_label_set_text(ui->scr_ubtn_u_kaydet_btn_label, "");
    lv_label_set_long_mode(ui->scr_ubtn_u_kaydet_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_ubtn_u_kaydet_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_ubtn_u_kaydet_btn, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_ubtn_u_kaydet_btn_label, LV_PCT(100));

    //Write style for scr_ubtn_u_kaydet_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_kaydet_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_ubtn_u_kaydet_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_ubtn_u_kaydet_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_kaydet_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_src(ui->scr_ubtn_u_kaydet_btn, &_saved_RGB565A8_96x52, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_opa(ui->scr_ubtn_u_kaydet_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_recolor_opa(ui->scr_ubtn_u_kaydet_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_ubtn_u_kaydet_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_ubtn_u_kaydet_btn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_kaydet_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_ubtn_u_kaydet_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_ubtn_u_kaydet_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_kaydet_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_color(ui->scr_ubtn_u_kaydet_btn, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn_u_kaydet_btn, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_border_width(ui->scr_ubtn_u_kaydet_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_radius(ui->scr_ubtn_u_kaydet_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_kaydet_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_ubtn_u_kaydet_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_ubtn_u_kaydet_btn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_kaydet_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    //Write codes scr_ubtn_u_duzenle_btn
    ui->scr_ubtn_u_duzenle_btn = lv_button_create(ui->scr_ubtn);
    lv_obj_set_pos(ui->scr_ubtn_u_duzenle_btn, 380, 151);
    lv_obj_set_size(ui->scr_ubtn_u_duzenle_btn, 96, 52);
    ui->scr_ubtn_u_duzenle_btn_label = lv_label_create(ui->scr_ubtn_u_duzenle_btn);
    lv_label_set_text(ui->scr_ubtn_u_duzenle_btn_label, "");
    lv_label_set_long_mode(ui->scr_ubtn_u_duzenle_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_ubtn_u_duzenle_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_ubtn_u_duzenle_btn, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_ubtn_u_duzenle_btn_label, LV_PCT(100));

    //Write style for scr_ubtn_u_duzenle_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_duzenle_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_ubtn_u_duzenle_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_ubtn_u_duzenle_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_duzenle_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_src(ui->scr_ubtn_u_duzenle_btn, &_duzenle_RGB565A8_96x52, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_opa(ui->scr_ubtn_u_duzenle_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_recolor_opa(ui->scr_ubtn_u_duzenle_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_ubtn_u_duzenle_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_ubtn_u_duzenle_btn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_duzenle_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_ubtn_u_duzenle_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_ubtn_u_duzenle_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_duzenle_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_color(ui->scr_ubtn_u_duzenle_btn, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn_u_duzenle_btn, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_border_width(ui->scr_ubtn_u_duzenle_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_radius(ui->scr_ubtn_u_duzenle_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_duzenle_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_ubtn_u_duzenle_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_ubtn_u_duzenle_btn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_duzenle_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    //Write codes scr_ubtn_u_sec_btn
    ui->scr_ubtn_u_sec_btn = lv_button_create(ui->scr_ubtn);
    lv_obj_set_pos(ui->scr_ubtn_u_sec_btn, 380, 90);
    lv_obj_set_size(ui->scr_ubtn_u_sec_btn, 96, 52);
    ui->scr_ubtn_u_sec_btn_label = lv_label_create(ui->scr_ubtn_u_sec_btn);
    lv_label_set_text(ui->scr_ubtn_u_sec_btn_label, "");
    lv_label_set_long_mode(ui->scr_ubtn_u_sec_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_ubtn_u_sec_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_ubtn_u_sec_btn, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_ubtn_u_sec_btn_label, LV_PCT(100));

    //Write style for scr_ubtn_u_sec_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_sec_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_ubtn_u_sec_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_ubtn_u_sec_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_sec_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_src(ui->scr_ubtn_u_sec_btn, &_sec_RGB565A8_96x52, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_opa(ui->scr_ubtn_u_sec_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_recolor_opa(ui->scr_ubtn_u_sec_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_ubtn_u_sec_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_ubtn_u_sec_btn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_sec_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_ubtn_u_sec_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_ubtn_u_sec_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_sec_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_color(ui->scr_ubtn_u_sec_btn, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn_u_sec_btn, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_border_width(ui->scr_ubtn_u_sec_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_radius(ui->scr_ubtn_u_sec_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_sec_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_ubtn_u_sec_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_ubtn_u_sec_btn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_sec_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    //Write codes scr_ubtn_u_bul_btn
    ui->scr_ubtn_u_bul_btn = lv_button_create(ui->scr_ubtn);
    lv_obj_set_pos(ui->scr_ubtn_u_bul_btn, 380, 28);
    lv_obj_set_size(ui->scr_ubtn_u_bul_btn, 96, 52);
    ui->scr_ubtn_u_bul_btn_label = lv_label_create(ui->scr_ubtn_u_bul_btn);
    lv_label_set_text(ui->scr_ubtn_u_bul_btn_label, "");
    lv_label_set_long_mode(ui->scr_ubtn_u_bul_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scr_ubtn_u_bul_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scr_ubtn_u_bul_btn, 0, static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_width(ui->scr_ubtn_u_bul_btn_label, LV_PCT(100));

    //Write style for scr_ubtn_u_bul_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_DEFAULT).
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_bul_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_border_width(ui->scr_ubtn_u_bul_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_radius(ui->scr_ubtn_u_bul_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_bul_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_src(ui->scr_ubtn_u_bul_btn, &_bul_RGB565A8_96x52, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_opa(ui->scr_ubtn_u_bul_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_bg_image_recolor_opa(ui->scr_ubtn_u_bul_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_color(ui->scr_ubtn_u_bul_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_font(ui->scr_ubtn_u_bul_btn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_bul_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    lv_obj_set_style_text_align(ui->scr_ubtn_u_bul_btn, LV_TEXT_ALIGN_CENTER, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));

    //Write style for scr_ubtn_u_bul_btn, Part: static_cast<int>(LV_PART_MAIN), State: static_cast<int>(LV_STATE_PRESSED).
    lv_obj_set_style_bg_opa(ui->scr_ubtn_u_bul_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_color(ui->scr_ubtn_u_bul_btn, lv_color_hex(0x2FDA64), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_bg_grad_dir(ui->scr_ubtn_u_bul_btn, LV_GRAD_DIR_NONE, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_border_width(ui->scr_ubtn_u_bul_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_radius(ui->scr_ubtn_u_bul_btn, 5, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_shadow_width(ui->scr_ubtn_u_bul_btn, 0, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_color(ui->scr_ubtn_u_bul_btn, lv_color_hex(0xffffff), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_font(ui->scr_ubtn_u_bul_btn, &lv_font_Oswald_Reg_15, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));
    lv_obj_set_style_text_opa(ui->scr_ubtn_u_bul_btn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_PRESSED));

    //Update current screen layout.
    lv_obj_update_layout(ui->scr_ubtn);

    //Init events for screen.
    events_init_scr_ubtn(ui);

    lv_obj_add_event_cb(ui->scr_ubtn_u_bul_btn, urun_bul_cb, LV_EVENT_CLICKED, ui);
}
