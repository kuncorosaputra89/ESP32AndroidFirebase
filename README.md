# ESP32AndroidFirebase
Project ini berisikan program untuk membangun aplikasi sistem internet of things untuk sensor monitoring dan kendali ESP32 dengan aplikasi Android yang terhung dengan Realtime Database Firebase 

Sistem yang dibuat terdiri dari
1. Aplikasi Android
2. Rangkaian Sensor yang terhubung dengan ESP32
3. Firebase Project

Untuk program pada ESP32, membutuhkan library tambahan untuk:
1. Sensor Ultrasonic : https://github.com/Martinsos/arduino-lib-hc-sr04
2. Firebase ESP32 : https://github.com/mobizt

Kebutuhan Hardware
- nodeMCU-32S
- Sensor: 
    1x HC-SR04 Ultrasonic (sensor jarak)
    1x LDR (sensor cahaya)
    1x Passive Infrared (sensor gerakan)
- 2x LED
- Kabel Jumper
- Project Board
