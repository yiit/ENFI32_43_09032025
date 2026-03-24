#ifndef HELPERS_SYSTEMVARIABLES_H
#define HELPERS_SYSTEMVARIABLES_H

#include "../../ESPEasy_common.h"

class SystemVariables {
public:

  enum Enum : uint8_t {
    // For optmization, keep enums sorted alfabetically by their flash string
    ACIK,
    ADET,
    ADETGRAMAJ,
    AGIRLIK,

    BARKOD,
    BEYAZ,
    BIRIMFIYAT,
    BOARD_NAME,
    BOOT_CAUSE,
    BRUT,
    BRUT_S,
    BRUT_V,
    BSSID,
    
    CEKMECE,
    CLIENTIP,
    CR,
    
    DARA,
    DARA_S,
    DARA_V,
    DNS,
    DNS_1,
    DNS_2,
    
    EAN8,
    EAN13,
    ESP_CHIP_CORES,
    ESP_CHIP_FREQ,
    ESP_CHIP_ID,
    ESP_CHIP_MODEL,
    ESP_CHIP_REVISION,
#if FEATURE_ETHERNET
    ETHCONNECTED,
    ETHDUPLEX,
    ETHSPEED,
    ETHSPEEDSTATE,
    ETHSTATE,
    ETHWIFIMODE,
#endif // if FEATURE_ETHERNET

    FLASH_CHIP_MODEL,
    FLASH_CHIP_VENDOR,
    FLASH_FREQ,
    FLASH_SIZE,
    FS_FREE,
    FS_SIZE,
    FISNO,
    FNET,
    FDARA,
    FBRUT,
    FIRMAISMI,
    FISBAS1,
    FISBAS2,
    FISBAS3,
    FISBAS4,
    FONT1,
    FONT2,
    FONT3,
    FONT4,
    FONT5,
    FONT6,

    GATEWAY,

#if FEATURE_INTERNAL_TEMPERATURE
    INTERNAL_TEMPERATURE,
#endif // if FEATURE_INTERNAL_TEMPERATURE

    IP4,
    IP,
    IRDADATA,
#if FEATURE_USE_IPV6
    IP6_LOCAL,
#endif
    ISVAR_DOUBLE,
    ISLIMITED_BUILD,
    ISMQTT,
    ISMQTTIMP,
    ISNTP,
    ISWIFI,
    
    KFONT1,
    KFONT2,
    KFONT3,
    KFONT4,
    KFONT5,
    KFONT6,
    KOYU,
    KES,
    
    LCLTIME,
    LCLTIME_AM,
    LF,
    LOGO,

    MAC,
    MAC_INT,
    MESAJ1,
    MESAJ2,
    MESAJ3,
    MESAJ4,
    MESAJ5,
    MESAJ6,
    MESAJ7,
    MESAJ8,
    MESAJ9,
    MUSTERIISMI,

    NET,
    NET_S,
    NET_V,

    OPERATORISMI,
    ORTA,

    PLAKANO,

    RSSI,

    QRKOD,

    SAAT,
    SAATV,
    SAG,
    SAYAC_1,
    SAYAC_2,
    SAYAC_3,
    SAYAC_4,
    SAYAC_1_C,
    SAYAC_2_C,
    SAYAC_3_C,
    SAYAC_4_C,
    SERINO,
    PARTINO,
    SIYAH,
    SKT,
    SNO,
    SOL,
    STABIL,
    SPACE,
    SSID,
    SUBNET,
    SUNRISE,
    SUNRISE_S,
    SUNRISE_M,
    SUNSET,
    SUNSET_S,
    SUNSET_M,
    SYSBUILD_DATE,
    SYSBUILD_DESCR,
    SYSBUILD_FILENAME,
    SYSBUILD_GIT,
    SYSBUILD_TIME,
    SYSDAY,
    SYSDAY_0,
    SYSHEAP,
    SYSHOUR,
    SYSHOUR_0,
    SYSLOAD,
    SYSMIN,
    SYSMIN_0,
    SYSMONTH,
    SYSMONTH_S,
    SYSNAME,
    SYSSEC,
    SYSSEC_0,
    SYSSEC_D,
    SYSSTACK,
    SYSTIME,
    SYSTIME_AM,
    SYSTIME_AM_0,
    SYSTIME_AM_SP,
    SYSTM_HM,
    SYSTM_HM_0,
    SYSTM_HM_AM,
    SYSTM_HM_AM_0,
    SYSTM_HM_AM_SP,
    SYSTM_HM_SP,
    SYSTZOFFSET,
    SYSWEEKDAY,
    SYSWEEKDAY_S,
    SYSYEAR,
    SYSYEARS,
    SYSYEAR_0,
    SYS_MONTH_0,
    S_CR,
    S_LF,
    
    TARIH,
    TARIHV,
    TOPADET,
    TOPBRUT,
    TOPDARA,
    TOPLAM_DETAY,
    TOPNET,
    TUTAR,

    UNIT_sysvar,
#if FEATURE_ZEROFILLED_UNITNUMBER
    UNIT_0_sysvar,
#endif // FEATURE_ZEROFILLED_UNITNUMBER
    UNIXDAY,
    UNIXDAY_SEC,
    UNIXTIME,
    UPTIME,
    UPTIME_MS,
    URUNISMI,
    URUNKOD,
    URUNNO,
    URUNMESAJ,

    VCC,
    VARIABLE,
    V0,
    V1,
    V2,
    V3,
    V4,
    V5,
    V6,
    V7,
    V8,
    V9,
    V10,
    V11,
    V12,
    V13,
    V14,
    V15,
    V16,
    V17,
    V18,
    V19,
    V20,
    V21,
    V22,
    V23,
    V24,
    V25,
    V26,
    V27,
    V28,
    V29,
    
    WI_CH,
    // Keep UNKNOWN as last
    UNKNOWN
  };

  // Find the next thing to replace.
  // Return UNKNOWN when nothing needs to be replaced.
  static SystemVariables::Enum nextReplacementEnum(const String        & str,
                                                   SystemVariables::Enum last_tested,
                                                   int                 & last_percent_pos);

  static String                     toString(SystemVariables::Enum enumval);

  static SystemVariables::Enum      startIndex_beginWith(char beginchar);
  static const __FlashStringHelper* toFlashString(SystemVariables::Enum enumval);

  static String                     getSystemVariable(SystemVariables::Enum enumval);

  static void                       parseSystemVariables(String& s,
                                                         boolean useURLencode);
};


#endif // HELPERS_SYSTEMVARIABLES_H
