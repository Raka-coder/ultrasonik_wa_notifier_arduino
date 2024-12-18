# Smart Ultrasonik WhatsApp Notifier

## 🌟 Fitur Utama
- [x] Deteksi jarak real-time
- [x] Notifikasi WhatsApp otomatis
- [x] Kontrol interval dinamis

## 🛠 Komponen Elektronik
Daftar Komponen
- Wemos D1 Mini / ESP8266
- Sensor Ultrasonik HC-SR04
- Kabel Jumper
- Kabel USB Micro
- Breadboard
- LED 5v
- BUZZER

## 🔌 Diagram Koneksi
```
Wemos D1 Mini    |   Sensor HC-SR04  |  LED  |  BUZZER  |
---------------------------------------------------------
5V               |   VCC             |       |          |
GND              |   GND             |  GND  |   GND    |
D2               |   TRIG            |       |          |
D1               |   ECHO            |       |          |
D0               |                   |  LED  |          |
D5               |                   |       |  BUZZER  |
```

## 📦 Dependensi / Library
- WiFiClientSecure
- CallMeBot WhatsApp API
  
## 🔒 Lisensi
MIT License
