#include <stdint.h>

#include "TimeStamp.hpp"


void TimeStamp::SetStamp(uint32_t time_in) {
  time = time_in;
}

uint32_t TimeStamp::GetStamp() {
  return time;
}
