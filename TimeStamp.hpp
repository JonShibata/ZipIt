
#ifndef TIMESTAMP_HPP
#define TIMESTAMP_HPP

#include <stdint.h>

class TimeStamp {
  public:
  void SetStamp(uint32_t time_in);
  uint32_t GetStamp();

  private:
  uint32_t time;
};

#endif
