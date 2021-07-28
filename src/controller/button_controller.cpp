#include "controller/button_controller.h"

button_controller::button_controller(const uint8_t pin, const arduino &model, int pressed_value) : _model(model), _pin(pin), _pressed_value(pressed_value) {}

bool button_controller::is_pressed() const
{
  return _model.digital_read(_pin) == _pressed_value;
}
