#include <Arduino.h>
#include "sensor/flow_sensor.h"

volatile double flow_sensor::_ticks = 0;
double flow_sensor::_ticks_per_liter = 516;

void flow_sensor::reset() {
  _ticks = 0;
}

void flow_sensor::set_tick_per_liter(const int count) {
  _ticks_per_liter = (double)count;
}


void flow_sensor::on_tick(void) {
  _ticks++;
}

void flow_sensor::attach(const int pin) {
  attachInterrupt(pin, &flow_sensor::on_tick, RISING);
}

double flow_sensor::liters() {
  return _ticks / _ticks_per_liter;
}

long flow_sensor::get_ticks() {
  return (long)_ticks;
}
