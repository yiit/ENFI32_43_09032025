#include "ESPNowManager.h"

// Static instance pointer for callback
ESPNowManager* ESPNowManager::instance = nullptr;

ESPNowManager::ESPNowManager() {
    pairedCount = 0;
    peerStatusCount = 0;
    discoveredCount = 0;
    dataIndex = 0;
    isPairing = false;
    pairingStartTime = 0;
    lastDiscoveryTime = 0;
    lastReceivedRSSI = -50;
    channel = 0;
    maxPeers = MAX_PAIRED_DEVICES;
    dataBufferSize = MAX_DATA_ENTRIES;
    lastPeerStatusUpdate = 0;
    initialized = false;
    deviceName = "ESP32_Device";
    
    // Initialize received data buffer
    receivedDataBuffer = "";
    hasNewData = false;
    lastDataTime = 0;
    
    // Initialize callbacks
    messageCallback = nullptr;
    peerStatusCallback = nullptr;
    logCallback = nullptr;
    rawDataCallback = nullptr;
    sendStatusCallback = nullptr;
    displayCallback = nullptr;
    espnowDataCallback = nullptr;
    
    // Initialize external variable pointers
    externalHataTimer = nullptr;
    externalHataFlag = nullptr;
    externalIsPairedFlag = nullptr;
    externalPairedCount = nullptr;
    externalPairedList = nullptr;
    externalLastFormattedText = nullptr;
    
    // Set static instance for callback
    instance = this;
}

ESPNowManager::~ESPNowManager() {
    end();
}

bool ESPNowManager::begin(const String& deviceName) {
    if (initialized) {
        log("ESPNowManager already initialized");
        return true;
    }
    
    this->deviceName = deviceName;
    
    // Initialize WiFi in STA mode
    WiFi.mode(WIFI_AP_STA);
    
    // Initialize ESP-NOW
    if (esp_now_init() != ESP_OK) {
        log("ESP-NOW initialization failed");
        return false;
    }
    
    // Register callbacks
    if (esp_now_register_recv_cb(onDataReceived) != ESP_OK) {
        log("Failed to register ESP-NOW receive callback");
        return false;
    }
    
    if (esp_now_register_send_cb(onDataSent) != ESP_OK) {
        log("Failed to register ESP-NOW send callback");
        return false;
    }
    
    // Setup broadcast peer
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = channel;
    peerInfo.encrypt = false;
    
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        log("Failed to add broadcast peer");
        return false;
    }
    
    // Load paired devices from preferences
    loadPairedDevices();
    
    initialized = true;
    log("ESPNowManager initialized successfully");
    return true;
}

void ESPNowManager::end() {
    if (!initialized) return;
    
    esp_now_deinit();
    initialized = false;
    instance = nullptr;
    log("ESPNowManager deinitialized");
}

void ESPNowManager::onMessage(MessageCallback callback) {
    messageCallback = callback;
}

void ESPNowManager::onPeerStatusChange(PeerStatusCallback callback) {
    peerStatusCallback = callback;
}

void ESPNowManager::onLog(LogCallback callback) {
    logCallback = callback;
}

void ESPNowManager::onRawData(RawDataCallback callback) {
    rawDataCallback = callback;
}

void ESPNowManager::onSendStatus(SendStatusCallback callback) {
    sendStatusCallback = callback;
}

void ESPNowManager::startPairing(unsigned long timeoutMs) {
    if (!initialized || isPairing) return;
    
    isPairing = true;
    pairingStartTime = millis();
    discoveredCount = 0;
    
    log("Device scan started...");
    
    const char *scanMessage = "DEVICE_SCAN";
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)scanMessage, strlen(scanMessage));
    
    if (result == ESP_OK) {
        log("Device scan broadcast sent successfully");
    } else {
        log("Failed to send device scan broadcast");
        isPairing = false;
    }
}

void ESPNowManager::startAutoPairing() {
    if (!initialized) return;
    
    log("Auto pairing started");
    startPairing(30000);  // Use timeout version
    
    // Wait for discovery responses - OVERFLOW SAFE
    unsigned long startTime = millis();
    unsigned long currentTime;
    bool timeoutReached = false;
    int loopCount = 0; // Sonsuz döngü koruması
    
    while (!timeoutReached && loopCount < 500) { // 500 * 100ms = 50s maksimum
        currentTime = millis();
        
        // Overflow kontrol: eğer currentTime < startTime ise overflow olmuş
        if (currentTime >= startTime) {
            // Normal durum: overflow yok
            if (currentTime - startTime >= 5000) {
                timeoutReached = true;
            }
        } else {
            // Overflow durumu: maksimum 5 saniye daha bekle
            if (currentTime >= 5000) {
                timeoutReached = true;
            }
        }
        
        handle();
        yield(); // Stack overflow önlemi
        delay(100);
        loopCount++; // Sonsuz döngü koruması
    }
    
    // Auto-pair with first discovered device
    if (discoveredCount > 0) {
        uint8_t targetMac[6];
        memcpy(targetMac, discoveredMacList[0], 6);
        sendPairRequest(targetMac);
        log("Auto pair request sent to first discovered device");
    } else {
        log("No devices discovered for auto pairing");
    }
    
    stopPairing();
}

// Overloaded startPairing for web interface
void ESPNowManager::startPairing() {
    if (!initialized) return;
    
    const char *scanMessage = "DEVICE_SCAN";
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)scanMessage, strlen(scanMessage));
    
    if (result == ESP_OK) {
        log("📡 Cihaz tarama başlatıldı");
    } else {
        log("❌ Cihaz tarama başlatılamadı: " + String(result));
    }
}

void ESPNowManager::stopPairing() {
    isPairing = false;
    log("Pairing stopped");
}

bool ESPNowManager::isPairingActive() {
    if (!isPairing) return false;
    
    // Check timeout
    if (millis() - pairingStartTime > 30000) { // 30 second timeout
        stopPairing();
        return false;
    }
    
    return true;
}

bool ESPNowManager::sendPairRequest(const uint8_t *mac_addr) {
    if (!initialized) return false;
    
    // Add peer if not exists
    if (!esp_now_is_peer_exist(mac_addr)) {
        esp_now_peer_info_t tempPeerInfo = {};
        memcpy(tempPeerInfo.peer_addr, mac_addr, 6);
        tempPeerInfo.channel = 0;
        tempPeerInfo.encrypt = false;
        
        if (esp_now_add_peer(&tempPeerInfo) != ESP_OK) {
            log("Failed to add peer for pair request");
            return false;
        }
    }
    
    const char *pairMessage = "PAIR_REQUEST";
    esp_err_t result = esp_now_send(mac_addr, (uint8_t *)pairMessage, strlen(pairMessage));
    
    if (result == ESP_OK) {
        log("Pair request sent successfully");
        // Add to paired devices automatically
        savePairedMac(mac_addr);
        return true;
    } else {
        log("Failed to send pair request");
        return false;
    }
}

