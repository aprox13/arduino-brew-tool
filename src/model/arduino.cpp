#include "model/arduino.h"
#include <Arduino.h>

volatile long arduino::_interrupts = 0;

void arduino::handle_interrupts()
{
  _interrupts++;
}

long arduino::get_interrupts_count()
{
  return _interrupts;
}
