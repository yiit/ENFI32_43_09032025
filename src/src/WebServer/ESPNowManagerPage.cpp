#include "../WebServer/ESPNowManagerPage.h"

#ifdef USES_ESPNOW_MANAGER

#include "../WebServer/ESPEasy_WebServer.h"
#include "../WebServer/HTML_wrappers.h"
#include "../WebServer/Markup.h"
#include "../WebServer/Markup_Buttons.h"
#include "../WebServer/Markup_Forms.h"
#include "../../lib/ESPNowManager/ESPNowManager.h"
#include "../../ESPEasy-Globals.h"

// Global ESPNowManager instance
ESPNowManager espnowManager;

// Log messages for web interface
String espnowManagerLogMessages = "";

// Initialize ESP-NOW Manager with ESPEasy callbacks
bool initESPNowManager() {
  static bool initialized = false;
  if (initialized) return true;
  
  // Initialize ESPNowManager with device name
  String deviceName = "ESPEasy_" + WiFi.macAddress();
  deviceName.replace(":", "");
  
  if (espnowManager.begin(deviceName)) {
    
    // Set up message callback
    espnowManager.onMessage([](const ESPNowManagerMessage& msg) {
      String logMsg = "[" + String(millis()) + "] Message received from " + msg.sender + 
                     " - Type: " + msg.type + " - Message: " + msg.message;
      espnowManagerLogMessages += logMsg + "\n";
      
      // Keep log size manageable
      if (espnowManagerLogMessages.length() > 8000) {
        espnowManagerLogMessages = espnowManagerLogMessages.substring(2000);
      }
    });
    
    // Set up peer status callback
    espnowManager.onPeerStatusChange([](const uint8_t* mac, bool active) {
      String macStr = espnowManager.macToString(mac);
      String logMsg = "[" + String(millis()) + "] Peer " + macStr + " is now " + 
                     (active ? "ACTIVE" : "INACTIVE");
      espnowManagerLogMessages += logMsg + "\n";
    });
    
    // Set up log callback
    espnowManager.onLog([](const String& message) {
      String logMsg = "[" + String(millis()) + "] " + message;
      espnowManagerLogMessages += logMsg + "\n";
    });
    
    initialized = true;
    espnowManagerLogMessages = "[" + String(millis()) + "] ESPNowManager initialized successfully\n";
    return true;
  }
  
  espnowManagerLogMessages = "[" + String(millis()) + "] Failed to initialize ESPNowManager\n";
  return false;
}

