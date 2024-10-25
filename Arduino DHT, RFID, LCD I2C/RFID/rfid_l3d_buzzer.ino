#include <Servo.h>

Servo myServo;  // Membuat objek servo
int servoPin = 9;  // Pin servo dihubungkan
int sensorPin = 2;  // Pin sensor proximity PNP NC dihubungkan
int sensorState = 0;  // Variabel untuk membaca status sensor

void setup() {
  myServo.attach(servoPin);  // Menghubungkan servo ke pin
  pinMode(sensorPin, INPUT);  // Mengatur sensor pin sebagai input
  myServo.write(90);  // Mengatur servo ke posisi netral (90 derajat)
  Serial.begin(9600);  // Memulai komunikasi serial untuk debugging
}

void loop() {
  sensorState = digitalRead(sensorPin);  // Membaca status sensor

  if (sensorState == LOW) {  // Jika benda organik terdeteksi (misalnya kertas)
    myServo.write(0);  // Servo berputar ke kiri (0 derajat)
    Serial.println("Benda organik terdeteksi, servo bergerak ke kiri (0 derajat)");
  } 
  else if (sensorState == HIGH) {  // Jika benda non-organik terdeteksi (misalnya logam)
    myServo.write(180);  // Servo berputar ke kanan (180 derajat)
    Serial.println("Benda non-organik terdeteksi, servo bergerak ke kanan (180 derajat)");
  }

  delay(500);  // Delay untuk stabilitas pembacaan sensor
}
