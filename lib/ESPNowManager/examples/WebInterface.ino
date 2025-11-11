#include <WiFi.h>
#include <ESPNowManager.h>

// Choose web server type:
// Option 1: ESPAsyncWebServer (recommended for better performance)
#define USE_ASYNC_WEBSERVER 1

#if USE_ASYNC_WEBSERVER
  #define ESPNOW_USE_ASYNC_WEBSERVER 1
  #include <ESPAsyncWebServer.h>
  #include <ESPNowWebEndpoints.h>
  AsyncWebServer server(80);
#else
  #define ESPNOW_USE_ASYNC_WEBSERVER 0
  #include <WebServer.h>
  #include <ESPNowWebEndpoints.h>
  WebServer server(80);
#endif

// ESP-NOW manager and web endpoints
ESPNowManager espnowManager;
ESPNowWebEndpoints webEndpoints(&espnowManager, &server);

void setup() {
  Serial.begin(115200);
  
  // Initialize WiFi
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("ESP32-ESPNow", "12345678");
  
  // Set ESP-NOW callbacks
  espnowManager.setDataCallback([](String data, String type) {
    Serial.println("Received: " + data + " Type: " + type);
  });
  
  espnowManager.setLogCallback([](String message) {
    Serial.println("[ESPNow] " + message);
  });
  
  // Initialize ESP-NOW
  if (espnowManager.init()) {
    Serial.println("ESP-NOW initialized successfully");
  } else {
    Serial.println("ESP-NOW initialization failed");
  }
  
  // Setup web endpoints (automatically detects server type)
  webEndpoints.setupEndpoints();
  
  // Add root handler
#if USE_ASYNC_WEBSERVER
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->redirect("/espnow");
  });
#else
  server.on("/", HTTP_GET, []() {
    server.sendHeader("Location", "/espnow");
    server.send(302, "text/plain", "");
  });
#endif
  
  server.begin();
  Serial.println("Web server started");
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());
  Serial.println("Open browser and go to http://" + WiFi.softAPIP().toString() + "/espnow");
}

void loop() {
#if !USE_ASYNC_WEBSERVER
  server.handleClient();
#endif
  espnowManager.handle();
  
  // Optional: Show periodic status
  static unsigned long lastStatus = 0;
  if (millis() - lastStatus > 30000) { // Every 30 seconds
    Serial.println("ESP-NOW Status: Paired devices: " + String(espnowManager.getPairedDeviceCount()));
    lastStatus = millis();
  }
}

// All web handling is now done by ESPNowWebEndpoints class
// No need for manual handlers - they are automatically set up