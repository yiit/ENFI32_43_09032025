#include "../../_Plugin_Helper.h"
#include "../Helpers/Misc.h"
#include "../DataTypes/TaskIndex.h"
#include "../Commands/FYZ.h"

#include "../../ESPEasy-Globals.h"
#include "../../ESPEasy_common.h"

#include "../Commands/Common.h"

#include "../ESPEasyCore/ESPEasyNetwork.h"
#include "../ESPEasyCore/Serial.h"

#include "../Globals/SecuritySettings.h"
#include "../Globals/ESPEasy_time.h"
#include "../Globals/Settings.h"

#include "../Helpers/ESPEasy_Storage.h"
#include "../Helpers/ESPEasy_time_calc.h"
#include "../Helpers/Memory.h"
#include "../Helpers/Misc.h"
#include "../Helpers/StringConverter.h"

#include "../DataStructs/TimingStats.h"

#include "../DataStructs/ExtraTaskSettingsStruct.h"

#include "../Helpers/RulesMatcher.h"
#include "../ESPEasyCore/ESPEasyRules.h"
int qrkod_bas = 0;
int qrkod_son = 0;

/*#ifdef ESP32
#include <qrcode.h>

#define QRWIDTH 384
#define QRHEIGHT 240
uint8_t ucBuf[48 * 384];
String qrkod_data;

#include <Thermal_Printer.h>
uint8_t qr_x10 = 10;
uint8_t qr_x9 = 9;
uint8_t qr_x8 = 8;
uint8_t qr_x7 = 7;
uint8_t qr_x6 = 6;
uint8_t qr_x5 = 5;
uint8_t qr_x4 = 4;
uint8_t qr_x3 = 3;
uint8_t qr_x2 = 2;
uint8_t qr_x1 = 1;

uint8_t qr_w1 = 1;
#endif*/

#include "EEPROM.h"

String kopya_data_s = "#### FiS KOPYASI ####\r\n";

#if defined(USES_P120) || defined(USES_P121) || defined(USES_P122)

void fis_yazdir_hata(boolean aktif, int mod) {
  /*#ifdef ESP8266
  Serial.end();
  Serial.begin(115200);
  delay(200);
#endif*/
  //if (aktif)
#ifdef ESP8266
    Serial1.write((const uint8_t*)hata_beep, sizeof(hata_beep));
#endif
#ifdef ESP32
  //Serial1.write((const uint8_t*)hata_beep, sizeof(hata_beep));
#endif
#ifdef ESP32
#ifdef HAS_BLUETOOTH
  if (Settings.bluetooth_mod == 1)
    SerialBT.write((const uint8_t*)hata_beep, sizeof(hata_beep));
#endif
#endif
#ifdef ESP8266
  tone(16, 500);
  delay(1000);
  noTone(16);
  /*Serial.end();
  if (Settings.BaudBit == 1)
    Serial.begin(Settings.BaudRate, SERIAL_7E1);
  else
    Serial.begin(Settings.BaudRate, SERIAL_8N1);*/
#endif
#ifdef ESP32
#ifdef HAS_WIFI
  //ledcWriteTone(2, 500);
  //ledcWrite(2, 255);
  //delay(1000);
  //ledcWrite(2, 0);
#endif
#endif
}

