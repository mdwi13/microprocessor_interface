#include <ESP8266WiFi.h>
#include <DHT.h>

#define DHTPIN 2           // Pin DHT terhubung ke GPIO2 (D4 pada NodeMCU)
#define DHTTYPE DHT11      // Ubah ke DHT22 jika menggunakan DHT22

const char* ssid = "dcv";            // Nama SSID WiFi
const char* password = "dwi12367";    // Password WiFi
const char* server = "api.thingspeak.com"; // Server ThingSpeak

String apiKey = "WMLDOYT5YMCOBH8P";            // Masukkan API Key ThingSpeak

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(10);
  dht.begin();

  // Menghubungkan ke jaringan WiFi
  Serial.println("Menghubungkan ke WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nTerhubung ke WiFi!");
}

void loop() {
  // Membaca suhu dan kelembaban
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Cek apakah pembacaan berhasil
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Gagal membaca dari sensor DHT!");
    return;
  }

  // Menampilkan data di Serial Monitor
  Serial.print("Kelembaban: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Suhu: ");
  Serial.print(temperature);
  Serial.println(" *C");

  // Mengirim data ke ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {  // Pastikan WiFi terhubung
    WiFiClient client;

    if (client.connect(server, 80)) {   // Koneksi ke server ThingSpeak
      String postStr = apiKey;
      postStr += "&field1=";
      postStr += String(temperature);
      postStr += "&field2=";
      postStr += String(humidity);
      postStr += "\r\n\r\n";

      client.print("POST /update HTTP/1.1\n");
      client.print("Host: " + String(server) + "\n");
      client.print("Connection: close\n");
      client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("Content-Length: ");
      client.print(postStr.length());
      client.print("\n\n");
      client.print(postStr);

      Serial.println("Data dikirim ke ThingSpeak");
    }
    client.stop();
  } else {
    Serial.println("Gagal terhubung ke ThingSpeak");
  }

  delay(1500);  // Mengirim data setiap 20 detik
}
