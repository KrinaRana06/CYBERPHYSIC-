
#include <SPI.h>

const uint8_t PIN_SS = 7;  // Any free GPIO used as SS

void setup() {
  pinMode(PIN_SS, OUTPUT);
  digitalWrite(PIN_SS, HIGH); // Deselect slave

  SPI.begin(); // Uses board's hardware SPI pins: MOSI=8, MISO=10, SCK=9
  // Configure: 1 MHz, MSB first, Mode 0
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

  Serial.begin(115200);
  while(!Serial) {}
  Serial.println("MKR1010 SPI Master ready: 1MHz, Mode 0, MSB");
}

void loop() {
  static const uint8_t tx[] = {0x55, 0xAA, 0x01, 0x02, 0x03};

  digitalWrite(PIN_SS, LOW);          // Select slave
  for (uint8_t b : tx) {
    SPI.transfer(b);
  }
  digitalWrite(PIN_SS, HIGH);         // Deselect slave

  Serial.println("Sent: 55 AA 01 02 03");
  delay(500);
}
