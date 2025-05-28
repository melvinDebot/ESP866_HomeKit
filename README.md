# 📡 ESP8266 HomeKit Motion Sensor

Un projet basé sur un **ESP8266 (NodeMCU/Wemos D1 mini)** pour créer un **capteur de mouvement PIR compatible avec Apple HomeKit**, sans passerelle externe.

Ce projet utilise la bibliothèque [Arduino-HomeKit-ESP8266](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266) pour exposer le capteur à HomeKit en tant qu’accessoire natif.

---

## 🚀 Fonctionnalités

- Détection de mouvement via un capteur PIR
- Intégration native avec l’application **Maison (Home)** d’iOS
- Envoie de **notifications push** lors de détection
- Connexion Wi-Fi configurable dans le code

---

## 🔧 Matériel nécessaire

- 1 × ESP8266 (NodeMCU ou Wemos D1 mini)
- 1 × Capteur de mouvement PIR (ex : HC-SR501)
- 3 × Fils Dupont
- Optionnel : Boîtier imprimé 3D

---

## 🔌 Schéma de câblage

| PIR        | ESP8266 (NodeMCU) |
|------------|------------------|
| VCC        | 3V3              |
| GND        | GND              |
| OUT        | D7 (GPIO13)      |

---

