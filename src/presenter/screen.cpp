#include <stdlib.h>
#include "presenter/screen.h"
#include "common.h"
#include "string.h"
#include "logging.h"

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

  PART_LOG("Got volume_str="); LOG(volume_str);

  pretty_double2_prec(liters_per_min, buff);
  strcpy(speed_str, buff);
  strcat(speed_str, " L/min");

  PART_LOG("Got speed_str="); LOG(speed_str);

  ltoa(ticks, buff, 10);
  strcpy(ticks_str, buff);
  strcat(ticks_str, " ticks");

  PART_LOG("Got ticks_str="); LOG(ticks_str);
}
