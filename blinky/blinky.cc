
#include <avr/io.h>
#include <util/delay.h>

void USART_Transmit(const char* data, unsigned int size);
void USART_Init(unsigned int ubrr);

int main() {
  const unsigned int BAUD = 9600;
  const unsigned int MYUBRR = 1843200 / 16 / BAUD - 1;
  USART_Init(MYUBRR);
  DDRB |= (1<<PB0);
  while (1) {
    USART_Transmit("hello", 6); 
    PORTB |= (1<<PB0);
    for (int i = 0; i < 100; ++i) {
      float a = 5.5;
      float b = 2.2;
      float c = a*b;
    }
    _delay_ms(1000);
    PORTB &= ~(1<<PB0);
    _delay_ms(1000);
  }
  return 0;
}

void USART_Init(unsigned int ubrr) {
  UBRR0H = (unsigned char) (ubrr>>8);
  UBRR0L = (unsigned char) (ubrr);
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit(char data) {
  while ( !(UCSR0A & (1<<UDRE0)) ) ;
  UDR0 = data;
}

void USART_Transmit(const char* data, unsigned int size) {
  for (unsigned int i = 0; i < size; ++i) {
    USART_Transmit(data[i]);
  }
}

