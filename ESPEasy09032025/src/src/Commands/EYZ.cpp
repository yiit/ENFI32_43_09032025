#include "HardwareSerial.h"
#include "../Commands/EYZ.h"

#include "../../_Plugin_Helper.h"
#include "../Helpers/Misc.h"
#include "../DataTypes/TaskIndex.h"

#include "../../ESPEasy-Globals.h"
#include "../../ESPEasy_common.h"

#include "../Commands/Common.h"

#include "../ESPEasyCore/ESPEasyNetwork.h"
#include "../ESPEasyCore/Serial.h"

#include "../Globals/SecuritySettings.h"
#include "../Globals/ESPEasy_time.h"
#include "../Globals/Settings.h"

#include "../Helpers/Misc.h"
#include "../Helpers/Memory.h"
#include "../Helpers/ESPEasy_Storage.h"
#include "../Helpers/ESPEasy_time_calc.h"
#include "../Helpers/StringConverter.h"
#include "../Helpers/SystemVariables.h"

#include "../DataStructs/TimingStats.h"

#include "../Helpers/Hardware.h"

#include "../ESPEasyCore/Controller.h"

#include "../DataStructs/ExtraTaskSettingsStruct.h"

#include "../Helpers/RulesMatcher.h"
#include "../ESPEasyCore/ESPEasyRules.h"

#include <HTTPClient.h>

#include <FS.h>

#if FEATURE_SD
#include <SD.h>
#include "../Helpers/ESPEasy_Storage.h"
#endif

#if defined(USES_P130) || defined(USES_P131) || defined(USES_P132) || defined(USES_P133) || defined(USES_140)

long control_data = 0;

void etiket_yazdir_hata(boolean aktif, int mod) {
  if (aktif) {
    Serial1.println("SOUND 100,2");
    Serial1.println("BEEP");
  }
#ifdef HAS_BLUETOOTH
  if (Settings.bluetooth_mod == 1)
    SerialBT.write((const uint8_t*)hata_beep, sizeof(hata_beep));
#endif
}

