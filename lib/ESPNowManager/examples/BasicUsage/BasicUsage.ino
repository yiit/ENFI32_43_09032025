#include <ESPNowManager.h>
#include <ESPNowWebEndpoints.h>
#include <ESPAsyncWebServer.h>

// ESP-NOW Manager instance
ESPNowManager espnowManager;

// Web server instance (optional - for web API)
AsyncWebServer server(80);
ESPNowWebEndpoints webEndpoints(&espnowManager, &server);

// LED pin for status indication
#define LED_PIN 2
#define PAIR_BUTTON 0  // Boot button

void setup() {
    Serial.begin(115200);
    
    // Initialize LED and button
    pinMode(LED_PIN, OUTPUT);
    pinMode(PAIR_BUTTON, INPUT_PULLUP);
    
    // Initialize ESP-NOW Manager
    if (espnowManager.begin("MyESP32Device")) {
        Serial.println("ESP-NOW Manager initialized successfully");
        
        // Set up callbacks
        espnowManager.onMessage([](const EspNowMessage& msg) {
            Serial.println("Message received:");
            Serial.println("  Type: " + msg.type);
            Serial.println("  Message: " + msg.message);
            Serial.println("  Sender: " + msg.sender);
            
            // Blink LED on message receive
            digitalWrite(LED_PIN, HIGH);
            delay(100);
            digitalWrite(LED_PIN, LOW);
        });
        
        espnowManager.onPeerStatusChange([](const uint8_t* mac, bool active) {
            String macStr = espnowManager.macToString(mac);
            Serial.printf("Peer %s is now %s\n", macStr.c_str(), active ? "ACTIVE" : "INACTIVE");
        });
        
        espnowManager.onLog([](const String& message) {
            Serial.println("[ESPNow] " + message);
        });
        
        // Setup web endpoints (optional)
        webEndpoints.setupEndpoints();
        server.begin();
        Serial.println("Web server started");
        
    } else {
        Serial.println("Failed to initialize ESP-NOW Manager");
    }
}

void loop() {
    // Handle ESP-NOW Manager
    espnowManager.handle();
    
    // Check pair button
    static bool lastButtonState = HIGH;
    static unsigned long buttonPressTime = 0;
    
    bool currentButtonState = digitalRead(PAIR_BUTTON);
    
    if (lastButtonState == HIGH && currentButtonState == LOW) {
        // Button pressed
        buttonPressTime = millis();
    } else if (lastButtonState == LOW && currentButtonState == HIGH) {
        // Button released
        unsigned long pressDuration = millis() - buttonPressTime;
        
        if (pressDuration > 100 && pressDuration < 3000) {
            // Short press: Start normal pairing
            Serial.println("Starting pairing mode...");
            espnowManager.startPairing();
        } else if (pressDuration >= 3000) {
            // Long press: Start auto pairing
            Serial.println("Starting auto pairing...");
            espnowManager.startAutoPairing();
        }
    }
    
    lastButtonState = currentButtonState;
    
    // Example: Send periodic broadcast message
    static unsigned long lastBroadcast = 0;
    if (millis() - lastBroadcast > 30000) { // Every 30 seconds
        espnowManager.sendBroadcast("Hello from " + espnowManager.getMacAddress(), "HEARTBEAT");
        lastBroadcast = millis();
    }
    
    delay(10);
}

// Additional helper functions you can use:

void sendMessageToDevice(const String& macStr, const String& message) {
    uint8_t mac[6];
    // Simple MAC string parsing (assumes format "AA:BB:CC:DD:EE:FF")
    sscanf(macStr.c_str(), "%02X:%02X:%02X:%02X:%02X:%02X", 
           &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]);
    
    espnowManager.sendMessage(mac, message, "USER_MESSAGE");
}

void printDeviceInfo() {
    Serial.println("=== Device Information ===");
    Serial.println("MAC Address: " + espnowManager.getMacAddress());
    Serial.println("Paired Devices: " + String(espnowManager.getPairedDeviceCount()));
    Serial.println("Active Peers: " + String(espnowManager.getActivePeerCount()));
    Serial.println("Last RSSI: " + String(espnowManager.getLastRSSI()) + " dBm");
    
    espnowManager.printPairedDevices();
}

void clearAllPairings() {
    espnowManager.clearPairedDevices();
    Serial.println("All pairings cleared");
}