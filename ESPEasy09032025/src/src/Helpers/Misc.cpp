#include "../Helpers/Misc.h"

#include "../../ESPEasy-Globals.h"
#include "../../ESPEasy_common.h"
#include "../../_Plugin_Helper.h"
#include "../ESPEasyCore/ESPEasy_backgroundtasks.h"
#include "../ESPEasyCore/Serial.h"
#include "../Globals/ESPEasy_time.h"
#include "../Globals/Statistics.h"
#include "../Helpers/ESPEasy_FactoryDefault.h"
#include "../Helpers/ESPEasy_Storage.h"
#include "../Helpers/Numerical.h"
#include "../Helpers/PeriodicalActions.h"
#include "../Helpers/StringConverter.h"
#include "../Helpers/StringParser.h"
#include "../Helpers/_Plugin_Helper_serial.h"

#ifdef USES_ESPNOW_MANAGER
# include "../../../lib/ESPNowManager/ESPNowManager.h"
extern ESPNowManager espnowManager;
#endif

#if FEATURE_SD
# include <SD.h>
#endif // if FEATURE_SD


bool remoteConfig(struct EventStruct *event, const String& string)
{
  // FIXME TD-er: Why have an event here as argument? It is not used.
  #ifndef BUILD_NO_RAM_TRACKER
  checkRAM(F("remoteConfig"));
  #endif // ifndef BUILD_NO_RAM_TRACKER
  bool   success = false;
  String command = parseString(string, 1);

  if (equals(command, F("config")))
  {
    // Command: "config,task,<taskname>,<actual Set Config command>"
    if (equals(parseString(string, 2), F("task")))
    {
      String configTaskName = parseStringKeepCase(string, 3);

      // FIXME TD-er: This command is not using the tolerance setting
      // tolerantParseStringKeepCase(Line, 4);
      String configCommand = parseStringToEndKeepCase(string, 4);

      if ((configTaskName.isEmpty()) || (configCommand.isEmpty())) {
        return success;
      }
      taskIndex_t index = findTaskIndexByName(configTaskName);

      if (validTaskIndex(index))
      {
        event->setTaskIndex(index);
        success = PluginCall(PLUGIN_SET_CONFIG, event, configCommand);
      }
    } else {
      addLog(LOG_LEVEL_ERROR, F("Expected syntax: config,task,<taskname>,<config command>"));
    }
  }
  return success;
}

/********************************************************************************************\
   delay in milliseconds with background processing
 \*********************************************************************************************/
void delayBackground(unsigned long dsdelay)
{
  unsigned long timer = millis() + dsdelay;

  while (!timeOutReached(timer)) {
    backgroundtasks();
  }
}

/********************************************************************************************\
   Toggle controller enabled state
 \*********************************************************************************************/
bool setControllerEnableStatus(controllerIndex_t controllerIndex, bool enabled)
{
  if (!validControllerIndex(controllerIndex)) { return false; }
  #ifndef BUILD_NO_RAM_TRACKER
  checkRAM(F("setControllerEnableStatus"));
  #endif // ifndef BUILD_NO_RAM_TRACKER

  // Only enable controller if it has a protocol configured
  if ((Settings.Protocol[controllerIndex] != 0) || !enabled) {
    Settings.ControllerEnabled[controllerIndex] = enabled;
    return true;
  }
  return false;
}

/********************************************************************************************\
   Toggle task enabled state
 \*********************************************************************************************/
bool setTaskEnableStatus(struct EventStruct *event, bool enabled)
{
  if (!validTaskIndex(event->TaskIndex)) { return false; }
  #ifndef BUILD_NO_RAM_TRACKER
  checkRAM(F("setTaskEnableStatus"));
  #endif // ifndef BUILD_NO_RAM_TRACKER

  // Only enable task if it has a Plugin configured
  if (validPluginID(Settings.getPluginID_for_task(event->TaskIndex)) || !enabled) {
    String dummy;

    if (!enabled) {
      PluginCall(PLUGIN_EXIT, event, dummy);
    }

    // Toggle enable/disable state via command
    // FIXME TD-er: Should this be a 'runtime' change, or actually change the intended state?
    // Settings.TaskDeviceEnabled[event->TaskIndex].enabled = enabled;
    Settings.TaskDeviceEnabled[event->TaskIndex] = enabled;

    if (enabled) {
      // Schedule the plugin to be read.
      // Do this before actual init, to allow the plugin to schedule a specific first read.
      Scheduler.schedule_task_device_timer(event->TaskIndex, millis() + 10);

      if (!PluginCall(PLUGIN_INIT, event, dummy)) {
        return false;
      }
    }
    return true;
  }
  return false;
}

/********************************************************************************************\
   Clear task settings for given task
 \*********************************************************************************************/
void taskClear(taskIndex_t taskIndex, bool save)
{
  if (!validTaskIndex(taskIndex)) { return; }
  #ifndef BUILD_NO_RAM_TRACKER
  checkRAM(F("taskClear"));
  #endif // ifndef BUILD_NO_RAM_TRACKER

  if (Settings.TaskDeviceEnabled[taskIndex]) {
    struct EventStruct TempEvent(taskIndex);
    String dummy;
    PluginCall(PLUGIN_EXIT, &TempEvent, dummy);
  }
  Settings.clearTask(taskIndex);
  clearTaskCache(taskIndex); // Invalidate any cached values.
  ExtraTaskSettings.clear();
  ExtraTaskSettings.TaskIndex = taskIndex;

  if (save) {
    addLog(LOG_LEVEL_INFO, F("taskClear() save settings"));
    SaveTaskSettings(taskIndex);
    SaveSettings();
  }
}

/********************************************************************************************\
   check the program memory hash
   The const MD5_MD5_MD5_MD5_BoundariesOfTheSegmentsGoHere... needs to remain unchanged as it will be replaced by
   - 16 bytes md5 hash, followed by
   - 4 * uint32_t start of memory segment 1-4
   - 4 * uint32_t end of memory segment 1-4
   currently there are only two segemts included in the hash. Unused segments have start adress 0.
   Execution time 520kb @80Mhz: 236ms
   Returns: 0 if hash compare fails, number of checked bytes otherwise.
   The reference hash is calculated by a .py file and injected into the binary.
   Caution: currently the hash sits in an unchecked segment. If it ever moves to a checked segment, make sure
   it is excluded from the calculation !
 \*********************************************************************************************/
#if defined(ARDUINO_ESP8266_RELEASE_2_3_0)
void dump(uint32_t addr) { // Seems already included in core 2.4 ...
  serialPrint(String(addr, HEX));
  serialPrint(": ");

  for (uint32_t a = addr; a < addr + 16; a++)
  {
    serialPrint(String(pgm_read_byte(a), HEX));
    serialPrint(" ");
  }
  serialPrintln();
}

#endif // if defined(ARDUINO_ESP8266_RELEASE_2_3_0)

/*
   uint32_t progMemMD5check(){
    checkRAM(F("progMemMD5check"));
 #define BufSize 10
    uint32_t calcBuffer[BufSize];
    CRCValues.numberOfCRCBytes = 0;
    memcpy (calcBuffer,CRCValues.compileTimeMD5,16);                                                  // is there still the dummy in memory
       ? - the dummy needs to be replaced by the real md5 after linking.
    if( memcmp (calcBuffer, "MD5_MD5_MD5_",12)==0){                                                   // do not memcmp with CRCdummy
       directly or it will get optimized away.
        addLog(LOG_LEVEL_INFO, F("CRC  : No program memory checksum found. Check output of crc2.py"));
        return 0;
    }
    MD5Builder md5;
    md5.begin();
    for (int l = 0; l<4; l++){                                                                            // check max segments,  if the
       pointer is not 0
        uint32_t *ptrStart = (uint32_t *)&CRCValues.compileTimeMD5[16+l*4];
        uint32_t *ptrEnd =   (uint32_t *)&CRCValues.compileTimeMD5[16+4*4+l*4];
        if ((*ptrStart) == 0) break;                                                                      // segment not used.
        for (uint32_t i = *ptrStart; i< (*ptrEnd) ; i=i+sizeof(calcBuffer)){                              // "<" includes last byte
             for (int buf = 0; buf < BufSize; buf ++){
                calcBuffer[buf] = pgm_read_dword((uint32_t*)i+buf);                                       // read 4 bytes
                CRCValues.numberOfCRCBytes+=sizeof(calcBuffer[0]);
             }
             md5.add(reinterpret_cast<const uint8_t *>(&calcBuffer[0]),(*ptrEnd-i)<sizeof(calcBuffer) ? (*ptrEnd-i):sizeof(calcBuffer) );
                    // add buffer to md5.
                At the end not the whole buffer. md5 ptr to data in ram.
        }
   }
   md5.calculate();
   md5.getBytes(CRCValues.runTimeMD5);
   if ( CRCValues.checkPassed())  {
      addLog(LOG_LEVEL_INFO, F("CRC  : program checksum       ...OK"));
      return CRCValues.numberOfCRCBytes;
   }
   addLog(LOG_LEVEL_INFO, F("CRC  : program checksum       ...FAIL"));
   return 0;
   }
 */