void etiket_yaz(String ETIKET, int BTmod, int HTTPmod, int SERIALmod, bool CLImod) {
  //ETIKET = "/eyzuruntek.prn";
  //yazdirEtiket();
  int address = 0;
  EEPROM.writeLong(address, seri_no);
  address += sizeof(uint32_t);
  EEPROM.writeLong(address, sno);
  address += sizeof(uint32_t);
  EEPROM.writeFloat(address, top_net);
  address += sizeof(float);
  EEPROM.writeLong(address, top_adet);
  address += sizeof(uint32_t);
  //EEPROM.writeLong(200 + (sirano_aktif * 4), sirano_s[sirano_aktif].toInt());
  EEPROM.commit();
  if (fileExists(ETIKET)) {
    fs::File form = tryOpenFile(ETIKET, "r");
    if (!ExtraTaskSettings.TaskPrintBartender) {
      String file_data = "";
      String http_data = "";
      kopya_etiket = "";
      WiFiClient client;
      if (CLImod) {
        client.setTimeout(1);
        client.connect(Settings.Cli_PrinterIP, Settings.Cli_PrinterPort, 100);
      }
      if ((Settings.Web_ServisAktif) && (HTTPmod == 1))
        client.connect(Settings.Web_ServisAdres, Settings.Web_ServisPort, 100);
      Serial1.println("SOUND 1,100");
      //Serial1.println("BEEP");
#ifdef HAS_WIFI
    //ledcWriteTone(2, 2000);
    //ledcWrite(2, 255);
#endif
      while (form.position() < form.size()) {
        file_data = form.readStringUntil('\n');
        file_data.replace("ENDUTEK.TTF","0");
        parseTemplate(file_data);
        parse_string_commands(file_data);
        //parseSystemVariables(file_data, false);
        file_data += '\n';
        if (HTTPmod)
          http_data += file_data;
        if ((CLImod) && (Settings.Cli_PrinterAktif)) {
          client.print(file_data);
          //String line = client.readStringUntil('\n');
          //client.println(line);
        }
        if ((CLImod) && (Settings.Web_ServisAktif)) {
          if (fileExists(Settings.sd_prn)) {
            fs::File form = tryOpenFile(Settings.sd_prn, "r");
            String file_data = "";
            while (form.position() < form.size()) {
              file_data = form.readStringUntil('\n');
              file_data.replace("ENDUTEK.TTF","0");
              parseTemplate(file_data);
              parse_string_commands(file_data);
              //file_data += '\n';
              client.print(file_data);
            }
          }
        }
        if ((Settings.Web_ServisAktif) && (HTTPmod == 1))
          client.print(file_data);
        kopya_etiket += file_data;
        //kopya_etiket += "\r\n";
        yazdir_c[0] = 0;
        strncpy(yazdir_c, file_data.c_str(), file_data.length());
#ifdef HAS_BLUETOOTH
        if (Settings.bluetooth_mod == BTmod)
          SerialBT.print(file_data);
#endif
        if (SERIALmod == 1) {
          for (int i = 0; i < file_data.length(); i++) {
            if (yazdir_c[i] == 94) {Serial1.write(0);}
            else if ((karakter_195) && (yazdir_c[i] == 135)) {Serial1.write(199); karakter_195 = false;}//Serial1.write(128); karakter_195 = false;} //Ç
            else if ((karakter_195) && (yazdir_c[i] == 167)) {Serial1.write(231); karakter_195 = false;}//Serial1.write(135); karakter_195 = false;} //ç
            else if ((karakter_195) && (yazdir_c[i] == 150)) {Serial1.write(214); karakter_195 = false;}//Serial1.write(153); karakter_195 = false;} //Ö
            else if ((karakter_195) && (yazdir_c[i] == 182)) {Serial1.write(246); karakter_195 = false;}//Serial1.write(148); karakter_195 = false;} //ö
            else if ((karakter_195) && (yazdir_c[i] == 156)) {Serial1.write(220); karakter_195 = false;}//Serial1.write(154); karakter_195 = false;} //Ü
            else if ((karakter_195) && (yazdir_c[i] == 188)) {Serial1.write(252); karakter_195 = false;}//Serial1.write(129); karakter_195 = false;} //ü
            else if ((karakter_196) && (yazdir_c[i] == 158)) {Serial1.write(208); karakter_196 = false;}//Serial1.write(166); karakter_196 = false;} //Ğ
            else if ((karakter_196) && (yazdir_c[i] == 159)) {Serial1.write(240); karakter_196 = false;}//Serial1.write(167); karakter_196 = false;} //ğ
            else if ((karakter_196) && (yazdir_c[i] == 176)) {Serial1.write(221); karakter_196 = false;}//Serial1.write(152); karakter_196 = false;} //İ
            else if ((karakter_196) && (yazdir_c[i] == 177)) {Serial1.write(253); karakter_196 = false;}//Serial1.write(141); karakter_196 = false;} //ı
            else if ((karakter_197) && (yazdir_c[i] == 158)) {Serial1.write(222); karakter_197 = false;}//Serial1.write(158); karakter_197 = false;} //Ş
            else if ((karakter_197) && (yazdir_c[i] == 159)) {Serial1.write(254); karakter_197 = false;}//Serial1.write(159); karakter_197 = false;} //ş
            else if (yazdir_c[i] == 195) {karakter_195 = true;}
            else if (yazdir_c[i] == 196) {karakter_196 = true;}
            else if (yazdir_c[i] == 197) {karakter_197 = true;}
            else {Serial1.write(yazdir_c[i]);}
          }
        }
      }
      form.close();
      if ((Settings.Web_ServisAktif) && (HTTPmod == 0)) {
        HTTPClient http;
        //String ServerName = "http://";
        //ServerName = Settings.Web_ServisIP;
        //ServerName += ":";
        //ServerName += (String)Settings.Web_ServisPort;
        //ServerName += "/";
        http_data.replace("\n", "");
        //http.begin(client, http_data);
        http.begin(client, http_data);
        http.addHeader("Content-Type", "text/plain");
        //int httpCode = http.POST(http_data);   //Send the request
        http.POST(http_data);
        String payload = http.getString();  //Get the response payload
        //addLog(LOG_LEVEL_INFO, httpCode);   //Print HTTP return code
        //addLog(LOG_LEVEL_INFO, payload);    //Print request response payload
        http.end();  //Close connection
      }
    } else {
      String file_data = "";
      yazdir_c[0] = 0;
      int file_data_i = 0;
      if (SERIALmod == 1) {
        Serial1.println("SOUND 1,100");
        //send_tspl_safe("SOUND 1,100");
      }
      while (form.position() < form.size()) {
        char file_data_s = form.read();
        yazdir_c[file_data_i] = file_data_s;
        file_data_i++;
        if ((file_data_i > 512) || (file_data_s == '\n')) {
          if (file_data_i < 510) {
            String yazdir_s = "";
            for (int i = 0; i < file_data_i; i++)
              yazdir_s += yazdir_c[i];
            yazdir_s.replace("ENDUTEK.TTF","0");
            parseTemplate(yazdir_s);
            parse_string_commands(yazdir_s);
            //parseSystemVariables(yazdir_s, false);
            Serial1.print(yazdir_s);
            /*if (yazdir_s.length() > 0) {
              send_tspl_command(yazdir_s.c_str());
            }*/
            //send_tspl_safe(yazdir_s.c_str());
          } else {
            for (int i = 0; i < file_data_i; i++) {
              Serial1.write(yazdir_c[i]);
              //send_tspl_safe((char*)yazdir_c[i]);
              //control_data = control_data + int(yazdir_c[i]);
              control_data += (uint8_t) yazdir_c[i];
            }
            //send_tspl_command(yazdir_c);
            //send_tspl_safe(file_data.c_str());
            file_data = "";
          }
          yazdir_c[0] = 0;
          Serial1.flush();
          file_data_i = 0;
        }
      }
      form.close();
    }
  }
/*#if FEATURE_SD
  String dosya_sd = "/";
  dosya_sd += node_time.getDateString('_');
  dosya_sd += ".dat";
  //XML_NET_S.replace(".", ",");
  if (fileExists(Settings.sd_prn)) {
    fs::File form = tryOpenFile(Settings.sd_prn, "r");
    String file_data = "";
    while (form.position() < form.size()) {
      file_data = form.readStringUntil('\n');
      //file_data += '\n';
      parseSystemVariables(file_data, false);
      delay(10);
      String data = "SDdata";
      data += dosya_sd;
      data += file_data;
      Serial1.print(data);
      delay(10);
      //Serial.print(data);
      fs::File logFile = SD.open(dosya_sd, "a+");
      if (logFile)
        logFile.print(file_data);
      logFile.close();
    }
  }
#endif*/
  //XML_URUN_ISMI_S = "";
  //XML_BARKOD_S = "";
  //XML_MESAJ1_S = "";
  //XML_MESAJ2_S = "";
  //XML_MESAJ3_S = "";
  //XML_MESAJ4_S = "";
}