// Main ESP-NOW Manager page
void handle_espnow_manager() {
  #ifndef BUILD_NO_RAM_TRACKER
  checkRAM(F("handle_espnow_manager"));
  #endif

  if (!isLoggedIn()) return;

  // Initialize if not already done
  initESPNowManager();

  navMenuIndex = MENU_INDEX_TOOLS;
  TXBuffer.startStream();
  sendHeadandTail_stdtemplate(_HEAD);

  addHtml(F("<form>"));
  html_table_class_normal();
  addFormHeader(F("ESP-NOW Manager"));

  // Device Information
  addFormSubHeader(F("Device Information"));
  addRowLabel(F("MAC Address"));
  addHtml(WiFi.macAddress());
  
  addRowLabel(F("Peer Count"));
  addHtml(String(espnowManager.getPairedDeviceCount()));

  // Control Buttons
  addFormSubHeader(F("Controls"));
  addRowLabel(F("Device Discovery"));
  addButton(F("espnow_scan"), F("Start Scan"));
  addRowLabel(F(""));
  addButton(F("espnow_discovery"), F("Start Discovery"));

  // Message Sending Form
  addFormSubHeader(F("Send Message"));
  addFormTextBox(F("Target MAC"), F("target_mac"), F(""), 18, false, false, F("AA:BB:CC:DD:EE:FF"));
  addFormTextBox(F("Message"), F("message"), F(""), 100, false, false, F("Hello World"));
  html_TR_TD();
  addSubmitButton(F("Send Message"), F("espnow_send"));

  // Broadcast Form  
  addFormSubHeader(F("Broadcast Message"));
  addFormTextBox(F("Broadcast Message"), F("broadcast_message"), F(""), 100, false, false, F("Hello Everyone"));
  html_TR_TD();
  addSubmitButton(F("Send Broadcast"), F("espnow_broadcast"));

  // Peer List (detailed with individual controls)
  addFormSubHeader(F("Paired Devices"));
  int peerCount = espnowManager.getPairedDeviceCount();
  if (peerCount > 0) {
    for (int i = 0; i < peerCount; i++) {
      uint8_t mac[6];
      if (espnowManager.getPairedDevice(i, mac)) {
        String macStr = espnowManager.macToString(mac);
        
        String deviceLabel = F("Device ");
        deviceLabel += String(i + 1);
        addRowLabel(deviceLabel);
        
        String deviceInfo = F("<div style='display: flex; align-items: center; gap: 10px;'>");
        deviceInfo += F("<span style='font-family: monospace;'>");
        deviceInfo += macStr;
        deviceInfo += F("</span>");
        deviceInfo += F("<span style='color: #666; font-size: 0.9em;'>(ESP32)</span>");
        
        // Add pairing/control buttons for this specific device
        deviceInfo += F("<button onclick=\"handlePairDevice('");
        deviceInfo += macStr;
        deviceInfo += F("')\" style='margin-left: 10px; padding: 2px 8px; font-size: 0.8em;'>Pair</button>");
        deviceInfo += F("<button onclick=\"handleRemoveDevice('");
        deviceInfo += macStr;
        deviceInfo += F("')\" style='margin-left: 5px; padding: 2px 8px; font-size: 0.8em; background: #ff6b6b; color: white;'>Remove</button>");
        deviceInfo += F("</div>");
        
        addHtml(deviceInfo);
      }
    }
  } else {
    addRowLabel(F("Status"));
    addHtml(F("No paired devices"));
  }

  // Discovered Devices
  addFormSubHeader(F("Discovered Devices"));
  int discoveredCount = espnowManager.getDiscoveredDeviceCount();
  if (discoveredCount > 0) {
    for (int i = 0; i < discoveredCount; i++) {
      uint8_t mac[6];
      if (espnowManager.getDiscoveredDevice(i, mac)) {
        String macStr = "";
        for (int j = 0; j < 6; j++) {
          if (j > 0) macStr += ":";
          if (mac[j] < 16) macStr += "0";
          macStr += String(mac[j], HEX);
        }
        macStr.toUpperCase();
        
        String deviceInfo = F("<div style='margin: 5px 0; padding: 5px; border: 1px solid #ddd; border-radius: 3px;'>");
        deviceInfo += F("MAC: ");
        deviceInfo += macStr;
        deviceInfo += F(" | Model: ESP32");
        deviceInfo += F("<button onclick=\"handlePairDiscoveredDevice('");
        deviceInfo += macStr;
        deviceInfo += F("')\" style='margin-left: 10px; padding: 2px 8px; font-size: 0.8em; background: #4CAF50; color: white;'>Pair</button>");
        deviceInfo += F("</div>");
        
        addHtml(deviceInfo);
      }
    }
  } else {
    addRowLabel(F("Status"));
    addHtml(F("No discovered devices. Use 'Start Discovery' to find devices."));
  }

  // Log Messages
  addFormSubHeader(F("Log Messages"));
  addFormTextArea(F("log_messages"), F("log_messages"), espnowManagerLogMessages, 10, 80, true);

  html_end_table();
  html_end_form();

  // JavaScript for device control
  addHtml(F("<script>"));
  addHtml(F("function handlePairDevice(mac) {"));
  addHtml(F("  if (confirm('Start pairing with device: ' + mac + '?')) {"));
  addHtml(F("    var xhr = new XMLHttpRequest();"));
  addHtml(F("    xhr.open('GET', '/espnow_pair_device?mac=' + encodeURIComponent(mac), true);"));
  addHtml(F("    xhr.onreadystatechange = function() {"));
  addHtml(F("      if (xhr.readyState === 4) {"));
  addHtml(F("        if (xhr.status === 200) {"));
  addHtml(F("          alert('Pairing started with ' + mac);"));
  addHtml(F("          location.reload();"));
  addHtml(F("        } else {"));
  addHtml(F("          alert('Failed to start pairing');"));
  addHtml(F("        }"));
  addHtml(F("      }"));
  addHtml(F("    };"));
  addHtml(F("    xhr.send();"));
  addHtml(F("  }"));
  addHtml(F("}"));
  
  addHtml(F("function handleRemoveDevice(mac) {"));
  addHtml(F("  if (confirm('Remove device: ' + mac + '?')) {"));
  addHtml(F("    var xhr = new XMLHttpRequest();"));
  addHtml(F("    xhr.open('GET', '/espnow_remove_device?mac=' + encodeURIComponent(mac), true);"));
  addHtml(F("    xhr.onreadystatechange = function() {"));
  addHtml(F("      if (xhr.readyState === 4) {"));
  addHtml(F("        if (xhr.status === 200) {"));
  addHtml(F("          alert('Device removed: ' + mac);"));
  addHtml(F("          location.reload();"));
  addHtml(F("        } else {"));
  addHtml(F("          alert('Failed to remove device');"));
  addHtml(F("        }"));
  addHtml(F("      }"));
  addHtml(F("    };"));
  addHtml(F("    xhr.send();"));
  addHtml(F("  }"));
  addHtml(F("}"));
  
  addHtml(F("function handlePairDiscoveredDevice(mac) {"));
  addHtml(F("  if (confirm('Pair with discovered device: ' + mac + '?')) {"));
  addHtml(F("    var xhr = new XMLHttpRequest();"));
  addHtml(F("    xhr.open('GET', '/espnow_pair_discovered?mac=' + encodeURIComponent(mac), true);"));
  addHtml(F("    xhr.onreadystatechange = function() {"));
  addHtml(F("      if (xhr.readyState === 4) {"));
  addHtml(F("        if (xhr.status === 200) {"));
  addHtml(F("          alert('Pairing started with discovered device: ' + mac);"));
  addHtml(F("          location.reload();"));
  addHtml(F("        } else {"));
  addHtml(F("          alert('Failed to start pairing with discovered device');"));
  addHtml(F("        }"));
  addHtml(F("      }"));
  addHtml(F("    };"));
  addHtml(F("    xhr.send();"));
  addHtml(F("  }"));
  addHtml(F("}"));
  addHtml(F("</script>"));

  sendHeadandTail_stdtemplate(_TAIL);
  TXBuffer.endStream();
}

