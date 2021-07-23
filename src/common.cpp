#include <stdlib.h>

#include "common.h"

void pretty_double(double d, char *to, int prec)
{
  dtostrf(d, 20, prec, to);
}

void pretty_double2_prec(double d, char *to)
{
  pretty_double(d, to, 2);
}