/********************************************************************************************\
   Handler for keeping ExtraTaskSettings up to date using cache
 \*********************************************************************************************/
String getTaskDeviceName(taskIndex_t TaskIndex) {
  return Cache.getTaskDeviceName(TaskIndex);
}

/********************************************************************************************\
   Handler for getting Value Names from TaskIndex

   - value names can be accessed with task variable index
   - maximum number of variables <= defined number of variables in plugin
 \*********************************************************************************************/
String getTaskValueName(taskIndex_t TaskIndex, uint8_t TaskValueIndex) {
  const int valueCount = getValueCountForTask(TaskIndex);

  if (TaskValueIndex < valueCount) {
    return Cache.getTaskDeviceValueName(TaskIndex, TaskValueIndex);
  }
  return EMPTY_STRING;
}

/********************************************************************************************\
   If RX and TX tied together, perform emergency reset to get the system out of boot loops
 \*********************************************************************************************/
void emergencyReset()
{
  // Direct Serial is allowed here, since this is only an emergency task.
  ESPEASY_SERIAL_0.begin(115200);
  ESPEASY_SERIAL_0.write(0xAA);
  ESPEASY_SERIAL_0.write(0x55);
  delay(1);

  if (ESPEASY_SERIAL_0.available() == 2) {
    if ((ESPEASY_SERIAL_0.read() == 0xAA) && (ESPEASY_SERIAL_0.read() == 0x55))
    {
      serialPrintln(F("\n\n\rSystem will reset to factory defaults in 10 seconds..."));
      delay(10000);
      ResetFactory();
    }
  }
}

/********************************************************************************************\
   Delayed reboot, in case of issues, do not reboot with high frequency as it might not help...
 \*********************************************************************************************/
void delayedReboot(int rebootDelay, IntendedRebootReason_e reason)
{
  // Direct Serial is allowed here, since this is only an emergency task.
  while (rebootDelay != 0)
  {
    serialPrint(F("Delayed Reset "));
    serialPrintln(String(rebootDelay));
    rebootDelay--;
    delay(1000);
  }
  reboot(reason);
}

void reboot(IntendedRebootReason_e reason) {
  prepareShutdown(reason);
  #if defined(ESP32)
  ESP.restart();
  #else // if defined(ESP32)
  ESP.reset();
  #endif // if defined(ESP32)
}

void FeedSW_watchdog()
{
  #ifdef ESP8266
  ESP.wdtFeed();
  #endif // ifdef ESP8266
}

void SendValueLogger(taskIndex_t TaskIndex)
{
#if !defined(BUILD_NO_DEBUG) || FEATURE_SD
  bool   featureSD = false;
  String logger;
  # if FEATURE_SD
  featureSD = true;
  # endif // if FEATURE_SD

  if (featureSD
      # ifndef BUILD_NO_DEBUG
      || loglevelActiveFor(LOG_LEVEL_DEBUG)
      # endif // ifndef BUILD_NO_DEBUG
      ) {
    const deviceIndex_t DeviceIndex = getDeviceIndex_from_TaskIndex(TaskIndex);

    if (validDeviceIndex(DeviceIndex)) {
      const uint8_t valueCount = getValueCountForTask(TaskIndex);

      const String logline_prefix =
        strformat(F("%s %s,%d,%s")
                  , node_time.getDateString('-').c_str()
                  , node_time.getTimeString(':').c_str()
                  , Settings.Unit
                  , getTaskDeviceName(TaskIndex).c_str()
                  );

      for (uint8_t varNr = 0; varNr < valueCount; varNr++)
      {
        logger += strformat(F("%s,%s,%s\r\n")
                            , logline_prefix.c_str()
                            , Cache.getTaskDeviceValueName(TaskIndex, varNr).c_str()
                            , formatUserVarNoCheck(TaskIndex, varNr).c_str()
                            );
      }
      # ifndef BUILD_NO_DEBUG
      addLog(LOG_LEVEL_DEBUG, logger);
      # endif // ifndef BUILD_NO_DEBUG
    }
  }
#endif // if !defined(BUILD_NO_DEBUG) || FEATURE_SD

#if FEATURE_SD

  if (!logger.isEmpty()) {
    String   filename = patch_fname(F("VALUES.CSV"));
    fs::File logFile  = SD.open(filename, "a+");

    if (logFile) {
      logFile.print(logger);
    }
    logFile.close();
  }
#endif // if FEATURE_SD
}

// #######################################################################################################
// ############################ quite acurate but slow color converter####################################
// #######################################################################################################
// uses H 0..360 S 1..100 I/V 1..100 (according to homie convention)
// Source https://blog.saikoled.com/post/44677718712/how-to-convert-from-hsi-to-rgb-white

void HSV2RGB(float H, float S, float I, int rgb[3]) {
  // FIXME TD-er:   Why not just call HSV2RGBW and leave out the W part?

  int rgbw[4]{};

  HSV2RGBW(H, S, I, rgbw);
  memcpy(rgb, rgbw, 3 * sizeof(int));

  /*

     int r, g, b;

     H = fmod(H, 360);                           // cycle H around to 0-360 degrees
     constexpr float deg2rad = 3.14159f / 180.0f;
     H *= deg2rad;                               // Convert to radians.
     S = S / 100;
     S = S > 0 ? (S < 1 ? S : 1) : 0;            // clamp S and I to interval [0,1]
     I = I / 100;
     I = I > 0 ? (I < 1 ? I : 1) : 0;

     // Math! Thanks in part to Kyle Miller.
     if (H < 2.09439f) {
     r = 255 * I / 3 * (1 + S * cosf(H) / cosf(1.047196667f - H));
     g = 255 * I / 3 * (1 + S * (1 - cosf(H) / cosf(1.047196667f - H)));
     b = 255 * I / 3 * (1 - S);
     } else if (H < 4.188787f) {
     H = H - 2.09439f;
     g = 255 * I / 3 * (1 + S * cosf(H) / cosf(1.047196667f - H));
     b = 255 * I / 3 * (1 + S * (1 - cosf(H) / cosf(1.047196667f - H)));
     r = 255 * I / 3 * (1 - S);
     } else {
     H = H - 4.188787f;
     b = 255 * I / 3 * (1 + S * cosf(H) / cosf(1.047196667f - H));
     r = 255 * I / 3 * (1 + S * (1 - cosf(H) / cosf(1.047196667f - H)));
     g = 255 * I / 3 * (1 - S);
     }
     rgb[0] = r;
     rgb[1] = g;
     rgb[2] = b;
   */
}

