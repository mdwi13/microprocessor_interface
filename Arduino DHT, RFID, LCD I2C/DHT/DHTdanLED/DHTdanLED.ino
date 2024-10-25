#include "DHT.h"

#define DHTPIN 2     // Pin yang terhubung ke DHT22
#define DHTTYPE DHT22   // Tipe sensor DHT
#define LEDPIN 9     // Pin PWM untuk LED

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(LEDPIN, OUTPUT);  // Set LED sebagai output
  analogWrite(LEDPIN, 0);   // Awalnya LED mati (nilai PWM 0)
}

void loop() {
  // Membaca data suhu dari sensor
  float suhu = dht.readTemperature();

  // Cek apakah data dari sensor valid
  if (isnan(suhu)) {
    Serial.println("Gagal membaca dari sensor DHT!");
    return;
  }

  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.println(" °C");

  // Jika suhu lebih dari 30°C, nyalakan LED dengan intensitas maksimal (PWM 255)
  if (suhu > 30.0) {
    analogWrite(LEDPIN, 255); // Nyalakan LED penuh
  } else {
    analogWrite(LEDPIN, 0);   // Matikan LED
  }

  delay(2000);  // Tunggu 2 detik sebelum membaca ulang
}