void fis_yaz(String FIS, int mod) {
  kopya_data_s = "#### FiS KOPYASI ####\r\n";
#ifdef ESP32
#ifdef HAS_WIFI
  //ledcAttach(5, 1000, 2);
#endif
#endif
#ifdef ESP32
  int address = 0;
  EEPROM.writeLong(address, seri_no);
  address += sizeof(long);
  EEPROM.writeLong(address, sno);
  address += sizeof(long);
  EEPROM.writeFloat(address, top_net);
  address += sizeof(float);
  EEPROM.commit();
#else
  int address = 0;
  EEPROM.put(address, seri_no);
  address += sizeof(seri_no);
  EEPROM.put(address, top_net);
  address += sizeof(top_net);
  EEPROM.put(address, sno);
  address += sizeof(sno);
  EEPROM.commit();
#endif
  if (fileExists(FIS)) {
    fs::File form = tryOpenFile(FIS, "r");
    String file_data = "";
#ifdef ESP32
#ifdef HAS_BLUETOOTH
    if (Settings.bluetooth_mod == 1)
      SerialBT.write((const uint8_t*)okey_beep, sizeof(okey_beep));
#endif
#endif
    WiFiClient client;
    if (Settings.Cli_PrinterAktif)
      client.connect(Settings.Cli_PrinterIP, Settings.Cli_PrinterPort);
#ifdef ESP8266
    Serial1.write((const uint8_t*)okey_beep, sizeof(okey_beep));
    tone(16, 5000, 1000);
#endif
#ifdef ESP32
    //Serial1.write((const uint8_t*)okey_beep, sizeof(okey_beep));
    //Serial1.write((const uint8_t*)cekmece, sizeof(cekmece));
#ifdef HAS_WIFI
    //ledcWriteTone(2, 2000);
    //ledcWrite(2, 255);
#endif
#endif
    while (form.position() < form.size()) {
      file_data = form.readStringUntil('\n');
      parseTemplate(file_data);
      parse_string_commands(file_data);
      //parseSystemVariables(file_data, false);
      file_data += '\n';
      //*****************************************//
      qrkod_bas = file_data.indexOf('<');
      qrkod_son = file_data.indexOf('>');
#ifdef DIKOMSAN_VERSION
      Serial.print(file_data);
#endif
      /*#ifdef ESP32
      if (qrkod_son > 6) {
        qrkod_data = file_data.substring(qrkod_bas + 1, qrkod_son);
        qrkod_bas = 0;
        qrkod_son = 0;
        Serial1.println();
        tpSetBackBuffer(ucBuf, QRWIDTH, QRHEIGHT);
        tpFill(0);
        QRCode qrcode;
        uint8_t qrcodeData[qrcode_getBufferSize(5)];
        qrcode_initText(&qrcode, qrcodeData, 5, 0, qrkod_data.c_str());
        for (uint8_t y = 0; y < qrcode.size; y++) {
          for (uint8_t x = 0; x < qrcode.size; x++) {
            if (qrcode_getModule(&qrcode, x, y) == 1) {
              for (uint8_t w = 0; w < 5; w++) {
                tpDrawLine(qr_x1 + x * 5, qr_w1 + w + y * 5, qr_x2 + x * 5, qr_w1 + w + y * 5, 1);
                tpDrawLine(qr_x2 + x * 5, qr_w1 + w + y * 5, qr_x2 + x * 5, qr_w1 + w + y * 5, 1);
                tpDrawLine(qr_x3 + x * 5, qr_w1 + w + y * 5, qr_x3 + x * 5, qr_w1 + w + y * 5, 1);
                tpDrawLine(qr_x4 + x * 5, qr_w1 + w + y * 5, qr_x4 + x * 5, qr_w1 + w + y * 5, 1);
                tpDrawLine(qr_x5 + x * 5, qr_w1 + w + y * 5, qr_x5 + x * 5, qr_w1 + w + y * 5, 1);
                //tpDrawLine(x6 + x * 7, w1 + w + y * 7, x6 + x * 7, w1 + w + y * 7, 1);
                //tpDrawLine(x7 + x * 7, w1 + w + y * 7, x7 + x * 7, w1 + w + y * 7, 1);
              }
            }
          }
        }
        tpPrintBuffer();
        Serial1.println();
        qrkod_data = "";
      } else {
#endif*/
      yazdir_c[0] = 0;
      strncpy(yazdir_c, file_data.c_str(), file_data.length());
      for (int i = 0; i < file_data.length(); i++) {
        if (yazdir_c[i] == 94)
        Serial1.write(0);
        else if ((karakter_195) && (yazdir_c[i] == 135)) {  //Ç
          Serial1.write(128);
          karakter_195 = false;
        }
        else if ((karakter_195) && (yazdir_c[i] == 167)) {  //ç
          Serial1.write(135);
          karakter_195 = false;
        }
        else if ((karakter_195) && (yazdir_c[i] == 150)) {  //Ö
          Serial1.write(153);
          karakter_195 = false;
        }
        else if ((karakter_195) && (yazdir_c[i] == 182)) {  //ö
          Serial1.write(148);
          karakter_195 = false;
        }
        else if ((karakter_195) && (yazdir_c[i] == 156)) {  //Ü
          Serial1.write(154);
          karakter_195 = false;
        }
        else if ((karakter_195) && (yazdir_c[i] == 188)) {  //ü
          Serial1.write(129);
          karakter_195 = false;
        }
        else if ((karakter_196) && (yazdir_c[i] == 158)) {  //Ğ
          Serial1.write(166);
          karakter_196 = false;
        }
        else if ((karakter_196) && (yazdir_c[i] == 159)) {  //ğ
          Serial1.write(167);
          karakter_196 = false;
        }
        else if ((karakter_196) && (yazdir_c[i] == 176)) {  //İ
          Serial1.write(152);
          karakter_196 = false;
        }
        else if ((karakter_196) && (yazdir_c[i] == 177)) {  //ı
          Serial1.write(141);
          karakter_196 = false;
        }
        else if ((karakter_197) && (yazdir_c[i] == 158)) {  //Ş
          Serial1.write(158);
          karakter_197 = false;
        }
        else if ((karakter_197) && (yazdir_c[i] == 159)) {  //ş
          Serial1.write(159);
          karakter_197 = false;
        }
        else if (yazdir_c[i] == 195)
        karakter_195 = true;
        else if (yazdir_c[i] == 196)
        karakter_196 = true;
        else if (yazdir_c[i] == 197)
        karakter_197 = true;
        //else if (yazdir_c[i] == 253)
        //Serial.write(uint8_t(qrkod_data.length()+3) % 256);
        /*else if (yazdir_c[i] == 254)
#ifdef ESP8266
          Serial1.write(uint8_t(qrkod_data.length() + 3));
#endif
#ifdef ESP32
        Serial1.write(uint8_t(qrkod_data.length() + 3));
#endif*/
        //Serial.write(uint8_t(qrkod_data.length()+3) / 256);
        else {
          Serial1.write(yazdir_c[i]);
          kopya_data_s += String(yazdir_c[i]);
        }
      }
      /*#ifdef ESP32
      }
#endif*/
      if (Settings.Cli_PrinterAktif)
        client.print(file_data);
#ifdef ESP32
#ifdef HAS_BLUETOOTH
      if (Settings.bluetooth_mod == 1)
        SerialBT.print(file_data);
#endif
/*#ifdef HAS_BLE
        const char* name = "RPP200";
        tpScan(name, 5);
        tpConnect();
        tpPrint(file_data.c_str());
        tpDisconnect();
#endif*/
#endif
      //file_data.trim();
    }
    form.close();
    if (Settings.Cli_PrinterAktif) {
      unsigned long timeout = millis();
      if (client.available() == 0) {
        if (millis() - timeout > 5000) {
          client.stop();
        }
      }
    }
  }
/*#ifdef FEATURE_SD
  String dosya_sd = "/";
  dosya_sd += node_time.getDateString('_');
  dosya_sd += ".dat";
  File logFile = SD.open(dosya_sd, "a");
  if (logFile) {
    String data = XML_TARIH_S;
    data += ",";
    data += XML_SAAT_S;
    data += ",";
    data += XML_QRKOD_S;
    data += ",";
    data += XML_NET_S;
    logFile.println(data);
  }
  logFile.close();
#endif*/
  delay(1000);
#ifdef ESP8266
  noTone(16);
#endif
  XML_URUN_ISMI_S = "";
  XML_BARKOD_S = "";
  XML_MESAJ1_S = "";
  XML_MESAJ2_S = "";
  XML_MESAJ3_S = "";
  XML_MESAJ4_S = "";
  toplam_detay = "";
#ifdef ESP32
#ifdef HAS_WIFI
  //ledcWrite(2, 0);
#endif
#endif
}

