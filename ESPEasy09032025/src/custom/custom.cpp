/*
* Copyright 2024 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"
#include "../ESPEasy-Globals.h"
#include "src/Globals/ESPEasy_time.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**
 * Create a demo application
 */
 
static uint32_t net = 0;
static uint32_t dara = 0;
static uint32_t brut = 0;

extern lv_ui guider_ui;

extern bool bnet;

void custom_init(lv_ui *ui)
{
    /* Add your codes here */
}

void loader_anim_cb(lv_obj_t* var, uint32_t value)
{
    lv_bar_set_value(var, value, LV_ANIM_ON);
}

void loader_anim_complete_cb(lv_obj_t* var)
{
    ui_load_scr_animation(&guider_ui, &guider_ui.scr_main, guider_ui.scr_main_del, &guider_ui.scr_logo_del, setup_scr_scr_main, LV_SCR_LOAD_ANIM_NONE, 2000, 1000, false, true);
}

void net_timer_cb(lv_timer_t * t)
{
	lv_ui * gui = static_cast<lv_ui *>(lv_timer_get_user_data(t));
	net += 1;

    if (top_net > 0) {
        //lv_imagebutton_set_src(gui->scr_main_topla_imgbtn, LV_IMAGEBUTTON_STATE_RELEASED, NULL, NULL, NULL);
        //lv_imagebutton_set_src(gui->scr_main_topla_imgbtn, LV_IMAGEBUTTON_STATE_PRESSED, NULL, NULL, NULL);

        //lv_imagebutton_set_src(gui->scr_main_yazdir_imgbtn, LV_IMAGEBUTTON_STATE_RELEASED, NULL, NULL, NULL);
        //lv_imagebutton_set_src(gui->scr_main_yazdir_imgbtn, LV_IMAGEBUTTON_STATE_PRESSED, NULL, NULL, NULL);

        lv_obj_set_style_image_opa(gui->scr_main_topla_imgbtn, 80, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_IMAGEBUTTON_STATE_RELEASED));
        lv_obj_set_style_image_opa(gui->scr_main_yazdir_imgbtn, 80, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_IMAGEBUTTON_STATE_RELEASED));
        char sno_data[4];
        sprintf_P(sno_data, PSTR("%03d"), sno);
        lv_label_set_text(gui->scr_main_topla_imgbtn_label, String(String(sno_data)+"\nTOPLA").c_str());
        lv_label_set_text(gui->scr_main_yazdir_imgbtn_label, "TOPLAM\nYAZDIR");
    }
    else {
        lv_obj_set_style_image_opa(gui->scr_main_topla_imgbtn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_IMAGEBUTTON_STATE_RELEASED));
        lv_obj_set_style_image_opa(gui->scr_main_yazdir_imgbtn, 255, static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_IMAGEBUTTON_STATE_RELEASED));

        lv_label_set_text(gui->scr_main_topla_imgbtn_label , "");
        lv_label_set_text(gui->scr_main_yazdir_imgbtn_label, "");
    }

    if ((hayvan_modu == 0) && (XML_STABIL_S == "ST") && (webapinettartim_son > 1)) {
        if ((topla_i == 1) || (top_net > 0)) {
          lv_label_set_text(gui->scr_main_knet_data_btn_label, "TOPLA");
        }
        else {
          lv_label_set_text(gui->scr_main_knet_data_btn_label, "YAZDIR");
        }
        lv_obj_set_style_bg_color(gui->scr_main_knet_data_btn_label, lv_color_hex(0x00CC00), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    }
    else {
        if (net_label) {
            if (urun_tipi[sec_URUN_buton] == 1) {
                lv_label_set_text(gui->scr_main_kg_label, "");
                lv_label_set_text(gui->scr_main_net_label, "ADET");
                lv_label_set_text_fmt(gui->scr_main_knet_data_btn_label , "%8s", XML_ADET_S);
            }
            else {
                lv_label_set_text(gui->scr_main_kg_label, "kg");
                lv_label_set_text(gui->scr_main_net_label, "NET KG");                
                lv_label_set_text_fmt(gui->scr_main_knet_data_btn_label , "%8s", XML_NET_S);
            }
        }
        else {
            if (urun_tipi[sec_URUN_buton] == 1) {
                lv_label_set_text(gui->scr_main_kg_label, "");
                lv_label_set_text_fmt(gui->scr_main_knet_data_btn_label , "%8s", XML_ADET_S);
            }
            else {
                lv_label_set_text(gui->scr_main_kg_label, "kg");
	            lv_label_set_text_fmt(gui->scr_main_knet_data_btn_label , "%8s", XML_NET_S);
                lv_obj_set_style_bg_color(gui->scr_main_knet_data_btn_label, lv_color_hex(0xFFFFFF), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
            }
        }
    }
    lv_label_set_text_fmt(gui->scr_main_dara_data_btn_label , "%8s", XML_DARA_S);
    //lv_label_set_text_fmt(gui->scr_main_birimgr_data_btn_label , "%8s", XML_ADET_GRAMAJ_S);
    lv_label_set_text_fmt(gui->scr_main_brut_data_btn_label , "%8s", XML_BRUT_S);
    //lv_label_set_text_fmt(gui->scr_main_adet_data_btn_label , "%8s", XML_ADET_S);
    XML_SAAT_S = node_time.getTimeString(':');
    lv_label_set_text_fmt(gui->scr_main_saat_btn_label , "%8s", XML_SAAT_S);
    XML_TARIH_S = node_time.getDateString('-');
    lv_label_set_text_fmt(gui->scr_main_tarih_btn_label , "%8s", XML_TARIH_S);
    /*if (XML_STABIL_S == "ST")
        lv_obj_set_style_text_color(gui->scr_main_knet_data_btn_label, lv_color_hex(0x00CC00), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));
    else
        lv_obj_set_style_text_color(gui->scr_main_knet_data_btn_label, lv_color_hex(0xCC0000), static_cast<int>(LV_PART_MAIN)|static_cast<int>(LV_STATE_DEFAULT));*/
}