// API Endpoints
void handle_espnow_scan() {
  if (!isLoggedIn()) return;
  
  initESPNowManager();
  espnowManager.startDiscovery();
  espnowManagerLogMessages += "[" + String(millis()) + "] Device scan started\n";
  
  TXBuffer.startStream();
  sendHeadandTail_stdtemplate(_HEAD);
  addHtml(F("ESP-NOW scan started. Redirecting..."));
  addHtml(F("<script>setTimeout(() => { window.location.href = '/espnow_manager'; }, 2000);</script>"));
  sendHeadandTail_stdtemplate(_TAIL);
  TXBuffer.endStream();
}

void handle_espnow_pair() {
  if (!isLoggedIn()) return;
  
  initESPNowManager();
  espnowManager.StartPairing(); // Use compatible version
  espnowManagerLogMessages += "[" + String(millis()) + "] Pairing mode started\n";
  
  TXBuffer.startStream();
  sendHeadandTail_stdtemplate(_HEAD);
  addHtml(F("ESP-NOW pairing started. Redirecting..."));
  addHtml(F("<script>setTimeout(() => { window.location.href = '/espnow_manager'; }, 2000);</script>"));
  sendHeadandTail_stdtemplate(_TAIL);
  TXBuffer.endStream();
}

void handle_espnow_send() {
  if (!isLoggedIn()) return;
  
  String targetMac = webArg(F("target_mac"));
  String message = webArg(F("message"));
  
  if (targetMac.length() > 0 && message.length() > 0) {
    uint8_t mac[6];
    if (espnowManager.parseMacAddress(targetMac.c_str(), mac)) {
      bool success = espnowManager.sendData(mac, (uint8_t*)message.c_str(), message.length());
      if (success) {
        espnowManagerLogMessages += "[" + String(millis()) + "] Message sent to " + targetMac + "\n";
      } else {
        espnowManagerLogMessages += "[" + String(millis()) + "] Failed to send message to " + targetMac + "\n";
      }
    }
  }
  
  TXBuffer.startStream();
  sendHeadandTail_stdtemplate(_HEAD);
  addHtml(F("Message sent. Redirecting..."));
  addHtml(F("<script>setTimeout(() => { window.location.href = '/espnow_manager'; }, 2000);</script>"));
  sendHeadandTail_stdtemplate(_TAIL);
  TXBuffer.endStream();
}

