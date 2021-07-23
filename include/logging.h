#define SERIAL_SPEED 9600
#include <Arduino.h>

#ifdef __LOGS

#define LOG(msg) (Serial.println(msg))
#define PART_LOG(msg) (Serial.print(msg))
#else
#define LOG(msg)
#define PART_LOG(msg)
#endif