// uses H 0..360 S 1..100 I/V 1..100 (according to homie convention)
// Source https://blog.saikoled.com/post/44677718712/how-to-convert-from-hsi-to-rgb-white
void HSV2RGBW(float H, float S, float I, int rgbw[4]) {
  H = fmod(H, 360);                 // cycle H around to 0-360 degrees
  constexpr float deg2rad = 3.14159f / 180.0f;
  H *= deg2rad;                     // Convert to radians.
  S  = S / 100;
  S  = S > 0 ? (S < 1 ? S : 1) : 0; // clamp S and I to interval [0,1]
  I  = I / 100;
  I  = I > 0 ? (I < 1 ? I : 1) : 0;

  #define RGB_ORDER 0
  #define BRG_ORDER 1
  #define GBR_ORDER 2

  int order = RGB_ORDER;

  constexpr float ANGLE_120_DEG = 120.0f * deg2rad;
  constexpr float ANGLE_240_DEG = 240.0f * deg2rad;
  constexpr float ANGLE_60_DEG  =  60.0f * deg2rad;

  if (H < ANGLE_120_DEG) {
    order = RGB_ORDER;
  } else if (H < ANGLE_240_DEG) {
    H     = H - ANGLE_120_DEG;
    order = BRG_ORDER;
  } else {
    H     = H - ANGLE_240_DEG;
    order = GBR_ORDER;
  }
  const float cos_h      = cosf(H);
  const float cos_1047_h = cosf(ANGLE_60_DEG - H);

  const int r = S * 255 * I / 3 * (1 + cos_h / cos_1047_h);
  const int g = S * 255 * I / 3 * (1 + (1 - cos_h / cos_1047_h));
  const int b = 0;
  rgbw[3] = 255 * (1 - S) * I;

  if (RGB_ORDER == order) {
    rgbw[0] = r;
    rgbw[1] = g;
    rgbw[2] = b;
  } else if (BRG_ORDER == order) {
    rgbw[0] = b;
    rgbw[1] = r;
    rgbw[2] = g;
  } else if (GBR_ORDER == order) {
    rgbw[0] = g;
    rgbw[1] = b;
    rgbw[2] = r;
  }
}

// Convert RGB Color to HSV Color
void RGB2HSV(uint8_t r, uint8_t g, uint8_t b, float hsv[3]) {
  const float rf = static_cast<float>(r) / 255.0f;
  const float gf = static_cast<float>(g) / 255.0f;
  const float bf = static_cast<float>(b) / 255.0f;
  float maxval   = rf;

  if (gf > maxval) { maxval = gf; }

  if (bf > maxval) { maxval = bf; }
  float minval = rf;

  if (gf < minval) { minval = gf; }

  if (bf < minval) { minval = bf; }
  float h = 0.0f, s, v = maxval;
  float f = maxval - minval;

  s = maxval == 0.0f ? 0.0f : f / maxval;

  if (maxval == minval) {
    h = 0.0f; // achromatic
  } else {
    if (maxval == rf) {
      h = (gf - bf) / f + (gf < bf ? 6.0f : 0.0f);
    } else if (maxval == gf) {
      h = (bf - rf) / f + 2.0f;
    } else if (maxval == bf) {
      h = (rf - gf) / f + 4.0f;
    }
    h /= 6.0f;
  }

  hsv[0] = h * 360.0f;
  hsv[1] = s * 255.0f;
  hsv[2] = v * 255.0f;
}

float getCPUload() {
  return 100.0f - Scheduler.getIdleTimePct();
}

int getLoopCountPerSec() {
  return loopCounterLast / 30;
}

int getUptimeMinutes() {
  return wdcounter / 2;
}

/******************************************************************************
 * scan an int array of specified size for a value
 *****************************************************************************/
bool intArrayContains(const int arraySize, const int array[], const int& value) {
  for (int i = 0; i < arraySize; i++) {
    if (array[i] == value) { return true; }
  }
  return false;
}

bool intArrayContains(const int arraySize, const uint8_t array[], const uint8_t& value) {
  for (int i = 0; i < arraySize; i++) {
    if (array[i] == value) { return true; }
  }
  return false;
}

#ifndef BUILD_NO_RAM_TRACKER
void logMemUsageAfter(const __FlashStringHelper *function, int value) {
  // Store free memory in an int, as subtracting may sometimes result in negative value.
  // The recorded used memory is not an exact value, as background (or interrupt) tasks may also allocate or free heap memory.
  static int last_freemem = ESP.getFreeHeap();
  const int  freemem_end  = ESP.getFreeHeap();

  if (loglevelActiveFor(LOG_LEVEL_DEBUG)) {
    String log;

    if (reserve_special(log, 128)) {
      log  = F("After ");
      log += function;

      if (value >= 0) {
        log += value;
      }

      while (log.length() < 30) { log += ' '; }
      log += F("Free mem after: ");
      log += freemem_end;

      while (log.length() < 55) { log += ' '; }
      log += F("diff: ");
      log += last_freemem - freemem_end;
      addLogMove(LOG_LEVEL_DEBUG, log);
    }
  }

  last_freemem = freemem_end;
}

#endif // ifndef BUILD_NO_RAM_TRACKER

#include "../Commands/ExecuteCommand.h"
#include "../DataTypes/FormSelectorOptions.h"

void indikator_secimi(struct EventStruct* event,long indikator, String plugin_indikator) {
  int choice1 = indikator;
  if (!Settings.UseCasVersion) {
    const __FlashStringHelper *options[] = {
      F("A12E"),
      F("BAYKON"),
      F("CAS"),
      F("ERTE"),
      F("SK210 SK330"),
      F("ESIT"),
      F("RINSTRUM"),
      F("SERBEST"),
      F("OCS-C E"),
      F("OCS-C Y"),
      F("OCS-SX"),
      F("KELI"),
      F("T18"),
      F("DH"),
      F("SUPER"),
      F("JADEVER"),
      F("RAW-RCW-RHW-RMW"),
      F("TUNAYLAR"),
      F("DiNiARGEO"),
      F("DiGiDEViCE"),
      F("METTLER TOLEDO"),
      F("BASTER"),
      F("AVERY"),
      F("MEGA"),
      F("LAUMAS"),
      F("RiCELAKE"),
      F("RCC"),
      F("DT"),
      F("OCS-K"),
      F("DENSi CM"),
      F("RCP"),
      F("X12"),
      F("DGT-60 Multi"),
      F("LEADER"),
      F("TEM")
    };
    constexpr int optionCount = NR_ELEMENTS(options);
    const FormSelectorOptions selector3(optionCount, options);
    selector3.addFormSelector(F("İndikatör"), plugin_indikator, choice1);
  } else {
    const __FlashStringHelper *options1[] = {
      F("CAS EC2"),
      F("CAS BI-200"),
      F("CAS CI-200"),
      F("CAS DB-II"),
      F("CAS DH")
    };
    constexpr int optionCount1 = NR_ELEMENTS(options1);
    const FormSelectorOptions selector4(optionCount1, options1);
    selector4.addFormSelector(F("İndikatör"), plugin_indikator, choice1);
  }
  addFormNumericBox(F("İşaret Byte"), F("isaret_byte_0"), ExtraTaskSettings.TaskDeviceIsaretByte, 0, 255);
  addFormNumericBox(F("Son Byte"), F("son_byte_0"), ExtraTaskSettings.TaskDeviceSonByte, 0, 255);
}

