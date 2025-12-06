void setup() {
  Serial.begin(38400);
  delay(100);
}

void loop() {
  const char* message = "HELLO UART 38400";

  Serial.println(message);

  delay(2000);

}