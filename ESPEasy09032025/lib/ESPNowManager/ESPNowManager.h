#ifndef ESPNOW_MANAGER_H
#define ESPNOW_MANAGER_H

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <Preferences.h>
#include <ArduinoJson.h>
#include <functional>

// Maksimum eşleştirilmiş cihaz sayısı (avoid conflicts with main.cpp)
#ifndef MAX_PAIRED_DEVICES
#define MAX_PAIRED_DEVICES 10
#endif
#ifndef MAX_DATA_ENTRIES 
#define MAX_DATA_ENTRIES 20
#endif

// ESP-NOW mesaj yapısı (ESPNowManager version)
typedef struct {
    String name;     // device name (same as SSID)
    String model;    // model name
    int rssi;        // signal strength (optional, -128 if unknown)
    String cmd;      // command
    String data;     // payload to display
    
    // Backward compatibility fields
    String message;  // For compatibility with old format
    String type;     // For compatibility with old format
    String sender;   // For compatibility with old format
    String command;  // For compatibility with old format
} ESPNowManagerMessage;

// Veri girdisi yapısı (ESPNowManager version)
typedef struct {
    String message;
    String type;
    unsigned long timestamp;
} ESPNowManagerDataEntry;

// Peer durumu yapısı (ESPNowManager version)
typedef struct {
    uint8_t mac[6];
    bool active;
} ESPNowManagerPeerStatus;

// Callback fonksiyon türleri
typedef std::function<void(const ESPNowManagerMessage&)> MessageCallback;
typedef std::function<void(const uint8_t*, bool)> PeerStatusCallback;
typedef std::function<void(const String&)> LogCallback;
typedef std::function<void(const uint8_t*, const uint8_t*, int)> RawDataCallback;
typedef std::function<void(const uint8_t*, esp_now_send_status_t)> SendStatusCallback;

class ESPNowManager {
private:
    // Eşleştirilmiş cihazlar
    uint8_t pairedMacList[MAX_PAIRED_DEVICES][6];
    int pairedCount;
    
    // Gelen veri için buffer
    String receivedDataBuffer;
    bool hasNewData;
    unsigned long lastDataTime;
    
    // Peer durumu listesi
    ESPNowManagerPeerStatus peerStatusList[MAX_PAIRED_DEVICES];
    int peerStatusCount;
    
    // Keşfedilen cihazlar (geçici)
    uint8_t discoveredMacList[MAX_PAIRED_DEVICES][6];
    int discoveredCount;
    
    // Veri buffer'ı
    ESPNowManagerDataEntry dataBuffer[MAX_DATA_ENTRIES];
    int dataIndex;
    
    // Preferences nesnesi
    Preferences preferences;
    
    // Callback fonksiyonları
    MessageCallback messageCallback;
    PeerStatusCallback peerStatusCallback;
    LogCallback logCallback;
    RawDataCallback rawDataCallback;
    SendStatusCallback sendStatusCallback;
    
    // Pairing durumu
    bool isPairing;
    unsigned long pairingStartTime;
    unsigned long lastDiscoveryTime;
    
    // Broadcast adresi
    uint8_t broadcastAddress[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    
    // ESP-NOW peer info
    esp_now_peer_info_t peerInfo;
    
    // Son alınan RSSI değeri
    int lastReceivedRSSI;
    
    // Private helper methods
    void log(const String& message);
    bool macExists(const uint8_t *mac_addr, uint8_t list[][6], int count);
    void macToString(const uint8_t *mac_addr, char *macStr);
    void stringToMac(const char *macStr, uint8_t *mac_addr);
    // legacy parseMessage removed; use parseEspNowMessage (compatible public API)
    void handlePairRequest(const uint8_t *mac_addr, const ESPNowManagerMessage &msg);
    void handlePairAccept(const uint8_t *mac_addr, const ESPNowManagerMessage &msg);
    void handleDiscoveryRequest(const uint8_t *mac_addr);
    
    // Static callback for ESP-NOW - Updated for ESP32-S3 API
    #if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
    static void onDataReceived(const esp_now_recv_info_t *esp_now_info, const uint8_t *data, int len);
    #else
    static void onDataReceived(const uint8_t *mac_addr, const uint8_t *data, int len);
    #endif
    static void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
    static ESPNowManager* instance;
    
    // External callback functions
    std::function<void(const String&, const String&)> displayCallback;
    std::function<void(const String&, const String&)> espnowDataCallback;
    
    // External variables (for main.cpp compatibility)
    unsigned long* externalHataTimer;
    bool* externalHataFlag;
    bool* externalIsPairedFlag;
    int* externalPairedCount;
    uint8_t (*externalPairedList)[6];
    String* externalLastFormattedText;

public:
    ESPNowManager();
    ~ESPNowManager();
    
    // Initialization
    bool begin(const String& deviceName = "ESP32_Device");
    void end();
    
    // Callback registration
    void onMessage(MessageCallback callback);
    void onPeerStatusChange(PeerStatusCallback callback);
    void onLog(LogCallback callback);
    void onRawData(RawDataCallback callback);
    void onSendStatus(SendStatusCallback callback);
    
    // Pairing management
    void startPairing(unsigned long timeoutMs = 30000);
    void startPairing();  // Overloaded for web interface
    void startAutoPairing();
    void stopPairing();
    bool isPairingActive();
    bool sendPairRequest(const uint8_t *mac_addr);  // Changed to bool return
    void sendPairAccept(const uint8_t *mac_addr);
    void sendPairReject(const uint8_t *mac_addr);
    
    // Device discovery
    void startDiscovery();
    void stopDiscovery();
    int getDiscoveredDeviceCount();
    bool getDiscoveredDevice(int index, uint8_t *mac_addr);
    void clearDiscoveredDevices();
    
    // Compatibility with main.cpp
    void StartPairing();  // Compatible with main.cpp version
    void StartAutoPairing();  // Compatible with main.cpp version
    void SendPairRequest(const uint8_t *mac_addr);  // Compatible with main.cpp version
    void PrintMacAddress(const uint8_t *mac);  // Compatible with main.cpp version
    void AddPeer(const uint8_t *mac_addr);  // Compatible with main.cpp version
    
    // Message parsing
    bool parseEspNowMessage(const char *payload, int len, ESPNowManagerMessage &msg);  // Compatible with main.cpp version
    
    // Callback type definitions
    typedef std::function<void(const String&, const String&)> DisplayCallback;
    typedef std::function<void(const String&, const String&)> EspnowDataCallback;
    
    // Callback functions - compatible with main.cpp
    void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);  // Compatible with main.cpp version
    
