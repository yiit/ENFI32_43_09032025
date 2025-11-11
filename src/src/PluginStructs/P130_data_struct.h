#ifndef PLUGINSTRUCTS_P130_DATA_STRUCT_H
#define PLUGINSTRUCTS_P130_DATA_STRUCT_H

#include "../../_Plugin_Helper.h"

#ifdef USES_P130

#include <ESPeasySerial.h>

struct P130_Task : public PluginTaskData_base {
  P130_Task(struct EventStruct *event);
  ~P130_Task();

  void serialBegin(const ESPEasySerialPort port,
                   int16_t                 rxPin,
                   int16_t                 txPin,
                   unsigned long           baud,
                   uint8_t                 config);
  
  void serialEnd();
  
  void handleSerialIn(struct EventStruct *event);
  
  bool isInit() const {
    return easySerial != nullptr;
  }

  ESPeasySerial *easySerial = nullptr;
  String tartimString;
};

#endif // ifdef USES_P130
#endif // ifndef PLUGINSTRUCTS_P130_DATA_STRUCT_H
