/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

#include "custom/custom.h"
#include "custom.h"
static lv_timer_t  * task_net;
bool bnet = false;
static bool duzenle = false;
uint8_t m_btn_no = 0;

static void scr_logo_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START:
    {
        lv_obj_set_y(guider_ui.scr_logo_bar_1, 230);
        ui_animation(guider_ui.scr_logo_bar_1, 5, 5, 0, 100, &lv_anim_path_linear, 0, 0, 0, 0, (lv_anim_exec_xcb_t)loader_anim_cb, NULL, (lv_anim_completed_cb_t)loader_anim_complete_cb, NULL);
        break;
    }
    case LV_EVENT_SCREEN_UNLOAD_START:
    {
        lv_obj_set_y(guider_ui.scr_logo_bar_1, 230);
        break;
    }
    default:
        break;
    }
}

void events_init_scr_logo (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->scr_logo, scr_logo_event_handler, LV_EVENT_ALL, ui);
}

static void scr_main_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        task_net = lv_timer_create(net_timer_cb, 1000, &guider_ui);
        lv_obj_add_flag(guider_ui.scr_main_kg_label, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED:
    {
        lv_timer_del(task_net);
        break;
    }
    default:
        break;
    }
}

static void scr_main_yazdir_imgbtn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SHORT_CLICKED:
    {
        printf("yazdir\r\n");
        lv_label_set_text(guider_ui.scr_main_knet_data_btn_label, "YAZDIR");
        break;
    }
    default:
        break;
    }
}

static void scr_main_topla_imgbtn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSED:
    {
        printf("topla\r\n");
        lv_label_set_text(guider_ui.scr_main_knet_data_btn_label, "TOPLA");
        break;
    }
    default:
        break;
    }
}

static void scr_main_m_cont_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCROLL:
    {
        break;
    }
    default:
        break;
    }
}

static void scr_main_m_btn_8_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_LONG_PRESSED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_mbtn, guider_ui.scr_mbtn_del, &guider_ui.scr_main_del, setup_scr_scr_mbtn, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        m_btn_no = 7;
        printf("M8\r\n");
        break;
    }
    default:
        break;
    }
}

static void scr_main_m_btn_7_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_LONG_PRESSED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_mbtn, guider_ui.scr_mbtn_del, &guider_ui.scr_main_del, setup_scr_scr_mbtn, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        m_btn_no = 6;
        printf("M7\r\n");
        break;
    }
    default:
        break;
    }
}

static void scr_main_m_btn_6_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_LONG_PRESSED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_mbtn, guider_ui.scr_mbtn_del, &guider_ui.scr_main_del, setup_scr_scr_mbtn, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        m_btn_no = 5;
        printf("M6\r\n");
        break;
    }
    default:
        break;
    }
}

static void scr_main_m_btn_5_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_LONG_PRESSED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_mbtn, guider_ui.scr_mbtn_del, &guider_ui.scr_main_del, setup_scr_scr_mbtn, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        m_btn_no = 4;
        printf("M5\r\n");
        break;
    }
    default:
        break;
    }
}

static void scr_main_m_btn_4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_LONG_PRESSED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_mbtn, guider_ui.scr_mbtn_del, &guider_ui.scr_main_del, setup_scr_scr_mbtn, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        m_btn_no = 3;
        printf("M4\r\n");
        break;
    }
    default:
        break;
    }
}

static void scr_main_m_btn_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_LONG_PRESSED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_mbtn, guider_ui.scr_mbtn_del, &guider_ui.scr_main_del, setup_scr_scr_mbtn, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        m_btn_no = 2;
        printf("M3\r\n");
        break;
    }
    default:
        break;
    }
}

static void scr_main_m_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_LONG_PRESSED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_mbtn, guider_ui.scr_mbtn_del, &guider_ui.scr_main_del, setup_scr_scr_mbtn, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        m_btn_no = 1;
        printf("M2\r\n");
        break;
    }
    default:
        break;
    }
}

static void scr_main_m_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_LONG_PRESSED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_mbtn, guider_ui.scr_mbtn_del, &guider_ui.scr_main_del, setup_scr_scr_mbtn, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        m_btn_no = 0;
        printf("M1\r\n");
        break;
    }
    default:
        break;
    }
}