String Command_Eyz_Sensor(struct EventStruct* event, const char* Line) {
  //Serial.println("& V1 do \"calibrate_sensor\"");
  for (size_t i = 0; i < 20; i++) {
    char c = pgm_read_byte_near(etiketcal + i);
    Serial1.write(c == 94 ? 0 : c);
  }
  //return return_see_serial(event);
  return return_command_success();
}

String Command_Eyz_Test(struct EventStruct* event, const char* Line) {
  String TmpStr1 = "0";
  String TmpStr2 = "0";
  String eyz_test = "";
  dtostrf(123456.7, 7, 1, XML_NET_C);
  dtostrf(123456.7, 7, 1, XML_DARA_C);
  dtostrf(123456.7, 7, 1, XML_BRUT_C);
  dtostrf(1234567, 7, 0, XML_ADET_C);
  dtostrf(123456.7, 7, 1, XML_TOP_NET_C);
  dtostrf(123456.7, 7, 1, XML_TOP_DARA_C);
  dtostrf(123456.7, 7, 1, XML_TOP_BRUT_C);
  dtostrf(123, 3, 0, XML_SNO_C);
  dtostrf(123.4567, 7, 4, XML_ADET_GRAMAJ_C);
  XML_TARIH_S = node_time.getDateString('-');
  XML_SAAT_S = node_time.getTimeString(':');
  if (GetArgv(Line, TmpStr1, 2))
    eyz_test = TmpStr1;
  if (GetArgv(Line, TmpStr1, 3))
    eyz_test = TmpStr1;
  etiket_yaz(eyz_test, 1, Settings.Web_ServisMod, 1, Settings.Cli_PrinterAktif);
  return return_see_serial(event);
}

