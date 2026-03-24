#include "../ESPEasyCore/Serial.h"


#include "../Commands/ExecuteCommand.h"

#include "../Globals/Cache.h"
#include "../Globals/ESPEasy_Console.h"
//#include "../Globals/Logging.h" //  For serialWriteBuffer
#include "../Globals/Settings.h"

#include "../Helpers/ESPEasy_time_calc.h"
#include "../Helpers/Memory.h"

#include "ESPEasy_common.h"
#include "ESPEasy-Globals.h"

//#ifdef ESP32
//#if FEATURE_ETHERNET
//#define RXD2 5
//#define TXD2 17
//#endif
/*#if (defined(HAS_BLUETOOTH) || defined(HAS_WIFI) || defined(HAS_BLE)) && !defined(PSRAM)
#if !defined(IND) && !defined(PLUS)
#define RXD2 17
#define TXD2 16
#elif defined(IND)
#define RXD2 12
#define TXD2 14
#elif defined(PSRAM)
#define RXD2 19
#define TXD2 23*/
#if defined(LVGL_ACTIVE)
#define RXD2 1
//#define TXD2 42
#define TXD2 8
#endif
//#endif
//#endif

/*#ifdef ESP8266
#define RXD2 15
#define TXD2 13
#endif*/

int butonbas = 0;
uint8_t SerialInByte;
int  SerialInByteCounter = 0;
char InputBuffer_Serial[INPUT_BUFFER_SIZE + 2];

uint8_t Serial2InByte;
int  Serial2InByteCounter = 0;
char InputBuffer_Serial2[INPUT_BUFFER_SIZE + 2];

void initSerial()
{
  ESPEasy_Console.init();
#ifdef ESP32
#if FEATURE_ETHERNET
  if (Settings.BaudBit1 == 1)
    Serial1.begin(Settings.BaudRate1, SERIAL_7N1, RXD2, TXD2);
  else
    Serial1.begin(Settings.BaudRate1, SERIAL_8N1, RXD2, TXD2);
#endif
#ifdef HAS_BLUETOOTH
  if (Settings.BaudBit1 == 1)
    Serial1.begin(Settings.BaudRate1, SERIAL_7N1, RXD2, TXD2);
  else
    Serial1.begin(Settings.BaudRate1, SERIAL_8N1, RXD2, TXD2);
#endif
#ifdef HAS_WIFI
  if (Settings.BaudBit1 == 1)
    Serial1.begin(Settings.BaudRate1, SERIAL_7N1, RXD2, TXD2);
  else if (Settings.BaudBit1 == 2)
    Serial1.begin(Settings.BaudRate1, SERIAL_8O1, RXD2, TXD2);
  else
    Serial1.begin(Settings.BaudRate1, SERIAL_8N1, RXD2, TXD2);
#endif
#endif
}

void serial2() {
  if (Serial2.available()) {
    String dummy;
    if (PluginCall(PLUGIN_SERIALBT_IN, 0, dummy)) {
      return;
    }
  }
  //if (!Settings.UseSerialBT) { return; }

  while (Serial2.available()) {
    Serial2InByte = Serial2.read();
    if ((escpos_mod) || (tspl_mod)) {
      if ((escpos_time > millis()) || (tspl_time > millis()))
        Serial1.write(Serial2InByte);
      else {
        tspl_mod = false;
        escpos_mod = false;
      }
    } else {
      if (Serial2InByte == 255)  // binary data...
      {
        Serial2.flush();
        return;
      }
      if (Serial2InByteCounter < INPUT_BUFFER_SIZE) {  // add char to string if it still fits
        InputBuffer_Serial2[Serial2InByteCounter++] = Serial2InByte;
      }
        if (Serial2InByte == '\n') {
        if (Serial2InByteCounter == 0) {  // empty command?
          break;
        }
        InputBuffer_Serial2[Serial2InByteCounter] = 0;  // serial data completed
        //SerialBT.println(InputBuffer_Serial);
        ExecuteCommand_all({EventValueSource::Enum::VALUE_SOURCE_SERIALBT, InputBuffer_Serial2});
        //ExecuteCommand_internal(EventValueSource::Enum::VALUE_SOURCE_SERIALBT, InputBuffer_SerialBT);
        Serial2InByteCounter = 0;
        InputBuffer_Serial2[0] = 0;  // serial data processed, clear buffer
      }
    }
  }
}

#ifdef ESP32
#if defined(HAS_WIFI) || FEATURE_ETHERNET
void serial1() {
  if (Serial1.available()) {
    String dummy;

    if (PluginCall(PLUGIN_SERIAL_IN, 0, dummy)) {
      return;
    }
  }

  if (!Settings.UseSerial1 || activeTaskUseSerial0()) { return; }

  while (Serial1.available()) {
    delay(0);
    SerialInByte = Serial1.read();

    if (SerialInByte == 255)  // binary data...
    {
      Serial1.flush();
      return;
    }

    if (isprint(SerialInByte)) {
      if (SerialInByteCounter < INPUT_BUFFER_SIZE) {  // add char to string if it still fits
        InputBuffer_Serial[SerialInByteCounter++] = SerialInByte;
      }
    }

    //if ((SerialInByte == '\r') || (SerialInByte == '\n')) {
    if (SerialInByte == '\n') {  
      if (SerialInByteCounter == 0) {  // empty command?
        break;
      }
      InputBuffer_Serial[SerialInByteCounter] = 0;  // serial data completed
      //Serial1.write('>');
      //serialPrintln(InputBuffer_Serial);
      ExecuteCommand_all({EventValueSource::Enum::VALUE_SOURCE_SERIAL, InputBuffer_Serial});
      SerialInByteCounter = 0;
      InputBuffer_Serial[0] = 0;  // serial data processed, clear buffer
    }
  }
}
#endif
#endif

void serial()
{
  ESPEasy_Console.loop();
}

bool process_serialWriteBuffer()
{
  return ESPEasy_Console.process_serialWriteBuffer();
}

// For now, only send it to the serial buffer and try to process it.
// Later we may want to wrap it into a log.
void serialPrint(const __FlashStringHelper *text) {
  ESPEasy_Console.addToSerialBuffer(text);
}

void serialPrint(const String& text) {
  ESPEasy_Console.addToSerialBuffer(text);
}

void serialPrintln(const __FlashStringHelper *text) {
  ESPEasy_Console.addToSerialBuffer(text);
  serialPrintln();
}

void serialPrintln(const String& text) {
  ESPEasy_Console.addToSerialBuffer(text);
  serialPrintln();
}

void serialPrintln() {
  ESPEasy_Console.addNewlineToSerialBuffer();
  ESPEasy_Console.process_serialWriteBuffer();
}

// Do not add helper functions for other types, since those types can only be
// explicit matched at a constructor, not a function declaration.

/*
   void serialPrint(char c) {
   serialPrint(String(c));
   }


   void serialPrint(unsigned long value) {
   serialPrint(String(value));
   }

   void serialPrint(long value) {
   serialPrint(String(value));
   }

   void serialPrintln(unsigned long value) {
   serialPrintln(String(value));
   }
 */