String Command_Fyz_Test(struct EventStruct* event, const char* Line) {
  String TmpStr1;
  String fyz_test = "";
  dtostrf(123456.7, 7, 1, XML_NET_C);
  dtostrf(123456.7, 7, 1, XML_DARA_C);
  dtostrf(123456.7, 7, 1, XML_BRUT_C);
  dtostrf(1234567, 7, 0, XML_ADET_C);
  dtostrf(123456.7, 7, 1, XML_TOP_NET_C);
  dtostrf(123456.7, 7, 1, XML_TOP_DARA_C);
  dtostrf(123456.7, 7, 1, XML_TOP_BRUT_C);
  dtostrf(1234567, 7, 0, XML_ADET_C);
  dtostrf(123, 3, 0, XML_SNO_C);
  dtostrf(123.4567, 7, 4, XML_ADET_GRAMAJ_C);
  XML_TARIH_S = node_time.getDateString('-');
  XML_SAAT_S = node_time.getTimeString(':');
  if (GetArgv(Line, TmpStr1, 2))
    fyz_test = TmpStr1;
  fis_yaz(fyz_test, 1);
  //return return_see_serial(event);
  return return_command_success();
}

String Command_Fyz_Art(struct EventStruct* event, const char* Line) {
  String TmpStr1;
  float fyz_art_f = 0;
  kopya_data_s = "";
  if (GetArgv(Line, TmpStr1, 2)) {
    fyz_art_f = TmpStr1.toFloat();
    if (fyz_art_f > 0)
      XML_NET_S = String(fyz_art_f, int(ExtraTaskSettings.TaskDeviceValueDecimals[0]));
  }
  if (XML_NET_S.toFloat() > 0.00001) {
    sno = sno + 1;
    XML_SNO_S = String(sno);
    top_net = XML_NET_S.toFloat() + top_net;
    XML_TOP_NET_S = top_net;
    top_dara = XML_DARA_S.toFloat() + top_dara;
    XML_TOP_DARA_S = top_dara;
    top_brut = XML_BRUT_S.toFloat() + top_brut;
    XML_TOP_BRUT_S = top_brut;
  }
  dtostrf(sno, 3, 0, XML_SNO_C);
  if (sno == 1 && ((XML_NET_S.toFloat() > 0.00001) || (Settings.UseNegatifYaz))) {
    if (Settings.UseNegatifYaz) {
      XML_TARIH_S = node_time.getDateString('-');
      XML_SAAT_S = node_time.getTimeString(':');
    }
    fis_no = fis_no + 1;
    XML_FIS_NO_S = String(fis_no);
    dtostrf(fis_no, 8, 0, XML_FIS_NO_C);
    seri_no = seri_no + 1;
    XML_SERI_NO_S = String(seri_no);
    dtostrf(seri_no, 8, 0, XML_SERI_NO_C);
    kopya_data_s = "#### FiS KOPYASI ####\r\n";
    fis_yaz(Settings.art_prn, 1);
  } else if ((XML_NET_S.toFloat() > 0.0001) || (Settings.UseNegatifYaz)) {
    if (Settings.UseNegatifYaz) {
      XML_TARIH_S = node_time.getDateString('-');
      XML_SAAT_S = node_time.getTimeString(':');
    }
    fis_yaz(Settings.ek_prn, 1);
  } else
    fis_yazdir_hata(true, 1);
  XML_URUN_ISMI_S = "";
  //return return_see_serial(event);
  return return_command_success();
}


