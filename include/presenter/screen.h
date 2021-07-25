#pragma once
#include <Adafruit_SSD1306.h>

class screen
{
private:
  Adafruit_SSD1306 &display;

public:
  screen(Adafruit_SSD1306 &);
  void draw_flow_screen(double liters, double liiters_per_min, long ticks);
};
