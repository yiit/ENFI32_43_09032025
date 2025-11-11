#ifndef WEBSERVER_WEBSERVER_ESPNOWMANAGERPAGE_H
#define WEBSERVER_WEBSERVER_ESPNOWMANAGERPAGE_H

#include "../WebServer/common.h"

#ifdef USES_ESPNOW_MANAGER

// Main ESP-NOW Manager page
void handle_espnow_manager();

// ESP-NOW Manager API endpoints  
void handle_espnow_scan();
void handle_espnow_pair();
void handle_espnow_send();
void handle_espnow_broadcast();
void handle_espnow_pair_device();
void handle_espnow_remove_device();
void handle_espnow_pair_discovered();
void handle_espnow_discovery();

// Initialize ESP-NOW Manager
bool initESPNowManager();

// Update function for main loop
void updateESPNowManager();

#endif // USES_ESPNOW_MANAGER

#endif // WEBSERVER_WEBSERVER_ESPNOWMANAGERPAGE_H