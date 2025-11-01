#include "sam.h"

// PB10 corresponds to Arduino D4 on MKR1010
#define LED_PIN   10
#define LED_PORT  1   // Port B = Group[1]

void setup() {
  // Enable the PORT peripheral clock
  PM->APBBMASK.reg |= PM_APBBMASK_PORT;

  // Configure PB10 as OUTPUT
  PORT->Group[LED_PORT].DIRSET.reg = (1 << LED_PIN);
}

void loop() {
  // Turn LED ON
  PORT->Group[LED_PORT].OUTSET.reg = (1 << LED_PIN);
  delay(1000);  // 1 second

  // Turn LED OFF
  PORT->Group[LED_PORT].OUTCLR.reg = (1 << LED_PIN);
  delay(1000);  // 1 second
}
