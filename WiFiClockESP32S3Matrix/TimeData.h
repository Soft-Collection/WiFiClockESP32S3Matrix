#ifndef TimeData_h
#define TimeData_h

#include <Arduino.h>
#include <time.h>      // time() ctime()
#include <sys/time.h>  // struct timeval
#include "DisplayStringHandler.h"

class TimeData : public DisplayStringHandler {
public:
  TimeData(uint32_t tryToUpdateIntervalInMS, uint32_t reupdateIntervalInCycles, const char* name, const char* nextName);
  virtual ~TimeData();
  bool IsDataUpdated();
protected:
  void OnPerformUpdate();
};

#endif  //TimeData_h