String Command_Eyz_Art(struct EventStruct* event, const char* Line) {
  String TmpStr1 = "0";
  String TmpStr2 = "0";
  int test_eyz_i = 0;
  if (GetArgv(Line, TmpStr1, 2))
    test_eyz_i = TmpStr1.toInt();
  if (webapinettartim > 0.0001) {
    sno = sno + 1;
    XML_SNO_S = String(sno);
    String(sno).toCharArray(XML_SNO_C, 3);
    top_adet = XML_ADET_S.toInt() + top_adet;
    XML_TOP_ADET_S = top_adet;
    top_net = webapinettartim + top_net;
    XML_TOP_NET_S = top_net;
    top_dara = webapidaratartim + top_dara;
    XML_TOP_DARA_S = top_dara;
    top_brut = webapibruttartim + top_brut;
    XML_TOP_BRUT_S = top_brut;
  }
  dtostrf(sno, 3, 0, XML_SNO_C);
  if ((webapinettartim > 0.0001) || (Settings.UseNegatifYaz)) {
    if (Settings.UseNegatifYaz) {
      XML_TARIH_S = node_time.getDateString('-');
      XML_SAAT_S = node_time.getTimeString(':');
    }
    etiket_yaz(Settings.art_prn, 1, Settings.Web_ServisMod, 1, Settings.Cli_PrinterAktif);
  } else etiket_yazdir_hata(true, 1);
  //return return_see_serial(event);
  return return_command_success();
}

String Command_Eyz_Tek(struct EventStruct* event, const char* Line) {
  String TmpStr1 = "0";
  String TmpStr2 = "0";
  int test_eyz_i = 0;
  if (GetArgv(Line, TmpStr1, 2))
    test_eyz_i = TmpStr1.toInt();
  dtostrf(top_net, 10, ExtraTaskSettings.TaskDeviceValueDecimals[0], XML_TOP_NET_C);
  dtostrf(top_dara, 10, ExtraTaskSettings.TaskDeviceValueDecimals[1], XML_TOP_DARA_C);
  dtostrf(top_brut, 10, ExtraTaskSettings.TaskDeviceValueDecimals[2], XML_TOP_BRUT_C);
  //String(sno).toCharArray(XML_SNO_C, 3);
  if (sno == 0 && ((webapinettartim > 0.00001) || Settings.UseNegatifYaz)) {
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
    //etiket_yaz(ETIKET_TEK,1,Settings.Web_ServisMod,0,Settings.Cli_PrinterAktif);   //SERİAL PASİF
    etiket_yaz(Settings.tek_prn, 1, Settings.Web_ServisMod, 1, Settings.Cli_PrinterAktif);  //SERİAL AKTİF
    sendData(event);
  } else if ((top_net > 0.0001) || (Settings.UseNegatifYaz)) {
    if (Settings.UseNegatifYaz) {
      XML_TARIH_S = node_time.getDateString('-');
      XML_SAAT_S = node_time.getTimeString(':');
    }
    XML_SNO_S = String(sno);
    dtostrf(sno, 3, 0, XML_SNO_C);
    dtostrf(top_net, 8, ExtraTaskSettings.TaskDeviceValueDecimals[0], XML_TOP_NET_C);
    dtostrf(top_dara, 8, ExtraTaskSettings.TaskDeviceValueDecimals[1], XML_TOP_DARA_C);
    dtostrf(top_brut, 8, ExtraTaskSettings.TaskDeviceValueDecimals[2], XML_TOP_BRUT_C);
    etiket_yaz(Settings.top_prn, 1, Settings.Web_ServisMod, 1, Settings.Cli_PrinterAktif);

  } else
    etiket_yazdir_hata(true, 1);
  sno = 0;
  XML_SNO_S = sno;
  top_adet = 0;
  XML_TOP_ADET_S = top_adet;
  top_net = 0;
  XML_TOP_NET_S = top_net;
  top_dara = 0;
  XML_TOP_DARA_S = top_dara;
  top_brut = 0;
  XML_TOP_BRUT_S = top_brut;
  int address = 0;
  EEPROM.writeLong(address, seri_no);
  address += sizeof(uint32_t);
  EEPROM.writeLong(address, sno);
  address += sizeof(uint32_t);
  EEPROM.writeFloat(address, top_net);
  address += sizeof(float);
  EEPROM.writeLong(address, top_adet);
  address += sizeof(uint32_t);
  EEPROM.commit();
  //return return_see_serial(event);
  return return_command_success();
}

