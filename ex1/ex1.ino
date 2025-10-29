
// Define the pins used

const int ledPin = 6;     // LED connected to Digital Pin 6

const int potPin = A1;    // Potentiometer connected to Analog Pin A1



// Variables for timing the blink and the read/print operations

// Using the millis() function for non-blocking timing is essential for doing both tasks concurrently.

unsigned long previousMillisBlink = 0; // Stores the last time the LED was updated

unsigned long previousMillisRead = 0;  // Stores the last time the pot value was read and printed

const long blinkInterval = 500;        // Interval for blinking (500 ms)

const long readInterval = 1000;        // Interval for reading and printing (1000 ms = 1 second)



// State variable for the LED

int ledState = LOW;

void setup() {

  // 1. Initialize the LED pin as an output

  pinMode(ledPin, OUTPUT);

  // 2. Initialize serial communication at 9600 baud

  Serial.begin(9600);

  analogReadResolution(12);

  Serial.println(" Arduino Sketch Started (D6 Blink / A1 Read)");

  Serial.println("Potentiometer readings will be printed every second (Range 0-4095).");

}

void loop() {

  // Get the current time

  unsigned long currentMillis = millis();

  // 1. LED Blinking Task (500 ms ON / 500 ms OFF)

  if (currentMillis - previousMillisBlink >= blinkInterval) {

    // Saving the current time for the next comparison

    previousMillisBlink = currentMillis;

    //Toggle the LED state

    if (ledState == LOW) {

      ledState = HIGH;

    } else {

      ledState = LOW;

    }

    // Apply the new state to the LED pin

    digitalWrite(ledPin, ledState);

  }

  // 2. Potentiometer Reading and Serial Print Task (Once per second)

  if (currentMillis - previousMillisRead >= readInterval) {

    // Saving the current time for the next comparison

    previousMillisRead = currentMillis;

    // Read the raw analog value from A1 (0-4095 on MKR1010)

    int rawValue = analogRead(potPin);

    // Print the raw value to the Serial Monitor

    Serial.print("Potentiometer Raw Value(0-4095): ");

    Serial.println(rawValue);

  }

}