    // Callback registration for external handling (display updates, etc.)
    void setDisplayCallback(DisplayCallback callback);
    void setEspnowDataCallback(EspnowDataCallback callback);
    
    // External variables access
    void setExternalVariables(unsigned long* hataTimer, bool* hataFlag, bool* isPairedFlag, 
                             int* pairedCount, uint8_t pairedList[][6], String* lastFormattedText);
    
    // Peer management
    bool addPeer(const uint8_t *mac_addr);
    bool removePeer(const uint8_t *mac_addr);
    bool removePeer(const char *macStr);
    int getPairedDeviceCount();
    bool getPairedDevice(int index, uint8_t *mac_addr);
    bool isPaired(const uint8_t *mac_addr);
    void clearPairedDevices();
    
    // Message sending
    bool sendMessage(const uint8_t *mac_addr, const String& message, const String& type = "");
    bool sendBroadcast(const String& message, const String& type = "");
    
    // Web interface support
    String getMacListJson();
    bool parseMacAddress(const String& macStr, uint8_t mac[6]);
    bool removePairedMac(const String& macStr);
    bool sendCommand(const uint8_t *mac_addr, const String& command, const String& data = "");
    
    // New format message sending: NAME|MODEL|RSSI|CMD|DATA
    bool sendFormattedMessage(const uint8_t *mac_addr, const String& name, const String& model, int rssi, const String& cmd, const String& data);
    bool sendFormattedBroadcast(const String& name, const String& model, int rssi, const String& cmd, const String& data);
    
    // Data management
    void addData(const String& message, const String& type);
    int getDataCount();
    bool getData(int index, ESPNowManagerDataEntry &entry);
    void clearData();
    
    // Peer status management
    void updatePeerStatus(const uint8_t *mac_addr, bool active, bool silent = false);
    bool getPeerStatus(const uint8_t *mac_addr);
    int getActivePeerCount();
    
    // Utility functions
    String getMacAddress();
    String macToString(const uint8_t *mac_addr);
    void printPairedDevices();
    void printDiscoveredDevices();
    int getLastRSSI();
    // printMacAddress removed (duplicate). Use PrintMacAddress or macToStr/macToString
    String macToStr(const uint8_t *mac);
    
    // Additional pairing and device management
    void addToDiscoveredList(const uint8_t *mac_addr);
    void removeFromDiscoveredList(const uint8_t *mac_addr);
    void loadPairedDevices();
    void savePairedDevices();
    void loadPairedMac();  // Main.cpp compatible version
    bool savePairedMac(const uint8_t *newMac);  // Changed to bool return
    void removePairedMac(const char* macStr);
    
    // Messaging
    // Compatible version of SendData for main.cpp
    void SendData(const String& data, const String& model = "ESP32");  // Compatible with main.cpp version
    
    // Status management
    int getActiveDeviceCount();
    
    // Web API helpers (for web server integration)
    String getPairedDevicesJSON();
    String getDiscoveredDevicesJSON();
    String getPeerStatusJSON();
    String getDataJSON();
    
    // Configuration
    void setChannel(uint8_t channel);
    void setMaxPeers(int maxPeers);
    void setDataBufferSize(int size);
    
    // Loop function (call in main loop)
    void handle();
    
    // Received data functions
    bool hasReceivedData();
    String getReceivedData();
    void clearReceivedData();
    
    // Status functions
    bool isInitialized();
    void setRawDataCallback(RawDataCallback callback);
    
    // ESPEasy compatibility functions
    int getPeerCount();
    String getPeerListString();
    bool sendData(const uint8_t *mac_addr, const uint8_t *data, size_t len);
    bool sendBroadcast(const uint8_t *data, size_t len);
    bool parseMacAddress(const char *macStr, uint8_t mac[6]);
    
private:
    String deviceName;
    uint8_t channel;
    int maxPeers;
    int dataBufferSize;
    unsigned long lastPeerStatusUpdate;
    bool initialized;
};

#endif // ESPNOW_MANAGER_H