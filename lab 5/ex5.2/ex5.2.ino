#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL
#define BAUD 115200
#define UBRR_VALUE ((F_CPU / 16 / BAUD) - 1) 

void uart_init() {
  UBRR0H = (unsigned char)(UBRR_VALUE >> 8);
  UBRR0L = (unsigned char)UBRR_VALUE;

  UCSR0C = (1 << USBS0) | (1 << UPM01) | (1 << UCSZ01);

  UCSR0B = (1 << TXEN0); 
}

void uart_transmit(unsigned char data) {
  while (!(UCSR0A & (1 << UDRE0))); 

  UDR0 = data;
}

void uart_print(const char *str) {
  for (int i = 0; str[i] != 0; i++) {
    uart_transmit(str[i]);
  }
}

void setup() {
  DDRD |= (1 << PD1); 
  uart_init();
}

void loop() {
  const char* message = "BARE METAL 7E2 TEST\r\n";
  
  uart_print(message);

  _delay_ms(2000); 

}