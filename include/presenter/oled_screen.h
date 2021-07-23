#pragma once
#include "presenter/screen.h"

#include <Adafruit_SSD1306.h>

class oled_screen : public screen
{
public:
  oled_screen(Adafruit_SSD1306 &);

  virtual void draw_flow_screen(double liters, double liiters_per_min, long ticks);

private:
  Adafruit_SSD1306 &display;
};