void handle_espnow_broadcast() {
  if (!isLoggedIn()) return;
  
  String message = webArg(F("broadcast_message"));
  
  if (message.length() > 0) {
    bool success = espnowManager.sendBroadcast((uint8_t*)message.c_str(), message.length());
    if (success) {
      espnowManagerLogMessages += "[" + String(millis()) + "] Broadcast sent\n";
    } else {
      espnowManagerLogMessages += "[" + String(millis()) + "] Failed to send broadcast\n";
    }
  }
  
  TXBuffer.startStream();
  sendHeadandTail_stdtemplate(_HEAD);
  addHtml(F("Broadcast sent. Redirecting..."));
  addHtml(F("<script>setTimeout(() => { window.location.href = '/espnow_manager'; }, 2000);</script>"));
  sendHeadandTail_stdtemplate(_TAIL);
  TXBuffer.endStream();
}

void handle_espnow_pair_device() {
  if (!isLoggedIn()) return;
  
  String macAddress = webArg(F("mac"));
  
  if (macAddress.length() > 0) {
    // Convert MAC address string to uint8_t array
    uint8_t mac[6];
    if (sscanf(macAddress.c_str(), "%02x:%02x:%02x:%02x:%02x:%02x",
               &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]) == 6) {
      
      bool success = espnowManager.addPeer(mac);
      String logMessage = "[" + String(millis()) + "] ";
      if (success) {
        logMessage += "Started pairing with " + macAddress;
      } else {
        logMessage += "Failed to start pairing with " + macAddress;
      }
      logMessage += "\n";
      espnowManagerLogMessages += logMessage;
    } else {
      espnowManagerLogMessages += "[" + String(millis()) + "] Invalid MAC address format\n";
    }
  }
  
  TXBuffer.startStream();
  sendHeadandTail_stdtemplate(_HEAD);
  addHtml(F("Pairing command sent. Redirecting..."));
  addHtml(F("<script>setTimeout(() => { window.location.href = '/espnow_manager'; }, 2000);</script>"));
  sendHeadandTail_stdtemplate(_TAIL);
  TXBuffer.endStream();
}