void indikator_secimi_kaydet(struct EventStruct* event, long indikator, boolean duzenle) {
  if (!duzenle) {
    switch (indikator) {
      case 0:
        ExtraTaskSettings.TaskDeviceIsaretByte = 2;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 3;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 9;
        ExtraTaskSettings.TaskDeviceSonByte = 10;
        Settings.Tersle = false;
        break;  //A12
      case 1:
        ExtraTaskSettings.TaskDeviceIsaretByte = 2;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 4;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 10;
        ExtraTaskSettings.TaskDeviceSonByte = 13;
        ExtraTaskSettings.TaskDeviceValueBas[1] = 10;
        ExtraTaskSettings.TaskDeviceValueBit[1] = 16;
        Settings.Tersle = false;
        break;  //BAYKON
      case 2:
        ExtraTaskSettings.TaskDeviceIsaretByte = 1;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 11;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 17;
        ExtraTaskSettings.TaskDeviceSonByte = 10;
        Settings.Tersle = false;
        break;  //CAS
      case 3:
        ExtraTaskSettings.TaskDeviceIsaretByte = 1;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 2;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 7;
        ExtraTaskSettings.TaskDeviceSonByte = 13;
        Settings.Tersle = false;
        break;  //ERTE
      case 4:
        ExtraTaskSettings.TaskDeviceIsaretByte = 1;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 3;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 9;
        ExtraTaskSettings.TaskDeviceSonByte = 13;
        ExtraTaskSettings.TaskDeviceValueBas[1] = 9;
        ExtraTaskSettings.TaskDeviceValueBit[1] = 16;
        Settings.Tersle = false;
        break;  //SK210 SK330
      case 5:
        ExtraTaskSettings.TaskDeviceIsaretByte = 0;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 1;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 7;
        ExtraTaskSettings.TaskDeviceSonByte = 13;
        Settings.Tersle = false;
        break;  //ESİT
      case 6:
        ExtraTaskSettings.TaskDeviceIsaretByte = 1;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 4;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 9;
        ExtraTaskSettings.TaskDeviceSonByte = 3;
        Settings.Tersle = false;
        break;  //RİNSTRUM
      case 8:
        ExtraTaskSettings.TaskDeviceIsaretByte = 0;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 1;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 6;
        ExtraTaskSettings.TaskDeviceSonByte = 127;
        Settings.Tersle = true;
        break;  //OCS-C E
      case 9:
        ExtraTaskSettings.TaskDeviceIsaretByte = 1;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 1;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 7;
        ExtraTaskSettings.TaskDeviceSonByte = 10;
        Settings.Tersle = false;
        break;  //OCS-C Y
      case 10:
        ExtraTaskSettings.TaskDeviceIsaretByte = 18;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 19;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 25;
        ExtraTaskSettings.TaskDeviceSonByte = 10;
        ExtraTaskSettings.TaskDeviceValueBas[1] = 11;
        ExtraTaskSettings.TaskDeviceValueBit[1] = 17;
        ExtraTaskSettings.TaskDeviceValueBas[2] = 3;
        ExtraTaskSettings.TaskDeviceValueBit[2] = 9;
        Settings.Tersle = false;
        break;  //OCS-SX
      case 11:
        ExtraTaskSettings.TaskDeviceIsaretByte = 1;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 2;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 8;
        ExtraTaskSettings.TaskDeviceSonByte = 10;
        Settings.Tersle = false;
        break;  //KELİ
      case 12:
        ExtraTaskSettings.TaskDeviceIsaretByte = 6;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 8;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 14;
        ExtraTaskSettings.TaskDeviceSonByte = 10;
        Settings.Tersle = false;
        break;  //T18
      case 13:
        ExtraTaskSettings.TaskDeviceIsaretByte = 2;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 3;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 10;
        ExtraTaskSettings.TaskDeviceSonByte = 10;
        Settings.Tersle = false;
        break;  //DH
      case 14:
        ExtraTaskSettings.TaskDeviceIsaretByte = 0;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 2;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 8;
        ExtraTaskSettings.TaskDeviceSonByte = 61;
        Settings.Tersle = false;
        break;  //SUPER
      case 15:
        ExtraTaskSettings.TaskDeviceIsaretByte = 6;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 8;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 14;
        ExtraTaskSettings.TaskDeviceSonByte = 10;
        Settings.Tersle = false;
        break;  //JADAVER
      //case 16 : ExtraTaskSettings.TaskDeviceIsaretByte =  0; ExtraTaskSettings.TaskDeviceValueBas[0] =  2; ExtraTaskSettings.TaskDeviceValueBit[0] =  8; ExtraTaskSettings.TaskDeviceSonByte = 10; break;
      case 16:
        ExtraTaskSettings.TaskDeviceIsaretByte = 6;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 7;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 14;
        ExtraTaskSettings.TaskDeviceSonByte = 10;
        Settings.Tersle = false;
        break;  //RAW-RCW-RHW-RMW
      case 17:
        ExtraTaskSettings.TaskDeviceIsaretByte = 1;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 4;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 10;
        ExtraTaskSettings.TaskDeviceSonByte = 13;
        Settings.Tersle = false;
        break;  //TUNAYLAR
      case 18:
        ExtraTaskSettings.TaskDeviceIsaretByte = 7;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 8;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 14;
        ExtraTaskSettings.TaskDeviceSonByte = 10;
        Settings.Tersle = false;
        break;  //DİNİ ARGEO
      case 19:
        ExtraTaskSettings.TaskDeviceIsaretByte = 4;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 4;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 9;
        ExtraTaskSettings.TaskDeviceSonByte = 9;
        Settings.Tersle = false;
        break;  //DİGİ DEVİCES
      case 20:
        ExtraTaskSettings.TaskDeviceIsaretByte = 1;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 3;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 10;
        ExtraTaskSettings.TaskDeviceSonByte = 13;
        ExtraTaskSettings.TaskDeviceValueBas[1] = 10;
        ExtraTaskSettings.TaskDeviceValueBit[1] = 17;
        Settings.Tersle = false;
        break;  //METTLER TOLEDO
      case 21:
        ExtraTaskSettings.TaskDeviceIsaretByte = 0;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 1;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 7;
        ExtraTaskSettings.TaskDeviceSonByte = 13;
        Settings.Tersle = false;
        break;  //BASTER
      case 22:
        ExtraTaskSettings.TaskDeviceIsaretByte = 1;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 1;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 8;
        ExtraTaskSettings.TaskDeviceSonByte = 3;
        Settings.Tersle = false;
        break;  //AVERY BERKEL
      case 23:
        ExtraTaskSettings.TaskDeviceIsaretByte = 0;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 1;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 7;
        ExtraTaskSettings.TaskDeviceSonByte = 61;
        Settings.Tersle = true;
        break;  //MEGA
      case 24:
        ExtraTaskSettings.TaskDeviceIsaretByte = 0;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 1;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 6;
        ExtraTaskSettings.TaskDeviceSonByte = 10;
        Settings.Tersle = false;
        break;  //LAUMAS
      case 25:
        ExtraTaskSettings.TaskDeviceIsaretByte = 1;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 3;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 9;
        ExtraTaskSettings.TaskDeviceSonByte = 10;
        Settings.Tersle = false;
        break;  //RICE LAKE
      case 26:
        ExtraTaskSettings.TaskDeviceIsaretByte = 4;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 5;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 12;
        ExtraTaskSettings.TaskDeviceSonByte = 10;
        ExtraTaskSettings.TaskDeviceValueBas[1] = 5;
        ExtraTaskSettings.TaskDeviceValueBit[1] = 12;
        ExtraTaskSettings.TaskDeviceValueBas[2] = 4;
        ExtraTaskSettings.TaskDeviceValueBit[2] = 12;
        ExtraTaskSettings.TaskDeviceValueBas[3] = 5;
        ExtraTaskSettings.TaskDeviceValueBit[3] = 12;
        ExtraTaskSettings.TaskDeviceValueBas[4] = 4;
        ExtraTaskSettings.TaskDeviceValueBit[4] = 12;
        Settings.Tersle = false;
        break;  //DİKOMSAN RCC
      case 27:
        ExtraTaskSettings.TaskDeviceIsaretByte = 4;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 5;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 12;
        ExtraTaskSettings.TaskDeviceSonByte = 10;
        ExtraTaskSettings.TaskDeviceValueBas[3] = 5;
        ExtraTaskSettings.TaskDeviceValueBit[3] = 13;
        Settings.Tersle = false;
        break;  //DT
      case 28:
        ExtraTaskSettings.TaskDeviceIsaretByte = 0;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 0;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 7;
        ExtraTaskSettings.TaskDeviceSonByte = 61;
        Settings.Tersle = false;
        break;  //OCS-K
      case 29:
        ExtraTaskSettings.TaskDeviceIsaretByte = 7;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 0;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 6;
        ExtraTaskSettings.TaskDeviceSonByte = 61;
        Settings.Tersle = true;
        break;  //DENSİ CM
      case 30:
        ExtraTaskSettings.TaskDeviceIsaretByte = 6;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 7;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 14;
        ExtraTaskSettings.TaskDeviceSonByte = 10;
        ExtraTaskSettings.TaskDeviceValueBas[1] = 7;
        ExtraTaskSettings.TaskDeviceValueBit[1] = 14;
        ExtraTaskSettings.TaskDeviceValueBas[6] = 6;
        ExtraTaskSettings.TaskDeviceValueBit[6] = 13;
        ExtraTaskSettings.TaskDeviceValueBas[7] = 6;
        ExtraTaskSettings.TaskDeviceValueBit[7] = 16;
        Settings.Tersle = false;
        break;  //DİKOMSAN RPC
      case 31:
        ExtraTaskSettings.TaskDeviceIsaretByte = 1;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 4;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 10;
        ExtraTaskSettings.TaskDeviceSonByte = 13;
        ExtraTaskSettings.TaskDeviceValueBas[1] = 10;
        ExtraTaskSettings.TaskDeviceValueBit[1] = 16;
        Settings.Tersle = false;
        break;  //X12
      case 32:
        ExtraTaskSettings.TaskDeviceIsaretByte = 3;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 4;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 11;
        ExtraTaskSettings.TaskDeviceSonByte = 10;
        //ExtraTaskSettings.TaskDeviceIsaretByte_2 = 18;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 19;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 26;
        Settings.Tersle = false;
        break;  //DİNİ ARGEO DGT60
      case 33:
        ExtraTaskSettings.TaskDeviceIsaretByte = 0;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 202;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 209;
        ExtraTaskSettings.TaskDeviceSonByte = 13;
        ExtraTaskSettings.TaskDeviceValueBas[1] = 139;
        ExtraTaskSettings.TaskDeviceValueBit[1] = 147;
        ExtraTaskSettings.TaskDeviceValueBas[2] = 130;
        ExtraTaskSettings.TaskDeviceValueBit[2] = 138;
        ExtraTaskSettings.TaskDeviceValueBas[3] = 8;
        ExtraTaskSettings.TaskDeviceValueBit[3] = 31;
        ExtraTaskSettings.TaskDeviceValueBas[4] = 32;
        ExtraTaskSettings.TaskDeviceValueBit[4] = 55;
        ExtraTaskSettings.TaskDeviceValueBas[5] = 56;
        ExtraTaskSettings.TaskDeviceValueBit[5] = 79;
        ExtraTaskSettings.TaskDeviceValueBas[6] = 80;
        ExtraTaskSettings.TaskDeviceValueBit[6] = 103;
        ExtraTaskSettings.TaskDeviceValueBas[7] = 104;
        ExtraTaskSettings.TaskDeviceValueBit[7] = 129;
        ExtraTaskSettings.TaskDeviceValueBas[8] = 159;
        ExtraTaskSettings.TaskDeviceValueBit[8] = 165;
        ExtraTaskSettings.TaskDeviceValueBas[9] = 0;
        ExtraTaskSettings.TaskDeviceValueBit[9] = 0;
        Settings.Tersle = false;
        break;  //LEADER
      case 34:
        ExtraTaskSettings.TaskDeviceIsaretByte = 0;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 2;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 9;
        ExtraTaskSettings.TaskDeviceSonByte = 10;
        ExtraTaskSettings.TaskDeviceValueBas[1] = 2;
        ExtraTaskSettings.TaskDeviceValueBit[1] = 9;
        Settings.Tersle = false;
        break;  //TEM
      case 50:
        ExtraTaskSettings.TaskDeviceIsaretByte = 6;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 6;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 14;
        ExtraTaskSettings.TaskDeviceSonByte = 10;
        ExtraTaskSettings.TaskDeviceValueBas[1] = 6;
        ExtraTaskSettings.TaskDeviceValueBit[1] = 14;
        ExtraTaskSettings.TaskDeviceValueBas[2] = 6;
        ExtraTaskSettings.TaskDeviceValueBit[2] = 14;
        ExtraTaskSettings.TaskDeviceValueBas[3] = 6;
        ExtraTaskSettings.TaskDeviceValueBit[3] = 14;
        ExtraTaskSettings.TaskDeviceValueBas[4] = 6;
        ExtraTaskSettings.TaskDeviceValueBit[4] = 14;
        Settings.Tersle = false;
        break;  //CAS EC2
      case 51:
        ExtraTaskSettings.TaskDeviceIsaretByte = 6;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 8;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 14;
        ExtraTaskSettings.TaskDeviceSonByte = 10;
        Settings.Tersle = false;
        break;  //CAS BI-200
      case 52:
        ExtraTaskSettings.TaskDeviceIsaretByte = 7;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 8;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 15;
        ExtraTaskSettings.TaskDeviceSonByte = 10;
        Settings.Tersle = false;
        break;  //CAS CI-200
      case 53:
        ExtraTaskSettings.TaskDeviceIsaretByte = 10;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 11;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 17;
        ExtraTaskSettings.TaskDeviceSonByte = 44;
        ExtraTaskSettings.TaskDeviceValueBas[1] = 19;
        ExtraTaskSettings.TaskDeviceValueBit[1] = 25;
        Settings.Tersle = false;
        break;  //CAS DB-II
      case 54:
        ExtraTaskSettings.TaskDeviceIsaretByte = 2;
        ExtraTaskSettings.TaskDeviceValueBas[0] = 3;
        ExtraTaskSettings.TaskDeviceValueBit[0] = 10;
        ExtraTaskSettings.TaskDeviceSonByte = 10;
        Settings.Tersle = false;
        break;  //DH
    }
  }
  else {
    ExtraTaskSettings.TaskDeviceIsaretByte = getFormItemInt(F("isaret_byte_0"));
    ExtraTaskSettings.TaskDeviceSonByte = getFormItemInt(F("son_byte_0"));
  }
}

