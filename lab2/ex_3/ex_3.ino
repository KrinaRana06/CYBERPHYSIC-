#include <avr/io.h>
#include <avr/interrupt.h>

void timer1_init() {
    // Set CTC mode: WGM12 = 1, WGM13:0 = 0100
    TCCR1B |= (1 << WGM12);
    TCCR1A &= ~((1 << WGM11) | (1 << WGM10));

    // Set compare match value for 1 second interval
    // 16 MHz / 1024 = 15625 ticks per second
    OCR1A = 15625;

    // Enable Timer1 Compare Match A interrupt
    TIMSK1 |= (1 << OCIE1A);

    // Set prescaler to 1024: CS12 = 1, CS11 = 0, CS10 = 1
    TCCR1B |= (1 << CS12) | (1 << CS10);

    // Enable global interrupts
    sei();
}

void gpio_init() {
    // Set pin PB5 (Arduino pin 13) as output
    DDRB |= (1 << DDB5);
}

ISR(TIMER1_COMPA_vect) {
    // Toggle LED on PB5
    PORTB ^= (1 << PORTB5);
}

int main(void) {
    gpio_init();
    timer1_init();

    while (1) {
        // Main loop does nothing, LED toggling is handled by ISR
    }
}
