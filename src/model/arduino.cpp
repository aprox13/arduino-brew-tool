#include "model/arduino.h"

#ifdef ARDUINO_BUILD
#include <Arduino.h>
#endif

volatile long arduino::_interrupts = 0;

void arduino::handle_interrupts()
{
  _interrupts++;
}

long arduino::get_interrupts_count()
{
  return _interrupts;
}

// int arduino::digital_read(uint8_t pin) const
// {
// #ifdef ARDUINO_BUILD
//   return digitalRead(pin);
// #else
//   return (active_pins >> pin) & 1;
// #endif
// }

// void arduino::digital_write(uint8_t pin, int value)
// {
// #ifdef ARDUINO_BUILD
//   digitalWrite(pin, value);
// #else
//   active_pins = (active_pins & ~(1 << pin)) | ((1 ? value > 0 : 0) << pin);
// #endif
// }