void udp_client(struct EventStruct* event, long indikator, String udp_data, int eyz_mod) {
  hataTimer_l = millis();
  if (((udp_data.substring(ExtraTaskSettings.TaskDeviceIsaretByte, ExtraTaskSettings.TaskDeviceIsaretByte + 1) == "3") ||  //daralı sabit eksi
       (udp_data.substring(ExtraTaskSettings.TaskDeviceIsaretByte, ExtraTaskSettings.TaskDeviceIsaretByte + 1) == "2") ||  //darasız sabit eksi
       (udp_data.substring(ExtraTaskSettings.TaskDeviceIsaretByte, ExtraTaskSettings.TaskDeviceIsaretByte + 1) == ":") ||  //darasız haraketli eksi
       (udp_data.substring(ExtraTaskSettings.TaskDeviceIsaretByte, ExtraTaskSettings.TaskDeviceIsaretByte + 1) == ";"))
      && (indikator == 20))  //daralı haraketli eksi
    isaret_f = -1;
  else if (udp_data.substring(ExtraTaskSettings.TaskDeviceIsaretByte, ExtraTaskSettings.TaskDeviceIsaretByte + 1) == "-")
    isaret_f = -1;
  else
    isaret_f = 1;
  //webapinettartim = isaret_f * (udp_data.substring(ExtraTaskSettings.TaskDeviceValueBas[0], ExtraTaskSettings.TaskDeviceValueBit[0]).toFloat());
  webapidaratartim = (udp_data.substring(ExtraTaskSettings.TaskDeviceValueBas[1], ExtraTaskSettings.TaskDeviceValueBit[1]).toFloat());
  //webapibruttartim = webapidaratartim + webapinettartim;
  webapibruttartim = isaret_f * (udp_data.substring(ExtraTaskSettings.TaskDeviceValueBas[2], ExtraTaskSettings.TaskDeviceValueBit[2]).toFloat());
  webapinettartim = webapibruttartim - webapidaratartim;
  UserVar.setFloat(event->BaseVarIndex, 0, webapinettartim);
  UserVar.setFloat(event->BaseVarIndex, 1, webapidaratartim);
  UserVar.setFloat(event->BaseVarIndex, 2, webapibruttartim);
  float bol = 1;
  if ((indikator == 1) || (indikator == 3) || (indikator == 4) || (indikator == 20) || (indikator == 31)) {
    switch (ExtraTaskSettings.TaskDeviceValueDecimals[0]) {
      case 0: bol = 1; break;
      case 1: bol = 10; break;
      case 2: bol = 100; break;
      case 3: bol = 1000; break;
    }
  }
  XML_NET_S = String((webapinettartim / bol), int(ExtraTaskSettings.TaskDeviceValueDecimals[0]));
  XML_DARA_S = String((webapidaratartim / bol), int(ExtraTaskSettings.TaskDeviceValueDecimals[1]));
  XML_BRUT_S = String((webapibruttartim / bol), int(ExtraTaskSettings.TaskDeviceValueDecimals[2]));
  XML_ADET_S = String(webapiadet, 0);
  XML_ADET_GRAMAJ_S = String(webapiadetgr, 0);
  XML_URUN_NO_S = String(webapiurunno, 0);
  XML_BIRIM_FIYAT_S = String(webapibfiyat, 0);
  XML_TUTAR_S = String(webapitutar, 0);
  XML_TARIH_S = node_time.getDateString('-');
  XML_SAAT_S = node_time.getTimeString(':');
  dtostrf(XML_NET_S.toFloat(), (ExtraTaskSettings.TaskDeviceValueBit[0] - ExtraTaskSettings.TaskDeviceValueBas[0]), ExtraTaskSettings.TaskDeviceValueDecimals[0], XML_NET_C);
  dtostrf(XML_DARA_S.toFloat(), (ExtraTaskSettings.TaskDeviceValueBit[1] - ExtraTaskSettings.TaskDeviceValueBas[1]), ExtraTaskSettings.TaskDeviceValueDecimals[1], XML_DARA_C);
  dtostrf(XML_BRUT_S.toFloat(), (ExtraTaskSettings.TaskDeviceValueBit[2] - ExtraTaskSettings.TaskDeviceValueBas[2]), ExtraTaskSettings.TaskDeviceValueDecimals[2], XML_BRUT_C);
  dtostrf(XML_ADET_S.toFloat(), (ExtraTaskSettings.TaskDeviceValueBit[3] - ExtraTaskSettings.TaskDeviceValueBas[3]), 0, XML_ADET_C);
  dtostrf(XML_ADET_GRAMAJ_S.toFloat(), (ExtraTaskSettings.TaskDeviceValueBit[4] - ExtraTaskSettings.TaskDeviceValueBas[4]), 0, XML_ADET_GRAMAJ_C);
  if ((eyz_mod == 1) && (webapinettartim > 0.001))
    ExecuteCommand_all({EventValueSource::Enum::VALUE_SOURCE_WEB_FRONTEND, "eyztek"});
}

