#include <Arduino.h>
#include <Wire.h>
#include "logging.h"

#define SECOND 1000
#define LCD_ADDR 0x3F

String pretty_double(double d, uint8_t prec = 2)
{
    char temp_res[10];
    dtostrf(d, 1, prec, temp_res);

    return String(temp_res);
}