void ESPNowManager::sendPairAccept(const uint8_t *mac_addr) {
    if (!initialized) return;
    
    const char *acceptMessage = "PAIR_ACCEPT";
    esp_err_t result = esp_now_send(mac_addr, (uint8_t *)acceptMessage, strlen(acceptMessage));
    
    if (result == ESP_OK) {
        addPeer(mac_addr);
        log("Pair accept sent and peer added");
    } else {
        log("Failed to send pair accept");
    }
}

void ESPNowManager::sendPairReject(const uint8_t *mac_addr) {
    if (!initialized) return;
    
    const char *rejectMessage = "PAIR_REJECT";
    esp_err_t result = esp_now_send(mac_addr, (uint8_t *)rejectMessage, strlen(rejectMessage));
    
    if (result == ESP_OK) {
        log("Pair reject sent");
    } else {
        log("Failed to send pair reject");
    }
}

bool ESPNowManager::addPeer(const uint8_t *mac_addr) {
    if (!initialized || pairedCount >= maxPeers) return false;
    
    // Check if already paired
    if (isPaired(mac_addr)) {
        log("Device already paired");
        return true;
    }
    
    // Add to paired list
    memcpy(pairedMacList[pairedCount], mac_addr, 6);
    pairedCount++;
    
    // Add to ESP-NOW peer list if not exists
    if (!esp_now_is_peer_exist(mac_addr)) {
        esp_now_peer_info_t tempPeerInfo = {};
        memcpy(tempPeerInfo.peer_addr, mac_addr, 6);
        tempPeerInfo.channel = 0;
        tempPeerInfo.encrypt = false;
        esp_now_add_peer(&tempPeerInfo);
    }
    
    // Save to preferences
    savePairedDevices();
    
    // Update peer status
    updatePeerStatus(mac_addr, true);
    
    log("Peer added successfully");
    return true;
}

bool ESPNowManager::removePeer(const uint8_t *mac_addr) {
    if (!initialized) return false;
    
    int index = -1;
    for (int i = 0; i < pairedCount; i++) {
        if (memcmp(pairedMacList[i], mac_addr, 6) == 0) {
            index = i;
            break;
        }
    }
    
    if (index >= 0) {
        // Shift array elements
        for (int i = index; i < pairedCount - 1; i++) {
            memcpy(pairedMacList[i], pairedMacList[i + 1], 6);
        }
        pairedCount--;
        
        // Remove from ESP-NOW
        esp_now_del_peer(mac_addr);
        
        // Save to preferences
        savePairedDevices();
        
        log("Peer removed successfully");
        return true;
    }
    
    return false;
}

bool ESPNowManager::removePeer(const char *macStr) {
    uint8_t mac[6];
    stringToMac(macStr, mac);
    return removePeer(mac);
}

int ESPNowManager::getPairedDeviceCount() {
    return pairedCount;
}

bool ESPNowManager::getPairedDevice(int index, uint8_t *mac_addr) {
    if (index < 0 || index >= pairedCount) return false;
    memcpy(mac_addr, pairedMacList[index], 6);
    return true;
}

bool ESPNowManager::isPaired(const uint8_t *mac_addr) {
    return macExists(mac_addr, pairedMacList, pairedCount);
}

void ESPNowManager::clearPairedDevices() {
    pairedCount = 0;
    preferences.begin("espnow", false);
    preferences.remove("paired_mac");
    preferences.end();
    log("All paired devices cleared");
}

bool ESPNowManager::sendMessage(const uint8_t *mac_addr, const String& message, const String& type) {
    if (!initialized) return false;
    
    String payload = message;
    if (type.length() > 0) {
        payload = type + "|" + message + "|" + deviceName;
    }
    
    esp_err_t result = esp_now_send(mac_addr, (uint8_t *)payload.c_str(), payload.length());
    return (result == ESP_OK);
}

bool ESPNowManager::sendBroadcast(const String& message, const String& type) {
    return sendMessage(broadcastAddress, message, type);
}

bool ESPNowManager::sendCommand(const uint8_t *mac_addr, const String& command, const String& data) {
    if (!initialized) return false;
    
    String payload = "CMD|" + command + "|" + data + "|" + deviceName;
    esp_err_t result = esp_now_send(mac_addr, (uint8_t *)payload.c_str(), payload.length());
    return (result == ESP_OK);
}

bool ESPNowManager::sendFormattedMessage(const uint8_t *mac_addr, const String& name, const String& model, int rssi, const String& cmd, const String& data) {
    if (!initialized) return false;
    
    // Format: NAME|MODEL|RSSI|CMD|DATA - MEMORY OPTIMIZED
    char payloadBuffer[256];
    int written = snprintf(payloadBuffer, sizeof(payloadBuffer), 
                          "%s|%s|%d|%s|%s", 
                          name.c_str(), model.c_str(), rssi, cmd.c_str(), data.c_str());
    
    if (written >= (int)sizeof(payloadBuffer)) {
        log("⚠️ sendFormattedMessage payload çok büyük, kesiliyor");
        payloadBuffer[sizeof(payloadBuffer)-1] = '\0';
        written = sizeof(payloadBuffer) - 1;
    }
    
    esp_err_t result = esp_now_send(mac_addr, (uint8_t *)payloadBuffer, written);
    return (result == ESP_OK);
}

bool ESPNowManager::sendFormattedBroadcast(const String& name, const String& model, int rssi, const String& cmd, const String& data) {
    return sendFormattedMessage(broadcastAddress, name, model, rssi, cmd, data);
}

void ESPNowManager::addData(const String& message, const String& type) {
    dataBuffer[dataIndex].message = message;
    dataBuffer[dataIndex].type = type;
    dataBuffer[dataIndex].timestamp = millis();
    dataIndex = (dataIndex + 1) % dataBufferSize;
}

int ESPNowManager::getDataCount() {
    // Count non-empty entries
    int count = 0;
    for (int i = 0; i < dataBufferSize; i++) {
        if (dataBuffer[i].message.length() > 0) count++;
    }
    return count;
}

bool ESPNowManager::getData(int index, ESPNowManagerDataEntry &entry) {
    if (index < 0 || index >= dataBufferSize) return false;
    if (dataBuffer[index].message.length() == 0) return false;
    
    entry = dataBuffer[index];
    return true;
}

void ESPNowManager::clearData() {
    for (int i = 0; i < dataBufferSize; i++) {
        dataBuffer[i].message = "";
        dataBuffer[i].type = "";
        dataBuffer[i].timestamp = 0;
    }
    dataIndex = 0;
}

void ESPNowManager::updatePeerStatus(const uint8_t *mac_addr, bool active, bool silent) {
    char macStr[18];
    sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", 
            mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    
    for (int i = 0; i < peerStatusCount; i++) {
        if (memcmp(peerStatusList[i].mac, mac_addr, 6) == 0) {
            if (peerStatusList[i].active != active && !silent) {
                log("📊 Peer status değişti: " + String(macStr) + " -> " + (active ? "ACTIVE" : "INACTIVE"));
            }
            peerStatusList[i].active = active;
            return;
        }
    }

    // Add new peer status
    if (peerStatusCount < MAX_PAIRED_DEVICES) {
        memcpy(peerStatusList[peerStatusCount].mac, mac_addr, 6);
        peerStatusList[peerStatusCount].active = active;
        peerStatusCount++;
        if (!silent) {
            log("📊 Yeni peer eklendi: " + String(macStr) + " -> " + (active ? "ACTIVE" : "INACTIVE"));
        }
    }
}

