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
	lv_ui * gui = lv_timer_get_user_data(t);
	net += 1;
    if (bnet)
      lv_label_set_text_fmt(gui->scr_main_knet_data_btn_label , "%8d", net);
    else
	  lv_label_set_text_fmt(gui->scr_main_knet_data_btn_label , "%8d", net);
    lv_label_set_text_fmt(gui->scr_main_dara_data_btn_label , "%8d", dara);
    lv_label_set_text_fmt(gui->scr_main_brut_data_btn_label , "%8d", brut);
}