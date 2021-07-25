#include "controller/brew_controller.h"
#include "logging.h"
#include "sensor/flow_sensor.h"

#define FLOW_SCREEN_UPDATE_MS (100)

brew_controller::brew_controller(screen &screen,
                                 button_controller &btn) : _screen(screen),
                                                           _reset_btn(btn),
                                                           _prev_processed(0) {}

template <class func_t>
void _internal_process(long now, long _delay, long &prev_counter, func_t processor)
{
  if (now - prev_counter > _delay)
  {
    prev_counter = now;
    processor();
  }
}

void brew_controller::process(long now)
{
  _internal_process(now, FLOW_SCREEN_UPDATE_MS, _prev_processed, [&]()
                    { process_tick(now); });
}

void brew_controller::process_tick(long now)
{
  if (_reset_btn.is_pressed())
    flow_sensor::reset();

  _screen.draw_flow_screen(flow_sensor::liters(), 0, flow_sensor::get_ticks());
}
