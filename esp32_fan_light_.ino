/*
 * ESP32 Fan & Light Control with Firebase Realtime Database
 * Controls relays on GPIO5 (fan) and GPIO18 (light) based on Firebase values
 * 
 * Required Libraries:
 * - FirebaseESP32 (by Mobizt)
 * - WiFi (built-in)
 * 
 * Hardware:
 * - ESP32 Development Board
 * - Relay Module 1 connected to GPIO5 (Fan)
 * - Relay Module 2 connected to GPIO18 (Light)
 * - Fan and Light connected to respective relays
 */

#include <WiFi.h>
#include <FirebaseESP32.h>

// ========================================
// CONFIGURATION - Replace with your values
// ========================================

// WiFi credentials
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// Firebase configuration
const char* FIREBASE_API_KEY = "YOUR_FIREBASE_API_KEY";
const char* FIREBASE_DATABASE_URL = "YOUR_FIREBASE_DATABASE_URL";

// ========================================
// GLOBAL VARIABLES
// ========================================

FirebaseData firebaseData;
FirebaseJson json;

// GPIO pins for relay control
const int FAN_RELAY_PIN = 5;    // Fan relay on GPIO5
const int LIGHT_RELAY_PIN = 18; // Light relay on GPIO18

// Status tracking
String lastFanStatus = "";
String lastLightStatus = "";
unsigned long lastCheckTime = 0;
const unsigned long CHECK_INTERVAL = 1000; // Check every 1 second

// ========================================
// SETUP FUNCTION
// ========================================

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  Serial.println();
  Serial.println("ESP32 Fan & Light Control Starting...");
  
  // Configure relay pins as output
  pinMode(FAN_RELAY_PIN, OUTPUT);
  pinMode(LIGHT_RELAY_PIN, OUTPUT);
  digitalWrite(FAN_RELAY_PIN, LOW);    // Start with fan relay OFF
  digitalWrite(LIGHT_RELAY_PIN, LOW);  // Start with light relay OFF
  Serial.println("Fan relay initialized on GPIO5 (OFF)");
  Serial.println("Light relay initialized on GPIO18 (OFF)");
  
  // Connect to WiFi
  connectToWiFi();
  
  // Initialize Firebase
  initializeFirebase();
  
  Serial.println("Setup complete! Monitoring fan and light status...");
  Serial.println("================================================");
}

// ========================================
// MAIN LOOP
// ========================================

void loop() {
  // Check Firebase every CHECK_INTERVAL milliseconds
  if (millis() - lastCheckTime >= CHECK_INTERVAL) {
    checkFanStatus();
    checkLightStatus();
    lastCheckTime = millis();
  }
  
  // Small delay to prevent overwhelming the system
  delay(100);
}

// ========================================
// WIFI CONNECTION
// ========================================

void connectToWiFi() {
  Serial.print("Connecting to WiFi: ");
  Serial.println(WIFI_SSID);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.println("WiFi connected successfully!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println();
    Serial.println("WiFi connection failed!");
    Serial.println("Please check your credentials and try again.");
    while (true) {
      delay(1000);
    }
  }
}

// ========================================
// FIREBASE INITIALIZATION
// ========================================

void initializeFirebase() {
  Serial.println("Initializing Firebase...");
  
  // Configure Firebase
  Firebase.begin(FIREBASE_DATABASE_URL, FIREBASE_API_KEY);
  Firebase.reconnectWiFi(true);
  
  // Set timeout values
  firebaseData.setResponseSize(1024);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteTimeout(firebaseData, 1000 * 60);
  
  Serial.println("Firebase initialized successfully!");
}

// ========================================
// FAN STATUS MONITORING
// ========================================

void checkFanStatus() {
  if (Firebase.getString(firebaseData, "/fanStatus")) {
    String currentStatus = firebaseData.stringData();
    
    // Only update if status has changed
    if (currentStatus != lastFanStatus) {
      lastFanStatus = currentStatus;
      
      Serial.print("Fan status changed to: ");
      Serial.println(currentStatus);
      
      // Control relay based on status
      if (currentStatus == "on") {
        digitalWrite(FAN_RELAY_PIN, HIGH);
        Serial.println("Fan relay ON - Fan activated");
      } else if (currentStatus == "off") {
        digitalWrite(FAN_RELAY_PIN, LOW);
        Serial.println("Fan relay OFF - Fan deactivated");
      } else {
        Serial.print("Unknown fan status: ");
        Serial.println(currentStatus);
      }
    }
  } else {
    Serial.println("Failed to read fan status from Firebase");
    Serial.print("Error: ");
    Serial.println(firebaseData.errorReason());
  }
}

// ========================================
// LIGHT STATUS MONITORING
// ========================================

void checkLightStatus() {
  if (Firebase.getString(firebaseData, "/lightStatus")) {
    String currentStatus = firebaseData.stringData();
    
    // Only update if status has changed
    if (currentStatus != lastLightStatus) {
      lastLightStatus = currentStatus;
      
      Serial.print("Light status changed to: ");
      Serial.println(currentStatus);
      
      // Control relay based on status
      if (currentStatus == "on") {
        digitalWrite(LIGHT_RELAY_PIN, HIGH);
        Serial.println("Light relay ON - Light activated");
      } else if (currentStatus == "off") {
        digitalWrite(LIGHT_RELAY_PIN, LOW);
        Serial.println("Light relay OFF - Light deactivated");
      } else {
        Serial.print("Unknown light status: ");
        Serial.println(currentStatus);
      }
    }
  } else {
    Serial.println("Failed to read light status from Firebase");
    Serial.print("Error: ");
    Serial.println(firebaseData.errorReason());
  }
}

// ========================================
// UTILITY FUNCTIONS
// ========================================

void printStatus() {
  Serial.println("=== Current Status ===");
  Serial.print("WiFi: ");
  Serial.println(WiFi.status() == WL_CONNECTED ? "Connected" : "Disconnected");
  Serial.print("Fan Status: ");
  Serial.println(lastFanStatus);
  Serial.print("Fan Relay State: ");
  Serial.println(digitalRead(FAN_RELAY_PIN) ? "ON" : "OFF");
  Serial.print("Light Status: ");
  Serial.println(lastLightStatus);
  Serial.print("Light Relay State: ");
  Serial.println(digitalRead(LIGHT_RELAY_PIN) ? "ON" : "OFF");
  Serial.println("=====================");
}
