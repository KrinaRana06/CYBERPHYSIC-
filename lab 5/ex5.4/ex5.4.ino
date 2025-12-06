

#ifndef F_CPU
#define F_CPU 16000000L
#endif

#include <avr/io.h>
#include <util/delay.h>

// Pins:
// TRIG = D8 (PB0), ECHO = D7 (PD7), FAN PWM = D9 (OC1A/PB1)

// -------- PWM init: Timer1 Fast PWM 8-bit on OC1A (D9) --------
static void pwm_init(void) {
    DDRB |= (1 << PB1);                       // D9 as output (OC1A)
    // Fast PWM 8-bit: WGM10=1, WGM12=1
    // Non-inverting output on OC1A: COM1A1=1
    // Prescaler 64: CS11=1, CS10=1 (~976 Hz PWM)
    TCCR1A = (1 << COM1A1) | (1 << WGM10);
    TCCR1B = (1 << WGM12)  | (1 << CS11) | (1 << CS10);
    OCR1A = 0;                                // Start fan OFF
}

static inline void pwm_set(uint8_t duty) { OCR1A = duty; }

// -------- HC-SR04 init & measurement --------
static void hcsr04_init(void) {
    DDRB |=  (1 << PB0);                      // TRIG output
    PORTB &= ~(1 << PB0);                     // TRIG low
    DDRD &= ~(1 << PD7);                      // ECHO input
    // No pull-up; sensor drives the line
}

// Return echo high width in microseconds (0 on timeout)
static uint16_t echo_high_us(void) {
    // Ensure line is low (if currently high)
    uint32_t to = 30000UL;
    while ((PIND & (1 << PD7)) && to--) _delay_us(1);
    if (!to) return 0;

    // Wait for rising edge
    to = 30000UL;
    while (!(PIND & (1 << PD7)) && to--) _delay_us(1);
    if (!to) return 0;

    // Measure high width
    uint32_t w = 0;
    while (PIND & (1 << PD7)) {
        _delay_us(1);
        if (++w > 30000UL) break;
    }
    return (uint16_t)w;                       // capped at 30 ms
}

// Distance in cm (0xFFFF on timeout/no echo)
static uint16_t read_distance_cm(void) {
    // Trigger: ≥10 µs HIGH
    PORTB |=  (1 << PB0);
    _delay_us(12);
    PORTB &= ~(1 << PB0);

    uint16_t echo_us = echo_high_us();
    if (echo_us == 0) return 0xFFFF;
    return (uint16_t)(echo_us / 58U);         // µs → cm
}

// -------- Distance → PWM mapping (rules from the lab) --------
// ≤ 4 cm  -> 255 (full)
// 4..20 cm -> linearly map to 255..64 (keeps fan from stalling)
// > 20 cm or timeout -> 0 (off)
static uint8_t distance_to_pwm(uint16_t d) {
    if (d == 0xFFFF || d >= 20) return 0;     // far/off
    if (d <= 4) return 255;                   // near/full
    // Integer math: 4..20 -> 255..64 (drop of 191 over 16 cm)
    uint16_t step = (uint16_t)(d - 4);        // 0..16
    uint16_t drop = (step * 191U) / 16U;      // 0..191
    uint16_t s = 255U - drop;                 // 255..64
    return (uint8_t)s;
}

int main(void) {
    pwm_init();
    hcsr04_init();

    for (;;) {
        uint16_t d = read_distance_cm();
        uint8_t duty = distance_to_pwm(d);
        pwm_set(duty);

        // Read every 2 seconds
        for (uint16_t i = 0; i < 200; ++i) _delay_ms(10);
    }
}
