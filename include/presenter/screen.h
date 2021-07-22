#pragma once
class screen
{

public:
  virtual void draw_flow_screen(double liters, double liiters_per_min, long ticks) = 0;
};

void fill_flow_string(double liters,
                      double liters_per_min,
                      long ticks,
                      char *volume_str,
                      char *speed_str,
                      char *ticks_str);
