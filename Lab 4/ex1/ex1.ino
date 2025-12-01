// Exercise 1A: LED ON 3s, OFF 1s
int ledPin = 9;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(3000);
  digitalWrite(ledPin, LOW);
  delay(1000);
}
