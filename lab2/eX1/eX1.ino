
  const int buttonPin =2;
  const int ledPin = 13;

  volatile bool ledState = false;

 void toggleLED(){
    ledState =!ledState;
    digitalWrite (ledPin, ledState);
  }
  void setup() {
pinMode(13,OUTPUT);
pinMode(2,INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(buttonPin),toggleLED,FALLING);
 }

void loop() {
  // update the physial LED state
  
}
