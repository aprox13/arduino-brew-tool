#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "presenter/screen.h"
#include "logging.h"

const int text_size_1_height = 8;
const int text_size_2_height = 16;

screen::screen(Adafruit_SSD1306 &sc) : display(sc) {}

void ensure_text_bound(Adafruit_SSD1306 &display, const String &str, uint16_t *w, uint16_t *h)
{
  int16_t x = 0, y = 0, x1 = 0, y1 = 0;
  display.getTextBounds(str, x, y, &x1, &y1, w, h);
}

void screen::draw_flow_screen(double liters, double liters_per_min, long ticks)
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  display.setCursor(0, display.height() - 1 - text_size_2_height);

  display.print(liters);
  display.print("L");
  display.setCursor(display.getCursorX(), display.height() - 1 - text_size_1_height);
  display.setTextSize(1);
  display.print("/");
  display.print(ticks);

  display.display();
}

void screen::draw_calibration(long ml) {
  display.setCursor(0, 0);
  display.setTextSize(1);

  display.print("Fill "); 
  display.print(ml);
  display.println("ml");
  display.println("Press button to continue");
}
