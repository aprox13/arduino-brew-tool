#include "presenter/oled_screen.h"
#include "presenter/screen.h"

#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <StringBuilder.h>

#include "common.h"
#include "string.h"

oled_screen::oled_screen(Adafruit_SSD1306 &screen) : display(screen) {}

void ensure_text_bound(Adafruit_SSD1306 &display, const String &str, uint16_t *w, uint16_t *h)
{
  int16_t x = 0, y = 0, x1 = 0, y1 = 0;
  display.getTextBounds(str, x, y, &x1, &y1, w, h);
}

String dtos(double d, int prec)
{
  String res = "";
  res += ((long)d);

  d -= (long)d;

  while (prec > 0)
  {
    d *= 10;
  }

  long ld = (long)d;

  while (ld > 0 && ld % 10 == 0)
    ld /= 10;

  if (ld != 0)
  {
    res += (".");
    res += (ld);
  }
  return res;
}

void oled_screen::draw_flow_screen(double liters, double liters_per_min, long ticks)
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  String volume_str = dtos(liters, 2) + "L";
  String speed_str = dtos(liters_per_min, 2) + " L/min";
  String ticks_str = String() + ticks + " ticks";

  uint16_t w, h;
  ensure_text_bound(display, volume_str, &w, &h);
  display.setCursor(display.width() - 1 - w, display.height() - 1 - h);
  display.print(volume_str);

  display.setTextSize(1);
  display.setCursor(0, 0);

  display.print(speed_str);
  ensure_text_bound(display, speed_str, &w, &h);
  display.setCursor(0, h + 3);
  display.print(ticks_str);

  display.display();
}
