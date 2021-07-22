#include <stdlib.h>
#include "presenter/screen.h"
#include "common.h"
#include "string.h"

void fill_flow_string(double liters,
                      double liters_per_min,
                      long ticks,
                      char *volume_str,
                      char *speed_str,
                      char *ticks_str)
{
  char *buff = new char[10];

  pretty_double2_prec(liters, buff);
  strcpy(volume_str, buff);
  strcat(volume_str, "L");

  pretty_double2_prec(liters_per_min, buff);
  strcpy(speed_str, buff);
  strcat(speed_str, " L/min");

  ltoa(ticks, buff, 10);
  strcpy(ticks_str, buff);
  strcat(ticks_str, " ticks");
}
