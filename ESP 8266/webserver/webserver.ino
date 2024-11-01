#include <ESP8266WiFi.h>

const char *ssid = "dcv";
const char *password = "dwi12367";

WiFiServer server(80);

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    // Tunggu sampai ESP8266 terhubung ke WiFi
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Sabar Sedang Menghubungkan ya^^...");
    }

    // Tampilkan alamat IP setelah terhubung
    Serial.println("Sudah Terhubung WIFInya^^");
    Serial.print("Alamat IP ESP8266^^: ");
    Serial.println(WiFi.localIP());
    
    server.begin();
}

void loop() {
    WiFiClient client = server.available();
    if (client) {
        Serial.println("Client connected");
        client.println("<html><body><h1>Selamat Datang di WEB yang kita rancang untuk tugas!</h1></body></html>");
        client.println("<html><body><h1>Hai Aku DZIKRI dengan NIM 4.31.23.0.12^^</h1></body></html>");
        client.println("<html><body><h1>Hai Aku DWI dengan NIM 4.31.23.0.13^</h1></body></html>");
        delay(1);
        delay(1);
        client.stop();
        Serial.println("Client disconnected");
    }
}