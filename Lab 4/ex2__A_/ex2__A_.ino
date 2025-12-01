

const int fanPin = 9; // PWM pin connected to transistor base

void setup() {
  pinMode(fanPin, OUTPUT);
}

void loop() {
  delay(15000); // Wait 15 seconds before starting the fan

  // Gradually increase speed for 5 seconds
  for (int speed = 50; speed <= 255; speed += 50) {
    analogWrite(fanPin, speed); // Set PWM duty cycle
    delay(1000); // Hold this speed for 1 second
  }

  // Turn fan OFF
  analogWrite(fanPin, 0);
}
