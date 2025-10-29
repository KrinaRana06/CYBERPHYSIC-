#include "sam.h"

// PB10 = Arduino D4 on MKR1010
#define LED_PIN 10     

void setup() {
  // Enable PORT hardware clock
  PM->APBBMASK.reg |= PM_APBBMASK_PORT;

  // Initially set PB10 as OUTPUT so LED can turn ON
  PORT->Group[1].DIRSET.reg = (1 << LED_PIN);
}

void loop() {
  // Turn LED ON (only works when OUTPUT)
  PORT->Group[1].OUTSET.reg = (1 << LED_PIN);
  delay(1000);  // 1 second wait

  // Toggle direction to INPUT (LED will float/off)
  PORT->Group[1].DIRCLR.reg = (1 << LED_PIN);
  delay(1000);

  // Toggle direction back to OUTPUT
  PORT->Group[1].DIRSET.reg = (1 << LED_PIN);

  // Turn LED OFF
  PORT->Group[1].OUTCLR.reg = (1 << LED_PIN);
  delay(1000);
}
