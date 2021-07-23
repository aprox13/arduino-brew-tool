#include "controller/brew_controller.h"
#include "logging.h"


brew_controller::brew_controller(screen &screen,
                                 button_controller &btn,
                                 flow_controller &fc,
                                 long delay) : _screen(screen),
                                               _reset_btn(btn),
                                               _flow_controller(fc),
                                               _delay(delay),
                                               _prev_processed(0) {}

void brew_controller::process(long now)
{
  if (now - _prev_processed > _delay)
  {
    _prev_processed = now;
    process_tick(now);
  }
}

void brew_controller::process_tick(long now)
{
  const flow_state flow_data = _flow_controller.get_flow_state();

  PART_LOG("Going to draw: v="); PART_LOG(flow_data.volume); 
  PART_LOG(", speed="); PART_LOG(flow_data.speed); 
  PART_LOG(", ticks="); LOG(flow_data.volume);

  if (_reset_btn.is_pressed())
    _flow_controller.reset();

  _screen.draw_flow_screen(flow_data.volume, flow_data.speed, flow_data.ticks);
}
