#include <string.h>
#include <stdio.h>
#include <math.h>

#include <avr/io.h>
#include <util/delay.h>

#include <lib/serial/serial.h>

int main() {
  char msg[50];
  float num = 0;
  serial::Initialize();
  DDRB |= (1<<PB0);
  while (1) {
    PORTB |= (1<<PB0);
    double v = num*num;
    PORTB &= ~(1<<PB0);
    int n = sprintf(msg, "Hello world: %i\r\n", static_cast<int>(v));
    msg[n] = 0;
    serial::Transmit(reinterpret_cast<uint8_t*>(msg)); 
    _delay_ms(500);
    num+=0.1;
  }
  return 0;
}
