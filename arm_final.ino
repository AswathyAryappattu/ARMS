#include <Wire.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <Adafruit_MLX90614.h>
#include "MAX30105.h"
#include "heartRate.h"
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5
#define RST_PIN 27
MFRC522 mfrc522(SS_PIN, RST_PIN);

//WiFi credentials
#define WIFI_SSID "your_SSID"
#define WIFI_PASSWORD "your_PASSWORD"

// Firebase credentials
#define API_KEY "your_FIREBASE_API_KEY"
#define DATABASE_URL "your_FIREBASE_DATABASE_URL"
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

MAX30105 particleSensor;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

float baseSystolic = 120;
float baseDiastolic = 80;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    SPI.begin();
    mfrc522.PCD_Init();
    
    // Connect to WiFi
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("Connected!");

    // Initialize Firebase
    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
    
    // Initialize MAX30102
    if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) {
        Serial.println("MAX30102 not found!");
        while (1);
    }
    particleSensor.setup();
    particleSensor.setPulseAmplitudeRed(0x0A);
    particleSensor.setPulseAmplitudeIR(0x0A);
    
    // Initialize MLX90614
    mlx.begin();
}

void loop() {
     Scan RFID card
    if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
        delay(500);
        return;
    }
    String uid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        uid += String(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.print("Scanned UID: ");
    Serial.println(uid);
    mfrc522.PICC_HaltA();
    
    String path = "/patients/" + uid;
    
    // Check if patient exists
    if (!Firebase.RTDB.getString(&fbdo, path + "/name")) {
        Serial.println("New patient detected. Registering...");
        Firebase.RTDB.setString(&fbdo, path + "/name", "Unknown Patient");
        Firebase.RTDB.setInt(&fbdo, path + "/age", 0);
        Firebase.RTDB.setString(&fbdo, path + "/health_status", "Pending");
    }
    
    // Read health vitals
    float bodyTemp = mlx.readObjectTempC();
    long irValue = particleSensor.getIR();
    long redValue = particleSensor.getRed();
    
    static uint32_t lastBeat = 0;
    static int heartRate = 0;
    float spo2 = 0;
    
    if (checkForBeat(irValue)) {
        uint32_t delta = millis() - lastBeat;
        lastBeat = millis();
        heartRate = 60 * 1000 / delta;
    }
    
    if (redValue > 0 && irValue > 0) {
        spo2 = (float)redValue / (float)irValue * 100.0;
        if (spo2 > 100) spo2 = 100;
    }
    
    float systolicBP = baseSystolic + (heartRate - 75) * 0.5;
    float diastolicBP = baseDiastolic + (heartRate - 75) * 0.3;
    
    // Send data to Firebase
    Firebase.RTDB.setFloat(&fbdo, path + "/health_data/body_temperature", bodyTemp);
    Firebase.RTDB.setInt(&fbdo, path + "/health_data/heart_rate", heartRate);
    Firebase.RTDB.setFloat(&fbdo, path + "/health_data/spo2", spo2);
    Firebase.RTDB.setFloat(&fbdo, path + "/health_data/blood_pressure/systolic", systolicBP);
    Firebase.RTDB.setFloat(&fbdo, path + "/health_data/blood_pressure/diastolic", diastolicBP);
    
    Serial.println("Data updated in Firebase");
    delay(3000);
}