String Command_Fyz_Top(struct EventStruct* event, const char* Line) {
  String TmpStr1 = "0";
  int test_fyz_i = 0;
  kopya_data_s = "";
  if (GetArgv(Line, TmpStr1, 2))
    test_fyz_i = TmpStr1.toInt();
  dtostrf(top_net, 8, int(ExtraTaskSettings.TaskDeviceValueDecimals[0]), XML_TOP_NET_C);
  dtostrf(top_dara, 8, int(ExtraTaskSettings.TaskDeviceValueDecimals[1]), XML_TOP_DARA_C);
  dtostrf(top_brut, 8, int(ExtraTaskSettings.TaskDeviceValueDecimals[2]), XML_TOP_BRUT_C);
  if (sno == 0 && ((XML_NET_S.toFloat() > 0.00001) || (Settings.UseNegatifYaz))) {
    if (Settings.UseNegatifYaz) {
      XML_TARIH_S = node_time.getDateString('-');
      XML_SAAT_S = node_time.getTimeString(':');
    }
    fis_no = fis_no + 1;
    XML_FIS_NO_S = String(fis_no);
    dtostrf(fis_no, 8, 0, XML_FIS_NO_C);
    seri_no = seri_no + 1;
    XML_SERI_NO_S = String(seri_no);
    dtostrf(seri_no, 8, 0, XML_SERI_NO_C);
    kopya_data_s = "#### FiS KOPYASI ####\r\n";
    fis_yaz(Settings.tek_prn, 1);
  } else if ((top_net > 0.00001) || (Settings.UseNegatifYaz)) {
    if (Settings.UseNegatifYaz) {
      XML_TARIH_S = node_time.getDateString('-');
      XML_SAAT_S = node_time.getTimeString(':');
    }
    XML_SNO_S = String(sno);
    dtostrf(sno, 3, 0, XML_SNO_C);
    dtostrf(top_net, 8, int(ExtraTaskSettings.TaskDeviceValueDecimals[0]), XML_TOP_NET_C);
    dtostrf(top_dara, 8, int(ExtraTaskSettings.TaskDeviceValueDecimals[1]), XML_TOP_DARA_C);
    dtostrf(top_brut, 8, int(ExtraTaskSettings.TaskDeviceValueDecimals[2]), XML_TOP_BRUT_C);
    fis_yaz(Settings.top_prn, 1);
  } else
    fis_yazdir_hata(true, 1);
  XML_URUN_ISMI_S = "";
  sno = 0;
  XML_SNO_S = sno;
  top_net = 0;
  XML_TOP_NET_S = top_net;
  top_dara = 0;
  XML_TOP_DARA_S = top_dara;
  top_brut = 0;
  XML_TOP_BRUT_S = top_brut;
#ifdef ESP32
  int address = 0;
  EEPROM.writeLong(address, seri_no);
  address += sizeof(long);
  EEPROM.writeLong(address, sno);
  address += sizeof(long);
  EEPROM.writeFloat(address, top_net);
  address += sizeof(float);
  EEPROM.commit();
#else
  int address = 0;
  EEPROM.put(address, seri_no);
  address += sizeof(seri_no);
  EEPROM.put(address, top_net);
  address += sizeof(top_net);
  EEPROM.put(address, sno);
  address += sizeof(sno);
  EEPROM.commit();
#endif
  //return return_see_serial(event);
  return return_command_success();
}

String Command_Fyz_Kopya(struct EventStruct* event, const char* Line) {
#ifdef ESP8266
  Serial1.println(kopya_data_s);
#endif
#ifdef ESP32
  //Serial1.println(kopya_data_s);
#endif
  //return return_see_serial(event);
  return return_command_success();
}

