#include <Servo.h>
#include <DHT.h>        
#define DHTPIN 7         // Pin untuk DHT22
#define DHTTYPE DHT22    // Tipe sensor DHT yang digunakan

DHT dht(DHTPIN, DHTTYPE); // Inisialisasi sensor DHT
Servo servo;

int suhu;            // Menggunakan int untuk suhu
int kelembapan;      // Menggunakan int untuk kelembapan
int lastKelembapan = 0; // Variabel untuk menyimpan kelembapan terakhir

// Array untuk menyimpan posisi servo
int posisiServo[] = {30, 60, 120, 180, 120, 60, 30}; 
int posisiIndex = 0; // Indeks untuk melacak posisi servo

void setup() {
  Serial.begin(9600);
  servo.attach(9); // Menyambungkan servo ke pin 9
  dht.begin();     // Memulai sensor DHT
  servo.write(posisiServo[posisiIndex]); // Posisi awal servo
}

void loop() {
  // Membaca suhu dan kelembapan dari DHT22
  suhu = dht.readTemperature(); 
  kelembapan = dht.readHumidity();
  
  // Cek apakah ada kesalahan saat membaca DHT
  if (isnan(suhu) || isnan(kelembapan)) {
    Serial.println("Gagal membaca dari sensor DHT!");
  } else {
    Serial.print("Suhu: ");
    Serial.print(suhu);
    Serial.print(" °C, Kelembapan: ");
    Serial.print(kelembapan);
    Serial.println(" %");

    // Cek apakah kelembapan berada dalam rentang 60% hingga 100%
    if (kelembapan >= 60 && kelembapan <= 100) {
      // Periksa apakah ada perubahan lebih dari 1% dari kelembapan terakhir
      if (abs(kelembapan - lastKelembapan) >= 1) {
        // Jika ada perubahan, gerakkan servo ke posisi berikutnya dalam urutan
        posisiIndex++; // Increment indeks posisi

        // Cek apakah indeks melebihi batas array
        if (posisiIndex >= sizeof(posisiServo) / sizeof(posisiServo[0])) {
          posisiIndex = 0; // Reset ke awal jika sudah mencapai akhir
        }

        // Gerakkan servo ke posisi baru
        servo.write(posisiServo[posisiIndex]); 
        Serial.print("Servo bergerak ke: ");
        Serial.println(posisiServo[posisiIndex]); // Tampilkan posisi servo di Serial Monitor

        lastKelembapan = kelembapan; // Update kelembapan terakhir

        delay(5000); // Tunggu 5 detik sebelum pembacaan berikutnya
      }
    } else {
      Serial.println("Kelembapan di luar rentang 60% hingga 100%");
    }
  }

  // Delay sebelum pembacaan berikutnya
  delay(500); // Tunggu 5 detik sebelum pembacaan berikutnya
}
