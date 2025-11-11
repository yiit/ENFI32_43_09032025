# ESPNowManager Library

ESP-NOW communication manager for ESP32 devices. This library provides easy-to-use functions for ESP-NOW peer-to-peer communication, device discovery, pairing, and data exchange.

## Features

- 🔄 **Device Discovery**: Automatic discovery of nearby ESP-NOW devices
- 🤝 **Device Pairing**: Simple pairing mechanism with handshake protocol
- 📡 **Data Communication**: Reliable data exchange between paired devices
- 🌐 **Web Interface**: Optional web-based device management
- 🛡️ **Security**: Paired device authentication and validation
- 📊 **Status Monitoring**: Connection status and peer management
- 🔧 **Easy Integration**: Simple callback-based API

## Installation

### PlatformIO
1. Copy the `ESPNowManager` folder to your project's `lib/` directory
2. Add dependencies to `platformio.ini`:
```ini
lib_deps = 
    WiFi
    Preferences
    ArduinoJson
```

### Arduino IDE
1. Copy the library to your Arduino libraries folder
2. Install required libraries: WiFi, Preferences, ArduinoJson

## Basic Usage

```cpp
#include <ESPNowManager.h>

ESPNowManager espnowManager;

void onDataReceived(String data, String type) {
    Serial.println("Received: " + data);
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    
    espnowManager.setDataCallback(onDataReceived);
    espnowManager.init();
}

void loop() {
    espnowManager.handle();
    
    // Check for new data
    if (espnowManager.hasReceivedData()) {
        String data = espnowManager.getReceivedData();
        Serial.println("New data: " + data);
        espnowManager.clearReceivedData();
    }
}
```

## API Reference

### Initialization
- `bool init()` - Initialize ESP-NOW manager
- `void setDataCallback(DataCallback callback)` - Set data received callback
- `void setDisplayCallback(DisplayCallback callback)` - Set display message callback
- `void setLogCallback(LogCallback callback)` - Set log message callback

### Device Discovery
- `void startDiscovery()` - Start device discovery
- `int getDiscoveredDeviceCount()` - Get number of discovered devices
- `DiscoveredDevice getDiscoveredDevice(int index)` - Get discovered device info

### Device Pairing
- `bool SendPairRequest(uint8_t* mac)` - Send pairing request to device
- `int getPairedDeviceCount()` - Get number of paired devices
- `String getPairedDeviceMac(int index)` - Get paired device MAC address

### Data Communication
- `bool sendBroadcast(String data)` - Send broadcast message
- `bool sendToDevice(uint8_t* mac, String data)` - Send message to specific device
- `bool hasReceivedData()` - Check if new data available
- `String getReceivedData()` - Get received data
- `void clearReceivedData()` - Clear data buffer

### Utility Functions
- `bool parseMacAddress(const char* macStr, uint8_t mac[6])` - Parse MAC address string
- `String macToString(const uint8_t* mac)` - Convert MAC address to string
- `void handle()` - Handle ESP-NOW operations (call in loop)

## Message Formats

The library supports multiple message formats:

### New Format (Recommended)
```
NAME|MODEL|RSSI|CMD|DATA
```
Example: `ESP32Device|ESP32|-45|DATA|Hello World`

### Legacy Format
```
Simple text message
```

### Control Messages
- `DEVICE_SCAN` - Device discovery request
- `PAIR_REQUEST` - Pairing request  
- `PAIR_RESPONSE` - Pairing response
- `PAIR_DEL` - Remove pairing
- `STATUS|PING` - Status/ping message

## Examples

See the `examples/` folder for complete working examples:
- `BasicUsage.ino` - Simple ESP-NOW communication
- `WebInterface.ino` - Web-based device management

## License

This library is provided as-is for educational and development purposes. Library

ESP-NOW communication manager for ESP32 devices. This library provides a complete solution for peer-to-peer communication, device discovery, pairing, and data exchange between ESP32 devices using the ESP-NOW protocol.

## Features

- 🔄 **Automatic Device Discovery**: Scan and discover nearby ESP32 devices
- 🤝 **Device Pairing**: Manual and automatic device pairing with preferences storage
- 📡 **Message Broadcasting**: Send messages to all paired devices or specific devices  
- 📊 **Peer Status Monitoring**: Track active/inactive status of paired devices
- 🌐 **Web API Integration**: RESTful API endpoints for web-based device management
- 💾 **Persistent Storage**: Automatic saving/loading of paired devices using Preferences
- 📝 **Flexible Messaging**: Support for different message types and structured data
- 🔧 **Callback System**: Event-driven programming with customizable callbacks

