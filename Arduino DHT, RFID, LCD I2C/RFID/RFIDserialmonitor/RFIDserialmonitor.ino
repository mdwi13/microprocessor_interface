#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10  // Pin SDA dari modul RFID
#define RST_PIN 9  // Pin RST dari modul RFID

MFRC522 rfid(SS_PIN, RST_PIN);   // Buat objek MFRC522
MFRC522::MIFARE_Key key;

// UID kartu yang diizinkan (ganti dengan UID kartu Anda)
byte allowedUID[4] = {0xDE, 0xAD, 0xBE, 0xEF};  // Contoh UID (ganti dengan UID kartu Anda)

void setup() {
  Serial.begin(9600);
  SPI.begin();       // Inisialisasi SPI
  rfid.PCD_Init();   // Inisialisasi MFRC522
  Serial.println("Scan kartu RFID Anda...");
}

void loop() {
  // Periksa apakah ada kartu yang terdeteksi
  if ( !rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial() ) {
    return;  // Jika tidak ada kartu yang terdeteksi, kembali ke loop
  }

  // Baca UID dari kartu yang terdeteksi
  Serial.print("UID kartu: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();

  // Cek apakah UID kartu yang terdeteksi cocok dengan UID yang diizinkan
  if (checkUID()) {
    Serial.println("Allow");  // Jika kartu dikenal
  } else {
    Serial.println("Deny");   // Jika kartu asing
  }

  // Hentikan komunikasi dengan kartu
  rfid.PICC_HaltA();
}

bool checkUID() {
  // Cek apakah UID dari kartu terdeteksi cocok dengan UID yang diizinkan
  for (byte i = 0; i < 4; i++) {
    if (rfid.uid.uidByte[i] != allowedUID[i]) {
      return false;  // Jika tidak cocok, return false
    }
  }
  return true;  // Jika cocok, return true
}
