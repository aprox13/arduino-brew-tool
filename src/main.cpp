
#ifdef ARDUINO_BUILD
#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "presenter/oled_screen.h"
#include "presenter/screen.h"
#include "controller/brew_controller.h"
#include "model/arduino.h"
#include "model/arduino_proxy.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET 4
#define SCREEN_ADDRESS 0x3C

#define FLOW_SENSOR_PIN 2
#define RESET_BNT_PIN ((uint8_t)5)
#define FLOW_SPEED_CALC_PERIOD 1000

#define CONTROLLER_TICK_DELAY (300)

brew_controller *controller;

void setup()
{
   Serial.begin(9600);

   Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

   if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
   {
      Serial.println(F("SSD1306 allocation failed"));
      for (;;)
         ;
   }

   pinMode(FLOW_SENSOR_PIN, INPUT_PULLUP);
   pinMode(RESET_BNT_PIN, INPUT_PULLUP);

   attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), &arduino::handle_interrupts, RISING);

   display.clearDisplay();

   arduino *arduino = new arduino_proxy();
   screen *scr = new oled_screen(display);
   button_controller btn(RESET_BNT_PIN, *arduino, LOW);
   flow_controller fc(*arduino, FLOW_SPEED_CALC_PERIOD);

   controller = new brew_controller(*scr, btn, fc, CONTROLLER_TICK_DELAY);
}

void loop()
{
   long now = millis();
   controller->process(now);
}

#else

int main()
{
   return 0;
}
#endif
