#include <stdlib.h>
#ifndef ARDUINO_BUILD
#include <stdio.h>
#endif

#include "common.h"

void pretty_double(double d, char *to, int prec)
{
#ifndef ARDUINO_BUILD
  char *fmt = new char[10];
  sprintf(fmt, "%%.%df", prec);

  sprintf(to, fmt, d);
#else
  dtostrf(d, 20, prec, to);

#endif
}

void pretty_double2_prec(double d, char *to)
{
  pretty_double(d, to, 2);
}
