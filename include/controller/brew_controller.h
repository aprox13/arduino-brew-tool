#pragma once

#include "presenter/screen.h"
#include "controller/flow_controller.h"
#include "controller/button_controller.h"

class brew_controller
{

public:
  brew_controller(screen &, button_controller &);

  void process(long);

protected:
  void process_tick(long);

private:
  screen &_screen;
  button_controller &_reset_btn;

  long _prev_processed;
};