void handle_espnow_remove_device() {
  if (!isLoggedIn()) return;
  
  String macAddress = webArg(F("mac"));
  
  if (macAddress.length() > 0) {
    // Convert MAC address string to uint8_t array
    uint8_t mac[6];
    if (sscanf(macAddress.c_str(), "%02x:%02x:%02x:%02x:%02x:%02x",
               &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]) == 6) {
      
      bool success = espnowManager.removePeer(mac);
      String logMessage = "[" + String(millis()) + "] ";
      if (success) {
        logMessage += "Removed device " + macAddress;
      } else {
        logMessage += "Failed to remove device " + macAddress;
      }
      logMessage += "\n";
      espnowManagerLogMessages += logMessage;
    } else {
      espnowManagerLogMessages += "[" + String(millis()) + "] Invalid MAC address format\n";
    }
  }
  
  TXBuffer.startStream();
  sendHeadandTail_stdtemplate(_HEAD);
  addHtml(F("Remove command sent. Redirecting..."));
  addHtml(F("<script>setTimeout(() => { window.location.href = '/espnow_manager'; }, 2000);</script>"));
  sendHeadandTail_stdtemplate(_TAIL);
  TXBuffer.endStream();
}

void handle_espnow_pair_discovered() {
  if (!isLoggedIn()) return;
  
  String macAddress = webArg(F("mac"));
  
  if (macAddress.length() > 0) {
    // Convert MAC address string to uint8_t array
    uint8_t mac[6];
    if (sscanf(macAddress.c_str(), "%02x:%02x:%02x:%02x:%02x:%02x",
               &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]) == 6) {
      
      // Start pairing mode first
      espnowManager.startPairing(30000);
      
      // Wait a bit for pairing mode to initialize
      delay(100);
      yield();
      
      // Then send pair request to discovered device
      espnowManager.SendPairRequest(mac);
      
      // Wait for the request to be processed
      delay(50);
      yield();
      
      String logMessage = "[" + String(millis()) + "] ";
      logMessage += "Pairing mode started and pair request sent to " + macAddress;
      logMessage += "\n";
      espnowManagerLogMessages += logMessage;
    } else {
      espnowManagerLogMessages += "[" + String(millis()) + "] Invalid MAC address format\n";
    }
  }
  
  TXBuffer.startStream();
  sendHeadandTail_stdtemplate(_HEAD);
  addHtml(F("Pair request sent to discovered device. Redirecting..."));
  addHtml(F("<script>setTimeout(() => { window.location.href = '/espnow_manager'; }, 2000);</script>"));  
  sendHeadandTail_stdtemplate(_TAIL);
  TXBuffer.endStream();
}

void handle_espnow_discovery() {
  if (!isLoggedIn()) return;
  
  espnowManager.startDiscovery();
  espnowManagerLogMessages += "[" + String(millis()) + "] Device discovery started\n";
  
  TXBuffer.startStream();
  sendHeadandTail_stdtemplate(_HEAD);
  addHtml(F("Device discovery started. Redirecting..."));
  addHtml(F("<script>setTimeout(() => { window.location.href = '/espnow_manager'; }, 2000);</script>"));
  sendHeadandTail_stdtemplate(_TAIL);
  TXBuffer.endStream();
}

// Update ESP-NOW Manager in main loop
void updateESPNowManager() {
  #ifdef USES_ESPNOW_MANAGER
  static bool initialized = false;
  if (!initialized) {
    initialized = initESPNowManager();
  }
  
  if (initialized) {
    espnowManager.handle();
    
    // Global ESP-NOW data integration - Check for received data and write to XML_NET_C
    if (espnowManager.hasReceivedData()) {
      String receivedData = espnowManager.getReceivedData();
      if (receivedData.length() > 0) {
        // XML_NET_C is char[9], so copy string data safely
        XML_NET_S = receivedData;
        
        // Also write to XML_NET_C char array (max 8 chars + null terminator)
        strncpy(XML_NET_C, receivedData.c_str(), sizeof(XML_NET_C) - 1);
        XML_NET_C[sizeof(XML_NET_C) - 1] = '\0'; // Ensure null termination
        
        espnowManager.clearReceivedData();
      }
    }
  }
  #endif
}

#endif // USES_ESPNOW_MANAGER