String Command_Fyz_Urun_Art(struct EventStruct* event, const char* Line) {
  String TmpStr1  = "0";
  String TmpStr2  = "0";
  String TmpStr3  = "0";
  String TmpStr4  = "0";
  String TmpStr5  = "0";
  String TmpStr6  = "0";
  String TmpStr7  = "0";
  String TmpStr8  = "0";
  String TmpStr9  = "0";
  String TmpStr10 = "0";
  String TmpStr11 = "0";  
  int8_t urunno_click = 0;
  int8_t test_fyz_i = 0;
  int8_t firma_click = 0;
  int8_t mesaj1_no = 0;
  int8_t mesaj2_no = 0;
  int8_t mesaj3_no = 0;
  int8_t mesaj4_no = 0;
  int8_t mesaj5_no = 0;
  int8_t mesaj6_no = 0;
  int8_t mesaj7_no = 0;
  int8_t mesaj8_no = 0;
  if (GetArgv(Line, TmpStr1, 2))
    urunno_click = TmpStr1.toInt();
  if (GetArgv(Line, TmpStr2, 3))
    test_fyz_i = TmpStr2.toInt();
  if (GetArgv(Line, TmpStr3, 5))
    firma_click = TmpStr3.toInt();
  if (GetArgv(Line, TmpStr4, 6))
    mesaj1_no = TmpStr4.toInt();
  if (GetArgv(Line, TmpStr5, 7))
    mesaj2_no = TmpStr5.toInt();
  if (GetArgv(Line, TmpStr6, 8))
    mesaj3_no = TmpStr6.toInt();
  if (GetArgv(Line, TmpStr7, 9))
    mesaj4_no = TmpStr7.toInt();
  if (GetArgv(Line, TmpStr8, 9))
    mesaj5_no = TmpStr8.toInt();
  if (GetArgv(Line, TmpStr9, 10))
    mesaj6_no = TmpStr9.toInt();
  if (GetArgv(Line, TmpStr10, 11))
    mesaj7_no = TmpStr10.toInt();
  if (GetArgv(Line, TmpStr11, 12))
    mesaj8_no = TmpStr11.toInt();
  if (urunno_click == 0) {
    Serial1.println(kopya_data_s);
    delay(100);
  }
  else {
    XML_URUN_ISMI_S = urun_labels[urunno_click];
    XML_URUN_KOD_S = urun_kod_labels[urunno_click];
    float bol = 1;
    switch (ExtraTaskSettings.TaskDeviceValueDecimals[0]) {
      case 0: bol = 1; break;
      case 1: bol = 10; break;
      case 2: bol = 100; break;
      case 3: bol = 1000; break;
      case 4: bol = 10000; break;
    }
    dtostrf(XML_NET_S.toFloat() * bol, 5, 0, XML_BARKOD_C);
    int tartim = atoi(XML_BARKOD_C);
    char XML_NET_BARKOD_C[6];
    snprintf_P(XML_NET_BARKOD_C, sizeof(XML_NET_BARKOD_C), PSTR("%05u"), tartim);
  
    XML_EAN8_S = XML_URUN_KOD_S;
    XML_EAN13_S = XML_URUN_KOD_S + XML_NET_BARKOD_C;

    if ((mesaj1_no == 0) || (!M_buton_aktif[0]))
      XML_MESAJ1_S = "";
    else
      XML_MESAJ1_S = mesaj_labels[0][mesaj1_no];
    if ((mesaj2_no == 0) || (!M_buton_aktif[1]))
      XML_MESAJ2_S = "";
    else
      XML_MESAJ2_S = mesaj_labels[1][mesaj2_no];
    if ((mesaj1_no == 0) || (!M_buton_aktif[2]))
      XML_MESAJ3_S = "";
    else
      XML_MESAJ3_S = mesaj_labels[2][mesaj3_no];
    if ((mesaj1_no == 0) || (!M_buton_aktif[3]))
      XML_MESAJ4_S = "";
    else  
      XML_MESAJ4_S = mesaj_labels[3][mesaj4_no];
    if ((mesaj5_no == 0) || (!M_buton_aktif[4]))
      XML_MESAJ5_S = "";
    else
      XML_MESAJ5_S = mesaj_labels[4][mesaj5_no];
    if ((mesaj6_no == 0) || (!M_buton_aktif[5]))
      XML_MESAJ6_S = "";
    else
      XML_MESAJ6_S = mesaj_labels[5][mesaj6_no];
    if ((mesaj7_no == 0) || (!M_buton_aktif[6]))
      XML_MESAJ7_S = "";
    else
      XML_MESAJ7_S = mesaj_labels[6][mesaj7_no];
    if ((mesaj8_no == 0) || (!M_buton_aktif[7]))
      XML_MESAJ8_S = "";
    else  
      XML_MESAJ8_S = mesaj_labels[7][mesaj8_no];
  if (XML_NET_S.toFloat() > 0.00001) {
    sno = sno + 1;
    XML_SNO_S = String(sno);
    top_net = XML_NET_S.toFloat() + top_net;
    XML_TOP_NET_S = top_net;
    top_dara = XML_DARA_S.toFloat() + top_dara;
    XML_TOP_DARA_S = top_dara;
    top_brut = XML_BRUT_S.toFloat() + top_brut;
    XML_TOP_BRUT_S = top_brut;
    urun_net[urunno_click] = XML_NET_S.toFloat() + urun_net[urunno_click];
    urun_adet[urunno_click] = 1 + urun_adet[urunno_click];
  }
  dtostrf(sno, 3, 0, XML_SNO_C);
  if (sno == 1 && ((XML_NET_S.toFloat() > 0.00001) || (Settings.UseNegatifYaz))) {
    if (Settings.UseNegatifYaz) {
      XML_TARIH_S = node_time.getDateString('-');
      XML_SAAT_S = node_time.getTimeString(':');
    }
    fis_no = fis_no + 1;
    XML_FIS_NO_S = String(fis_no);
    dtostrf(fis_no, 8, 0, XML_FIS_NO_C);
    seri_no = seri_no + 1;
    XML_SERI_NO_S = String(seri_no);
    dtostrf(seri_no, 8, 0, XML_SERI_NO_C);
    kopya_data_s = "#### FiS KOPYASI ####\r\n";
    fis_yaz(Settings.urun_art_prn, 1);
  } else if ((XML_NET_S.toFloat() > 0.0001) || (Settings.UseNegatifYaz)) {
    if (Settings.UseNegatifYaz) {
      XML_TARIH_S = node_time.getDateString('-');
      XML_SAAT_S = node_time.getTimeString(':');
    }
    fis_yaz(Settings.urun_ek_prn, 1);
  } else
    fis_yazdir_hata(true, 1);
  XML_URUN_ISMI_S = "";
    //if (XML_NET_S.toFloat() > 0.00001)   {
  }
  return return_command_success();
}