## Installation

1. Copy the `lib/ESPNowManager` folder to your PlatformIO project's `lib` directory
2. Add the following dependencies to your `platformio.ini`:

```ini
lib_deps = 
    ESP Async WebServer
    ArduinoJson
```

## Quick Start

```cpp
#include <ESPNowManager.h>

ESPNowManager espnowManager;

void setup() {
    Serial.begin(115200);
    
    // Initialize ESP-NOW Manager
    if (espnowManager.begin("MyDevice")) {
        Serial.println("ESP-NOW initialized");
        
        // Set message callback
        espnowManager.onMessage([](const EspNowMessage& msg) {
            Serial.println("Received: " + msg.message);
        });
        
        // Set peer status callback
        espnowManager.onPeerStatusChange([](const uint8_t* mac, bool active) {
            Serial.printf("Peer status changed: %s\n", active ? "ACTIVE" : "INACTIVE");
        });
    }
}

void loop() {
    espnowManager.handle();
    delay(10);
}
```

## API Reference

### Initialization

#### `bool begin(const String& deviceName = "ESP32_Device")`
Initialize the ESP-NOW manager with a device name.

#### `void end()`
Deinitialize and cleanup resources.

### Callbacks

#### `void onMessage(MessageCallback callback)`
Set callback for received messages.

#### `void onPeerStatusChange(PeerStatusCallback callback)`
Set callback for peer status changes.

#### `void onLog(LogCallback callback)`
Set callback for log messages.

### Pairing & Discovery

#### `void startPairing(unsigned long timeoutMs = 30000)`
Start pairing mode to discover and pair with new devices.

#### `void startAutoPairing()`
Start automatic pairing - discovers devices and auto-pairs with the first found.

#### `void stopPairing()`
Stop pairing mode.

#### `bool isPairingActive()`
Check if pairing mode is currently active.

#### `void sendPairRequest(const uint8_t *mac_addr)`
Send pairing request to a specific device.

### Device Management

#### `bool addPeer(const uint8_t *mac_addr)`
Manually add a device to the paired list.

#### `bool removePeer(const uint8_t *mac_addr)`
#### `bool removePeer(const char *macStr)`
Remove a device from the paired list.

#### `int getPairedDeviceCount()`
Get the number of paired devices.

#### `bool getPairedDevice(int index, uint8_t *mac_addr)`
Get MAC address of a paired device by index.

#### `bool isPaired(const uint8_t *mac_addr)`
Check if a device is paired.

#### `void clearPairedDevices()`
Clear all paired devices.

### Messaging

#### `bool sendMessage(const uint8_t *mac_addr, const String& message, const String& type = "")`
Send a message to a specific device.

#### `bool sendBroadcast(const String& message, const String& type = "")`
Send a broadcast message to all paired devices.

#### `bool sendCommand(const uint8_t *mac_addr, const String& command, const String& data = "")`
Send a command message to a specific device.

### Status & Monitoring

#### `void updatePeerStatus(const uint8_t *mac_addr, bool active)`
Update the status of a peer device.

#### `bool getPeerStatus(const uint8_t *mac_addr)`
Get the current status of a peer device.

#### `int getActivePeerCount()`
Get the number of currently active peers.

### Utility Functions

#### `String getMacAddress()`
Get the device's own MAC address.

#### `String macToString(const uint8_t *mac_addr)`
Convert MAC address bytes to string format.

#### `void printPairedDevices()`
Print all paired devices to serial output.

#### `int getLastRSSI()`
Get the RSSI of the last received message.

### Web API Integration

```cpp
#include <ESPNowWebEndpoints.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);
ESPNowWebEndpoints webEndpoints(&espnowManager, &server);

void setup() {
    // ... initialize espnowManager
    
    // Setup web endpoints
    webEndpoints.setupEndpoints();
    server.begin();
}
```

#### Available Web Endpoints