void serial_error(struct EventStruct* event, int yazdir, String komut) {
  if ((millis() - hataTimer_l) > 2000) {
    //SensorSendAll();
    if ((yazdir == 6) && (oto_yazdir == true)) {
      XML_NET_S    = paketVeri_s.substring(ExtraTaskSettings.TaskDeviceValueBas[0], ExtraTaskSettings.TaskDeviceValueBit[0]);
      XML_TARIH_S  = paketVeri_s.substring(ExtraTaskSettings.TaskDeviceValueBas[1], ExtraTaskSettings.TaskDeviceValueBit[1]);
      XML_SAAT_S   = paketVeri_s.substring(ExtraTaskSettings.TaskDeviceValueBas[2], ExtraTaskSettings.TaskDeviceValueBit[2]);
      XML_MESAJ1_S = paketVeri_s.substring(ExtraTaskSettings.TaskDeviceValueBas[3], ExtraTaskSettings.TaskDeviceValueBit[3]);
      XML_MESAJ2_S = paketVeri_s.substring(ExtraTaskSettings.TaskDeviceValueBas[4], ExtraTaskSettings.TaskDeviceValueBit[4]);
      XML_MESAJ3_S = paketVeri_s.substring(ExtraTaskSettings.TaskDeviceValueBas[5], ExtraTaskSettings.TaskDeviceValueBit[5]);
      XML_MESAJ4_S = paketVeri_s.substring(ExtraTaskSettings.TaskDeviceValueBas[6], ExtraTaskSettings.TaskDeviceValueBit[6]);
      XML_MESAJ5_S = paketVeri_s.substring(ExtraTaskSettings.TaskDeviceValueBas[7], ExtraTaskSettings.TaskDeviceValueBit[7]);
      XML_MESAJ6_S = paketVeri_s.substring(ExtraTaskSettings.TaskDeviceValueBas[8], ExtraTaskSettings.TaskDeviceValueBit[8]);
      XML_MESAJ7_S = paketVeri_s.substring(ExtraTaskSettings.TaskDeviceValueBas[9], ExtraTaskSettings.TaskDeviceValueBit[9]);
      //XML_MESAJ8_S = paketVeri_s.substring(ExtraTaskSettings.TaskDeviceValueBas[0], ExtraTaskSettings.TaskDeviceValueBit[0]);
      //XML_MESAJ9_S = paketVeri_s.substring(ExtraTaskSettings.TaskDeviceValueBas[0], ExtraTaskSettings.TaskDeviceValueBit[0]);
      paketVeri_s = "";
      ExecuteCommand_all({EventValueSource::Enum::VALUE_SOURCE_WEB_FRONTEND, komut.c_str()});
      oto_yazdir = false;
    } else if ((yazdir == 3) && (oto_yazdir == true)) {
      ExecuteCommand_all({EventValueSource::Enum::VALUE_SOURCE_WEB_FRONTEND, komut.c_str()});
      oto_yazdir = false;
    } else {
      // Check if ESP-NOW peers are connected before showing ERROR
#ifdef USES_ESPNOW_MANAGER
      if (espnowManager.getPairedDeviceCount() > 0) {
        // ESP-NOW peers connected, don't show ERROR - data might come via ESP-NOW
        return;
      }
#endif
      XML_NET_S = "ERROR";
      XML_DARA_S = "ERROR";
      XML_BRUT_S = "ERROR";
      XML_ADET_S = "ADET";
      XML_ADET_GRAMAJ_S = "ERROR";
      XML_URUN_NO_S = "ERROR";
      XML_BIRIM_FIYAT_S = "ERROR";
      XML_TUTAR_S = "ERROR";
      XML_NET_S_2 = "ERROR";
      XML_DARA_S_2 = "ERROR";
      for (int i=0;i<10;i++)
       UserVar.setFloat(event->BaseVarIndex, i, NAN);
      webapinettartim = 0;
      webapidaratartim = 0;
      webapibruttartim = 0;
      webapiadet = 0;
      tartimdata_s = XML_NET_S;
    }
  }
  //Serial.flush();
}

void tersle(struct EventStruct* event, String data_s) {
  String tartim;
  int karakter_say = ExtraTaskSettings.TaskDeviceValueBit[0] - (ExtraTaskSettings.TaskDeviceValueBas[0]);
  for (int i = karakter_say; i > 0; i--)
    tartim += data_s.substring(((i + ExtraTaskSettings.TaskDeviceValueBas[0]) - 1) , (i + ExtraTaskSettings.TaskDeviceValueBas[0]));
  tartimString_s = tartim;
  XML_NET_S = tartim;
  dtostrf(XML_NET_S.toFloat(), (ExtraTaskSettings.TaskDeviceValueBit[0] - ExtraTaskSettings.TaskDeviceValueBas[0]), ExtraTaskSettings.TaskDeviceValueDecimals[0], XML_NET_C);
}

void isaret(struct EventStruct* event, long indikator, String data_s) {
  if (((data_s.substring(ExtraTaskSettings.TaskDeviceIsaretByte, ExtraTaskSettings.TaskDeviceIsaretByte + 1) == "3") ||  //daralı sabit eksi
       (data_s.substring(ExtraTaskSettings.TaskDeviceIsaretByte, ExtraTaskSettings.TaskDeviceIsaretByte + 1) == "2") ||  //darasız sabit eksi
       (data_s.substring(ExtraTaskSettings.TaskDeviceIsaretByte, ExtraTaskSettings.TaskDeviceIsaretByte + 1) == ":") ||  //darasız haraketli eksi
       (data_s.substring(ExtraTaskSettings.TaskDeviceIsaretByte, ExtraTaskSettings.TaskDeviceIsaretByte + 1) == ";"))    //daralı haraketli eksi
      && ((indikator == 4) || (indikator == 20) || (indikator == 31)))  
    isaret_f = -1;
  else if (data_s.substring(ExtraTaskSettings.TaskDeviceIsaretByte, ExtraTaskSettings.TaskDeviceIsaretByte + 1) == "-")
    isaret_f = -1;
  else
    isaret_f = 1;
}