bool ESPNowManager::getPeerStatus(const uint8_t *mac_addr) {
    for (int i = 0; i < peerStatusCount; i++) {
        if (memcmp(peerStatusList[i].mac, mac_addr, 6) == 0) {
            return peerStatusList[i].active;
        }
    }
    return false;
}

int ESPNowManager::getActivePeerCount() {
    int count = 0;
    for (int i = 0; i < peerStatusCount; i++) {
        if (peerStatusList[i].active) count++;
    }
    return count;
}

String ESPNowManager::getMacAddress() {
    return WiFi.macAddress();
}

String ESPNowManager::macToString(const uint8_t *mac_addr) {
    char buf[18];
    snprintf(buf, sizeof(buf), "%02X:%02X:%02X:%02X:%02X:%02X",
             mac_addr[0], mac_addr[1], mac_addr[2], 
             mac_addr[3], mac_addr[4], mac_addr[5]);
    return String(buf);
}

void ESPNowManager::printPairedDevices() {
    log("=== Paired Devices ===");
    for (int i = 0; i < pairedCount; i++) {
        String macStr = macToString(pairedMacList[i]);
        log("Device " + String(i) + ": " + macStr);
    }
}

void ESPNowManager::printDiscoveredDevices() {
    log("=== Discovered Devices ===");
    for (int i = 0; i < discoveredCount; i++) {
        String macStr = macToString(discoveredMacList[i]);
        log("Device " + String(i) + ": " + macStr);
    }
}

int ESPNowManager::getLastRSSI() {
    return lastReceivedRSSI;
}

String ESPNowManager::getPairedDevicesJSON() {
    DynamicJsonDocument doc(1024);
    JsonArray devices = doc.createNestedArray("devices");
    
    for (int i = 0; i < pairedCount; i++) {
        JsonObject device = devices.createNestedObject();
        device["mac"] = macToString(pairedMacList[i]);
        device["active"] = getPeerStatus(pairedMacList[i]);
    }
    
    String jsonString;
    serializeJson(doc, jsonString);
    return jsonString;
}

String ESPNowManager::getDiscoveredDevicesJSON() {
    DynamicJsonDocument doc(512);
    JsonArray devices = doc.createNestedArray("devices");
    
    for (int i = 0; i < discoveredCount; i++) {
        devices.add(macToString(discoveredMacList[i]));
    }
    
    String jsonString;
    serializeJson(doc, jsonString);
    return jsonString;
}

String ESPNowManager::getPeerStatusJSON() {
    DynamicJsonDocument doc(1024);
    JsonArray peers = doc.createNestedArray("peers");
    
    for (int i = 0; i < peerStatusCount; i++) {
        JsonObject peer = peers.createNestedObject();
        peer["mac"] = macToString(peerStatusList[i].mac);
        peer["active"] = peerStatusList[i].active;
    }
    
    String jsonString;
    serializeJson(doc, jsonString);
    return jsonString;
}

String ESPNowManager::getDataJSON() {
    DynamicJsonDocument doc(2048);
    JsonArray dataArray = doc.createNestedArray("data");
    
    for (int i = 0; i < dataBufferSize; i++) {
        if (dataBuffer[i].message.length() > 0) {
            JsonObject dataObj = dataArray.createNestedObject();
            dataObj["message"] = dataBuffer[i].message;
            dataObj["type"] = dataBuffer[i].type;
            dataObj["timestamp"] = dataBuffer[i].timestamp;
        }
    }
    
    String jsonString;
    serializeJson(doc, jsonString);
    return jsonString;
}

void ESPNowManager::setChannel(uint8_t channel) {
    this->channel = channel;
}

void ESPNowManager::setMaxPeers(int maxPeers) {
    if (maxPeers > 0 && maxPeers <= MAX_PAIRED_DEVICES) {
        this->maxPeers = maxPeers;
    }
}

void ESPNowManager::setDataBufferSize(int size) {
    if (size > 0 && size <= MAX_DATA_ENTRIES) {
        this->dataBufferSize = size;
    }
}

void ESPNowManager::handle() {
    if (!initialized) return;
    
    unsigned long currentTime = millis();
    
    // Handle pairing timeout - OVERFLOW SAFE
    if (isPairing) {
        // Overflow-safe time comparison
        bool timeoutReached = false;
        if (currentTime >= pairingStartTime) {
            // Normal case
            timeoutReached = (currentTime - pairingStartTime > 30000);
        } else {
            // Overflow case: if current time is small, we probably overflowed
            timeoutReached = (currentTime > 30000); // Wait maximum 30s after overflow
        }
        
        if (timeoutReached) {
            stopPairing();
        }
    }
    
    // Periodic peer status update (every 30 seconds) - OVERFLOW SAFE
    bool updateNeeded = false;
    if (currentTime >= lastPeerStatusUpdate) {
        // Normal case
        updateNeeded = (currentTime - lastPeerStatusUpdate > 30000);
    } else {
        // Overflow case
        updateNeeded = (currentTime > 30000);
    }
    
    if (updateNeeded) {
        // Send ping to all paired devices to check their status - BOUNDS CHECK
        for (int i = 0; i < pairedCount && i < MAX_PAIRED_DEVICES; i++) {
            sendMessage(pairedMacList[i], "PING", "STATUS");
            yield(); // Stack overflow önlemi
        }
        lastPeerStatusUpdate = currentTime;
    }
}

// Private helper methods
void ESPNowManager::log(const String& message) {
    if (logCallback) {
        logCallback(message);
    } else {
        Serial.println("[ESPNowManager] " + message);
    }
}

bool ESPNowManager::macExists(const uint8_t *mac_addr, uint8_t list[][6], int count) {
    // BOUNDS CHECK: Sonsuz döngü koruması
    if (count > MAX_PAIRED_DEVICES) count = MAX_PAIRED_DEVICES;
    if (count < 0) return false;
    
    for (int i = 0; i < count; i++) {
        if (memcmp(list[i], mac_addr, 6) == 0) {
            return true;
        }
    }
    return false;
}

void ESPNowManager::macToString(const uint8_t *mac_addr, char *macStr) {
    sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X",
            mac_addr[0], mac_addr[1], mac_addr[2],
            mac_addr[3], mac_addr[4], mac_addr[5]);
}

void ESPNowManager::stringToMac(const char *macStr, uint8_t *mac_addr) {
    String macString = String(macStr);
    String macParts[6];
    int partIndex = 0;
    int startPos = 0;
    
    // Parse MAC address parts separated by ':'
    for (int i = 0; i <= (int)macString.length() && partIndex < 6; i++) {
        if (i == (int)macString.length() || macString.charAt(i) == ':') {
            if (i > startPos) {
                macParts[partIndex] = macString.substring(startPos, i);
                partIndex++;
            }
            startPos = i + 1;
        }
    }
    
    // Convert hex strings to bytes
    for (int i = 0; i < 6 && i < partIndex; i++) {
        mac_addr[i] = (uint8_t)strtol(macParts[i].c_str(), NULL, 16);
    }
}

