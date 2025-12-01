
const int fanPin = 9;    // PWM pin
const int potPin = A0;   // Potentiometer pin

void setup() {
  pinMode(fanPin, OUTPUT);
}

void loop() {
  delay(15000); // Wait 15 seconds
  int potValue = analogRead(potPin); // Read potentiometer (0-1023)
  int pwmValue = map(potValue, 0, 1023, 0, 255); // Convert to PWM range
  analogWrite(fanPin, pwmValue); // Set fan speed
  delay(5000); // Fan runs for 5 seconds
  analogWrite(fanPin, 0); // Turn off fan
}