String Command_Fyz_Urun_Tek(struct EventStruct* event, const char* Line) {
  String TmpStr1 = "0";
  String TmpStr2 = "0";
  String TmpStr3 = "0";
  String TmpStr4 = "0";
  String TmpStr5 = "0";
  String TmpStr6 = "0";
  String TmpStr7 = "0";
  String TmpStr8 = "0";
  String TmpStr9  = "0";
  String TmpStr10 = "0";
  String TmpStr11 = "0";
  int8_t urunno_click = 0;
  int8_t test_fyz_i = 0;
  int8_t firma_click = 0;
  int8_t mesaj1_no = 0;
  int8_t mesaj2_no = 0;
  int8_t mesaj3_no = 0;
  int8_t mesaj4_no = 0;
  int8_t mesaj5_no = 0;
  int8_t mesaj6_no = 0;
  int8_t mesaj7_no = 0;
  int8_t mesaj8_no = 0;
  kopya_data_s = "";
  if (GetArgv(Line, TmpStr1, 2))
    urunno_click = TmpStr1.toInt();
  if (GetArgv(Line, TmpStr2, 3))
    test_fyz_i = TmpStr2.toInt();
  if (GetArgv(Line, TmpStr3, 4))
    firma_click = TmpStr3.toInt();
  if (GetArgv(Line, TmpStr4, 5))
    mesaj1_no = TmpStr4.toInt();
  if (GetArgv(Line, TmpStr5, 6))
    mesaj2_no = TmpStr5.toInt();
  if (GetArgv(Line, TmpStr6, 7))
    mesaj3_no = TmpStr6.toInt();
  if (GetArgv(Line, TmpStr7, 8))
    mesaj4_no = TmpStr7.toInt();
  if (GetArgv(Line, TmpStr8, 9))
    mesaj5_no = TmpStr8.toInt();
  if (GetArgv(Line, TmpStr9, 10))
    mesaj6_no = TmpStr9.toInt();
  if (GetArgv(Line, TmpStr10, 11))
    mesaj7_no = TmpStr10.toInt();
  if (GetArgv(Line, TmpStr11, 12))
    mesaj8_no = TmpStr11.toInt();
  if (urunno_click == 0) {
    Serial1.println(kopya_data_s);
    delay(100);
  } else {  
    XML_URUN_ISMI_S = urun_labels[urunno_click];
    XML_URUN_KOD_S = urun_kod_labels[urunno_click];
    float bol = 1;
    switch (ExtraTaskSettings.TaskDeviceValueDecimals[0]) {
      case 0: bol = 1; break;
      case 1: bol = 10; break;
      case 2: bol = 100; break;
      case 3: bol = 1000; break;
      case 4: bol = 10000; break;
    }
    dtostrf(XML_NET_S.toFloat() * bol, 5, 0, XML_BARKOD_C);
    int tartim = atoi(XML_BARKOD_C);
    char XML_NET_BARKOD_C[6];
    snprintf_P(XML_NET_BARKOD_C, sizeof(XML_NET_BARKOD_C), PSTR("%05u"), tartim);
  
    XML_EAN8_S = XML_URUN_KOD_S;
    XML_EAN13_S = XML_URUN_KOD_S + XML_NET_BARKOD_C;
    if ((mesaj1_no == 0) || (!M_buton_aktif[0]))
      XML_MESAJ1_S = "";
    else
      XML_MESAJ1_S = mesaj_labels[0][mesaj1_no];
    if ((mesaj2_no == 0) || (!M_buton_aktif[1]))
      XML_MESAJ2_S = "";
    else
      XML_MESAJ2_S = mesaj_labels[1][mesaj2_no];
    if ((mesaj3_no == 0) || (!M_buton_aktif[2]))
      XML_MESAJ3_S = "";
    else
      XML_MESAJ3_S = mesaj_labels[2][mesaj3_no];
    if ((mesaj4_no == 0) || (!M_buton_aktif[3]))
      XML_MESAJ4_S = "";
    else  
      XML_MESAJ4_S = mesaj_labels[3][mesaj4_no];
      char* label = mesaj_labels[3][mesaj4_no];
      if (strcmp(label, "FIS") == 0) {
        const char* prefix = "/rules/fyzurun";
        const char* suffix = ".prn";
        // Dizinin başına ekleme yap
        strcpy(Settings.urun_tek_prn, prefix);           // Önce prefix'i kopyala
        strcat(Settings.urun_tek_prn, mesaj_labels[3][mesaj4_no]);            // Ardından ana içeriği ekle
        strcat(Settings.urun_tek_prn, suffix);           // Son olarak suffix'i ekle
        //strncpy(Settings.urun_tek_prn, M4[mesaj4_no], sizeof(Settings.urun_tek_prn) - 1);
        //Settings.urun_tek_prn[sizeof(Settings.urun_tek_prn) - 1] = '\0';
      }
    if ((mesaj5_no == 0) || (!M_buton_aktif[4]))
      XML_MESAJ5_S = "";
    else
      XML_MESAJ5_S = mesaj_labels[4][mesaj5_no];
    if ((mesaj6_no == 0) || (!M_buton_aktif[5]))
      XML_MESAJ6_S = "";
    else
      XML_MESAJ6_S = mesaj_labels[5][mesaj6_no];
    if ((mesaj7_no == 0) || (!M_buton_aktif[6]))
      XML_MESAJ7_S = "";
    else
      XML_MESAJ7_S = mesaj_labels[6][mesaj7_no];
    if ((mesaj8_no == 0) || (!M_buton_aktif[7]))
      XML_MESAJ8_S = "";
    else  
      XML_MESAJ8_S = mesaj_labels[7][mesaj8_no];
  if (GetArgv(Line, TmpStr1, 2))
    test_fyz_i = TmpStr1.toInt();
  dtostrf(top_net, 8, int(ExtraTaskSettings.TaskDeviceValueDecimals[0]), XML_TOP_NET_C);
  dtostrf(top_dara, 8, int(ExtraTaskSettings.TaskDeviceValueDecimals[1]), XML_TOP_DARA_C);
  dtostrf(top_brut, 8, int(ExtraTaskSettings.TaskDeviceValueDecimals[2]), XML_TOP_BRUT_C);
  if (sno == 0 && ((XML_NET_S.toFloat() > 0.00001) || (Settings.UseNegatifYaz))) {
    if (Settings.UseNegatifYaz) {
      XML_TARIH_S = node_time.getDateString('-');
      XML_SAAT_S = node_time.getTimeString(':');
    }
    fis_no = fis_no + 1;
    XML_FIS_NO_S = String(fis_no);
    dtostrf(fis_no, 8, 0, XML_FIS_NO_C);
    seri_no = seri_no + 1;
    XML_SERI_NO_S = String(seri_no);
    dtostrf(seri_no, 8, 0, XML_SERI_NO_C);
    kopya_data_s = "#### FiS KOPYASI ####\r\n";
    fis_yaz(Settings.urun_tek_prn, 1);
  } else if ((top_net > 0.00001) || (Settings.UseNegatifYaz)) {
    if (Settings.UseNegatifYaz) {
      XML_TARIH_S = node_time.getDateString('-');
      XML_SAAT_S = node_time.getTimeString(':');
    }
    XML_SNO_S = String(sno);
    dtostrf(sno, 3, 0, XML_SNO_C);
    dtostrf(top_net, 8, int(ExtraTaskSettings.TaskDeviceValueDecimals[0]), XML_TOP_NET_C);
    dtostrf(top_dara, 8, int(ExtraTaskSettings.TaskDeviceValueDecimals[1]), XML_TOP_DARA_C);
    dtostrf(top_brut, 8, int(ExtraTaskSettings.TaskDeviceValueDecimals[2]), XML_TOP_BRUT_C);
    for (uint8_t urunno = 1;urunno < 254;urunno++) {
      if (urun_net[urunno] > 0) {
        char toplam_detay_c[64];
        sprintf_P(toplam_detay_c, PSTR("%02d)%16s : %9.3f kg Adet: %03u\r\n"), urunno, urun_labels[urunno],urun_net[urunno], urun_adet[urunno]);
        toplam_detay += String(toplam_detay_c);// urunadi[urunno]+": "+String(urunnet[urunno].toFloat(), 1)+" kg"+"   Adet : "+urunadet[urunno] +"\r\n";
        urun_net[urunno]  = 0;
        urun_adet[urunno] = 0;
      }
    }
    fis_yaz(Settings.urun_top_prn, 1);
  } else
    fis_yazdir_hata(true, 1);
  XML_URUN_ISMI_S = "";
  sno = 0;
  XML_SNO_S = sno;
  top_net = 0;
  XML_TOP_NET_S = top_net;
  top_dara = 0;
  XML_TOP_DARA_S = top_dara;
  top_brut = 0;
  XML_TOP_BRUT_S = top_brut;
#ifdef ESP32
  int address = 0;
  EEPROM.writeLong(address, seri_no);
  address += sizeof(long);
  EEPROM.writeLong(address, sno);
  address += sizeof(long);
  EEPROM.writeFloat(address, top_net);
  address += sizeof(float);
  EEPROM.commit();
#else
  int address = 0;
  EEPROM.put(address, seri_no);
  address += sizeof(seri_no);
  EEPROM.put(address, top_net);
  address += sizeof(top_net);
  EEPROM.put(address, sno);
  address += sizeof(sno);
  EEPROM.commit();
#endif
  }
  //return return_see_serial(event);
  return return_command_success();
}

