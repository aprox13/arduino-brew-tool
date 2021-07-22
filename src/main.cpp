#include <Arduino.h>
#include "flow_sensor.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "logging.h"
#include "math.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET 4
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define FLOW_SENSOR_PIN 2
long average(int count, ...)
{
   va_list ap;
   int j;
   double sum = 0;

   va_start(ap, count);
   for (j = 0; j < count; j++)
   {
      sum += va_arg(ap, int); /* Увеличивает ap до следующего аргумента. */
   }
   va_end(ap);


   return (long)(sum / count);
}

flow_sensor sensor(average(5, 347, 353, 359, 369, 380), 500);

void flow_hanler() { sensor.handle(millis()); }

void text_bounds(const String &str, uint16_t *w, uint16_t *h)
{
   display.getTextBounds(str, 0, 0, 0, 0, w, h);
}

class printer : public delayed_action
{

public:
   printer(long delay) : delayed_action(delay) {}

protected:
   void action(long now)
   {

      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(WHITE);

      String volumeStr = pretty_double(sensor.volume()) + String("L");
      uint16_t w, h;
      text_bounds(volumeStr, &w, &h);
      display.setCursor(SCREEN_WIDTH - 1 - w, SCREEN_HEIGHT - 1 - h);
      display.print(volumeStr);

      display.setTextSize(1);
      display.setCursor(0, 0);
      String speedStr = pretty_double(sensor.liters_per_min()) + " L/min";
      display.print(speedStr);
      text_bounds(speedStr, &w, &h);
      display.setCursor(0, h + 3);
      display.print(String(sensor.ticks()) + " ticks");

      display.display();
   }

private:
   int i = 0;
};

class btn : public delayed_action
{
public:
   btn(long delay) : delayed_action(delay) {}

protected:
   void action(long now)
   {
      if (digitalRead(5) == LOW)
         sensor.reset();
   }
};

printer my_printer(500);
btn button(500);

void setup()
{
   Serial.begin(9600);

   // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
   if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
   {
      Serial.println(F("SSD1306 allocation failed"));
      for (;;)
         ; // Don't proceed, loop forever
   }
   display.clearDisplay();
   delay(2000);
   pinMode(FLOW_SENSOR_PIN, INPUT_PULLUP);
   pinMode(5, INPUT_PULLUP);
   // digitalWrite(FLOW_SENSOR_PIN, HIGH); // Optional Internal Pull-Up
   // lcd.init();
   // lcd.backlight();
   attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), flow_hanler, RISING);
   // lcd.clear();
   // lcd.setCursor(0, 0);
   // lcd.print("Water Flow Meter");
   // lcd.setCursor(0, 1);
   // lcd.print("Circuit Digest");
   sensor.reset();
}

void loop()
{
   long now = millis();
   my_printer.tick(now);
   button.tick(now);
}