#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>

// Pin untuk potensiometer dan DHT22
const int potPin = A0;  // Pin untuk potensiometer
const int dhtPin = D1;  // Pin untuk DHT22 (pin digital)

// DHT22 setup
#define DHTTYPE DHT22
DHT dht(dhtPin, DHTTYPE);

// Ganti dengan SSID dan password WiFi Anda
const char* ssid = "msdimskuyy";
const char* password = "masdimas";

// Ganti dengan API Key dari ThingSpeak
String apiKey = "ARGDYHZO2BP4XRWV";
const char* server = "api.thingspeak.com";

// Fungsi untuk mengirim data ke ThingSpeak
void sendToThingSpeak(int pwmValue, float temperature, float humidity) {
  if (WiFi.status() == WL_CONNECTED) { // Pastikan ESP terhubung ke WiFi
    WiFiClient client;
    HTTPClient http;

    // Kirim data ke field1 (pwm), field2 (suhu), dan field3 (kelembapan)
    String url = String("/update?api_key=") + apiKey +
                 "&field1=" + String(pwmValue) +
                 "&field2=" + String(temperature) +
                 "&field3=" + String(humidity);

    http.begin(client, String("http://") + server + url); // Membuat koneksi ke server ThingSpeak
    int httpCode = http.GET(); // Mengirim permintaan HTTP GET

    if (httpCode > 0) {
      Serial.println("Data berhasil dikirim ke ThingSpeak");
      Serial.println("HTTP Response code: " + String(httpCode));
    } else {
      Serial.println("Gagal mengirim data ke ThingSpeak");
    }

    http.end(); // Mengakhiri koneksi HTTP
  }
}

void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(115200);
  dht.begin(); // Inisialisasi sensor DHT22

  // Hubungkan ke WiFi
  Serial.print("Menghubungkan ke ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi terhubung");
  Serial.print("Alamat IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Membaca nilai potensiometer (nilai PWM)
  int pwmValue = analogRead(potPin); // Membaca nilai dari 0 hingga 1023
  
  // Membaca suhu dan kelembapan dari DHT22
  float temperature = dht.readTemperature(); // Membaca suhu dalam derajat Celcius
  float humidity = dht.readHumidity(); // Membaca kelembapan dalam persen

  // Cek apakah pembacaan suhu dan kelembapan valid
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Gagal membaca data dari DHT22!");
    temperature = 0; // Set nilai default jika pembacaan gagal
    humidity = 0;
  }

  // Menampilkan nilai di Serial Monitor
  Serial.print("Nilai PWM: ");
  Serial.println(pwmValue);
  Serial.print("Suhu: ");
  Serial.println(temperature);
  Serial.print("Kelembapan: ");
  Serial.println(humidity);

  // Mengirim nilai PWM, suhu, dan kelembapan ke ThingSpeak
  sendToThingSpeak(pwmValue, temperature, humidity);

  // Tunggu 5 detik sebelum mengirim data lagi (sesuai rate limit ThingSpeak)
  delay(5000);
}
