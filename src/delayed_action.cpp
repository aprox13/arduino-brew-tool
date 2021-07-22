#include "delayed_action.h"
#include <Arduino.h>

delayed_action::delayed_action(long delay)
{
    this->delay = delay;
    this->lastExecTime = 0;
}

void delayed_action::tick(long now)
{
    if (now - lastExecTime > delay)
    {
        this->action(now);

        this->lastExecTime = now;
    }
}
