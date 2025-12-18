
// ATmega328P SPI MASTER, Mode 3, MSB, SCK = Fosc/16 (1 MHz @16MHz)
// Build with avr-gcc; flash via avrdude. Connect to a slave or probe MOSI/SCK on scope.

#include <avr/io.h>
#include <util/delay.h>

#define SS_PIN   PB2
#define MOSI_PIN PB3
#define MISO_PIN PB4
#define SCK_PIN  PB5

static void spi_init_master_mode3_fosc16(void) {
    // MOSI, SCK, SS as outputs; MISO as input
    DDRB |= (1<<MOSI_PIN) | (1<<SCK_PIN) | (1<<SS_PIN);
    DDRB &= ~(1<<MISO_PIN);
    PORTB |= (1<<SS_PIN); // SS high (no slave selected)

    // SPCR: SPE=1 enable, MSTR=1 master, CPOL=1, CPHA=1 (Mode 3), SPR1:SPR0=01 -> Fosc/16
    SPCR = (1<<SPE) | (1<<MSTR) | (1<<CPOL) | (1<<CPHA) | (1<<SPR0);
    // SPI2X=0 for Fosc/16
    SPSR &= ~(1<<SPI2X);
}

static uint8_t spi_transfer(uint8_t data) {
    SPDR = data;
    while (!(SPSR & (1<<SPIF))); // wait
    return SPDR;
}

intint main(void) {
    spi_init_master_mode3_fosc16();

    while (1) {
        // Select slave (active low)
        PORTB &= ~(1<<SS_PIN);
        spi_transfer(0xA5);
        spi_transfer(0x5A);
        spi_transfer(0x00);
        spi_transfer(0xFF);
        PORTB |= (1<<SS_PIN);

        _delay_ms(500);
    }
