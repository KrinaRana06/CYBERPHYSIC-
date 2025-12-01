
// Pin connected to MOSFET gate
const int fanPin = 9;  // Use PWM-capable pin if needed

void setup() {
  pinMode(fanPin, OUTPUT);
}

void loop() {
  // Turn fan ON
  digitalWrite(fanPin, HIGH);
  delay(6000);  // 6 seconds ON

  // Turn fan OFF
  digitalWrite(fanPin, LOW);
  delay(10000); // 10 seconds OFF
}
