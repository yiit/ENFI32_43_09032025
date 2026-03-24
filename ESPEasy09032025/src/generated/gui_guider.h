/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"


typedef struct
{
  
	lv_obj_t *scr_logo;
	bool scr_logo_del;
	lv_obj_t *scr_logo_label_1;
	lv_obj_t *scr_logo_bar_1;
	lv_obj_t *scr_logo_img_1;
	lv_obj_t *scr_main;
	bool scr_main_del;
	lv_obj_t *scr_main_m_cont;
	lv_obj_t *scr_main_m_btn_1;
	lv_obj_t *scr_main_m_btn_1_label;
	lv_obj_t *scr_main_m_btn_2;
	lv_obj_t *scr_main_m_btn_2_label;
	lv_obj_t *scr_main_m_btn_3;
	lv_obj_t *scr_main_m_btn_3_label;
	lv_obj_t *scr_main_m_btn_4;
	lv_obj_t *scr_main_m_btn_4_label;
	lv_obj_t *scr_main_m_btn_5;
	lv_obj_t *scr_main_m_btn_5_label;
	lv_obj_t *scr_main_m_btn_6;
	lv_obj_t *scr_main_m_btn_6_label;
	lv_obj_t *scr_main_m_btn_7;
	lv_obj_t *scr_main_m_btn_7_label;
	lv_obj_t *scr_main_m_btn_8;
	lv_obj_t *scr_main_m_btn_8_label;
	lv_obj_t *scr_main_f_cont;
	lv_obj_t *scr_main_f_btn_1;
	lv_obj_t *scr_main_f_btn_1_label;
	lv_obj_t *scr_main_f_btn_2;
	lv_obj_t *scr_main_f_btn_2_label;
	lv_obj_t *scr_main_f_btn_3;
	lv_obj_t *scr_main_f_btn_3_label;
	lv_obj_t *scr_main_f_btn_4;
	lv_obj_t *scr_main_f_btn_4_label;
	lv_obj_t *scr_main_f_btn_5;
	lv_obj_t *scr_main_f_btn_5_label;
	lv_obj_t *scr_main_f_btn_6;
	lv_obj_t *scr_main_f_btn_6_label;
	lv_obj_t *scr_main_f_btn_7;
	lv_obj_t *scr_main_f_btn_7_label;
	lv_obj_t *scr_main_f_btn_8;
	lv_obj_t *scr_main_f_btn_8_label;
	lv_obj_t *scr_main_daraekle_btn;
	lv_obj_t *scr_main_daraekle_btn_label;
	lv_obj_t *scr_main_darasil_btn;
	lv_obj_t *scr_main_darasil_btn_label;
	lv_obj_t *scr_main_bar_cont;
	lv_obj_t *scr_main_tarih_btn;
	lv_obj_t *scr_main_tarih_btn_label;
	lv_obj_t *scr_main_saat_btn;
	lv_obj_t *scr_main_saat_btn_label;
	lv_obj_t *scr_main_wifi_sta_imgbt;
	lv_obj_t *scr_main_wifi_sta_imgbt_label;
	lv_obj_t *scr_main_net_label;
	lv_obj_t *scr_main_dara_label;
	lv_obj_t *scr_main_birimgr_label;
	lv_obj_t *scr_main_brut_label;
	lv_obj_t *scr_main_adet_label;
	lv_obj_t *scr_main_yazdir_imgbtn;
	lv_obj_t *scr_main_yazdir_imgbtn_label;
	lv_obj_t *scr_main_topla_imgbtn;
	lv_obj_t *scr_main_topla_imgbtn_label;
	lv_obj_t *scr_main_urun_btn;
	lv_obj_t *scr_main_urun_btn_label;
	lv_obj_t *scr_main_menu_btn;
	lv_obj_t *scr_main_menu_btn_label;
	lv_obj_t *scr_main_kod_btn;
	lv_obj_t *scr_main_kod_btn_label;
	lv_obj_t *scr_main_knet_data_btn;
	lv_obj_t *scr_main_knet_data_btn_label;
	lv_obj_t *scr_main_dara_data_btn;
	lv_obj_t *scr_main_dara_data_btn_label;
	lv_obj_t *scr_main_birimgr_data_btn;
	lv_obj_t *scr_main_birimgr_data_btn_label;
	lv_obj_t *scr_main_brut_data_btn;
	lv_obj_t *scr_main_brut_data_btn_label;
	lv_obj_t *scr_main_adet_data_btn;
	lv_obj_t *scr_main_adet_data_btn_label;
	lv_obj_t *scr_main_kg_label;
	lv_obj_t *scr_main_sol_label;
	lv_obj_t *scr_main_sag_label;
	lv_obj_t *scr_mbtn;
	lv_obj_t *scr_dara_data_ta;
	lv_obj_t *scr_birimgr_data_ta;
	lv_obj_t *scr_adet_data_ta;
	lv_obj_t *scr_knet_data_ta;
	bool scr_mbtn_del;
	lv_obj_t *scr_mbtn_m_label;
	lv_obj_t *scr_mbtn_m1_ta;
	lv_obj_t *scr_mbtn_m_cont;
	
	lv_obj_t *scr_mbtn_m_name_btn[8][30];
	lv_obj_t *scr_mbtn_m_name_btn_label[8][30];
	lv_obj_t *scr_mbtn_m_no_label[30];
	
	/*lv_obj_t *scr_mbtn_m_name_btn_0;
	lv_obj_t *scr_mbtn_m_name_btn_0_label;
	lv_obj_t *scr_mbtn_m_name_btn_1;
	lv_obj_t *scr_mbtn_m_name_btn_1_label;
	lv_obj_t *scr_mbtn_m_no_label_1;
	lv_obj_t *scr_mbtn_m_no_label_2;
	lv_obj_t *scr_mbtn_m_name_btn_2;
	lv_obj_t *scr_mbtn_m_name_btn_2_label;*/

	lv_obj_t *scr_mbtn_m_bar_cont;
	lv_obj_t *scr_mbtn_m_geri_btn;
	lv_obj_t *scr_mbtn_m_geri_btn_label;
	lv_obj_t *scr_mbtn_m_kaydet_btn;
	lv_obj_t *scr_mbtn_m_kaydet_btn_label;
	lv_obj_t *scr_mbtn_m_duzenle_btn;
	lv_obj_t *scr_mbtn_m_duzenle_btn_label;
	lv_obj_t *scr_mbtn_m_sec_btn;
	lv_obj_t *scr_mbtn_m_sec_btn_label;
	lv_obj_t *scr_mbtn_m_bul_btn;
	lv_obj_t *scr_mbtn_m_bul_btn_label;

	lv_obj_t *scr_mbtn_m_sw[8];
	
	lv_obj_t *scr_mbtn_m_duzenle_label;
	lv_obj_t *scr_mbtn_m_sec_label;
	lv_obj_t *scr_fbtn;
	bool scr_fbtn_del;
	lv_obj_t *scr_fbtn_f_btn_cont;

	lv_obj_t *scr_fbtn_f_name_btn[8];
	lv_obj_t *scr_fbtn_f_name_btn_label[8];
	lv_obj_t *scr_fbtn_f_no_label[8];

	/*lv_obj_t *scr_fbtn_f_name_btn_2;
	lv_obj_t *scr_fbtn_f_name_btn_2_label;
	lv_obj_t *scr_fbtn_f_no_label_2;
	lv_obj_t *scr_fbtn_f_name_btn_1;
	lv_obj_t *scr_fbtn_f_name_btn_1_label;
	lv_obj_t *scr_fbtn_f_no_label_1;
	lv_obj_t *scr_fbtn_f_btn_0;
	lv_obj_t *scr_fbtn_f_btn_0_label;*/

	lv_obj_t *scr_fbtn_f_geri_btn;
	lv_obj_t *scr_fbtn_f_geri_btn_label;
	lv_obj_t *scr_fbtn_f_sec_btn;
	lv_obj_t *scr_fbtn_f_sec_btn_label;
	lv_obj_t *scr_fbtn_f_bar_cont;
	lv_obj_t *scr_ubtn;
	bool scr_ubtn_del;
	lv_obj_t *scr_ubtn_u_ta;
	lv_obj_t *scr_ubtn_u_cont;

	lv_obj_t *scr_ubtn_u_name_btn[101];
	lv_obj_t *scr_ubtn_u_name_btn_label[101];
	lv_obj_t *scr_ubtn_u_no_label[101];

	/*lv_obj_t *scr_ubtn_u_name_btn_0;
	lv_obj_t *scr_ubtn_u_name_btn_0_label;
	lv_obj_t *scr_ubtn_u_name_btn_2;
	lv_obj_t *scr_ubtn_u_name_btn_2_label;
	lv_obj_t *scr_ubtn_u_name_btn_1;
	lv_obj_t *scr_ubtn_u_name_btn_1_label;
	lv_obj_t *scr_ubtn_u_no_label_2;
	lv_obj_t *scr_ubtn_u_no_label_1;*/
	
	lv_obj_t *scr_ubtn_u_bar_cont;
	lv_obj_t *scr_ubtn_u_duzenle_label;
	lv_obj_t *scr_ubtn_u_sec_label;
	lv_obj_t *scr_ubtn_u_geri_btn;
	lv_obj_t *scr_ubtn_u_geri_btn_label;
	lv_obj_t *scr_ubtn_u_kaydet_btn;
	lv_obj_t *scr_ubtn_u_kaydet_btn_label;
	lv_obj_t *scr_ubtn_u_duzenle_btn;
	lv_obj_t *scr_ubtn_u_duzenle_btn_label;
	lv_obj_t *scr_ubtn_u_sec_btn;
	lv_obj_t *scr_ubtn_u_sec_btn_label;
	lv_obj_t *scr_ubtn_u_bul_btn;
	lv_obj_t *scr_ubtn_u_bul_btn_label;
	lv_obj_t *scr_wifi_sta;
	bool scr_wifi_sta_del;
	lv_obj_t *scr_wifi_sta_cb_1;
	lv_obj_t *scr_wifi_sta_cb_2;
	lv_obj_t *scr_wifi_sta_img_1;
	lv_obj_t *scr_wifi_sta_img_2;
	lv_obj_t *scr_wifi_sta_w_img;
	lv_obj_t *scr_wifi_sta_w_cb;
	lv_obj_t *scr_kaydedildi;
	bool scr_kaydedildi_del;
	lv_obj_t *scr_kaydedildi_kaydet_img;
	lv_obj_t *scr_kaydedildi_2;
	bool scr_kaydedildi_2_del;
	lv_obj_t *scr_kaydedildi_2_kaydet_2_img;
	lv_obj_t *scr_kod;
	bool scr_kod_del;
	lv_obj_t *scr_kod_k_ta;
	lv_obj_t *scr_kod_k_cont;
	lv_obj_t *scr_kod_k_duzen_btn;
	lv_obj_t *scr_kod_k_duzen_btn_label;
	lv_obj_t *scr_kod_k_bul_btn;
	lv_obj_t *scr_kod_k_bul_btn_label;
	lv_obj_t *scr_kod_k_u_label;
	lv_obj_t *scr_kod_k_geri_btn;
	lv_obj_t *scr_kod_k_geri_btn_label;
	lv_obj_t *scr_kod_k_sec_btn;
	lv_obj_t *scr_kod_k_sec_btn_label;
	lv_obj_t *g_kb_top_layer;
	lv_obj_t *scr_menu;
	bool scr_menu_del;
	lv_obj_t *scr_menu_ekran_btn;
	lv_obj_t *scr_menu_ekran_btn_label;
	lv_obj_t *scr_menu_wsta_btn;
	lv_obj_t *scr_menu_wsta_btn_label;
	lv_obj_t *scr_menu_wap_btn;
	lv_obj_t *scr_menu_wap_btn_label;
	lv_obj_t *scr_menu_yazici_btn;
	lv_obj_t *scr_menu_yazici_btn_label;
	lv_obj_t *scr_menu_terazi_btn;
	lv_obj_t *scr_menu_terazi_btn_label;
	lv_obj_t *scr_menu_fis_dizayn_btn;
	lv_obj_t *scr_menu_fis_dizayn_btn_label;
	lv_obj_t *scr_menu_wifiap_btn_1;
	lv_obj_t *scr_menu_wifiap_btn_1_label;
	lv_obj_t *scr_menu_wifiap_btn_2;
	lv_obj_t *scr_menu_wifiap_btn_2_label;
	lv_obj_t *scr_menu_etiket_dizayn_btn;
	lv_obj_t *scr_menu_etiket_dizayn_btn_label;
	lv_obj_t *scr_menu_geri_btn;
	lv_obj_t *scr_menu_geri_btn_label;
	lv_obj_t *scr_ekran;
	bool scr_ekran_del;
	lv_obj_t *scr_ekran_btn_1;
	lv_obj_t *scr_ekran_btn_1_label;
	lv_obj_t *scr_ekran_slider_1;
	lv_obj_t *scr_ekran_label_1;
	lv_obj_t *scr_fis;
	bool scr_fis_del;
	lv_obj_t *scr_fis_geri_btn;
	lv_obj_t *scr_fis_geri_btn_label;
	lv_obj_t *scr_fis_duzenle_btn;
	lv_obj_t *scr_fis_duzenle_btn_label;
	lv_obj_t *scr_fis_sec_btn;
	lv_obj_t *scr_fis_sec_btn_label;
	lv_obj_t *scr_fis_kaydet_btn;
	lv_obj_t *scr_fis_kaydet_btn_label;
	lv_obj_t *scr_fis_ta_5;
	lv_obj_t *scr_fis_ta_4;
	lv_obj_t *scr_fis_ta_3;
	lv_obj_t *scr_fis_ta_2;
	lv_obj_t *scr_fis_ta_1;
	lv_obj_t *scr_fis_cont_1;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_screen_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, uint32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                  uint32_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                  lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_completed_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_bottom_layer(void);

void setup_ui(lv_ui *ui);

void video_play(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_scr_logo(lv_ui *ui);
void setup_scr_scr_main(lv_ui *ui);
void setup_scr_scr_mbtn(lv_ui *ui);
void setup_scr_scr_fbtn(lv_ui *ui);
void setup_scr_scr_ubtn(lv_ui *ui);
void setup_scr_scr_wifi_sta(lv_ui *ui);
void setup_scr_scr_kaydedildi(lv_ui *ui);
void setup_scr_scr_kaydedildi_2(lv_ui *ui);
void setup_scr_scr_kod(lv_ui *ui);
void setup_scr_scr_menu(lv_ui *ui);
void setup_scr_scr_ekran(lv_ui *ui);
void setup_scr_scr_fis(lv_ui *ui);
LV_IMAGE_DECLARE(_endutek_logo_RGB565A8_280x68);
LV_IMAGE_DECLARE(_wifi_lost_RGB565A8_25x25);
LV_IMAGE_DECLARE(_printing_RGB565A8_96x52);
LV_IMAGE_DECLARE(_topla_RGB565A8_96x52);

LV_IMAGE_DECLARE(_geri_RGB565A8_96x52);

LV_IMAGE_DECLARE(_saved_RGB565A8_96x52);

LV_IMAGE_DECLARE(_duzenle_RGB565A8_96x52);

LV_IMAGE_DECLARE(_sec_RGB565A8_96x52);

LV_IMAGE_DECLARE(_bul_RGB565A8_96x52);
LV_IMAGE_DECLARE(_wifi_RGB565A8_27x27);
LV_IMAGE_DECLARE(_ready_RGB565A8_85x85);

//LV_FONT_DECLARE(lv_font_montserratMedium_16)
//LV_FONT_DECLARE(lv_font_montserratMedium_12)
//LV_FONT_DECLARE(lv_font_Bebas_16)
//LV_FONT_DECLARE(lv_font_Bebas_12)

LV_FONT_DECLARE(lv_font_Bebas_48)
LV_FONT_DECLARE(lv_font_Bebas_100)

//LV_FONT_DECLARE(lv_font_Bebas_30)
LV_FONT_DECLARE(lv_font_Oswald_Reg_12)
LV_FONT_DECLARE(lv_font_Oswald_Reg_15)
LV_FONT_DECLARE(lv_font_Oswald_Reg_20)
LV_FONT_DECLARE(lv_font_Oswald_Reg_48)


#ifdef __cplusplus
}
#endif
#endif
