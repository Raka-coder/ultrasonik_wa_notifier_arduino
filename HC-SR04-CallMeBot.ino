/*============================================================
 *
 *  Sistem Pemantauan Jarak Berbasis IoT
 *
 *============================================================
 * 
 * @Informasi Umum
 * --------------
 * Nama        : Ultrasonik WhatsApp Notifier
 * Status      : Aktif Pengembangan
 * 
 * @Pembuat
 * --------
 * Nama        : [Raka Restu Saputra]
 * 
 * @Tanggal
 * --------
 * Dibuat      : 18/12/2024
 * 
 * @Sumber Daya
 * ------------
 * Mikrokontroller : ESP8266 (Wemos D1 Mini)
 * Sensor          : HC-SR04 Ultrasonic
 * Aktuator        : - LED
 *                   - BUZZER
 * Komunikasi      : WhatsApp API (CallMeBot)
 * 
 * @Dokumentasi
 * ------------
 * GitHub       : https://github.com/Raka-coder/ultrasonik_wa_notifier_arduino
 * 
 * @Lisensi
 * --------
 * MIT License
 * Copyright (c) [2024] [Raka]
 * 
 *
 * @Dependensi / Library
 * ---------------------
 * - WiFiClientSecure
 * - CallMeBot WhatsApp API
 *
 *============================================================
 */



// Library
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

// Konfigurasi WiFi
const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

// Konfigurasi WhatsApp CallMeBot
const String nomorHP = "62XXXXXXXXXX";  // Nomor HP dengan kode negara
const String apiKey = "XXXXXXX"; // API Key CallMeBot

// Device Pin
#define TRIG_PIN D2
#define ECHO_PIN D1
#define LED_PIN D0
#define BUZZ_PIN D5

// Variabel Global
WiFiClientSecure client;
unsigned long terakhirNotif = 0;
const long intervalNotif = 2000;  // Jeda 2 detik

void setup() {
  Serial.begin(9600);
  // Koneksi Pin
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZ_PIN, OUTPUT);

  // Koneksi WiFi
  koneksiWiFi();
}

void loop() {
  long jarak = bacaJarak();

  if(jarak < 10){               // Jarak kurang dari 10 cm
    kirimPesanWhatsApp(jarak);
    digitalWrite(LED_PIN, HIGH);
    tone(D5, 700, 500);
  }else{
    digitalWrite(LED_PIN, LOW);
    noTone(D5);
  }
  
  delay(1000);
}

long bacaJarak() {
  // Kirim sinyal trig
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Baca sinyal echo
  long durasi = pulseIn(ECHO_PIN, HIGH);
  
  // Hitung jarak
  long jarak = durasi * 0.034 / 2;
  
  return jarak;
}

// Fungsi Koneksi WiFi
void koneksiWiFi() {
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nTerhubung ke WiFi");
  Serial.print("Alamat IP: ");
  Serial.println(WiFi.localIP());
}

// Fungsi Kirim Pesan WhatsApp
void kirimPesanWhatsApp(long jarak) {
  unsigned long waktuSekarang = millis();
  
  // Cek interval notifikasi
  if (waktuSekarang - terakhirNotif >= intervalNotif) {
    // Persiapkan URL
    String url = "https://api.callmebot.com/whatsapp.php?phone=" + nomorHP + 
                "&apikey=" + apiKey + 
                "&text=";
    
    // Buat Pesan
    String pesan = "PERINGATAN%21%0A";
    pesan += "Sensor+Mendeteksi+Adanya+Objek%0A";
    pesan += "Jarak+Terdeteksi%3A+" + String(jarak) + "+cm%0A";
    
    // Tambahkan kategori bahaya
    if (jarak < 10) {
      
    } else {
      pesan += "Objek+Mendekati+Zona+Berbahaya%21";
    }
    
    // Gabungkan URL
    String fullUrl = url + pesan;
    
    // Kirim Pesan
    client.setInsecure();
    HTTPSRedirect(fullUrl);
    
    // Update waktu terakhir notifikasi
    terakhirNotif = waktuSekarang;
    
    Serial.println("Pesan WhatsApp Terkirim!");
  }
}

// Fungsi Redirect HTTPS
void HTTPSRedirect(String url) {
  const char* host = "api.callmebot.com";
  const int httpsPort = 443;
  
  if (!client.connect(host, httpsPort)) {
    Serial.println("Koneksi Gagal");
    return;
  }
  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Timeout Koneksi!");
      client.stop();
      return;
    }
  }
  
  // Baca Respon
  while (client.available()) {
    String line = client.readStringUntil('\n');
    Serial.println(line);
  }
}

// Fungsi Debug
void debugLog(String pesan) {
  #ifdef DEBUG_MODE
    Serial.println(pesan);
  #endif
}