String Command_Fyz_Yaz(struct EventStruct* event, const char* Line) {
  String TmpStr1;
  String md5data;
  if (GetArgv(Line, TmpStr1, 2))
    XML_FIRMA_ISMI_S = TmpStr1;
  if (GetArgv(Line, TmpStr1, 3))
    XML_TARIH_V = TmpStr1;
  if (GetArgv(Line, TmpStr1, 4))
    XML_SAAT_V = TmpStr1;
  if (GetArgv(Line, TmpStr1, 5))
    XML_PLAKA_NO_S = TmpStr1;
  if (GetArgv(Line, TmpStr1, 6))
    XML_OPERATOR_ISMI_S = TmpStr1;
  if (GetArgv(Line, TmpStr1, 7))
    XML_MUSTERI_ISMI_S = TmpStr1;
  if (GetArgv(Line, TmpStr1, 8))
    XML_URUN_ISMI_S = TmpStr1;
  if (GetArgv(Line, TmpStr1, 9))
    XML_NET_V = TmpStr1;
  if (GetArgv(Line, TmpStr1, 10)) {
    md5data = TmpStr1;
    String md5chck = "fyzyaz";
    md5chck += "#";
    md5chck += XML_FIRMA_ISMI_S;
    md5chck += "#";
    md5chck += XML_TARIH_V;
    md5chck += "#";
    md5chck += XML_SAAT_V;
    md5chck += "#";
    md5chck += XML_PLAKA_NO_S;
    md5chck += "#";
    md5chck += XML_OPERATOR_ISMI_S;
    md5chck += "#";
    md5chck += XML_MUSTERI_ISMI_S;
    md5chck += "#";
    md5chck += XML_URUN_ISMI_S;
    md5chck += "#";
    md5chck += XML_NET_V;
    md5chck += "#";
    //Serial.println(md5chck);
    _md5.begin();
    _md5.add(md5chck);
    _md5.calculate();
    _md5.toString();
    //Serial.println(_md5.toString());
    //Serial.println(md5data);
  }
  if (_md5.toString() == md5data) {
    fis_yaz(FIS_YAZ, 2);
  } else {
    fis_yazdir_hata(true, 2);
    return return_command_failed();
  }
  //return return_command_yazdir();
  return return_command_success();
}

