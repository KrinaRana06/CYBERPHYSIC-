#include <avr/io.h>
#include <avr/interrupt.h>

void setup() {
    // Set PB0 (pin 8) as input with pull-up
    DDRB &= ~(1 << DDB0);     // Clear PB0 for input
    PORTB |= (1 << PORTB0);   // Enable pull-up resistor

    // Enable pin change interrupt on PB0 (PCINT0)
    PCICR |= (1 << PCIE0);    // Enable pin change interrupt for PCINT[7:0]
    PCMSK0 |= (1 << PCINT0);  // Enable interrupt for PCINT0 (PB0)

    sei(); // Enable global interrupts
}

ISR(PCINT0_vect) {
    if (!(PINB & (1 << PINB0))) {
        // Falling edge detected on PB0
        // Do something here
    }
}

int main(void) {
    setup();
    while (1) {
        // Main loop can do other tasks
    }
}
