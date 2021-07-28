#pragma once
#include "model/arduino.h"

#define SPEED_CALC_PERIOD_MS 1000

struct flow_state
{
  long ticks;
  double speed;
  double volume;
};

class flow_controller
{

public:
  flow_controller(const arduino &, const int);

  void process_now(long);

  flow_state get_flow_state() const;

  void reset();

private:
  const double _ticks_in_liter;

  const arduino &_arduino;
  long _prev_ticks;
  long _prev_speed_calc_ms;
  double _speed_in_last_period;
  long _reset_interrupts;
};
