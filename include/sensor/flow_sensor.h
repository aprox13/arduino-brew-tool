#pragma once 

class flow_sensor {

public:
  
  static void attach(const int);

  static void set_tick_per_liter(const int);

  static void reset();

  static double liters();

  static void on_tick(void);

  static long get_ticks();

private:

  static volatile double _ticks;
  static double _ticks_per_liter;
};
