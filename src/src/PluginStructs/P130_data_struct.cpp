#include "P130_data_struct.h"

#ifdef USES_P130

#include "../Globals/ExtraTaskSettings.h"
#include "../Helpers/Misc.h"
#include "../Commands/InternalCommands.h"
#include "../Commands/ExecuteCommand.h"

// Global değişkenler (Misc.h'de extern olarak tanımlı)
extern unsigned long hataTimer_l;
extern float webapibruttartim;
extern float webapibruttartim_son;
extern float sum_f_d_130[128];
extern float sum_f_130;
extern uint8_t i_130;

P130_Task::P130_Task(struct EventStruct *event) : PluginTaskData_base() {
  tartimString.reserve(128);
}

P130_Task::~P130_Task() {
  serialEnd();
}

void P130_Task::serialBegin(const ESPEasySerialPort port,
                             int16_t                 rxPin,
                             int16_t                 txPin,
                             unsigned long           baud,
                             uint8_t                 config) {
  serialEnd();
  
  easySerial = new (std::nothrow) ESPeasySerial(port, rxPin, txPin, false);
  
  if (easySerial != nullptr) {
    easySerial->begin(baud, config);
  }
}

void P130_Task::serialEnd() {
  if (easySerial != nullptr) {
    delete easySerial;
    easySerial = nullptr;
  }
}

void P130_Task::handleSerialIn(struct EventStruct *event) {
  if (easySerial == nullptr) {
    addLog(LOG_LEVEL_ERROR, F("P130: easySerial is NULL!"));
    return;
  }
  
  int available = easySerial->available();
  if (available > 0) {
    addLog(LOG_LEVEL_INFO, concat(F("P130: Serial available bytes: "), String(available)));
  }
  
  while (easySerial->available()) {
    char inChar = easySerial->read();
    
    addLog(LOG_LEVEL_DEBUG, concat(F("P130: Read byte: "), String((int)inChar)));
    
    if (inChar == 255) {
      easySerial->flush();
      break;
    }
    
    if (isprint(inChar)) {
      tartimString += (String)inChar;
    }
    
    if ((inChar == ExtraTaskSettings.TaskDeviceSonByte) && (tartimString.length() > 1)) {
      // Process complete data packet
      addLog(LOG_LEVEL_INFO, concat(F("P130: Received: "), tartimString));
      addLog(LOG_LEVEL_INFO, concat(F("P130: Calling formul_seri, mod="), String(ExtraTaskSettings.TaskDevicePluginConfigLong[2])));
      hataTimer_l = millis();
      
      if (Settings.Tersle) {
        tersle(event, tartimString);
      }
      
      isaret(event, ExtraTaskSettings.TaskDevicePluginConfigLong[1], tartimString);
      
      uint8_t mod = ExtraTaskSettings.TaskDevicePluginConfigLong[2];
      
      if ((mod == 3) || (mod == 4)) {
        formul_kontrol(event, tartimString, mod, true);
      } else {
        if (mod == 5) {
          // Kumanda modu - komut kontrol
          String art_komut = ExtraTaskSettings.TaskDeviceMesage[0];
          String top_komut = ExtraTaskSettings.TaskDeviceMesage[2];
          String tek_komut = ExtraTaskSettings.TaskDeviceMesage[1];
          
          if ((art_komut.length() > 0) && 
              (tartimString.substring(ExtraTaskSettings.TaskDeviceValueBas[0], 
                                     (art_komut.length() + ExtraTaskSettings.TaskDeviceValueBas[0])) == art_komut)) {
            ExecuteCommand_all({EventValueSource::Enum::VALUE_SOURCE_WEB_FRONTEND, "eyzart"});
          }
          if ((top_komut.length() > 0) && 
              (tartimString.substring(ExtraTaskSettings.TaskDeviceValueBas[0], 
                                     (top_komut.length() + ExtraTaskSettings.TaskDeviceValueBas[0])) == top_komut)) {
            ExecuteCommand_all({EventValueSource::Enum::VALUE_SOURCE_WEB_FRONTEND, "eyztek"});
          }
          if ((tek_komut.length() > 0) && 
              (tartimString.substring(ExtraTaskSettings.TaskDeviceValueBas[0], 
                                     (tek_komut.length() + ExtraTaskSettings.TaskDeviceValueBas[0])) == tek_komut)) {
            ExecuteCommand_all({EventValueSource::Enum::VALUE_SOURCE_WEB_FRONTEND, "eyztek"});
          }
        }
        
        formul_seri(event, tartimString, ExtraTaskSettings.TaskDevicePluginConfigLong[1]);
        
        if ((mod == 1) && ((webapibruttartim > 0.001) || (Settings.UseNegatifYaz))) {
          ExecuteCommand_all({EventValueSource::Enum::VALUE_SOURCE_WEB_FRONTEND, "eyztek"});
        }
      }
      
      // Buffer average calculation
      uint8_t sayac = ExtraTaskSettings.TaskDevicePluginConfigLong[4];
      
      if (i_130 >= sayac) {
        i_130--;
        sum_f_130 = sum_f_130 - sum_f_d_130[0];
        for (uint8_t i = 0; i < sayac; i++) {
          sum_f_d_130[i] = sum_f_d_130[i + 1];
        }
      } else {
        sum_f_d_130[i_130] = webapibruttartim;
        sum_f_130 = sum_f_130 + sum_f_d_130[i_130];
        webapibruttartim_son = sum_f_130 / float(i_130 + 1);
        i_130++;
      }
      
      tartimString = "";
      easySerial->flush();
    }
  }
}

#endif // ifdef USES_P130
