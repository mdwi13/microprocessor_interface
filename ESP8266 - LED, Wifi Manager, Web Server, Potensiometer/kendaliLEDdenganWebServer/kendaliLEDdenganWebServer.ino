#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define LED_PIN 5  // GPIO5 (D1)

const char* ssid = "dcv";            // Nama SSID WiFi lokal
const char* password = "dwi12367";    // Password WiFi

ESP8266WebServer server(80);               // Inisiasi Web Server pada port 80

// Halaman HTML dengan slider untuk kontrol kecerahan
String webpage = R"=====(
<!DOCTYPE html>
<html>
<head>
  <title>LED Brightness Control</title>
</head>
<body>
  <h1>LED Brightness Control with Slider</h1>
  <p>Kecerahan LED: <span id="brightness">0</span></p>
  <input type="range" min="0" max="255" value="0" id="slider" oninput="updateBrightness(this.value)">
  <script>
    function updateBrightness(val) {
      document.getElementById("brightness").innerText = val;
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/setBrightness?value=" + val, true);
      xhr.send();
    }
  </script>
</body>
</html>
)=====";

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  // Menghubungkan ESP8266 ke jaringan WiFi lokal
  Serial.print("Menghubungkan ke WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi terhubung!");

  // Menampilkan IP Address lokal ESP8266
  Serial.print("IP Address lokal: ");
  Serial.println(WiFi.localIP());

  // Rute halaman utama
  server.on("/", []() {
    server.send(200, "text/html", webpage);
  });

  // Rute untuk mengatur kecerahan LED
  server.on("/setBrightness", []() {
    String value = server.arg("value");  // Membaca nilai dari parameter "value"
    int brightness = value.toInt();      // Mengonversi nilai ke integer
    analogWrite(LED_PIN, brightness);    // Mengatur PWM LED sesuai nilai slider
    Serial.print("Brightness set to: ");
    Serial.println(brightness);
    server.send(200, "text/plain", "OK");
  });

  server.begin();
  Serial.println("Webserver dijalankan");
}

void loop() {
  server.handleClient();
}
