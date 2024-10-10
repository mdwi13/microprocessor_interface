int potPin = A0;         // Pin analog tempat potensiometer terhubung
int ledPin = 9;          // Pin PWM tempat LED terhubung
int potValue = 0;        // Variabel untuk menyimpan nilai potensiometer
float voltage = 0.0;     // Variabel untuk menyimpan tegangan
int ledBrightness = 0;   // Variabel untuk menyimpan kecerahan LED

void setup() {
  Serial.begin(9600);    // Memulai komunikasi serial pada baud rate 9600
  pinMode(ledPin, OUTPUT); // Mengatur pin LED sebagai output
}

void loop() {
  potValue = analogRead(potPin);          // Membaca nilai dari potensiometer (0 hingga 1023)
  voltage = potValue * (5.0 / 1023.0);    // Mengonversi nilai potensiometer ke tegangan (0 hingga 5V)
  
  Serial.print("Voltage: ");
  Serial.print(voltage);                  // Menampilkan tegangan ke Serial Monitor
  Serial.println(" V");                   // Menambahkan satuan "V"
  
  // Mengonversi nilai potensiometer (0-1023) menjadi nilai PWM (0-255)
  ledBrightness = map(potValue, 0, 1023, 0, 255);
  
  analogWrite(ledPin, ledBrightness);     // Mengatur kecerahan LED sesuai nilai PWM
  
  delay(500);                             // Jeda 500ms sebelum pembacaan ulang
}
