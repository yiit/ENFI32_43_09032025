#ifndef ESPNOW_WEB_ENDPOINTS_H
#define ESPNOW_WEB_ENDPOINTS_H

#include "ESPNowManager.h"

// Parametric Web Server Support
// Define which web server to use:
// ESPNOW_USE_ASYNC_WEBSERVER = 1 for ESPAsyncWebServer
// ESPNOW_USE_ASYNC_WEBSERVER = 0 for standard WebServer
#ifndef ESPNOW_USE_ASYNC_WEBSERVER
  #define ESPNOW_USE_ASYNC_WEBSERVER 0
#endif

#if ESPNOW_USE_ASYNC_WEBSERVER
  #include <ESPAsyncWebServer.h>
  #define ESPNOW_WEB_SERVER AsyncWebServer
  #define ESPNOW_WEB_REQUEST AsyncWebServerRequest
#else
  #include <WebServer.h>
  #define ESPNOW_WEB_SERVER WebServer
  #define ESPNOW_WEB_REQUEST void
#endif

class ESPNowWebEndpoints {
private:
    ESPNowManager* espnowManager;
    ESPNOW_WEB_SERVER* server;
    
    // Helper functions for MAC address parsing
    bool parseMacAddress(const String& macStr, uint8_t mac[6]);
    String getRequestParam(const String& paramName, bool isPost = false);
    void sendJsonResponse(int code, const String& json);
    
public:
    ESPNowWebEndpoints(ESPNowManager* manager, ESPNOW_WEB_SERVER* webServer);
    
    // Setup all web endpoints
    void setupEndpoints();
    
    // Individual endpoint handlers
    void handleMacList();
    void handleAddMac();
    void handleDeleteMac();
    void handlePairRequest();
    void handleStartPairing();
    void handleStopPairing();
    void handleDiscoveredDevices();
    void handlePeerStatus();
    void handleSendMessage();
    void handleGetData();
    void handleClearData();
    void handleWebInterface();
    
#if ESPNOW_USE_ASYNC_WEBSERVER
    // AsyncWebServer specific handlers
    void handleMacListAsync(AsyncWebServerRequest *request);
    void handleAddMacAsync(AsyncWebServerRequest *request);
    void handleDeleteMacAsync(AsyncWebServerRequest *request);
    void handlePairRequestAsync(AsyncWebServerRequest *request);
    void handleStartPairingAsync(AsyncWebServerRequest *request);
    void handleStopPairingAsync(AsyncWebServerRequest *request);
    void handleDiscoveredDevicesAsync(AsyncWebServerRequest *request);
    void handlePeerStatusAsync(AsyncWebServerRequest *request);
    void handleSendMessageAsync(AsyncWebServerRequest *request);
    void handleGetDataAsync(AsyncWebServerRequest *request);
    void handleClearDataAsync(AsyncWebServerRequest *request);
    void handleWebInterfaceAsync(AsyncWebServerRequest *request);
#endif
};

#endif // ESPNOW_WEB_ENDPOINTS_H