String Command_Fyz_Yaz_Satir(struct EventStruct* event, const char* Line) {
  String TmpStr1;
  String message;
  if (GetArgv(Line, TmpStr1, 2)) {
    message = TmpStr1;
    message += "\r\n";
  }
  if (message.length() > 0) {
    //Serial1.write((const uint8_t*)okey_beep, sizeof(okey_beep));
    //Serial1.println(message);
    yazdir_c[0] = 0;
    strncpy(yazdir_c, message.c_str(), message.length());
    for (int i = 0; i < message.length(); i++) {
      if (yazdir_c[i] == 94) {Serial1.write(0);}        
      else if ((karakter_195) && (yazdir_c[i] == 135)) { Serial1.write(128); karakter_195 = false;} //Ç
      else if ((karakter_195) && (yazdir_c[i] == 167)) { Serial1.write(135); karakter_195 = false;} //ç
      else if ((karakter_195) && (yazdir_c[i] == 150)) { Serial1.write(153); karakter_195 = false;} //Ö
      else if ((karakter_195) && (yazdir_c[i] == 182)) { Serial1.write(148); karakter_195 = false;} //ö
      else if ((karakter_195) && (yazdir_c[i] == 156)) { Serial1.write(154); karakter_195 = false;} //Ü
      else if ((karakter_195) && (yazdir_c[i] == 188)) { Serial1.write(129); karakter_195 = false;} //ü
      else if ((karakter_196) && (yazdir_c[i] == 158)) { Serial1.write(166); karakter_196 = false;} //Ğ
      else if ((karakter_196) && (yazdir_c[i] == 159)) { Serial1.write(167); karakter_196 = false;} //ğ
      else if ((karakter_196) && (yazdir_c[i] == 176)) { Serial1.write(152); karakter_196 = false;} //İ
      else if ((karakter_196) && (yazdir_c[i] == 177)) { Serial1.write(141); karakter_196 = false;} //ı
      else if ((karakter_197) && (yazdir_c[i] == 158)) { Serial1.write(158); karakter_197 = false;} //Ş
      else if ((karakter_197) && (yazdir_c[i] == 159)) { Serial1.write(159); karakter_197 = false;} //ş
      else if (yazdir_c[i] == 195) {karakter_195 = true;}
      else if (yazdir_c[i] == 196) {karakter_196 = true;}
      else if (yazdir_c[i] == 197) {karakter_197 = true;}
      else {Serial1.write(yazdir_c[i]);}
    }
  } else {
    fis_yazdir_hata(true, 2);
    return return_command_failed();
  }
  //return return_command_yazdir();
  //return return_command_success();
  //return return_see_serial(event);
  return F("");
}

String Command_Fyz_Esc_Pos(struct EventStruct* event, const char* Line) {
  String TmpStr1;
  int time = 5;
  if (GetArgv(Line, TmpStr1, 2))
    time = TmpStr1.toInt();
#ifdef ESP8266
  Serial1.write((const uint8_t*)okey_beep, sizeof(okey_beep));
#endif
#ifdef ESP32
  //Serial1.write((const uint8_t*)okey_beep, sizeof(okey_beep));
#endif
  escpos_mod = true;
  escpos_time = millis() + (time * 1000);
  //return return_command_yazdir();
  return return_command_success();
}

String Command_Fyz_Net(struct EventStruct* event, const char* Line) {
#ifdef ESP8266
  Serial1.write((const uint8_t*)okey_beep, sizeof(okey_beep));
#endif
#ifdef ESP32
  //Serial1.write((const uint8_t*)okey_beep, sizeof(okey_beep));
#endif
#if defined(ESP32)
#ifdef HAS_BLUETOOTH
  if (Settings.bluetooth_mod == 2)
    SerialBT.println("TARTIM:" + XML_NET_S);
#endif
#endif
  return F("");
  //return return_see_serial(event);
  //return return_command_success();
}

String Command_Fyz_Serino(struct EventStruct* event, const char* Line) {
  String TmpStr1 = "0";
  if (GetArgv(Line, TmpStr1, 2))
    seri_no = TmpStr1.toInt();
  XML_SERI_NO_S = String(seri_no);
  dtostrf(seri_no, 8, 0, XML_SERI_NO_C);
  for (int addr = 0; addr < 9; addr++) {
    EEPROM.write(addr, (byte)(XML_SERI_NO_C[addr]));
  }
  return return_command_success();
}
#endif