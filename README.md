# Smart Ultrasonik WhatsApp Notifier

[![CallMeBot](https://img.shields.io/badge/CallMeBot-WhatsApp%20API-25D366?logo=data:image/png;base64,BASE64_ICON)](https://www.callmebot.com/blog/whatsapp-messages-from-esp8266-esp32/)
[![Arduino IDE](https://img.shields.io/badge/Arduino%20IDE-v2.3.4-blue)](https://www.arduino.cc/en/software)

[![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white/)](https://www.arduino.cc/)

[![CallMeBot](https://www.callmebot.com/wp-content/uploads/2019/10/Logo-Negro_x1.png)](https://www.callmebot.com/)


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
  
Komponen Pendukung
- Internet/WiFi
- Kontak CallMeBot
- Nomor Ponsel
- API Key CallMeBot

## 💻 Penggunaan
### Inisialisasi
Mengirim Pesan Ke Whatsapp Dengan ESP8266 / ESP32
Instruksi API Key: [https://www.callmebot.com/blog/free-api-whatsapp-messages/](https://www.callmebot.com/blog/whatsapp-messages-from-esp8266-esp32/)

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
MIT License - Lihat [![License]()

