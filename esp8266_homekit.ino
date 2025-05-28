#include <ESP8266WiFi.h>
#include <arduino_homekit_server.h>

// Wi-Fi credentials
const char* ssid = "*******";
const char* password = "******";

// Inclure les définitions HomeKit en C
extern "C" {
  #include "my_accessory.h"
}

// Pin du capteur PIR
const int pirPin = 13; // D7

// État précédent
bool motionDetected = false;

void setup() {
  Serial.begin(115200);
  pinMode(pirPin, INPUT);

  // Connexion Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connexion au WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnecté au WiFi");

  // Démarrage HomeKit
  arduino_homekit_setup(&config);
}

void loop() {
  arduino_homekit_loop();

  bool currentMotion = digitalRead(pirPin);

  if (currentMotion != motionDetected) {
    motionDetected = currentMotion;
    cha_motion_detected.value.bool_value = motionDetected;
    homekit_characteristic_notify(&cha_motion_detected, cha_motion_detected.value);
    Serial.print("Présence : ");
    Serial.println(motionDetected ? "Détectée" : "Aucune");
  }

  delay(100);
}