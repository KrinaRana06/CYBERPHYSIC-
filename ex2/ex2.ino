#include <WiFiNINA.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("WiFi module not found!");
  }

  Serial.println("Scanning available networks...");

  int numNetworks = WiFi.scanNetworks();  // FIX: changed uint8_t to int because scanNetworks() returns int in WiFiNINA.h

  // FIX: Added missing variable name "i" and type "int"
  for (int i = 0; i < numNetworks; i++) { // Fixed loop syntax, now correct index type as per library

    Serial.print("Network: ");
    Serial.print(WiFi.SSID(i)); // FIX: Added index parameter 'i' based on function definition in WiFiNINA.h
    Serial.print(" | Signal Strength: ");
    Serial.print(WiFi.RSSI(i)); // FIX: Added index parameter 'i'
    Serial.print(" dBm | Encryption: ");
    Serial.println(WiFi.encryptionType(i)); // FIX: Added index parameter 'i'
  }

  delay(30000); // FIX: Simplified 3 delays of 10 seconds into one delay as instructed (30 seconds)
}
