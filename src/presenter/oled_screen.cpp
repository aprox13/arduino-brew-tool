#include "presenter/oled_screen.h"
#include "presenter/screen.h"

#ifdef ARDUINO_BUILD
#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "common.h"
#include "string.h"

oled_screen::oled_screen(Adafruit_SSD1306 &screen) : display(screen) {}

void ensure_text_bound(Adafruit_SSD1306 &display, const char *str, uint16_t *w, uint16_t *h)
{
  int16_t x = 0, y = 0, x1 = 0, y1 = 0;
  display.getTextBounds(str, x, y, &x1, &y1, w, h);
}

void oled_screen::draw_flow_screen(double liters, double liters_per_min, long ticks)
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  char *volume_str = new char[20],
       *speed_str = new char[20],
       *ticks_str = new char[30];

  fill_flow_string(liters, liters_per_min, ticks, volume_str, speed_str, ticks_str);

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

#endif