void formul_seri(struct EventStruct* event, String data_s, long indikator) {
  XML_NET_V  = data_s.substring(ExtraTaskSettings.TaskDeviceValueBas[0], ExtraTaskSettings.TaskDeviceValueBit[0]);
  XML_DARA_V = data_s.substring(ExtraTaskSettings.TaskDeviceValueBas[1], ExtraTaskSettings.TaskDeviceValueBit[1]);
  XML_BRUT_V = data_s.substring(ExtraTaskSettings.TaskDeviceValueBas[2], ExtraTaskSettings.TaskDeviceValueBit[2]);
  if (((indikator == 8) || (indikator == 9)) && ExtraTaskSettings.TaskDeviceValueDecimals[0] == 1) {
    XML_NET_S = data_s.substring(ExtraTaskSettings.TaskDeviceValueBas[0], ExtraTaskSettings.TaskDeviceValueBit[0]);
    XML_NET_S.replace(")", "0.");
    XML_NET_S.replace("!", "1.");
    XML_NET_S.replace("@", "2.");
    XML_NET_S.replace("#", "3.");
    XML_NET_S.replace("$", "4.");
    XML_NET_S.replace("%", "5.");
    XML_NET_S.replace("^", "6.");
    XML_NET_S.replace("&", "7.");
    XML_NET_S.replace("*", "8.");
    XML_NET_S.replace("(", "9.");
  } else {
    // Parse BRUT first (if available in serial data)
    if (uint8_t(ExtraTaskSettings.TaskDeviceValueBit[2]) > 0)
      webapibruttartim = isaret_f * (data_s.substring(uint8_t(ExtraTaskSettings.TaskDeviceValueBas[2]), uint8_t(ExtraTaskSettings.TaskDeviceValueBit[2])).toFloat());
    
    // Parse DARA (if available in serial data, otherwise keep current value)
    if (uint8_t(ExtraTaskSettings.TaskDeviceValueBit[1]) > 0) {
      webapidaratartim = (data_s.substring(uint8_t(ExtraTaskSettings.TaskDeviceValueBas[1]), uint8_t(ExtraTaskSettings.TaskDeviceValueBit[1])).toFloat());
    }
    // If DARA not in serial data, keep existing webapidaratartim (set by eyzdaraekle or previous value)
    // Don't reset to eyz_dara_degeri here - that would overwrite manual DARA setting
    
    // Parse NET or calculate it (NET = BRUT - DARA)
    if (uint8_t(ExtraTaskSettings.TaskDeviceValueBit[0]) > 0) {
      // NET value exists in serial data, use it
      webapinettartim = isaret_f * (data_s.substring(uint8_t(ExtraTaskSettings.TaskDeviceValueBas[0]), uint8_t(ExtraTaskSettings.TaskDeviceValueBit[0])).toFloat());
    } else {
      // NET not in serial data, calculate: NET = BRUT - DARA
      webapinettartim = webapibruttartim - webapidaratartim;
    }
    
    /*if (ExtraTaskSettings.TaskDeviceValueBit[3] > 0)
      webapiadet = (data_s.substring(ExtraTaskSettings.TaskDeviceValueBas[3], ExtraTaskSettings.TaskDeviceValueBit[3]).toFloat());
    else {
      if (adet_i == 1) 
        webapiadet = webapinettartim / webapiadetgr;
    }*/

    if (uint8_t(ExtraTaskSettings.TaskDeviceValueBit[4]) > 0)
      webapiadetgr = (data_s.substring(uint8_t(ExtraTaskSettings.TaskDeviceValueBas[4]), uint8_t(ExtraTaskSettings.TaskDeviceValueBit[4])).toFloat());
    /*else {
      //if (adet_i == 2)
      //  webapiadetgr = webapinettartim / webapiadet;
    }*/

    int carpan = 100;
    switch (int(ExtraTaskSettings.TaskDeviceValueDecimals[5])) {
      case 0: carpan = 1; break;
      case 1: carpan = 10; break;
      case 2: carpan = 100; break;
      case 3: carpan = 1000; break;
    }
    int urunno    = (data_s.substring(ExtraTaskSettings.TaskDeviceValueBas[5], ExtraTaskSettings.TaskDeviceValueBit[5]).toFloat()) * carpan;
    webapiurunno  = urunno;
    webapibfiyat = (data_s.substring(ExtraTaskSettings.TaskDeviceValueBas[6], ExtraTaskSettings.TaskDeviceValueBit[6]).toFloat());
    webapitutar  = (data_s.substring(ExtraTaskSettings.TaskDeviceValueBas[7], ExtraTaskSettings.TaskDeviceValueBit[7]).toFloat());
    UserVar.setFloat(event->TaskIndex, 0, webapinettartim);
    UserVar.setFloat(event->TaskIndex, 1, webapidaratartim);
    UserVar.setFloat(event->TaskIndex, 2, webapibruttartim);
    UserVar.setFloat(event->TaskIndex, 3, webapiadet);
    UserVar.setFloat(event->TaskIndex, 4, webapiadetgr);
    UserVar.setFloat(event->TaskIndex, 5, webapiurunno);
    UserVar.setFloat(event->TaskIndex, 6, webapibfiyat);
    UserVar.setFloat(event->TaskIndex, 7, webapitutar);
    float bol = 1;
    if ((indikator == 1) || (indikator == 3) || (indikator == 4) || (indikator == 20) || (indikator == 31)) {
      switch (ExtraTaskSettings.TaskDeviceValueDecimals[0]) {
        case 0: bol = 1; break;
        case 1: bol = 10; break;
        case 2: bol = 100; break;
        case 3: bol = 1000; break;
      }
    }
    XML_NET_S  = String((webapinettartim / bol),  int(ExtraTaskSettings.TaskDeviceValueDecimals[0]));
    XML_DARA_S = String((webapidaratartim / bol), int(ExtraTaskSettings.TaskDeviceValueDecimals[1]));
    XML_BRUT_S = String((webapibruttartim / bol), int(ExtraTaskSettings.TaskDeviceValueDecimals[2]));
    //XML_ADET_S = String(webapiadet, 0);
    XML_ADET_GRAMAJ_S = String(webapiadetgr, int(ExtraTaskSettings.TaskDeviceValueDecimals[4]));
    XML_URUN_NO_S = String(webapiurunno, 0);
    XML_BIRIM_FIYAT_S = String(webapibfiyat, 0);
    XML_TUTAR_S = String(webapitutar, 0);
    
    addLog(LOG_LEVEL_INFO, concat(F("formul_seri: XML_NET_S="), XML_NET_S));
    addLog(LOG_LEVEL_INFO, concat(F("formul_seri: XML_DARA_S="), XML_DARA_S));
    addLog(LOG_LEVEL_INFO, concat(F("formul_seri: XML_BRUT_S="), XML_BRUT_S));
  }
  XML_TARIH_S = node_time.getDateString('-');
  XML_SAAT_S = node_time.getTimeString(':');
  event->String1 = XML_NET_S;
  event->String2 = XML_DARA_S;
  event->String3 = XML_BRUT_S;
  event->String4 = XML_ADET_S;
  event->String5 = XML_ADET_GRAMAJ_S;
  dtostrf(XML_NET_S.toFloat(), (ExtraTaskSettings.TaskDeviceValueBit[0] - ExtraTaskSettings.TaskDeviceValueBas[0]), ExtraTaskSettings.TaskDeviceValueDecimals[0], XML_NET_C);
  dtostrf(XML_DARA_S.toFloat(), (ExtraTaskSettings.TaskDeviceValueBit[1] - ExtraTaskSettings.TaskDeviceValueBas[1]), ExtraTaskSettings.TaskDeviceValueDecimals[1], XML_DARA_C);
  dtostrf(XML_BRUT_S.toFloat(), (ExtraTaskSettings.TaskDeviceValueBit[2] - ExtraTaskSettings.TaskDeviceValueBas[2]), ExtraTaskSettings.TaskDeviceValueDecimals[2], XML_BRUT_C);
  dtostrf(XML_ADET_S.toFloat(), (ExtraTaskSettings.TaskDeviceValueBit[3] - ExtraTaskSettings.TaskDeviceValueBas[3]), 0, XML_ADET_C);
  dtostrf(XML_ADET_GRAMAJ_S.toFloat(), (ExtraTaskSettings.TaskDeviceValueBit[4] - ExtraTaskSettings.TaskDeviceValueBas[4]), 0, XML_ADET_GRAMAJ_C);
}


