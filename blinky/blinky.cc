#include <string.h>
#include <stdio.h>
#include <math.h>

#include <avr/io.h>
#include <util/delay.h>

void USART_Transmit(const char* data, unsigned int size);
void USART_Transmit(const char* data);
void USART_Init(uint32_t ubrr);

int main() {
  char msg[50];
  float num = 0;
  USART_Init(9600);
  DDRB |= (1<<PB0);
  while (1) {
    PORTB |= (1<<PB0);
    double v = num*num;
    PORTB &= ~(1<<PB0);
    int n = sprintf(msg, "Hello world: %i\r\n", static_cast<int>(v));
    msg[n] = 0;
    USART_Transmit(msg); 
    _delay_ms(100);
    num+=0.1;
  }
  return 0;
}

void USART_Init(uint32_t baud) {
  #define BAUD 9600
  #include <util/setbaud.h>
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
  //UBRR0L = (unsigned char) (0xff & ubrr);
  #if USE_2X
  UCSR0A |= (1 << U2X0);
  #else
  UCSR0A &= ~(1 << U2X0);
  #endif
  UCSR0C = (3<<UCSZ00); // N81.
  UCSR0B = (1<<TXEN0); // Tx on.
}

void USART_Transmit(const char* data) {
  while (*data) {
    while ( !(UCSR0A & (1<<UDRE0)) ) ;
    UDR0 = *data;
    data++;
  }
}

void USART_Transmit(const char* data, unsigned int size) {
  for (unsigned int i = 0; i < size; ++i) {
    while ( ! (UCSR0A & (1<<UDRE0)) ) ;
    UDR0 = data[i];
  }
}
