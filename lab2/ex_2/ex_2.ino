const int pin8 = 8;
bool lastState = HIGH;

void setup() {
  pinMode(pin8, INPUT_PULLUP); // Enable internal pull-up resistor
  Serial.begin(9600);
}

void loop() {
  bool currentState = digitalRead(pin8);
  if (lastState == HIGH && currentState == LOW) {
    // Falling edge detected
    Serial.println("Interrupt: Pin 8 changed from HIGH to LOW");
  }
  lastState = currentState;
  delay(10); // Debounce delay
}
