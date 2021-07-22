#pragma once
#include "model/arduino.h"

class button_controller
{
public:
  button_controller(const uint8_t, const arduino &, int = 0);
  bool is_pressed() const;

private:
  const arduino &_model;
  const uint8_t _pin;
  const int _pressed_value;
};
