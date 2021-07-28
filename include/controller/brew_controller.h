#pragma once

#include "presenter/screen.h"
#include "controller/flow_controller.h"
#include "controller/button_controller.h"


enum BrewState {
  SHOW_FLOW,
  CALIBRATION
};

class brew_controller
{

public:
  brew_controller(Adafruit_SSD1306 &, button_controller &);

  void process(long);

protected:
  void show_flow(long, bool);

  void calib(long);


private:
  Adafruit_SSD1306 &_screen;
  button_controller &_reset_btn;

  long _prev_processed;

  BrewState _state;

  int _calib_step;
  bool _calib_in_progress = 0;
  int _calib_acc;
};