- `GET /api/espnow/mac_list` - Get paired devices list
- `POST /api/espnow/add_mac` - Add device by MAC address
- `POST /api/espnow/delete_mac` - Remove device by MAC address
- `POST /api/espnow/pair_request` - Send pair request to device
- `GET /api/espnow/discovered_devices` - Get discovered devices
- `GET /api/espnow/peer_status` - Get peer status information
- `POST /api/espnow/start_pairing` - Start pairing mode
- `POST /api/espnow/stop_pairing` - Stop pairing mode
- `POST /api/espnow/send_message` - Send message to device
- `GET /api/espnow/get_data` - Get received data
- `POST /api/espnow/clear_data` - Clear data buffer

## Message Format

The library supports structured messages with the following format:

```
type|message|sender|command|data
```

- **type**: Message type (e.g., "HEARTBEAT", "COMMAND", "DATA")
- **message**: Main message content
- **sender**: Sender device name
- **command**: Command type (for command messages)
- **data**: Additional data payload

## Configuration

### Constants

```cpp
#define MAX_PAIRED_DEVICES 10   // Maximum number of paired devices
#define MAX_DATA_ENTRIES 20     // Maximum data buffer size
```

### Methods

```cpp
void setChannel(uint8_t channel);        // Set WiFi channel
void setMaxPeers(int maxPeers);          // Set maximum peers
void setDataBufferSize(int size);        // Set data buffer size
```

## Examples

### Basic Message Exchange

```cpp
// Send message to specific device
uint8_t targetMAC[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
espnowManager.sendMessage(targetMAC, "Hello World!", "GREETING");

// Send broadcast
espnowManager.sendBroadcast("System status OK", "STATUS");
```

### Automatic Pairing with Button

```cpp
#define PAIR_BUTTON 0

void loop() {
    static bool lastState = HIGH;
    bool currentState = digitalRead(PAIR_BUTTON);
    
    if (lastState == HIGH && currentState == LOW) {
        // Button pressed - start auto pairing
        espnowManager.startAutoPairing();
    }
    
    lastState = currentState;
    espnowManager.handle();
}
```

### Device Status Monitoring

```cpp
espnowManager.onPeerStatusChange([](const uint8_t* mac, bool active) {
    String macStr = espnowManager.macToString(mac);
    
    if (active) {
        Serial.println("Device connected: " + macStr);
        // Send welcome message
        espnowManager.sendMessage(mac, "Welcome!", "GREETING");
    } else {
        Serial.println("Device disconnected: " + macStr);
    }
});
```

## Integration with Existing Projects

To integrate with your existing ESP32 project:

1. Include the library headers
2. Create an ESPNowManager instance
3. Initialize in `setup()`
4. Call `handle()` in `loop()`
5. Set up callbacks for your specific needs

```cpp
// Replace your existing ESP-NOW code with:
#include <ESPNowManager.h>

ESPNowManager espnowManager;

void setup() {
    // Your existing setup code...
    
    // Replace esp_now_init() and callback setup with:
    espnowManager.begin("YourDeviceName");
    espnowManager.onMessage(yourMessageHandler);
}

void loop() {
    // Your existing loop code...
    
    // Add this to handle ESP-NOW operations:
    espnowManager.handle();
}
```

## Troubleshooting

### Common Issues

1. **ESP-NOW initialization fails**
   - Make sure WiFi is in STA mode
   - Check that ESP-NOW is not already initialized elsewhere

2. **Devices not pairing**
   - Ensure both devices are in pairing mode
   - Check that devices are within range (< 200m in open space)
   - Verify MAC addresses are correct

3. **Messages not received**
   - Check if devices are paired
   - Verify callback functions are set up correctly
   - Check RSSI values for signal strength

4. **Web API not working**
   - Ensure AsyncWebServer is properly initialized
   - Check that endpoints are set up before server.begin()
   - Verify JSON format in POST requests

### Debug Output

Enable debug output by setting up the log callback:

```cpp
espnowManager.onLog([](const String& message) {
    Serial.println("[DEBUG] " + message);
});
```

## License

This library is provided as-is for educational and commercial use. Based on the ESP-NOW implementation from the DMD32_HRCxxx project.

## Contributing

Feel free to submit issues, feature requests, and pull requests to improve this library.

## Version History

- **v1.0.0** - Initial release with core ESP-NOW functionality
- **v1.0.1** - Added web API integration and improved error handling