// parseMessage legacy implementation removed - use parseEspNowMessage which is compatible with main.cpp

void ESPNowManager::handlePairRequest(const uint8_t *mac_addr, const ESPNowManagerMessage &msg) {
    log("Pair request received from: " + macToString(mac_addr));
    
    // Auto-accept pairing during pairing mode
    if (isPairing) {
        sendPairAccept(mac_addr);
        log("Auto-accepted pair request");
    }
}

void ESPNowManager::handlePairAccept(const uint8_t *mac_addr, const ESPNowManagerMessage &msg) {
    log("Pair accept received from: " + macToString(mac_addr));
    addPeer(mac_addr);
}

void ESPNowManager::handleDiscoveryRequest(const uint8_t *mac_addr) {
    // Respond to device scan
    String response = "DEVICE_RESPONSE|" + deviceName + "|" + getMacAddress();
    esp_now_send(mac_addr, (uint8_t *)response.c_str(), response.length());
    log("Discovery response sent");
}

void ESPNowManager::startDiscovery() {
    discoveredCount = 0;
    const char *scanMessage = "DEVICE_SCAN";
    esp_now_send(broadcastAddress, (uint8_t *)scanMessage, strlen(scanMessage));
    log("Device discovery started");
}

void ESPNowManager::stopDiscovery() {
    log("Device discovery stopped");
}

int ESPNowManager::getDiscoveredDeviceCount() {
    return discoveredCount;
}

bool ESPNowManager::getDiscoveredDevice(int index, uint8_t *mac_addr) {
    if (index < 0 || index >= discoveredCount) return false;
    memcpy(mac_addr, discoveredMacList[index], 6);
    return true;
}

void ESPNowManager::clearDiscoveredDevices() {
    discoveredCount = 0;
    log("Discovered devices cleared");
}

// Compatible version of StartPairing for main.cpp
void ESPNowManager::StartPairing() {
    const char *scanMessage = "DEVICE_SCAN";
    
    // Broadcast adresine tarama mesajı gönder
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)scanMessage, strlen(scanMessage));
    if (result == ESP_OK) {
        log("📡 Cihaz tarama başlatıldı.");
        // Discovered listesini temizle
        discoveredCount = 0;
    } else {
        log("⚠️ Cihaz tarama başlatılamadı.");
    }
}

// Compatible version of StartAutoPairing for main.cpp
void ESPNowManager::StartAutoPairing() {
    log("🤖 Otomatik eşleştirme başlatıldı");
    
    // Önce keşfedilen listeyi temizle
    discoveredCount = 0;
    
    // Cihaz taraması başlat
    const char *scanMessage = "DEVICE_SCAN";
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)scanMessage, strlen(scanMessage));
    
    if (result == ESP_OK) {
        log("📡 Otomatik tarama başlatıldı");
        
        // 3 saniye bekle (cihazların yanıt vermesi için)
        delay(3000);
        
        // İlk bulunan cihazla eşleştirme yap
        if (discoveredCount > 0) {
            log("✅ " + String(discoveredCount) + " cihaz bulundu, ilki ile eşleştiriliyor");
            
            // İlk cihazın MAC adresini al
            uint8_t targetMAC[6];
            memcpy(targetMAC, discoveredMacList[0], 6);
            
            // Eşleştirme isteği gönder
            SendPairRequest(targetMAC);
            
            // MAC adresini kaydet
            savePairedMac(targetMAC);
            
        } else {
            log("❌ Hiç cihaz bulunamadı");
        }
    } else {
        log("❌ Otomatik tarama başlatılamadı");
    }
}

// Compatible version of SendPairRequest for main.cpp
void ESPNowManager::SendPairRequest(const uint8_t *mac_addr) {
    log("🎯 PAIR_REQUEST gönderilecek MAC: " + macToString(mac_addr));
    
    // Hedef cihazın peer olarak ekli olup olmadığını kontrol et
    if (!esp_now_is_peer_exist(mac_addr)) {
        log("⚠️ Hedef cihaz peer listesinde yok, ekleniyor...");
        esp_now_peer_info_t peerInfo = {};
        memcpy(peerInfo.peer_addr, mac_addr, 6);
        peerInfo.channel = 0;
        peerInfo.encrypt = false;
        
        esp_err_t addResult = esp_now_add_peer(&peerInfo);
        if (addResult == ESP_OK) {
            log("✅ Hedef cihaz peer olarak eklendi");
        } else {
            log("❌ Peer ekleme hatası: " + String(addResult));
            return;
        }
    } else {
        log("ℹ️ Hedef cihaz zaten peer listesinde");
    }
    
    const char *pairMessage = "PAIR_REQUEST";
    esp_err_t result = esp_now_send(mac_addr, (uint8_t *)pairMessage, strlen(pairMessage));
    
    // Watchdog beslemesi - reset önlemi
    yield();
    delay(10);
    
    if (result == ESP_OK) {
        log("✅ PAIR_REQUEST başarıyla gönderildi");
    } else {
        log("❌ PAIR_REQUEST gönderilemedi, hata kodu: " + String(result));
    }
}

// Compatible version of PrintMacAddress for main.cpp
void ESPNowManager::PrintMacAddress(const uint8_t *mac) {
    String macStr = "MAC Adresi: ";
    for (int i = 0; i < 6; i++) {
        if (mac[i] < 0x10) macStr += "0";
        macStr += String(mac[i], HEX);
        if (i < 5) macStr += ":";
    }
    log(macStr);
}

// Compatible version of AddPeer for main.cpp
void ESPNowManager::AddPeer(const uint8_t *mac_addr) {
    if (esp_now_is_peer_exist(mac_addr)) {
        log("ℹ️ Peer zaten kayıtlı.");
        return;
    }

    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, mac_addr, 6);
    peerInfo.channel = 0;         // aynı kanal
    peerInfo.encrypt = false;     // şifreleme kullanmıyoruz

    esp_err_t result = esp_now_add_peer(&peerInfo);
    if (result == ESP_OK) {
        log("✅ Peer eklendi: " + macToString(mac_addr));
    } else {
        log("❌ Peer eklenemedi! Hata kodu: " + String(result));
    }
}