static void scr_main_f_btn_8_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SHORT_CLICKED:
    {

        break;
    }
    case LV_EVENT_LONG_PRESSED:
    {

        ui_load_scr_animation(&guider_ui, &guider_ui.scr_fbtn, guider_ui.scr_fbtn_del, &guider_ui.scr_main_del, setup_scr_scr_fbtn, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void scr_main_f_btn_7_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SHORT_CLICKED:
    {

        break;
    }
    case LV_EVENT_LONG_PRESSED:
    {

        ui_load_scr_animation(&guider_ui, &guider_ui.scr_fbtn, guider_ui.scr_fbtn_del, &guider_ui.scr_main_del, setup_scr_scr_fbtn, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void scr_main_f_btn_6_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SHORT_CLICKED:
    {

        break;
    }
    case LV_EVENT_LONG_PRESSED:
    {

        ui_load_scr_animation(&guider_ui, &guider_ui.scr_fbtn, guider_ui.scr_fbtn_del, &guider_ui.scr_main_del, setup_scr_scr_fbtn, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void scr_main_f_btn_5_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SHORT_CLICKED:
    {

        break;
    }
    case LV_EVENT_LONG_PRESSED:
    {

        ui_load_scr_animation(&guider_ui, &guider_ui.scr_fbtn, guider_ui.scr_fbtn_del, &guider_ui.scr_main_del, setup_scr_scr_fbtn, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void scr_main_f_btn_4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SHORT_CLICKED:
    {
        printf("F4\r\n");
        break;
    }
    case LV_EVENT_LONG_PRESSED:
    {

        ui_load_scr_animation(&guider_ui, &guider_ui.scr_fbtn, guider_ui.scr_fbtn_del, &guider_ui.scr_main_del, setup_scr_scr_fbtn, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void scr_main_f_btn_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SHORT_CLICKED:
    {
        printf("F3\r\n");
        break;
    }
    case LV_EVENT_LONG_PRESSED:
    {

        ui_load_scr_animation(&guider_ui, &guider_ui.scr_fbtn, guider_ui.scr_fbtn_del, &guider_ui.scr_main_del, setup_scr_scr_fbtn, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void scr_main_f_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SHORT_CLICKED:
    {
        printf("F2\r\n");
        break;
    }
    case LV_EVENT_LONG_PRESSED:
    {

        ui_load_scr_animation(&guider_ui, &guider_ui.scr_fbtn, guider_ui.scr_fbtn_del, &guider_ui.scr_main_del, setup_scr_scr_fbtn, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void scr_main_f_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_LONG_PRESSED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_fbtn, guider_ui.scr_fbtn_del, &guider_ui.scr_main_del, setup_scr_scr_fbtn, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        printf("F1");
        break;
    }
    case LV_EVENT_SHORT_CLICKED:
    {

        break;
    }
    default:
        break;
    }
}

static void scr_main_knet_data_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SHORT_CLICKED:
    {
        if (bnet) {
            bnet = false;
            lv_obj_remove_flag(guider_ui.scr_main_brut_data_btn, LV_OBJ_FLAG_HIDDEN);
            lv_obj_remove_flag(guider_ui.scr_main_dara_data_btn, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_x(guider_ui.scr_main_knet_data_btn, 330);
            lv_obj_set_y(guider_ui.scr_main_knet_data_btn, 76);
            lv_obj_set_width(guider_ui.scr_main_knet_data_btn, 150);
            lv_obj_set_height(guider_ui.scr_main_knet_data_btn, 39);
            lv_obj_set_style_text_font(guider_ui.scr_main_knet_data_btn, &lv_font_Bebas_48, 0);
            lv_obj_remove_flag(guider_ui.scr_main_brut_label, LV_OBJ_FLAG_HIDDEN);
            lv_obj_remove_flag(guider_ui.scr_main_dara_label, LV_OBJ_FLAG_HIDDEN);
            lv_obj_remove_flag(guider_ui.scr_main_net_label, LV_OBJ_FLAG_HIDDEN);
            lv_obj_remove_flag(guider_ui.scr_main_menu_btn, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_x(guider_ui.scr_main_urun_btn, 83);
            lv_obj_set_y(guider_ui.scr_main_urun_btn, 26);
            lv_obj_set_width(guider_ui.scr_main_urun_btn, 314);
            lv_obj_set_height(guider_ui.scr_main_urun_btn, 32);
            lv_obj_add_flag(guider_ui.scr_main_kg_label, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_width(guider_ui.scr_main_kod_btn, 80);
        } else {
            lv_obj_add_flag(guider_ui.scr_main_brut_data_btn, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(guider_ui.scr_main_dara_data_btn, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_x(guider_ui.scr_main_knet_data_btn, 150);
            lv_obj_set_y(guider_ui.scr_main_knet_data_btn, 26);
            lv_obj_set_width(guider_ui.scr_main_knet_data_btn, 285);
            lv_obj_set_height(guider_ui.scr_main_knet_data_btn, 88);
            lv_obj_set_style_text_font(guider_ui.scr_main_knet_data_btn, &lv_font_Bebas_90, 0);
            lv_obj_add_flag(guider_ui.scr_main_brut_label, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(guider_ui.scr_main_dara_label, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(guider_ui.scr_main_net_label, LV_OBJ_FLAG_HIDDEN);
            bnet = true;
            lv_obj_add_flag(guider_ui.scr_main_menu_btn, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_x(guider_ui.scr_main_urun_btn, 1);
            lv_obj_set_y(guider_ui.scr_main_urun_btn, 60);
            lv_obj_set_width(guider_ui.scr_main_urun_btn, 148);
            lv_obj_set_height(guider_ui.scr_main_urun_btn, 54);
            lv_obj_remove_flag(guider_ui.scr_main_kg_label, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_width(guider_ui.scr_main_kod_btn, 148);
        }
        break;
    }
    default:
        break;
    }
}

static void scr_main_menu_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_menu, guider_ui.scr_menu_del, &guider_ui.scr_main_del, setup_scr_scr_menu, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void scr_main_urun_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_ubtn, guider_ui.scr_ubtn_del, &guider_ui.scr_main_del, setup_scr_scr_ubtn, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void scr_main_kod_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_kod, guider_ui.scr_kod_del, &guider_ui.scr_main_del, setup_scr_scr_kod, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void scr_main_tarih_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSED:
    {
        printf("tarih");
        break;
    }
    default:
        break;
    }
}

static void scr_main_saat_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSED:
    {
        printf("saat");
        break;
    }
    case LV_EVENT_VALUE_CHANGED:
    {
        lv_label_set_text(guider_ui.scr_main_saat_btn_label, "saat");
        break;
    }
    default:
        break;
    }
}

void events_init_scr_main (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->scr_main, scr_main_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_yazdir_imgbtn, scr_main_yazdir_imgbtn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_topla_imgbtn, scr_main_topla_imgbtn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_m_cont, scr_main_m_cont_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_m_btn_8, scr_main_m_btn_8_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_m_btn_7, scr_main_m_btn_7_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_m_btn_6, scr_main_m_btn_6_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_m_btn_5, scr_main_m_btn_5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_m_btn_4, scr_main_m_btn_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_m_btn_3, scr_main_m_btn_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_m_btn_2, scr_main_m_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_m_btn_1, scr_main_m_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_f_btn_8, scr_main_f_btn_8_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_f_btn_7, scr_main_f_btn_7_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_f_btn_6, scr_main_f_btn_6_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_f_btn_5, scr_main_f_btn_5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_f_btn_4, scr_main_f_btn_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_f_btn_3, scr_main_f_btn_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_f_btn_2, scr_main_f_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_f_btn_1, scr_main_f_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_knet_data_btn, scr_main_knet_data_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_menu_btn, scr_main_menu_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_urun_btn, scr_main_urun_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_kod_btn, scr_main_kod_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_tarih_btn, scr_main_tarih_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_main_saat_btn, scr_main_saat_btn_event_handler, LV_EVENT_ALL, ui);
}

static void scr_mbtn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        lv_obj_add_flag(guider_ui.scr_mbtn_m1_ta, LV_OBJ_FLAG_HIDDEN);

        lv_obj_add_flag(guider_ui.scr_mbtn_m_duzenle_btn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.scr_mbtn_m_kaydet_btn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.scr_mbtn_m_sec_btn, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void scr_mbtn_m_name_btn_0_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_LONG_PRESSED:
    {

        lv_obj_remove_flag(guider_ui.scr_mbtn_m_duzenle_btn, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    case LV_EVENT_SHORT_CLICKED:
    {
        lv_obj_remove_flag(guider_ui.scr_mbtn_m_sec_btn, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void scr_mbtn_m_name_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SHORT_CLICKED:
    {
        lv_obj_remove_flag(guider_ui.scr_mbtn_m_sec_btn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_style_bg_color(guider_ui.scr_mbtn_m_name_btn_1, lv_color_hex(0x00c800), LV_PART_MAIN);
        break;
    }
    case LV_EVENT_LONG_PRESSED_REPEAT:
    {
        lv_obj_remove_flag(guider_ui.scr_mbtn_m_duzenle_btn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_style_bg_color(guider_ui.scr_mbtn_m_name_btn_1, lv_color_hex(0xc8c8c8), LV_PART_MAIN);
        break;
    }
    default:
        break;
    }
}

static void scr_mbtn_m_geri_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_main, guider_ui.scr_main_del, &guider_ui.scr_mbtn_del, setup_scr_scr_main, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        duzenle = false;
        break;
    }
    default:
        break;
    }
}

static void scr_mbtn_m_kaydet_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        lv_obj_add_flag(guider_ui.scr_mbtn_m_kaydet_btn, LV_OBJ_FLAG_HIDDEN);
        duzenle = false;
        lv_obj_add_flag(guider_ui.scr_mbtn_m1_ta, LV_OBJ_FLAG_HIDDEN);
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_kaydedildi, guider_ui.scr_kaydedildi_del, &guider_ui.scr_mbtn_del, setup_scr_scr_kaydedildi, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 1000, 500, true, true);
        lv_obj_remove_flag(guider_ui.scr_mbtn_m_sec_btn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(guider_ui.scr_mbtn_m_bul_btn, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void scr_mbtn_m_duzenle_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        lv_obj_add_flag(guider_ui.scr_mbtn_m_duzenle_btn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(guider_ui.scr_mbtn_m_kaydet_btn, LV_OBJ_FLAG_HIDDEN);
        duzenle = true;
        lv_obj_remove_flag(guider_ui.scr_mbtn_m1_ta, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.scr_mbtn_m_sec_btn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.scr_mbtn_m_bul_btn, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void scr_mbtn_m_sec_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_main, guider_ui.scr_main_del, &guider_ui.scr_mbtn_del, setup_scr_scr_main, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void scr_mbtn_m_bul_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        lv_obj_remove_flag(guider_ui.scr_mbtn_m1_ta, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

void events_init_scr_mbtn (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->scr_mbtn, scr_mbtn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_mbtn_m_name_btn_0, scr_mbtn_m_name_btn_0_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_mbtn_m_name_btn_1, scr_mbtn_m_name_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_mbtn_m_geri_btn, scr_mbtn_m_geri_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_mbtn_m_kaydet_btn, scr_mbtn_m_kaydet_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_mbtn_m_duzenle_btn, scr_mbtn_m_duzenle_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_mbtn_m_sec_btn, scr_mbtn_m_sec_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_mbtn_m_bul_btn, scr_mbtn_m_bul_btn_event_handler, LV_EVENT_ALL, ui);
}

static void scr_fbtn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        lv_obj_add_flag(guider_ui.scr_fbtn_f_sec_btn, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void scr_fbtn_f_name_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        lv_obj_remove_flag(guider_ui.scr_fbtn_f_sec_btn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_style_bg_color(guider_ui.scr_fbtn_f_name_btn_1, lv_color_hex(0x00c800), LV_PART_MAIN);
        break;
    }
    default:
        break;
    }
}

static void scr_fbtn_f_geri_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_main, guider_ui.scr_main_del, &guider_ui.scr_fbtn_del, setup_scr_scr_main, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_scr_fbtn (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->scr_fbtn, scr_fbtn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_fbtn_f_name_btn_1, scr_fbtn_f_name_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_fbtn_f_geri_btn, scr_fbtn_f_geri_btn_event_handler, LV_EVENT_ALL, ui);
}

static void scr_ubtn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START:
    {
        lv_obj_add_flag(guider_ui.scr_ubtn_u_kaydet_btn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.scr_ubtn_u_ta, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.scr_ubtn_u_sec_btn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.scr_ubtn_u_duzenle_btn, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void scr_ubtn_u_name_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SHORT_CLICKED:
    {
        lv_obj_remove_flag(guider_ui.scr_ubtn_u_sec_btn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_style_bg_color(guider_ui.scr_ubtn_u_name_btn_1, lv_color_hex(0x00c800), LV_PART_MAIN);
        break;
    }
    case LV_EVENT_LONG_PRESSED_REPEAT:
    {
        lv_obj_remove_flag(guider_ui.scr_ubtn_u_duzenle_btn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_style_bg_color(guider_ui.scr_ubtn_u_name_btn_1, lv_color_hex(0xc8c8c8), LV_PART_MAIN);
        break;
    }
    default:
        break;
    }
}

static void scr_ubtn_u_geri_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_main, guider_ui.scr_main_del, &guider_ui.scr_ubtn_del, setup_scr_scr_main, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void scr_ubtn_u_kaydet_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        lv_obj_add_flag(guider_ui.scr_ubtn_u_kaydet_btn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(guider_ui.scr_ubtn_u_duzenle_btn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.scr_ubtn_u_ta, LV_OBJ_FLAG_HIDDEN);
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_kaydedildi_2, guider_ui.scr_kaydedildi_2_del, &guider_ui.scr_ubtn_del, setup_scr_scr_kaydedildi_2, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 1000, 500, true, true);
        lv_obj_remove_flag(guider_ui.scr_ubtn_u_bul_btn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(guider_ui.scr_ubtn_u_sec_btn, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void scr_ubtn_u_duzenle_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        lv_obj_add_flag(guider_ui.scr_ubtn_u_duzenle_btn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(guider_ui.scr_ubtn_u_kaydet_btn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(guider_ui.scr_ubtn_u_ta, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.scr_ubtn_u_bul_btn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.scr_ubtn_u_sec_btn, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void scr_ubtn_u_sec_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_main, guider_ui.scr_main_del, &guider_ui.scr_ubtn_del, setup_scr_scr_main, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void scr_ubtn_u_bul_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        lv_obj_remove_flag(guider_ui.scr_ubtn_u_ta, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

void events_init_scr_ubtn (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->scr_ubtn, scr_ubtn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_ubtn_u_name_btn_1, scr_ubtn_u_name_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_ubtn_u_geri_btn, scr_ubtn_u_geri_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_ubtn_u_kaydet_btn, scr_ubtn_u_kaydet_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_ubtn_u_duzenle_btn, scr_ubtn_u_duzenle_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_ubtn_u_sec_btn, scr_ubtn_u_sec_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_ubtn_u_bul_btn, scr_ubtn_u_bul_btn_event_handler, LV_EVENT_ALL, ui);
}

static void scr_kaydedildi_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_mbtn, guider_ui.scr_mbtn_del, &guider_ui.scr_kaydedildi_del, setup_scr_scr_mbtn, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_scr_kaydedildi (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->scr_kaydedildi, scr_kaydedildi_event_handler, LV_EVENT_ALL, ui);
}

static void scr_kaydedildi_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_ubtn, guider_ui.scr_ubtn_del, &guider_ui.scr_kaydedildi_2_del, setup_scr_scr_ubtn, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_scr_kaydedildi_2 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->scr_kaydedildi_2, scr_kaydedildi_2_event_handler, LV_EVENT_ALL, ui);
}

static void scr_kod_k_geri_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_main, guider_ui.scr_main_del, &guider_ui.scr_kod_del, setup_scr_scr_main, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_scr_kod (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->scr_kod_k_geri_btn, scr_kod_k_geri_btn_event_handler, LV_EVENT_ALL, ui);
}

static void scr_menu_fis_dizayn_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_fis, guider_ui.scr_fis_del, &guider_ui.scr_menu_del, setup_scr_scr_fis, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void scr_menu_geri_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_main, guider_ui.scr_main_del, &guider_ui.scr_menu_del, setup_scr_scr_main, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_scr_menu (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->scr_menu_fis_dizayn_btn, scr_menu_fis_dizayn_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scr_menu_geri_btn, scr_menu_geri_btn_event_handler, LV_EVENT_ALL, ui);
}

static void scr_fis_geri_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scr_menu, guider_ui.scr_menu_del, &guider_ui.scr_fis_del, setup_scr_scr_menu, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_scr_fis (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->scr_fis_geri_btn, scr_fis_geri_btn_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
