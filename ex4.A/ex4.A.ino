#include "sam.h"

// PB10 corresponds to Arduino D4 on MKR1010
#define LED_PIN 10     // bit position within Port B
#define LED_PORT 1     // Port B => Group[1]

void setup() {
  // Enable the PORT peripheral clock so the PORT registers are usable
  PM->APBBMASK.reg |= PM_APBBMASK_PORT;  // enables PORT peripheral (bit 3)

  // Configure PB10 as output by setting the bit in DIRSET
  PORT->Group[LED_PORT].DIRSET.reg = (1u << LED_PIN);
}

void loop() {
  // Turn LED ON
  PORT->Group[LED_PORT].OUTSET.reg = (1u << LED_PIN);
  delay(1000);  // 1 second

  // Turn LED OFF
  PORT->Group[LED_PORT].OUTCLR.reg = (1u << LED_PIN);
  delay(1000);  // 1 second
}