void formul_kontrol(struct EventStruct* event, String data_s, int yazdir, boolean yazdir_aktif) {
  //if ((data_s.substring(0, String(ExtraTaskSettings.TaskDeviceFormula[7]).length()) == String(ExtraTaskSettings.TaskDeviceFormula[7])) && String(ExtraTaskSettings.TaskDeviceFormula[7]).length() > 1)
  //XML_TUTAR_S = data_s.substring(ExtraTaskSettings.TaskDeviceValueBas[7], ExtraTaskSettings.TaskDeviceValueBit[7]);
  //data_s.toUpperCase();
  if ((data_s.substring(0, String(ExtraTaskSettings.TaskDeviceFormula[7]).length()) == String(ExtraTaskSettings.TaskDeviceFormula[7])) && String(ExtraTaskSettings.TaskDeviceFormula[7]).length() > 1)
    XML_URUN_ISMI_S = data_s.substring(ExtraTaskSettings.TaskDeviceValueBas[7], (data_s.length()));
  //else if ((data_s.substring(0, String(ExtraTaskSettings.TaskDeviceFormula[6]).length()) == String(ExtraTaskSettings.TaskDeviceFormula[6])) && String(ExtraTaskSettings.TaskDeviceFormula[6]).length() > 1)
  //XML_BIRIM_FIYAT_S = data_s.substring(ExtraTaskSettings.TaskDeviceValueBas[6], ExtraTaskSettings.TaskDeviceValueBit[6]);
  else if ((data_s.substring(0, String(ExtraTaskSettings.TaskDeviceFormula[6]).length()) == String(ExtraTaskSettings.TaskDeviceFormula[6])) && String(ExtraTaskSettings.TaskDeviceFormula[6]).length() > 1)
    XML_URUN_NO_S = data_s.substring(ExtraTaskSettings.TaskDeviceValueBas[6], (data_s.length()));
  /*else if ((data_s.substring(0, String(ExtraTaskSettings.TaskDeviceFormula[5]).length()) == String(ExtraTaskSettings.TaskDeviceFormula[5])) && String(ExtraTaskSettings.TaskDeviceFormula[5]).length() > 1) {
    int carpan = 100;
    switch (int(ExtraTaskSettings.TaskDeviceValueDecimals[5])) {
      case 0: carpan = 1; break;
      case 1: carpan = 10; break;
      case 2: carpan = 100; break;
      case 3: carpan = 1000; break;
    }
    int pluno = (data_s.substring(ExtraTaskSettings.TaskDeviceValueBas[5], ExtraTaskSettings.TaskDeviceValueBit[5]).toFloat()) * carpan;
    XML_URUN_NO_S = String(pluno);
  }*/
  else if ((data_s.substring(0, String(ExtraTaskSettings.TaskDeviceFormula[5]).length()) == String(ExtraTaskSettings.TaskDeviceFormula[5])) && String(ExtraTaskSettings.TaskDeviceFormula[5]).length() > 1)
    XML_QRKOD_S = data_s.substring(ExtraTaskSettings.TaskDeviceValueBas[5], (data_s.length()));
  else if ((data_s.substring(0, String(ExtraTaskSettings.TaskDeviceFormula[4]).length()) == String(ExtraTaskSettings.TaskDeviceFormula[4])) && String(ExtraTaskSettings.TaskDeviceFormula[4]).length() > 1)
    XML_ADET_GRAMAJ_S = data_s.substring(ExtraTaskSettings.TaskDeviceValueBas[4], ExtraTaskSettings.TaskDeviceValueBit[4]);
  else if ((data_s.substring(0, String(ExtraTaskSettings.TaskDeviceFormula[3]).length()) == String(ExtraTaskSettings.TaskDeviceFormula[3])) && String(ExtraTaskSettings.TaskDeviceFormula[3]).length() > 1)
    XML_ADET_S = data_s.substring(ExtraTaskSettings.TaskDeviceValueBas[3], ExtraTaskSettings.TaskDeviceValueBit[3]);
  else if ((data_s.substring(0, String(ExtraTaskSettings.TaskDeviceFormula[2]).length()) == String(ExtraTaskSettings.TaskDeviceFormula[2])) && String(ExtraTaskSettings.TaskDeviceFormula[2]).length() > 1)
    XML_BRUT_S = data_s.substring(ExtraTaskSettings.TaskDeviceValueBas[2], ExtraTaskSettings.TaskDeviceValueBit[2]);
  else if ((data_s.substring(0, String(ExtraTaskSettings.TaskDeviceFormula[1]).length()) == String(ExtraTaskSettings.TaskDeviceFormula[1])) && String(ExtraTaskSettings.TaskDeviceFormula[1]).length() > 1)
    XML_DARA_S = data_s.substring(ExtraTaskSettings.TaskDeviceValueBas[1], ExtraTaskSettings.TaskDeviceValueBit[1]);
  else if ((data_s.substring(0, String(ExtraTaskSettings.TaskDeviceFormula[0]).length()) == String(ExtraTaskSettings.TaskDeviceFormula[0])) && String(ExtraTaskSettings.TaskDeviceFormula[0]).length() > 1)
    XML_NET_S = data_s.substring(ExtraTaskSettings.TaskDeviceValueBas[0], ExtraTaskSettings.TaskDeviceValueBit[0]);
  if (String(ExtraTaskSettings.TaskDeviceFormula[2]).length() == 0) {
    float brut = XML_NET_S.toFloat() + XML_DARA_S.toFloat();
    XML_BRUT_S = String(brut, int(ExtraTaskSettings.TaskDeviceValueDecimals[0]));
  }
  XML_TARIH_S = node_time.getDateString('-');
  XML_SAAT_S = node_time.getTimeString(':');
  dtostrf(XML_NET_S.toFloat(),  (ExtraTaskSettings.TaskDeviceValueBit[0] - ExtraTaskSettings.TaskDeviceValueBas[0]), ExtraTaskSettings.TaskDeviceValueDecimals[0], XML_NET_C);
  dtostrf(XML_DARA_S.toFloat(), (ExtraTaskSettings.TaskDeviceValueBit[1] - ExtraTaskSettings.TaskDeviceValueBas[1]), ExtraTaskSettings.TaskDeviceValueDecimals[1], XML_DARA_C);
  dtostrf(XML_BRUT_S.toFloat(), (ExtraTaskSettings.TaskDeviceValueBit[2] - ExtraTaskSettings.TaskDeviceValueBas[2]), ExtraTaskSettings.TaskDeviceValueDecimals[2], XML_BRUT_C);
  dtostrf(XML_ADET_S.toFloat(), (ExtraTaskSettings.TaskDeviceValueBit[3] - ExtraTaskSettings.TaskDeviceValueBas[3]), 0, XML_ADET_C);
  UserVar.setFloat(event->BaseVarIndex, 0, XML_NET_S.toFloat());
  UserVar.setFloat(event->BaseVarIndex, 1, XML_DARA_S.toFloat());
  UserVar.setFloat(event->BaseVarIndex, 2, XML_BRUT_S.toFloat());
  UserVar.setFloat(event->BaseVarIndex, 3, XML_ADET_S.toFloat());
  UserVar.setFloat(event->BaseVarIndex, 4, XML_ADET_GRAMAJ_S.toFloat());
  UserVar.setFloat(event->BaseVarIndex, 5, XML_URUN_NO_S.toFloat());
  UserVar.setFloat(event->BaseVarIndex, 6, XML_BIRIM_FIYAT_S.toFloat());
  UserVar.setFloat(event->BaseVarIndex, 7, XML_TUTAR_S.toFloat());

  if ((yazdir == 3) && (yazdir_aktif))
    oto_yazdir = true;
}

unsigned long str2int(char* string) {
  unsigned long temp = atof(string);
  return temp;
}

unsigned int f_2uint_int1(float float_number) {  // split the float and return first unsigned integer

  union f_2uint {
    float f;
    uint16_t i[2];
  };

  union f_2uint f_number;
  f_number.f = float_number;

  return f_number.i[0];
}

unsigned int f_2uint_int2(float float_number) {  // split the float and return first unsigned integer

  union f_2uint {
    float f;
    uint16_t i[2];
  };

  union f_2uint f_number;
  f_number.f = float_number;

  return f_number.i[1];
}

float f_2uint_float(unsigned int uint1, unsigned int uint2) {  // reconstruct the float from 2 unsigned integers

  union f_2uint {
    float f;
    uint16_t i[2];
  };

  union f_2uint f_number;
  f_number.i[0] = uint1;
  f_number.i[1] = uint2;

  return f_number.f;
}