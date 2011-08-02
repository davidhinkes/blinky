#ifndef __LIB_SERIAL_SERIAL_H__
#define __LIB_SERIAL_SERIAL_H__

#include <avr/io.h>

namespace serial {

  void Initialize();
  void Transmit(const uint8_t* data);
  void Transmit(const uint8_t* data, uint16_t length);

}

#endif