// Compatible version of parseEspNowMessage for main.cpp
bool ESPNowManager::parseEspNowMessage(const char *payload, int len, ESPNowManagerMessage &msg) {
    if (payload == nullptr || len <= 0) return false;
    String s = String(payload).substring(0, len);
    
    // Yeni format kontrolü: NAME|MODEL|RSSI|CMD|DATA (5 parça olmalı)
    // Find first four separators. DATA may contain pipes, so extract first 4 splits only.
    int p1 = s.indexOf('|');
    if (p1 < 0) return false; // Hiç | yoksa false döndür
    
    int p2 = s.indexOf('|', p1 + 1);
    int p3 = s.indexOf('|', p2 + 1);
    int p4 = s.indexOf('|', p3 + 1);
    
    // Eğer 4 tane | varsa yeni format
    if (p2 > 0 && p3 > 0 && p4 > 0) {
        msg.name = s.substring(0, p1);
        msg.model = s.substring(p1 + 1, p2);
        String rssiStr = s.substring(p2 + 1, p3);
        rssiStr.trim();
        if (rssiStr.length() == 0) msg.rssi = -128;
        else msg.rssi = rssiStr.toInt();
        msg.cmd = s.substring(p3 + 1, p4);
        msg.data = s.substring(p4 + 1);
        return true;
    }
    
    return false; // Yeni format değilse false döndür
}

// Set external variables for main.cpp compatibility
void ESPNowManager::setExternalVariables(unsigned long* hataTimer, bool* hataFlag, bool* isPairedFlag,
                                        int* pairedCount, uint8_t pairedList[][6], String* lastFormattedText) {
    externalHataTimer = hataTimer;
    externalHataFlag = hataFlag;
    externalIsPairedFlag = isPairedFlag;
    externalPairedCount = pairedCount;
    externalPairedList = pairedList;
    externalLastFormattedText = lastFormattedText;
}

// Set display callback
void ESPNowManager::setDisplayCallback(DisplayCallback callback) {
    displayCallback = callback;
}

// Set espnow data callback
void ESPNowManager::setEspnowDataCallback(EspnowDataCallback callback) {
    espnowDataCallback = callback;
}

// OnDataRecv removed - now using only onDataReceived static callback to prevent duplicate processing

// Compatible version of OnDataSent for main.cpp
void ESPNowManager::OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    updatePeerStatus(mac_addr, status == ESP_NOW_SEND_SUCCESS);
}

void ESPNowManager::loadPairedDevices() {
    preferences.begin("espnow", true);
    int macDataLength = preferences.getBytesLength("paired_mac");
    pairedCount = macDataLength / 6;
    
    if (pairedCount > maxPeers) pairedCount = maxPeers;
    
    if (pairedCount > 0) {
        preferences.getBytes("paired_mac", pairedMacList, macDataLength);
        
        // Add peers to ESP-NOW
        for (int i = 0; i < pairedCount; i++) {
            esp_now_peer_info_t tempPeerInfo = {};
            memcpy(tempPeerInfo.peer_addr, pairedMacList[i], 6);
            tempPeerInfo.channel = 0;
            tempPeerInfo.encrypt = false;
            esp_now_add_peer(&tempPeerInfo);
            updatePeerStatus(pairedMacList[i], false);
        }
        
        log("Loaded " + String(pairedCount) + " paired devices");
    }
    
    preferences.end();
}

void ESPNowManager::savePairedDevices() {
    preferences.begin("espnow", false);
    
    if (pairedCount > 0) {
        preferences.putBytes("paired_mac", pairedMacList, pairedCount * 6);
    } else {
        preferences.remove("paired_mac");
    }
    
    preferences.end();
    log("Paired devices saved to preferences");
}

// Main.cpp compatible version
void ESPNowManager::loadPairedMac() {
    preferences.begin("espnow", true);
    int macDataLength = preferences.getBytesLength("paired_mac");
    pairedCount = macDataLength / 6;
    if (pairedCount > maxPeers) pairedCount = maxPeers;
    
    if (pairedCount > 0) {
        preferences.getBytes("paired_mac", pairedMacList, macDataLength);
        
        // Add peers to ESP-NOW and update status
        for (int i = 0; i < pairedCount; i++) {
            esp_now_peer_info_t tempPeerInfo = {};
            memcpy(tempPeerInfo.peer_addr, pairedMacList[i], 6);
            tempPeerInfo.channel = 0;
            tempPeerInfo.encrypt = false;
            esp_now_add_peer(&tempPeerInfo);
            updatePeerStatus(pairedMacList[i], false);
        }
        
        log("LoadPairedMac: Loaded " + String(pairedCount) + " paired devices");
    }
    
    preferences.end();
}

