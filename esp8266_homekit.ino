#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <arduino_homekit_server.h>
#include <WiFiClientSecure.h>

// Wi-Fi credentials
const char *ssid = "********";
const char *password = "******";

// Telegram Bot
const char* botToken = "*******"; // Ton token
const char* chatId = "******"; // Ton chat ID

// Inclure les définitions HomeKit en C
extern "C"
{
#include "my_accessory.h"
}

// Pin du capteur PIR
const int pirPin = 13; // D7

// État précédent
bool motionDetected = false;

// Envoi message Telegram
void sendTelegramMessage(const String& message) {
  WiFiClientSecure client;
  client.setInsecure();  // ⚠️ Ignore la vérification SSL (pour tests uniquement)

  HTTPClient http;
  String url = "https://api.telegram.org/bot" + String(botToken) + "/sendMessage?chat_id=" + String(chatId) + "&text=" + message;

  if (http.begin(client, url)) {
    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.printf("[Telegram] Réponse HTTP : %d\n", httpCode);
      String payload = http.getString();
      Serial.println(payload);
    } else {
      Serial.printf("[Telegram] Échec HTTP : %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  } else {
    Serial.println("[Telegram] Échec de la connexion");
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(pirPin, INPUT);

  // Connexion Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connexion au WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
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

    if (motionDetected) {
      sendTelegramMessage("🚨 Mouvement détecté !");
    }
  }

  delay(100);
}