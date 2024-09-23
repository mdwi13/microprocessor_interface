// Pin definisi
const int led1 = 4;
const int led2 = 3;
const int led3 = 2;
const int buttonPin = 7;

int buttonState = 0;

void setup() {
  // Atur pin LED sebagai output
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  // Atur pin push button sebagai input
  pinMode(buttonPin, INPUT);
}

void loop() {
  // Baca status push button
  buttonState = digitalRead(buttonPin);

  // Jika tombol ditekan, jalankan LED blink dari kiri ke kanan
  if (buttonState == HIGH) {
    digitalWrite(led1, HIGH);
    delay(500);
    digitalWrite(led1, LOW);

    digitalWrite(led2, HIGH);
    delay(500);
    digitalWrite(led2, LOW);

    digitalWrite(led3, HIGH);
    delay(500);
    digitalWrite(led3, LOW);
  } 
  // Jika tombol tidak ditekan, matikan semua LED
  else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
}