String Command_Eyz_Urun_Tek(struct EventStruct* event, const char* Line) {
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
  String TmpStr12 = "0";
  int8_t urunno_click = 0;
  int8_t etiket_sayisi = 0;
  int8_t test_eyz_i = 0;
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
    etiket_sayisi = TmpStr2.toInt();
  if (GetArgv(Line, TmpStr3, 4))
    test_eyz_i = TmpStr3.toInt();
  if (GetArgv(Line, TmpStr4, 5))
    firma_click = TmpStr4.toInt();
  if (GetArgv(Line, TmpStr5, 6))
    mesaj1_no = TmpStr5.toInt();
  if (GetArgv(Line, TmpStr6, 7))
    mesaj2_no = TmpStr6.toInt();
  if (GetArgv(Line, TmpStr7, 8))
    mesaj3_no = TmpStr7.toInt();
  if (GetArgv(Line, TmpStr8, 9))
    mesaj4_no = TmpStr8.toInt();
  if (GetArgv(Line, TmpStr9, 10))
    mesaj5_no = TmpStr9.toInt();
  if (GetArgv(Line, TmpStr10, 11))
    mesaj6_no = TmpStr10.toInt();
  if (GetArgv(Line, TmpStr11, 12))
    mesaj7_no = TmpStr11.toInt();
  if (GetArgv(Line, TmpStr12, 13))
    mesaj8_no = TmpStr12.toInt();
  if (urunno_click == 0) {
    Serial1.println(kopya_etiket);
    delay(100);
  } else {
    XML_URUN_ISMI_S = urun_labels[urunno_click];
    XML_URUN_KOD_S = urun_kod_labels[urunno_click];
    XML_URUN_MESAJ_S = urun_msg[urunno_click];
    float bol = 1;
    switch (ExtraTaskSettings.TaskDeviceValueDecimals[0]) {
      case 0: bol = 1; break;
      case 1: bol = 10; break;
      case 2: bol = 100; break;
      case 3: bol = 1000; break;
      case 4: bol = 10000; break;
    }
    dtostrf(webapinettartim * bol, 5, 0, XML_BARKOD_C);
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
    else { 
      XML_MESAJ4_S = mesaj_labels[3][mesaj4_no];
      char* label = mesaj_labels[3][0];
      if (strcmp(label, "ETIKET") == 0) {
        //const char* prefix = "/rules/eyzurun";
        const char* prefix = "eyzurun";
        const char* suffix = ".prn";
        // Dizinin başına ekleme yap
        strcpy(Settings.urun_tek_prn, prefix);           // Önce prefix'i kopyala
        strcat(Settings.urun_tek_prn, mesaj_labels[3][mesaj4_no]);            // Ardından ana içeriği ekle
        strcat(Settings.urun_tek_prn, suffix);           // Son olarak suffix'i ekle
        //strncpy(Settings.urun_tek_prn, M4[mesaj4_no], sizeof(Settings.urun_tek_prn) - 1);
        //Settings.urun_tek_prn[sizeof(Settings.urun_tek_prn) - 1] = '\0';
      }
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
      test_eyz_i = TmpStr1.toInt();
    dtostrf(top_net, 10, ExtraTaskSettings.TaskDeviceValueDecimals[0], XML_TOP_NET_C);
    dtostrf(top_dara, 10, ExtraTaskSettings.TaskDeviceValueDecimals[1], XML_TOP_DARA_C);
    dtostrf(top_brut, 10, ExtraTaskSettings.TaskDeviceValueDecimals[2], XML_TOP_BRUT_C);
    //String(sno).toCharArray(XML_SNO_C, 3);
    if (sno == 0) {//((webapinettartim > 0.00001) || (Settings.UseNegatifYaz) || (urun_tipi[urunno_click] == 1)))  {
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
      //etiket_yaz(ETIKET_TEK,1,Settings.Web_ServisMod,0,Settings.Cli_PrinterAktif);   //SERİAL PASİF
      if (urun_tipi[urunno_click] == 1)
        etiket_yaz(Settings.urun_adet_tek_prn, 1, Settings.Web_ServisMod, 1, Settings.Cli_PrinterAktif);
      else {
        if (urun_etiket_format[urunno_click] != 0) {
          fs::File root = ESPEASY_FS.open(F("/")); //rules"));
          fs::File file = root.openNextFile();
          int fileno = 1;
          while (file && fileno < 10) {
            if (!file.isDirectory()) {
              const String fname(file.name());
              if (fname.startsWith(F("/eyz")) || fname.startsWith(F("eyz"))) {
                options2[fileno] = file.name();
                if ( fileno == urun_etiket_format[urunno_click]) {
                  //strcpy(Settings.urun_tek_prn, file.name());
                  etiket_yaz(file.name(), 1, Settings.Web_ServisMod, 1, Settings.Cli_PrinterAktif);  //SERİAL AKTİF
                  addLog(LOG_LEVEL_INFO, file.name());
                  break;
                }
                fileno++;
              }
              file = root.openNextFile();
            }
          }
        }
        else
          etiket_yaz(Settings.urun_tek_prn, 1, Settings.Web_ServisMod, 1, Settings.Cli_PrinterAktif);  //SERİAL AKTİF
          //sendData(event);
      }
    } else if ((top_net > 0.0001) || (Settings.UseNegatifYaz)) {
      if (Settings.UseNegatifYaz) {
        XML_TARIH_S = node_time.getDateString('-');
        XML_SAAT_S = node_time.getTimeString(':');
      }
      XML_SNO_S = String(sno);
      dtostrf(sno, 3, 0, XML_SNO_C);
      dtostrf(top_net, 8, ExtraTaskSettings.TaskDeviceValueDecimals[0], XML_TOP_NET_C);
      dtostrf(top_dara, 8, ExtraTaskSettings.TaskDeviceValueDecimals[1], XML_TOP_DARA_C);
      dtostrf(top_brut, 8, ExtraTaskSettings.TaskDeviceValueDecimals[2], XML_TOP_BRUT_C);
      if (urun_tipi[urunno_click] == 1)
        etiket_yaz(Settings.urun_adet_top_prn, 1, Settings.Web_ServisMod, 1, Settings.Cli_PrinterAktif);
      else
        etiket_yaz(Settings.urun_top_prn, 1, Settings.Web_ServisMod, 1, Settings.Cli_PrinterAktif);
    } else
      etiket_yazdir_hata(true, 1);
    sno = 0;
    XML_SNO_S = sno;
    top_adet = 0;
    XML_TOP_ADET_S = top_adet;
    top_net = 0;
    XML_TOP_NET_S = top_net;
    top_dara = 0;
    XML_TOP_DARA_S = top_dara;
    top_brut = 0;
    XML_TOP_BRUT_S = top_brut;
    sno = 0;
    int address = 0;
    EEPROM.writeLong(address, seri_no);
    address += sizeof(uint32_t);
    EEPROM.writeLong(address, sno);
    address += sizeof(uint32_t);
    EEPROM.writeFloat(address, top_net);
    address += sizeof(float);
    EEPROM.writeLong(address, top_adet);
    address += sizeof(uint32_t);
    EEPROM.commit();
  }
    //return return_see_serial(event);
  return return_command_success();
}

String Command_Eyz_Urun_Art(struct EventStruct* event, const char* Line) {
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
  String TmpStr12 = "0";
  int8_t urunno_click = 0;
  int8_t etiket_sayisi = 0;
  int8_t test_eyz_i = 0;
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
    etiket_sayisi = TmpStr2.toInt();
  if (GetArgv(Line, TmpStr3, 4))
    test_eyz_i = TmpStr3.toInt();
  if (GetArgv(Line, TmpStr4, 5))
    firma_click = TmpStr4.toInt();
  if (GetArgv(Line, TmpStr5, 6))
    mesaj1_no = TmpStr5.toInt();
  if (GetArgv(Line, TmpStr6, 7))
    mesaj2_no = TmpStr6.toInt();
  if (GetArgv(Line, TmpStr7, 8))
    mesaj3_no = TmpStr7.toInt();
  if (GetArgv(Line, TmpStr8, 9))
    mesaj4_no = TmpStr8.toInt();
  if (GetArgv(Line, TmpStr9, 10))
    mesaj5_no = TmpStr9.toInt();
  if (GetArgv(Line, TmpStr10, 11))
    mesaj6_no = TmpStr10.toInt();
  if (GetArgv(Line, TmpStr11, 12))
    mesaj7_no = TmpStr11.toInt();
  if (GetArgv(Line, TmpStr12, 13))
    mesaj8_no = TmpStr12.toInt();
  if (urunno_click == 0) {
    Serial1.println(kopya_etiket);
    delay(100);
  } else {
    XML_URUN_ISMI_S = urun_labels[urunno_click];
    XML_URUN_KOD_S = urun_kod_labels[urunno_click];
    XML_URUN_MESAJ_S = urun_msg[urunno_click];
    float bol = 1;
    switch (ExtraTaskSettings.TaskDeviceValueDecimals[0]) {
      case 0: bol = 1; break;
      case 1: bol = 10; break;
      case 2: bol = 100; break;
      case 3: bol = 1000; break;
      case 4: bol = 10000; break;
    }
    dtostrf(webapinettartim * bol, 5, 0, XML_BARKOD_C);
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
      
    if ((webapinettartim > 0.0001) || (Settings.UseNegatifYaz) || (urun_tipi[urunno_click] == 1)) {
      if (Settings.UseNegatifYaz) {
        XML_TARIH_S = node_time.getDateString('-');
        XML_SAAT_S = node_time.getTimeString(':');
      }
      top_adet = XML_ADET_S.toInt() + top_adet;
      XML_TOP_ADET_S = top_adet;
      top_net = webapinettartim + top_net;
      XML_TOP_NET_S = top_net;
      top_dara = webapidaratartim + top_dara;
      XML_TOP_DARA_S = top_dara;
      top_brut = webapibruttartim + top_brut;
      XML_TOP_BRUT_S = top_brut;
      dtostrf(top_net, 8, ExtraTaskSettings.TaskDeviceValueDecimals[0], XML_TOP_NET_C);
      dtostrf(top_dara, 8, ExtraTaskSettings.TaskDeviceValueDecimals[1], XML_TOP_DARA_C);
      dtostrf(top_brut, 8, ExtraTaskSettings.TaskDeviceValueDecimals[2], XML_TOP_BRUT_C);
      sno = sno + 1;
      XML_SNO_S = String(sno);
      dtostrf(sno, 4, 0, XML_SNO_C);
      fis_no = fis_no + 1;
      XML_FIS_NO_S = String(fis_no);
      dtostrf(fis_no, 8, 0, XML_FIS_NO_C);
      seri_no = seri_no + 1;
      XML_SERI_NO_S = String(seri_no);
      dtostrf(seri_no, 8, 0, XML_SERI_NO_C);
      int sirano_i;// = sirano_s[sirano_aktif].toInt();
      sirano_i++;
      //sirano_s[sirano_aktif] = sirano_i;
      //printf(sirano_s[sirano_aktif].c_str());
      //dtostrf(sirano_s[sirano_aktif].toInt(), 8, 0, XML_SIRA_NO_C);
      //etiket_yaz(Settings.srv_prn, 1, Settings.Web_ServisMod, 0, Settings.Cli_PrinterAktif);
      if (urun_tipi[urunno_click] == 1)
        etiket_yaz(Settings.urun_adet_art_prn, 1, 3, 1, Settings.Cli_PrinterAktif);
      else
        etiket_yaz(Settings.urun_art_prn, 1, 3, 1, Settings.Cli_PrinterAktif);
    } else
        etiket_yazdir_hata(true, 1);
  }
  //return return_see_serial(event);
  return return_command_success();
}

String Command_Eyz_Yaz(struct EventStruct* event, const char* Line) {
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
    String md5chck = "eyzyaz";
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
    etiket_yaz(ETIKET_YAZ, 1, Settings.Web_ServisMod, 1, Settings.Cli_PrinterAktif);  //SERİAL AKTİF
  } else {
    etiket_yazdir_hata(true, 1);
    return return_command_failed();
  }
  //return return_command_yazdir();
  return return_command_success();
}

