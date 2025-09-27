# ESP32 Fan Control Setup Guide

## Overview
This Arduino code controls a fan relay connected to an ESP32 based on Firebase Realtime Database values. When "fanStatus" is "on", GPIO5 goes HIGH to activate the relay. When "off", GPIO5 goes LOW.

## Hardware Requirements
- ESP32 Development Board
- Relay Module (5V or 3.3V compatible)
- Fan (AC or DC)
- Jumper wires
- Breadboard (optional)

## Wiring
```
ESP32 GPIO5 → Relay IN/Control Pin
ESP32 3.3V  → Relay VCC
ESP32 GND   → Relay GND
Fan Live    → Relay NO (Normally Open) terminal
Fan Neutral → Direct to power source
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
3. **Status Monitoring**: Checks "fanStatus" value every 1 second
4. **Relay Control**: 
   - "on" → GPIO5 HIGH → Relay ON → Fan ON
   - "off" → GPIO5 LOW → Relay OFF → Fan OFF
5. **Serial Debugging**: Prints status updates to Serial Monitor

## Serial Monitor Output
```
ESP32 Fan Control Starting...
Relay initialized on GPIO5 (OFF)
Connecting to WiFi: YourWiFiName
WiFi connected successfully!
IP address: 192.168.1.100
Firebase initialized successfully!
Setup complete! Monitoring fan status...
=====================================
Fan status changed to: on
Relay ON - Fan activated
Fan status changed to: off
Relay OFF - Fan deactivated
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
- Check wiring connections
- Verify relay module voltage compatibility
- Test relay with multimeter
- Ensure fan power requirements match relay rating

## Safety Notes
- Always turn off power before making connections
- Use appropriate relay rating for your fan's power consumption
- Double-check all connections before powering on
- Consider using a fuse for additional protection

## Testing
1. Upload the code to ESP32
2. Open Serial Monitor (115200 baud)
3. Use your web interface to toggle the fan
4. Watch Serial Monitor for status updates
5. Verify relay clicks and fan turns on/off
