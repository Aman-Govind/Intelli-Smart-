/*
 * ESP32 Fan Control with Firebase Realtime Database
 * Controls a relay on GPIO5 based on "fanStatus" value from Firebase
 * 
 * Required Libraries:
 * - FirebaseESP32 (by Mobizt)
 * - WiFi (built-in)
 * 
 * Hardware:
 * - ESP32 Development Board
 * - Relay Module connected to GPIO5
 * - Fan connected to relay
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

// GPIO pin for relay control
const int RELAY_PIN = 5;

// Status tracking
String lastFanStatus = "";
unsigned long lastCheckTime = 0;
const unsigned long CHECK_INTERVAL = 1000; // Check every 1 second

// ========================================
// SETUP FUNCTION
// ========================================

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  Serial.println();
  Serial.println("ESP32 Fan Control Starting...");
  
  // Configure relay pin as output
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Start with relay OFF
  Serial.println("Relay initialized on GPIO5 (OFF)");
  
  // Connect to WiFi
  connectToWiFi();
  
  // Initialize Firebase
  initializeFirebase();
  
  Serial.println("Setup complete! Monitoring fan status...");
  Serial.println("=====================================");
}

// ========================================
// MAIN LOOP
// ========================================

void loop() {
  // Check Firebase every CHECK_INTERVAL milliseconds
  if (millis() - lastCheckTime >= CHECK_INTERVAL) {
    checkFanStatus();
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
        digitalWrite(RELAY_PIN, HIGH);
        Serial.println("Relay ON - Fan activated");
      } else if (currentStatus == "off") {
        digitalWrite(RELAY_PIN, LOW);
        Serial.println("Relay OFF - Fan deactivated");
      } else {
        Serial.print("Unknown status: ");
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
// UTILITY FUNCTIONS
// ========================================

void printStatus() {
  Serial.println("=== Current Status ===");
  Serial.print("WiFi: ");
  Serial.println(WiFi.status() == WL_CONNECTED ? "Connected" : "Disconnected");
  Serial.print("Fan Status: ");
  Serial.println(lastFanStatus);
  Serial.print("Relay State: ");
  Serial.println(digitalRead(RELAY_PIN) ? "ON" : "OFF");
  Serial.println("=====================");
}