String Command_Eyz_Yaz_Satir(struct EventStruct* event, const char* Line) {
  String TmpStr1;
  String message;
  if (GetArgv(Line, TmpStr1, 2)) {
    message = TmpStr1;
    message += "\r\n";
  }
  if (message.length() > 0) {
    Serial1.println("BEEP");
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
    etiket_yazdir_hata(true, 1);
    return return_command_failed();
  }
  //return return_command_yazdir();
  return return_command_success();
}

String Command_Eyz_tspl(struct EventStruct* event, const char* Line) {
  String TmpStr1;
  int time = 5;
  if (GetArgv(Line, TmpStr1, 2))
    time = TmpStr1.toInt();
  Serial1.println("BEEP");
  tspl_mod = true;
  tspl_time = millis() + (time * 1000);
  //return return_command_yazdir();
  return return_command_success();
}

String Command_Eyz_Net(struct EventStruct* event, const char* Line) {
  Serial1.println("BEEP");
#ifdef HAS_BLUETOOTH
  if (Settings.bluetooth_mod == 2)
    SerialBT.println("TARTIM:" + XML_NET_S);
#endif
  return return_command_success();
}

String Command_Eyz_Serino(struct EventStruct* event, const char* Line) {
  String TmpStr1 = "0";
  if (GetArgv(Line, TmpStr1, 2))
    seri_no = TmpStr1.toInt();
  XML_SERI_NO_S = String(seri_no);
  dtostrf(seri_no, 8, 0, XML_SERI_NO_C);
  int address = 0;
  EEPROM.writeLong(address, seri_no);
  address += sizeof(uint32_t);
  EEPROM.commit();
  return return_command_success();
}

