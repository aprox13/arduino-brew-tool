#include <stdlib.h>

#include "common.h"

void pretty_double(double d, char *to, int prec)
{

  double tmp = d;
  int leading = 1;

  while (tmp >= 10)
  {
    tmp /= 10;
    leading++;
  }
  

  dtostrf(d, leading + 1 + prec, prec, to);
}

void pretty_double2_prec(double d, char *to)
{
  pretty_double(d, to, 2);
}
