#include "controller/flow_controller.h"

flow_controller::flow_controller(const arduino &arduino, const int ticks_in_liter) : _ticks_in_liter(ticks_in_liter),
                                                                                     _arduino(arduino),
                                                                                     _prev_ticks(0),
                                                                                     _prev_speed_calc_ms(0),
                                                                                     _speed_in_last_period(0),
                                                                                     _reset_interrupts(0) {}

void flow_controller::process_now(long now)
{

  if (_prev_speed_calc_ms + SPEED_CALC_PERIOD_MS < now)
  {
    _prev_speed_calc_ms = now;
    long now_ticks = _arduino.get_interrupts_count() - _reset_interrupts;

    double ml_in_last_period = (1000.0 * (double)(now_ticks - _prev_ticks)) / _ticks_in_liter;

    double minutes_in_last_period = (double)(now - _prev_speed_calc_ms) / (1000.0 * 60.0);

    _speed_in_last_period = (ml_in_last_period / minutes_in_last_period) / 1000.0; // L/min

    _prev_ticks = now_ticks;
  }
}

flow_state flow_controller::get_flow_state() const
{
  flow_state result = flow_state();

  result.speed = _speed_in_last_period;
  result.ticks = _arduino.get_interrupts_count();
  result.volume = (double)result.ticks / _ticks_in_liter;

  return result;
}

void flow_controller::reset()
{
  _speed_in_last_period = 0;
  _prev_ticks = 0;
  _reset_interrupts = _arduino.get_interrupts_count();
}
