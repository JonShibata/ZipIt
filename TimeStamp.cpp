
#include "TimeStamp.hpp"

class TimeStamp {
  private:

  void SetStamp(int time_in) {
    time = time_in;
  }

  int GetStamp() {
    return time;
  }

  int time;
};
