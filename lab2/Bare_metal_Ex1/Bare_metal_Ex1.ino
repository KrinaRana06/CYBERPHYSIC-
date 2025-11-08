
  #include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t ledState = 0;

ISR(INT0_vect) {
    ledState ^= 1;
    if (ledState)
        PORTB |= (1 << PORTB5);  // Turn LED on
    else
        PORTB &= ~(1 << PORTB5); // Turn LED off
}

void setup() {
    DDRB |= (1 << DDB5);           // Set PB5 (LED) as output
    DDRD &= ~(1 << DDD2);          // Set PD2 (INT0) as input
    PORTD |= (1 << PORTD2);        // Enable pull-up on PD2

    EICRA |= (1 << ISC01);         // Falling edge trigger
    EICRA &= ~(1 << ISC00);
    EIMSK |= (1 << INT0);          // Enable INT0
    sei();                         // Enable global interrupts
}

int main(void) {
    setup();
    while (1) {
        // Main loop does nothing
    }
}
