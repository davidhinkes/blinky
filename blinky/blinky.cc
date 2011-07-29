#include <string.h>

#include <avr/io.h>
#include <util/delay.h>

void USART_Transmit(const char* data, unsigned int size);
void USART_Init(uint32_t ubrr);

static char msg[] = "Hello world!";

int main() {
  USART_Init(9600);
  DDRB |= (1<<PB0);
  while (1) {
    PORTB |= (1<<PB0);
    USART_Transmit(msg, strlen(msg)); 
    _delay_ms(1000);
    PORTB &= ~(1<<PB0);
  }
  return 0;
}

void USART_Init(uint32_t baud) {
  uint16_t ubrr = F_CPU / (16 * baud) - 1;
  UBRR0H = (unsigned char) (ubrr>>8);
  UBRR0L = (unsigned char) (0xff & ubrr);
  UCSR0C = (3<<UCSZ00); // N81.
  UCSR0B = (1<<TXEN0); // Tx on.
}

void USART_Transmit(char data) {
  while ( !(UCSR0A & (1<<UDRE0)) ) ;
  UDR0 = data;
}

void USART_Transmit(const char* data, unsigned int size) {
  for (unsigned int i = 0; i < size; ++i) {
    while ( ! (UCSR0A & (1<<UDRE0)) ) ;
    UDR0 = data[i];
  }
}
