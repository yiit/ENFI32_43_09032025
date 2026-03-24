/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include "gui_guider.h"
#include "widgets_init.h"
#include <stdlib.h>
#include <string.h>
#include "../ESPEasy-Globals.h"

extern lv_ui guider_ui;
#define ui (&guider_ui)

__attribute__((unused)) void kb_event_cb (lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *kb = static_cast<lv_obj_t *>(lv_event_get_target(e));
    if(code == LV_EVENT_READY || code == LV_EVENT_CANCEL) {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

static const char * custom_kb_map[] = {
    "1", "2", "3", "\n",
    "4", "5", "6", "\n",
    "7", "8", "9", "\n",
    ".", "0", ",", LV_SYMBOL_BACKSPACE,  NULL // Silme tuşu
};

/*static const lv_buttonmatrix_ctrl_t custom_kb_ctrl[] = {
    1,1,1,1,
    1,1,1,1,
    1,1,1,1,
    1,1,1,1
};*/
// Tüm diğer textarea'ları gizle (except hariç)
void clear_all_other_textareas(lv_obj_t *except) {
    lv_obj_t *textareas[] = {
        //ui->scr_adet_data_ta,
        //ui->scr_birimgr_data_ta,
        ui->scr_dara_data_ta,
        ui->scr_knet_data_ta,
        ui->scr_kod_k_ta,
        ui->scr_ubtn_u_ta, // Bu da varsa ekle!
    };

    for (int i = 0; i < sizeof(textareas) / sizeof(textareas[0]); i++) {
        if (textareas[i] && textareas[i] != except && !lv_obj_has_flag(textareas[i], LV_OBJ_FLAG_HIDDEN)) {
            lv_obj_add_flag(textareas[i], LV_OBJ_FLAG_HIDDEN);
        }
    }
}

static bool kb_first_input = false;
static lv_obj_t* last_focused_ta = NULL;

    __attribute__((unused)) void ta_event_cb(lv_event_t *e) {
#if LV_USE_KEYBOARD
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = static_cast<lv_obj_t *>(lv_event_get_target(e));
    lv_obj_t *kb = static_cast<lv_obj_t *>(lv_event_get_user_data(e));
    if (!ta || !kb) return; // NULL koruması

    if (code == LV_EVENT_FOCUSED) {
        if (lv_indev_get_type(lv_indev_active()) != LV_INDEV_TYPE_KEYPAD) {
            if (lv_keyboard_get_textarea(kb) != ta) {
                lv_keyboard_set_textarea(kb, ta);
                lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);

                // Klavye modunu seç
                if ((ta == ui->scr_kod_k_ta) || (ta == ui->scr_dara_data_ta) || (ta == ui->scr_knet_data_ta))
                    lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_NUMBER);
                else if (ta == ui->scr_ubtn_u_ta)
                    lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_TEXT_LOWER);
                else if (ta == ui->scr_mbtn_m1_ta)
                    lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_TEXT_UPPER);
            }

            lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
            kb_first_input = true;
            last_focused_ta = ta;
        }
    }

    else if (code == LV_EVENT_CANCEL) {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_keyboard_set_textarea(kb, NULL);
    }

    else if (code == LV_EVENT_INSERT) {
        if (kb_first_input) {
            beep(2000, 300); // ilk tuşta bip
            kb_first_input = false;
        }
    }

    else if (code == LV_EVENT_DEFOCUSED) {
        kb_first_input = false;
        last_focused_ta = NULL;
    }

    else if (code == LV_EVENT_READY) {
        // Son girilen text burada okunur
        const char *txt = lv_textarea_get_text(ta);
        if (!txt) txt = "";

        // Değer boş değilse işle
        if (strlen(txt) > 0) {
            if (ta == ui->scr_dara_data_ta) {
                webapidaratartim = atof(txt);
                Serial.printf("[TA] Dara: %.3f\n", webapidaratartim);

                lv_textarea_set_text(ta, ""); // input'u temizle
                lv_obj_add_flag(ui->scr_dara_data_ta, LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(ui->scr_main_m_cont, LV_OBJ_FLAG_HIDDEN);
            }
            else if (ta == ui->scr_knet_data_ta) {
                XML_ADET_S = String(atoi(txt));
                Serial.printf("[TA] KNet: %s\n", txt);

                lv_textarea_set_text(ta, "");
                lv_obj_add_flag(ui->scr_knet_data_ta, LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(ui->scr_main_m_cont, LV_OBJ_FLAG_HIDDEN);
            }
            else if (ta == ui->scr_kod_k_ta) {
                Serial.printf("[TA] Kod: %s\n", txt);
            }
            else if (ta == ui->scr_ubtn_u_ta) {
                Serial.printf("[TA] Kullanıcı: %s\n", txt);
                lv_textarea_set_text(ta, "");
            }
            else if (ta == ui->scr_mbtn_m1_ta) {
                Serial.printf("[TA] M1: %s\n", txt);
                lv_textarea_set_text(ta, "");
            }
        }

        // Klavyeyi gizle
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_clear_state(ta, LV_STATE_FOCUSED);
        lv_indev_reset(NULL, ta);
        kb_first_input = false;
        last_focused_ta = NULL;
    }
#endif
}

           

void clock_count(int *hour, int *min, int *sec)
{
    (*sec)++;
    if(*sec == 60)
    {
        *sec = 0;
        (*min)++;
    }
    if(*min == 60)
    {
        *min = 0;
        if(*hour < 12)
        {
            (*hour)++;
        } else {
            (*hour)++;
            *hour = *hour %12;
        }
    }
}

void digital_clock_count(int * hour, int * minute, int * seconds, char * meridiem)
{

    (*seconds)++;
    if(*seconds == 60) {
        *seconds = 0;
        (*minute)++;
    }
    if(*minute == 60) {
        *minute = 0;
        if(*hour < 12) {
            (*hour)++;
        }
        else {
            (*hour)++;
            (*hour) = (*hour) % 12;
        }
    }
    if(*hour == 12 && *seconds == 0 && *minute == 0) {
        if((lv_strcmp(meridiem, "PM") == 0)) {
            lv_strcpy(meridiem, "AM");
        }
        else {
            lv_strcpy(meridiem, "PM");
        }
    }
}