// Static callback implementation - Updated for ESP32-S3 API
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
void ESPNowManager::onDataReceived(const esp_now_recv_info_t *esp_now_info, const uint8_t *data, int len) {
    if (!instance) return;
    
    // Extract MAC address from recv_info
    const uint8_t *mac_addr = esp_now_info->src_addr;
    
    // Update external hata_timer if available (main.cpp compatibility)
    if (instance->externalHataTimer) {
        *(instance->externalHataTimer) = millis();
    }
    
    // BUFFER OVERFLOW KORUMASI - maksimum 250 byte
    const int MAX_BUFFER_SIZE = 250;
    if (len > MAX_BUFFER_SIZE) {
        instance->log("⚠️ Veri çok büyük, kesiliyor: " + String(len) + " -> " + String(MAX_BUFFER_SIZE));
        len = MAX_BUFFER_SIZE;
    }
#else
void ESPNowManager::onDataReceived(const uint8_t *mac_addr, const uint8_t *data, int len) {
    if (!instance) return;
    
    // Update external hata_timer if available (main.cpp compatibility)
    if (instance->externalHataTimer) {
        *(instance->externalHataTimer) = millis();
    }
    
    // BUFFER OVERFLOW KORUMASI - maksimum 250 byte
    const int MAX_BUFFER_SIZE = 250;
    if (len > MAX_BUFFER_SIZE) {
        instance->log("⚠️ Veri çok büyük, kesiliyor: " + String(len) + " -> " + String(MAX_BUFFER_SIZE));
        len = MAX_BUFFER_SIZE;
    }
#endif
    
    char receivedData[MAX_BUFFER_SIZE + 1];
    memcpy(receivedData, data, len);
    receivedData[len] = '\0';
    
    // Log received data if callback is available - Filter out status/ping messages
    if (instance->espnowDataCallback) {
        char macStr[18];
        sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", 
                mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
        
        // STATUS mesajlarını loglamayalım (30 saniyede bir gönderilen ping mesajları)
        bool isStatusMessage = (strncmp(receivedData, "STATUS|", 7) == 0);
        bool isPingMessage = (strstr(receivedData, "|PING|") != nullptr);
        
        if (!isStatusMessage && !isPingMessage) {
            instance->espnowDataCallback("From " + String(macStr) + ": " + String(receivedData), "in");
        }
    }

    if (strcmp(receivedData, "DEVICE_SCAN") == 0) {
        // Handle device scan request
        Preferences prefs;
        prefs.begin("wifi", true);
        String deviceName = prefs.getString("ssid", "ESPNowDevice");
        prefs.end();
        
        String response = "SCAN_RESPONSE|NODE:" + deviceName + "|MODEL:ESP32|VER:v1.0.0";
        
        uint8_t broadcast[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        esp_err_t result = esp_now_send(broadcast, (uint8_t *)response.c_str(), response.length());
        
        if (result == ESP_OK) {
            instance->log("📤 Tarama yanıtı broadcast gönderildi: " + deviceName);
        } else {
            instance->log("❌ Tarama yanıtı gönderilemedi, hata: " + String(result));
        }
    }
    else if (strcmp(receivedData, "PAIR_REQUEST") == 0) {
        // Handle pair request
        Preferences prefs;
        prefs.begin("wifi", true);
        String deviceName = prefs.getString("ssid", "ESPNowDevice");
        prefs.end();
        
        String response = "PAIR_RESPONSE|NODE:" + deviceName + "|MODEL:ESP32|VER:v1.0.0";
        esp_now_send(mac_addr, (uint8_t *)response.c_str(), response.length());
        
        if (instance->externalIsPairedFlag) {
            *(instance->externalIsPairedFlag) = true;
        }
        
        instance->savePairedMac(mac_addr);
        instance->AddPeer(mac_addr);
        
        if (instance->displayCallback) {
            instance->displayCallback("BAGLANDI!", "");
        }
        
        // Reset formatted text
        if (instance->externalLastFormattedText) {
            *(instance->externalLastFormattedText) = "";
        }
        return;
    }
    else if (strcmp(receivedData, "PAIR_DEL") == 0) {
        // Handle pair delete request
        String macStr = instance->macToString(mac_addr);
        instance->removePairedMac(macStr.c_str());
    }
    else if (strncmp(receivedData, "SCAN_RESPONSE", 13) == 0) {
        instance->log("📡 Tarama yanıtı alındı: " + String(receivedData));
        instance->addToDiscoveredList(mac_addr);
        return;
    }
    else if (strncmp(receivedData, "PAIR_RESPONSE", 13) == 0) {
        instance->log("🤝 Eşleştirme yanıtı alındı: " + String(receivedData));
        
        if (instance->externalIsPairedFlag) {
            *(instance->externalIsPairedFlag) = true;
        }
        
        instance->savePairedMac(mac_addr);
        instance->PrintMacAddress(mac_addr);
        
        if (instance->displayCallback) {
            instance->displayCallback("BAGLANDI!", "");
        }
        
        // Reset formatted text
        if (instance->externalLastFormattedText) {
            *(instance->externalLastFormattedText) = "";
        }
        return;
    }
    else if (strncmp(receivedData, "STATUS|", 7) == 0) {
        // Handle status/ping messages - sadece bağlantı durumunu güncelle, log gösterme
        bool isPairedDevice = false;
        for (int i = 0; i < instance->pairedCount; i++) {
            if (memcmp(instance->pairedMacList[i], mac_addr, 6) == 0) {
                isPairedDevice = true;
                break;
            }
        }
        
        if (isPairedDevice) {
            // Peer status güncelle ama log mesajı gösterme
            instance->updatePeerStatus(mac_addr, true, true); // silent=true
        }
        return; // STATUS mesajları için başka işlem yapma
    }
    else {
        // Handle normal data messages - only from paired devices
        bool isPairedDevice = false;
        for (int i = 0; i < instance->pairedCount; i++) {
            if (memcmp(instance->pairedMacList[i], mac_addr, 6) == 0) {
                isPairedDevice = true;
                break;
            }
        }
        
        if (!isPairedDevice) {
            instance->log("⚠️ Eşleşmemiş cihazdan veri, reddedildi: " + String(receivedData));
            return;
        }
        
        // Try to parse as new format message
        ESPNowManagerMessage parsedMsg;
        
        if (instance->parseEspNowMessage(receivedData, len, parsedMsg)) {
            // New format message
            instance->log("✅ ESP-NOW: " + parsedMsg.name + " (" + parsedMsg.model + ") RSSI:" + String(parsedMsg.rssi) + " -> " + parsedMsg.data);
            
            String displayText = parsedMsg.data;
            String formattedText = displayText;// + "() ";
            
            // Store in data buffer for loop-based access
            instance->receivedDataBuffer = formattedText;
            instance->hasNewData = true;
            instance->lastDataTime = millis();
            
            if (instance->displayCallback) {
                instance->displayCallback(formattedText, "new_format");
            }
            
        } else {
            // Old format message
            instance->log("📊 ESP-NOW Eski Format: " + String(receivedData));
            
            String formattedText = String(receivedData);// + "() ";
            
            // Store in data buffer for loop-based access
            instance->receivedDataBuffer = formattedText;
            instance->hasNewData = true;
            instance->lastDataTime = millis();
            
            if (instance->displayCallback) {
                instance->displayCallback(formattedText, "old_format");
            }
        }
        
        // Update external hata flag
        if (instance->externalHataFlag) {
            *(instance->externalHataFlag) = false;
        }
    }
}

// Additional implementation functions from main.cpp

// legacy printMacAddress removed; use PrintMacAddress or macToStr/macToString

String ESPNowManager::macToStr(const uint8_t *mac) {
    char buf[18];
    snprintf(buf, sizeof(buf), "%02X:%02X:%02X:%02X:%02X:%02X",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return String(buf);
}

void ESPNowManager::addToDiscoveredList(const uint8_t *mac_addr) {
    // Debug için MAC adresini yazdır
    char macStr[18];
    macToString(mac_addr, macStr);
    log("🔍 Discovered listesine eklenmeye çalışılan MAC: " + String(macStr));
    
    // Sadece zaten discovered listesinde var mı kontrol et
    for (int i = 0; i < discoveredCount; i++) {
        if (memcmp(discoveredMacList[i], mac_addr, 6) == 0) {
            log("ℹ️ MAC zaten discovered listesinde");
            return;
        }
    }
    
    if (discoveredCount < MAX_PAIRED_DEVICES) {
        memcpy(discoveredMacList[discoveredCount], mac_addr, 6);
        discoveredCount++;
        log("✅ Yeni cihaz discovered listesine eklendi. Toplam: " + String(discoveredCount));
    } else {
        log("⚠️ Discovered listesi dolu!");
    }
}

void ESPNowManager::removeFromDiscoveredList(const uint8_t *mac_addr) {
    int index = -1;
    for (int i = 0; i < discoveredCount; i++) {
        if (memcmp(discoveredMacList[i], mac_addr, 6) == 0) {
            index = i;
            break;
        }
    }
    
    if (index >= 0) {
        // Listedeki öğeyi kaydırarak sil
        for (int i = index; i < discoveredCount - 1; i++) {
            memcpy(discoveredMacList[i], discoveredMacList[i + 1], 6);
        }
        discoveredCount--;
        log("🗑️ MAC discovered listesinden çıkarıldı. Yeni toplam: " + String(discoveredCount));
    }
}

bool ESPNowManager::savePairedMac(const uint8_t *newMac) {
    // MAC adresini debug için yazdır
    char macStr[18];
    macToString(newMac, macStr);
    log("💾 Kaydetmeye çalışılan MAC: " + String(macStr));
    
    preferences.begin("espnow", false);
    pairedCount = preferences.getBytesLength("paired_mac") / 6;
    if (pairedCount > MAX_PAIRED_DEVICES) pairedCount = MAX_PAIRED_DEVICES;
    preferences.getBytes("paired_mac", pairedMacList, pairedCount * 6);
    
    log("📊 Mevcut eşleşmiş cihaz sayısı (kaydetmeden önce): " + String(pairedCount));

    bool alreadyExists = false;
    for (int i = 0; i < pairedCount; i++) {
        if (memcmp(pairedMacList[i], newMac, 6) == 0) {
            alreadyExists = true;
            break;
        }
    }

    if (!alreadyExists) {
        if (pairedCount < MAX_PAIRED_DEVICES) {
            memcpy(pairedMacList[pairedCount], newMac, 6);
            pairedCount++;
            log("✅ Yeni MAC eklendi. Yeni toplam: " + String(pairedCount));
        } else {
            for (int i = 0; i < MAX_PAIRED_DEVICES - 1; i++) {
                memcpy(pairedMacList[i], pairedMacList[i + 1], 6);
            }
            memcpy(pairedMacList[MAX_PAIRED_DEVICES - 1], newMac, 6);
            log("🔄 Liste dolu, en eskisi silindi, yenisi eklendi");
        }
    } else {
        log("ℹ️ MAC zaten kayıtlı");
    }

    preferences.putBytes("paired_mac", pairedMacList, pairedCount * 6);
    preferences.end();
    
    // Kaydedilen MAC'leri listele
    log("📋 Kaydedilmiş MAC listesi:");
    for (int i = 0; i < pairedCount; i++) {
        char tempMacStr[18];
        macToString(pairedMacList[i], tempMacStr);
        log("  " + String(i) + ": " + String(tempMacStr));
    }

    updatePeerStatus(newMac, true);
    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, newMac, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    if (!esp_now_is_peer_exist(newMac)) {
        esp_now_add_peer(&peerInfo);
    }
    return true;
}

void ESPNowManager::removePairedMac(const char* macStr) {
    log("🔍 MAC silme işlemi başlıyor: " + String(macStr));
    
    // Önce preferences'tan güncel verileri oku
    preferences.begin("espnow", false);
    pairedCount = preferences.getBytesLength("paired_mac") / 6;
    if (pairedCount > MAX_PAIRED_DEVICES) pairedCount = MAX_PAIRED_DEVICES;
    preferences.getBytes("paired_mac", pairedMacList, pairedCount * 6);
    preferences.end();
    
    log("🔢 Preferences'tan okunan cihaz sayısı: " + String(pairedCount));
    
    // Mevcut MAC listesini göster
    log("📋 Mevcut eşleşmiş MAC'ler:");
    for (int i = 0; i < pairedCount; i++) {
        char tempMacStr[18];
        macToString(pairedMacList[i], tempMacStr);
        log("  " + String(i) + ": " + String(tempMacStr));
    }
    
    uint8_t mac[6];
    stringToMac(macStr, mac);
    
    char parsedMacStr[18];
    macToString(mac, parsedMacStr);
    log("🎯 Parse edilmiş MAC: " + String(parsedMacStr));

    int index = -1;
    for (int i = 0; i < pairedCount; i++) {
        if (memcmp(pairedMacList[i], mac, 6) == 0) {
            index = i;
            break;
        }
    }

    if (index >= 0) {
        log("✅ MAC bulundu, index: " + String(index));
        // listedeki öğeyi kaydırarak sil
        for (int i = index; i < pairedCount - 1; i++) {
            memcpy(pairedMacList[i], pairedMacList[i + 1], 6);
        }
        pairedCount--;

        // preferences'a gerçekten yaz
        preferences.begin("espnow", false);
        if (pairedCount > 0) {
            preferences.putBytes("paired_mac", pairedMacList, pairedCount * 6);
        } else {
            preferences.remove("paired_mac");  // hepsi silindiyse key'i kaldır
        }
        preferences.end();

        // RAM'den ve esp-now'dan da çıkar
        esp_err_t result = esp_now_del_peer(mac);
        log("🗑️ ESP-NOW peer silme sonucu: " + String(result == ESP_OK ? "Başarılı" : "Hata"));
        log("✅ MAC başarıyla silindi. Yeni sayı: " + String(pairedCount));
    } else {
        log("⚠️ MAC adresi listede bulunamadı: " + String(macStr));
    }
}



int ESPNowManager::getActiveDeviceCount() {
    int activeCount = 0;
    for (int i = 0; i < peerStatusCount; i++) {
        if (peerStatusList[i].active) {
            activeCount++;
        }
    }
    return activeCount;
}

// Static callback for send status
void ESPNowManager::onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    if (!instance) return;
    
    // Update peer status based on send result
    instance->updatePeerStatus(mac_addr, status == ESP_NOW_SEND_SUCCESS);
    
    // Call user callback if registered
    if (instance->sendStatusCallback) {
        instance->sendStatusCallback(mac_addr, status);
    }
}

// Status functions
bool ESPNowManager::isInitialized() {
    return initialized;
}

// Web interface support functions
String ESPNowManager::getMacListJson() {
    // MEMORY-OPTIMIZED JSON: Dinamik boyut hesaplama
    int estimatedSize = 100 + (pairedCount * 60) + (discoveredCount * 40);
    if (estimatedSize > 4096) estimatedSize = 4096; // Maksimum limit
    if (estimatedSize < 512) estimatedSize = 512;   // Minimum limit
    
    DynamicJsonDocument doc(estimatedSize);

    // Paired devices
    JsonArray paired = doc.createNestedArray("paired");
    for (int i = 0; i < pairedCount && i < MAX_PAIRED_DEVICES; i++) { // Double check bounds
        JsonObject obj = paired.createNestedObject();
        char macStr[18];
        sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X",
                pairedMacList[i][0], pairedMacList[i][1], pairedMacList[i][2],
                pairedMacList[i][3], pairedMacList[i][4], pairedMacList[i][5]);
        obj["mac"] = macStr;
        
        // Check if peer is active - optimized loop
        bool aktif = false;
        for (int j = 0; j < peerStatusCount && j < MAX_PAIRED_DEVICES; j++) {
            if (memcmp(peerStatusList[j].mac, pairedMacList[i], 6) == 0) {
                aktif = peerStatusList[j].active;
                break;
            }
        }
        obj["active"] = aktif;
    }

    // Discovered devices
    JsonArray discovered = doc.createNestedArray("discovered");
    for (int i = 0; i < discoveredCount && i < MAX_PAIRED_DEVICES; i++) { // Double check bounds
        JsonObject obj = discovered.createNestedObject();
        char macStr[18];
        sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X",
                discoveredMacList[i][0], discoveredMacList[i][1], discoveredMacList[i][2],
                discoveredMacList[i][3], discoveredMacList[i][4], discoveredMacList[i][5]);
        obj["mac"] = macStr;
    }

    String output;
    if (serializeJson(doc, output) == 0) {
        log("⚠️ JSON serialization failed - memory issue?");
        return "{\"error\":\"json_failed\",\"paired\":[],\"discovered\":[]}";
    }
    return output;
}

