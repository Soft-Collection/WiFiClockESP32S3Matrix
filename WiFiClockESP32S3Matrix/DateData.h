#ifndef DateData_h
#define DateData_h

#include <Arduino.h>
#include <time.h>      // time() ctime()
#include <sys/time.h>  // struct timeval
#include "DisplayStringHandler.h"

class DateData : public DisplayStringHandler {
public:
  DateData(uint32_t tryToUpdateIntervalInMS, uint32_t reupdateIntervalInCycles, const char* name, const char* nextName);
  virtual ~DateData();
  bool IsDataUpdated();
protected:
  void OnPerformUpdate();
};

#endif  //DateData_h