#ifndef RTC_h
#define RTC_h

#include <Arduino.h>
#include "Config.h"
#include "esp_sntp.h"
#include <time.h>      // time() ctime()
#include <sys/time.h>  // struct timeval
#include <sntp.h>      // sntp_servermode_dhcp()
#include "DisplayStringHandler.h"

class RTC : public DisplayStringHandler {
public:
  RTC(uint32_t tryToUpdateIntervalInMS, uint32_t reupdateIntervalInCycles, const char* name, const char* nextName);
  virtual ~RTC();
  bool IsDataUpdated();
protected:
  void OnPerformUpdate();
};

#endif  //RTC_h