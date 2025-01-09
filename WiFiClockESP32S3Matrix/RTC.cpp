#include "RTC.h"
#include "CommonFunctions.h"

RTC::RTC(uint32_t tryToUpdateIntervalInMS, uint32_t reupdateIntervalInCycles, const char* color, const char* name, const char* nextName)
  : DisplayStringHandler(tryToUpdateIntervalInMS, reupdateIntervalInCycles, color, name, nextName) {
}
RTC::~RTC() {
}
bool RTC::IsDataUpdated() {
  timeval tv;
  time_t now;
  gettimeofday(&tv, nullptr);
  now = time(nullptr);
  int year = localtime(&now)->tm_year;
  mDisplayString = (year != 70) ? "" : "Updating...  ";
  return (year != 70);
}
void RTC::OnPerformUpdate() {
  // sntp_set_time_sync_notification_cb(timeavailable);
  // configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
  // https://github.com/esp8266/Arduino/blob/master/cores/esp8266/TZ.h
  configTzTime(Cfg.GetMyTZ().c_str(), "pool.ntp.org", "time.nist.gov");
}
