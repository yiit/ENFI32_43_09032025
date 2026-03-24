#ifndef WEBSERVER_WEBSERVER_MANAGEMESAGES_H
#define WEBSERVER_WEBSERVER_MANAGEMESAGES_H

#include "../WebServer/common.h"


//#ifdef WEBSERVER_MANAGEMESAGES

# include "../Commands/ExecuteCommand.h"

// ********************************************************************************
// Web Interface Tools page
// ********************************************************************************
void handle_managemesages();
void handle_savemesages();
void handle_newmesages();


//#endif // ifdef WEBSERVER_MANAGEMESAGES

#endif // ifndef WEBSERVER_WEBSERVER_TOOLSPAGE_H
