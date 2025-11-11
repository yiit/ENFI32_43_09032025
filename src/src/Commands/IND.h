#ifndef COMMAND_IND_H
#define COMMAND_IND_H

#include "../../ESPEasy_common.h"

const __FlashStringHelper * Command_Ind_Kaydet(struct EventStruct *event, const char* Line);
const __FlashStringHelper * Command_Ind_Sifir_Kal(struct EventStruct *event, const char* Line);
String Command_Ind_Yuk_Kal(struct EventStruct *event, const char* Line);
String Command_Ind_Sifir(struct EventStruct *event, const char* Line);
String Command_Ind_Elle_Dara(struct EventStruct *event, const char* Line);
String Command_Ind_Dara_Ekle(struct EventStruct *event, const char* Line);
String Command_Ind_Dara_Sil(struct EventStruct *event, const char* Line);
String Command_Ind_Seri_Data(struct EventStruct *event, const char* Line);

#endif // COMMAND_IND_H
