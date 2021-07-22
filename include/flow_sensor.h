#include "delayed_action.h"
#include "common.h"
#include <Arduino.h>

#define INIT_TCIKS -1

class flow_sensor
{

public:
    flow_sensor(int ticks_in_liter, long speed_calc_delay) : _ticks(INIT_TCIKS),
                                                             _ticks_for_speed(0),
                                                             _prev_ticks(0),
                                                             _ticks_in_liter(ticks_in_liter),
                                                             _speed_calc_delay(speed_calc_delay),
                                                             _prev_call_ms(0)
    {
    }

    void handle(long now)
    {
        _ticks++;
        if (now - _prev_call_ms > _speed_calc_delay)
        {
            _prev_call_ms = now;
            _ticks_for_speed = _ticks - _prev_ticks;
            _prev_ticks = _ticks;
        }
    }

    void reset()
    {
        _ticks = 0;
        _prev_ticks = 0;
    }

    double volume()
    {
        return (_ticks * 1.0) / _ticks_in_liter;
    }

    double ml_per_sec()
    {
        double ml = 1000.0 * _ticks_for_speed / _ticks_in_liter;
        return ml * _speed_calc_delay / SECOND;
    }

    double liters_per_min()
    {
        double liters = _ticks_for_speed / _ticks_in_liter;
        return 60.0 * liters * _speed_calc_delay / SECOND;
    }

    long ticks() const
    {
        return _ticks;
    }

private:
    volatile long _ticks;
    volatile long _ticks_for_speed;
    volatile long _prev_ticks;

    double _ticks_in_liter;
    long _speed_calc_delay;
    long _prev_call_ms;
};
