#pragma once
#include "model/arduino.h"

class arduino_proxy : public arduino
{
  int digital_read(uint8_t) const;
  void digital_write(uint8_t, int);
};
