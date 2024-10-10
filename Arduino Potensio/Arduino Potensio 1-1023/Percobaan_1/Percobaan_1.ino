int potPin = A0;         // Pin analog tempat potensiometer terhubung
int potValue = 0;        // Variabel untuk menyimpan nilai potensiometer
float voltage = 0.0;     // Variabel untuk menyimpan tegangan

void setup() {
  Serial.begin(9600);    // Memulai komunikasi serial pada baud rate 9600
}

void loop() {
  potValue = analogRead(potPin);          // Membaca nilai dari potensiometer (0 hingga 1023)
  voltage = potValue * (5.0 / 1023.0);    // Mengonversi nilai potensiometer ke tegangan (0 hingga 5V)
  
  Serial.print("Voltage: ");
  Serial.print(voltage);                  // Menampilkan tegangan ke Serial Monitor
  Serial.println(" V");                   // Menambahkan satuan "V"
  
  delay(500);                             // Memberikan jeda 500ms sebelum membaca lagi
}
