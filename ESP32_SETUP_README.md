# ESP32 Fan & Light Control Setup Guide

## Overview
This Arduino code controls fan and light relays connected to an ESP32 based on Firebase Realtime Database values. When "fanStatus" is "on", GPIO5 goes HIGH to activate the fan relay. When "lightStatus" is "on", GPIO18 goes HIGH to activate the light relay.

## Hardware Requirements
- ESP32 Development Board
- 2x Relay Modules (5V or 3.3V compatible)
- Fan (AC or DC)
- Light (AC or DC)
- Jumper wires
- Breadboard (optional)

## Wiring
```
Fan Relay:
ESP32 GPIO5  → Fan Relay IN/Control Pin
ESP32 3.3V   → Fan Relay VCC
ESP32 GND    → Fan Relay GND
Fan Live     → Fan Relay NO (Normally Open) terminal
Fan Neutral  → Direct to power source

Light Relay:
ESP32 GPIO18 → Light Relay IN/Control Pin
ESP32 3.3V   → Light Relay VCC
ESP32 GND    → Light Relay GND
Light Live   → Light Relay NO (Normally Open) terminal
Light Neutral → Direct to power source
```

## Software Setup

### 1. Install Required Libraries
In Arduino IDE, go to **Tools > Manage Libraries** and install:
- **FirebaseESP32** by Mobizt

### 2. Configure the Code
Open `esp32_fan_control.ino` and update these variables:

```cpp
// WiFi credentials
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// Firebase configuration
const char* FIREBASE_API_KEY = "YOUR_FIREBASE_API_KEY";
const char* FIREBASE_DATABASE_URL = "YOUR_FIREBASE_DATABASE_URL";
```

### 3. Get Firebase Credentials
1. Go to your Firebase Console
2. Select your project
3. Go to **Project Settings** (gear icon)
4. Scroll down to **Your apps** section
5. Click on **Web app** config
6. Copy the `apiKey` and `databaseURL`

### 4. Upload to ESP32
1. Select your ESP32 board in Arduino IDE
2. Select the correct COM port
3. Click **Upload**

## How It Works

1. **WiFi Connection**: Connects to your specified WiFi network
2. **Firebase Connection**: Establishes connection to Firebase Realtime Database
3. **Status Monitoring**: Checks "fanStatus" and "lightStatus" values every 1 second
4. **Fan Relay Control**: 
   - "on" → GPIO5 HIGH → Fan Relay ON → Fan ON
   - "off" → GPIO5 LOW → Fan Relay OFF → Fan OFF
5. **Light Relay Control**:
   - "on" → GPIO18 HIGH → Light Relay ON → Light ON
   - "off" → GPIO18 LOW → Light Relay OFF → Light OFF
6. **Serial Debugging**: Prints status updates to Serial Monitor

## Serial Monitor Output
```
ESP32 Fan & Light Control Starting...
Fan relay initialized on GPIO5 (OFF)
Light relay initialized on GPIO18 (OFF)
Connecting to WiFi: YourWiFiName
WiFi connected successfully!
IP address: 192.168.1.100
Firebase initialized successfully!
Setup complete! Monitoring fan and light status...
================================================
Fan status changed to: on
Fan relay ON - Fan activated
Light status changed to: on
Light relay ON - Light activated
Fan status changed to: off
Fan relay OFF - Fan deactivated
Light status changed to: off
Light relay OFF - Light deactivated
```

## Troubleshooting

### WiFi Connection Issues
- Verify SSID and password are correct
- Check if WiFi network is 2.4GHz (ESP32 doesn't support 5GHz)
- Ensure WiFi signal strength is adequate

### Firebase Connection Issues
- Verify API key and database URL are correct
- Check Firebase project is active
- Ensure database rules allow read access

### Relay Not Working
- Check wiring connections for both fan and light relays
- Verify relay module voltage compatibility
- Test relays with multimeter
- Ensure fan and light power requirements match relay ratings
- Check that GPIO5 is connected to fan relay and GPIO18 to light relay

## Safety Notes
- Always turn off power before making connections
- Use appropriate relay ratings for your fan's and light's power consumption
- Double-check all connections before powering on
- Consider using fuses for additional protection
- Ensure proper electrical isolation between control and load circuits

## Testing
1. Upload the code to ESP32
2. Open Serial Monitor (115200 baud)
3. Use your web interface to toggle the fan and light
4. Watch Serial Monitor for status updates
5. Verify both relays click and devices turn on/off independently
6. Test both toggles work independently without affecting each other
