#include <lib/serial/serial.h>

void serial::Initialize() {
  #define BAUD 9600
  #include <util/setbaud.h>
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
  #if USE_2X
  UCSR0A |= (1 << U2X0);
  #else
  UCSR0A &= ~(1 << U2X0);
  #endif
  UCSR0C = (3<<UCSZ00); // N81.
  UCSR0B = (1<<TXEN0); // Tx on.
}

void serial::Transmit(const uint8_t* data) {
  while (*data) {
    while ( !(UCSR0A & (1<<UDRE0)) ) ;
    UDR0 = *data;
    data++;
  }
}

void serial::Transmit(const uint8_t* data, uint16_t size) {
  for (unsigned int i = 0; i < size; ++i) {
    while ( ! (UCSR0A & (1<<UDRE0)) ) ;
    UDR0 = data[i];
  }
}
