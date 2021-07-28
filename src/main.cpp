#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "presenter/screen.h"
#include "controller/brew_controller.h"
#include "model/arduino.h"
#include "model/arduino_proxy.h"
#include "sensor/flow_sensor.h"
#include <EEPROM.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET 4
#define SCREEN_ADDRESS 0x3C

#define FLOW_SENSOR_PIN 2
#define RESET_BNT_PIN ((uint8_t)5)
#define FLOW_SPEED_CALC_PERIOD 1000

#define DELAY_PERIOD_MS 100

brew_controller *controller;
screen *_screen;

long prev_ticks = 0;

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

   flow_sensor::attach(digitalPinToInterrupt(FLOW_SENSOR_PIN));

   display.clearDisplay();

   arduino *arduino = new arduino_proxy();
   button_controller btn(RESET_BNT_PIN, *arduino, LOW);

   controller = new brew_controller(display, btn);

   int cnt;
   EEPROM.get(0, cnt);

   Serial.println(cnt);

}

void loop()
{
   long now = millis();

   // controller->process(now);
}