String Command_Eyz_Dara_Ekle(struct EventStruct* event, const char* Line) {
  if ((webapinettartim > 0.0001) && (webapidaratartim >= 0.0001))
    webapidaratartim = float(webapinettartim + webapidaratartim) * 1;
  else if ((webapinettartim > 0.0001) && (webapidaratartim < 0.0001))
    webapidaratartim = float(webapidaratartim + (webapinettartim * 1));
  
  // Update UserVar with new DARA value
  if (Settings.WebAPP == 130) {  // P130 - EYZ Etiket Yazıcı
    for (taskIndex_t taskIndex = 0; taskIndex < TASKS_MAX; taskIndex++) {
      if (Settings.getPluginID_for_task(taskIndex) == pluginID_t(130)) {
        UserVar.setFloat(taskIndex, 1, webapidaratartim);  // Update DARA value
        
        // Recalculate NET = BRUT - DARA
        webapibruttartim = UserVar.getFloat(taskIndex, 2);  // Get BRUT
        webapinettartim = webapibruttartim - webapidaratartim;
        UserVar.setFloat(taskIndex, 0, webapinettartim);  // Update NET
        
        // Update XML strings
        XML_DARA_S = String(webapidaratartim, int(ExtraTaskSettings.TaskDeviceValueDecimals[1]));
        XML_NET_S = String(webapinettartim, int(ExtraTaskSettings.TaskDeviceValueDecimals[0]));
        addLog(LOG_LEVEL_INFO, concat(F("eyzdaraekle: NET="), XML_NET_S) + concat(F(" DARA="), XML_DARA_S));
        addLog(LOG_LEVEL_INFO, concat(F("eyzdaraekle: NET="), XML_NET_S) + concat(F(" DARA="), XML_DARA_S));
        break;
      }
    }
  }
  
  return return_command_success();
}

String Command_Eyz_Dara_Sil(struct EventStruct* event, const char* Line) {
  webapidaratartim = 0;
  
  // Update UserVar with zero DARA value
  if (Settings.WebAPP == 130) {  // P130 - EYZ Etiket Yazıcı
    for (taskIndex_t taskIndex = 0; taskIndex < TASKS_MAX; taskIndex++) {
      if (Settings.getPluginID_for_task(taskIndex) == pluginID_t(130)) {
        UserVar.setFloat(taskIndex, 1, 0);  // Clear DARA
        
        // Recalculate NET = BRUT - 0
        webapibruttartim = UserVar.getFloat(taskIndex, 2);
        webapinettartim = webapibruttartim;
        UserVar.setFloat(taskIndex, 0, webapinettartim);
        
        XML_DARA_S = "0";
        XML_NET_S = String(webapinettartim, int(ExtraTaskSettings.TaskDeviceValueDecimals[0]));
        
        addLog(LOG_LEVEL_INFO, F("eyzdarasil: DARA cleared, NET recalculated"));
        break;
      }
    }
  }
  
  return return_command_success();
}

#endif