bool ESPNowManager::parseMacAddress(const String& macStr, uint8_t mac[6]) {
    if (macStr.length() != 17) return false;
    
    int values[6];
    if (sscanf(macStr.c_str(), "%x:%x:%x:%x:%x:%x",
               &values[0], &values[1], &values[2], 
               &values[3], &values[4], &values[5]) == 6) {
        for (int i = 0; i < 6; i++) {
            mac[i] = (uint8_t)values[i];
        }
        return true;
    }
    return false;
}



bool ESPNowManager::removePairedMac(const String& macStr) {
    uint8_t mac[6];
    if (!parseMacAddress(macStr, mac)) {
        return false;
    }
    
    // Find and remove from paired list
    for (int i = 0; i < pairedCount; i++) {
        if (memcmp(pairedMacList[i], mac, 6) == 0) {
            // Shift remaining items
            for (int j = i; j < pairedCount - 1; j++) {
                memcpy(pairedMacList[j], pairedMacList[j + 1], 6);
            }
            pairedCount--;
            
            // Remove from ESP-NOW peer list
            esp_now_del_peer(mac);
            
            // Save to preferences
            preferences.begin("espnow", false);
            preferences.putBytes("paired_mac", pairedMacList, pairedCount * 6);
            preferences.end();
            
            log("🗑️ MAC silindi: " + macStr);
            return true;
        }
    }
    return false;
}

