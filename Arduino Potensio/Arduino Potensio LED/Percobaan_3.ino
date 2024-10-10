#include <Servo.h>   // Library untuk kontrol servo

int potPin = A0;     // Pin analog tempat potensiometer terhubung
int potValue = 0;    // Variabel untuk menyimpan nilai potensiometer
int servoPin = 9;    // Pin PWM tempat servo terhubung
int servoAngle = 0;  // Variabel untuk menyimpan sudut servo

Servo myServo;       // Membuat objek servo

void setup() {
  myServo.attach(servoPin);  // Menghubungkan servo ke pin PWM
  Serial.begin(9600);        // Memulai komunikasi serial pada baud rate 9600
}

void loop() {
  potValue = analogRead(potPin);         // Membaca nilai dari potensiometer (0 hingga 1023)
  
  // Mengonversi nilai potensiometer (0-1023) menjadi sudut servo (0-180)
  servoAngle = map(potValue, 0, 1023, 0, 180);
  
  myServo.write(servoAngle);             // Mengatur posisi servo sesuai sudut
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);                // Menampilkan nilai potensiometer
  Serial.print("  Servo Angle: ");
  Serial.println(servoAngle);            // Menampilkan sudut servo
  
  delay(15);  // Menunggu sedikit sebelum melakukan pembacaan lagi
}
