#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "controller/brew_controller.h"
#include "logging.h"
#include "sensor/flow_sensor.h"

#define MAIN_DELAY (100)
#define CALIBS_N 2

int calibs[CALIBS_N] = {
    500,
    700,
    // 1000,
    // 2000,
    // 500
};

enum VolumeShowType
{
  LITERS,
  TICKS,
  ALL
};

brew_controller::brew_controller(Adafruit_SSD1306 &sc,
                                 button_controller &btn) : _screen(sc),
                                                           _reset_btn(btn)
{
  _prev_processed = 0;
  _state = BrewState::CALIBRATION;
  _calib_step = 0;

  _calib_acc = 0;
  _calib_in_progress = false;
}

template <class func_t>
void _internal_process(long now, long _delay, long &prev_counter, func_t processor)
{
  if (now - prev_counter > _delay)
  {
    prev_counter = now;
    processor();
  }
}

void draw_volume(Adafruit_SSD1306 &sc, VolumeShowType type)
{ 
  sc.setTextColor(WHITE);

  switch (type)
  {
  case VolumeShowType::LITERS:
    sc.setTextSize(2);
    sc.setCursor(0, sc.height() - 16 - 1);
    sc.print(flow_sensor::liters());
    sc.print("L");
    break;

  case VolumeShowType::TICKS:
    sc.setCursor(0, sc.height() - 8 - 1);
    sc.setTextSize(1);
    sc.print(flow_sensor::get_ticks());
    sc.print(" ticks");
    break;
  case VolumeShowType::ALL:
    sc.setTextSize(2);
    sc.setCursor(0, sc.height() - 16 - 1);
    sc.print(flow_sensor::liters());
    sc.print("L");
    sc.setCursor(sc.getCursorX(), sc.height() - 8 - 1);
    sc.setTextSize(1);
    sc.print("/");
    sc.print(flow_sensor::get_ticks());
    break;
  }
}

void brew_controller::process(long now)
{
  if (_state == BrewState::SHOW_FLOW)
    _internal_process(now, MAIN_DELAY, _prev_processed, [&]()
                      { show_flow(now, true); });
  else if (_state == BrewState::CALIBRATION)
    _internal_process(now, MAIN_DELAY, _prev_processed, [&]()
                      { calib(now); });
}

void brew_controller::show_flow(long now, bool allow_reset)
{
  LOG("show flow");
  if (allow_reset && _reset_btn.is_pressed())
    flow_sensor::reset();
  _screen.clearDisplay();
  draw_volume(_screen, VolumeShowType::ALL);
  _screen.display();
}

void brew_controller::calib(long now)
{
  _screen.clearDisplay();
  _screen.setTextColor(WHITE);

  if (_calib_step != CALIBS_N)
  {
    if (!_reset_btn.is_pressed())
    {
      _screen.setTextSize(1);
      _screen.setCursor(0, 0);
      _screen.print("Fill ");
      _screen.print(calibs[_calib_step]);
      _screen.println("ml and press reset button");

      draw_volume(_screen, VolumeShowType::TICKS);
    } else {
      long ticks = flow_sensor::get_ticks();

      long in_liter_ticks = (long)((double)ticks) / ((double) calibs[_calib_step] / 1000.0);

      _calib_step++;
      _calib_acc += in_liter_ticks;
      flow_sensor::reset();
    }
  } else {
    long calibrated_ticks_in_liter = _calib_acc / CALIBS_N;

    _screen.print(calibrated_ticks_in_liter);
  }

  _screen.display();
}