void ESPNowManager::setRawDataCallback(RawDataCallback callback) {
    rawDataCallback = callback;
}

// Compatible version of SendData for main.cpp
void ESPNowManager::SendData(const String& data, const String& model) {
    if (pairedCount == 0) {
        log("❌ SendData: Eşleşmiş cihaz yok");
        return;
    }

    for (int i = 0; i < pairedCount; i++) {
        String macStr = macToStr(pairedMacList[i]);
        
        // Peer'in ESP-NOW listesinde olup olmadığını kontrol et
        if (!esp_now_is_peer_exist(pairedMacList[i])) {
            log("⚠️ Peer mevcut değil, ekleniyor: " + macStr);
            
            // Peer'i ekle
            esp_now_peer_info_t peerInfo = {};
            memcpy(peerInfo.peer_addr, pairedMacList[i], 6);
            peerInfo.channel = 0;  // Otomatik kanal
            peerInfo.encrypt = false;
            
            esp_err_t addResult = esp_now_add_peer(&peerInfo);
            if (addResult != ESP_OK) {
                log("❌ Peer eklenemedi: " + String(addResult));
                continue;
            } else {
                log("✅ Peer eklendi: " + macStr);
            }
        }
        
        // ESP-NOW veri callback'i çağır (main.cpp uyumluluğu için)
        if (espnowDataCallback) {
            espnowDataCallback("To " + macStr + ": " + data, "out");
        }
        
        int rssi = WiFi.RSSI();
        if (rssi == 0) rssi = lastReceivedRSSI;
        
        // DeviceName'i preferences'tan oku
        preferences.begin("wifi", true);
        String deviceName = preferences.getString("ssid", "HRCMINI");
        preferences.end();
        
        // MEMORY OPTIMIZED: sprintf kullanarak string concatenation yerine
        char formattedBuffer[256]; // Maksimum ESP-NOW payload boyutu
        int written = snprintf(formattedBuffer, sizeof(formattedBuffer), 
                              "%s|%s|%d|CMD|%s", 
                              deviceName.c_str(), model.c_str(), rssi, data.c_str());
        
        // Buffer overflow kontrolü
        if (written >= (int)sizeof(formattedBuffer)) {
            log("⚠️ Payload çok büyük, kesiliyor: " + String(written));
            formattedBuffer[sizeof(formattedBuffer)-1] = '\0';
        }
        
        String formattedData(formattedBuffer); // Sadece gerekli durumlarda String'e çevir
        
        log("📤 Gönderiliyor: " + macStr + " -> " + formattedData);
        
        esp_err_t result = esp_now_send(pairedMacList[i], (uint8_t *)formattedData.c_str(), formattedData.length());
        
        if (result == ESP_OK) {
            log("✅ ESP-NOW başarılı: " + macStr);
        } else {
            log("❌ ESP-NOW hatası: " + String(result) + " (" + macStr + ")");
        }
        
        updatePeerStatus(pairedMacList[i], result == ESP_OK);
    }
}

// ESPEasy compatibility functions
int ESPNowManager::getPeerCount() {
    return getPairedDeviceCount();
}

String ESPNowManager::getPeerListString() {
    String result = "";
    int count = getPairedDeviceCount();
    for (int i = 0; i < count; i++) {
        uint8_t mac[6];
        if (getPairedDevice(i, mac)) {
            if (result.length() > 0) result += ", ";
            result += macToString(mac);
        }
    }
    return result;
}

bool ESPNowManager::sendData(const uint8_t *mac_addr, const uint8_t *data, size_t len) {
    // Hedef cihazın peer olarak ekli olup olmadığını kontrol et
    if (!esp_now_is_peer_exist(mac_addr)) {
        esp_now_peer_info_t peerInfo = {};
        memcpy(peerInfo.peer_addr, mac_addr, 6);
        peerInfo.channel = 0;
        peerInfo.encrypt = false;
        
        esp_err_t addResult = esp_now_add_peer(&peerInfo);
        if (addResult != ESP_OK) {
            return false;
        }
    }
    
    esp_err_t result = esp_now_send(mac_addr, data, len);
    return (result == ESP_OK);
}

bool ESPNowManager::sendBroadcast(const uint8_t *data, size_t len) {
    uint8_t broadcastMac[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    
    // Broadcast peer'ı ekle
    if (!esp_now_is_peer_exist(broadcastMac)) {
        esp_now_peer_info_t peerInfo = {};
        memcpy(peerInfo.peer_addr, broadcastMac, 6);
        peerInfo.channel = 0;
        peerInfo.encrypt = false;
        
        esp_err_t addResult = esp_now_add_peer(&peerInfo);
        if (addResult != ESP_OK) {
            return false;
        }
    }
    
    esp_err_t result = esp_now_send(broadcastMac, data, len);
    return (result == ESP_OK);
}

bool ESPNowManager::parseMacAddress(const char *macStr, uint8_t mac[6]) {
    if (!macStr) return false;
    
    int values[6];
    int result = sscanf(macStr, "%02x:%02x:%02x:%02x:%02x:%02x",
                       &values[0], &values[1], &values[2],
                       &values[3], &values[4], &values[5]);
    
    if (result == 6) {
        for (int i = 0; i < 6; i++) {
            mac[i] = (uint8_t)values[i];
        }
        return true;
    }
    return false;
}

// Data buffer management functions
bool ESPNowManager::hasReceivedData() {
    return hasNewData;
}

String ESPNowManager::getReceivedData() {
    if (hasNewData) {
        String data = receivedDataBuffer;
        return data;
    }
    return "";
}

void ESPNowManager::clearReceivedData() {
    receivedDataBuffer = "";
    hasNewData = false;
    lastDataTime = 0;
}