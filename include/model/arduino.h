#pragma once
#include <stdint.h>

class arduino
{
public:
  virtual int digital_read(uint8_t) const = 0;
  virtual void digital_write(uint8_t, int) = 0;

  static long get_interrupts_count();

  static void handle_interrupts(void);

private:
  static volatile long _interrupts;
};
