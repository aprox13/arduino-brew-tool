#include "model/arduino_proxy.h"

#ifdef ARDUINO_BUILD
#include <Arduino.h>

int arduino_proxy::digital_read(uint8_t pin) const
{
  return digitalRead(pin);
}

void arduino_proxy::digital_write(uint8_t pin, int v)
{
  return digitalWrite(pin, v);
}

#endif