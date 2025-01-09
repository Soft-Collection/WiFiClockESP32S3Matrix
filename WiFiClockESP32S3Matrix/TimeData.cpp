#include "TimeData.h"
#include "CommonFunctions.h"
#include "Config.h"

TimeData::TimeData(uint32_t tryToUpdateIntervalInMS, uint32_t reupdateIntervalInCycles, const char* color, const char* name, const char* nextName)
  : DisplayStringHandler(tryToUpdateIntervalInMS, reupdateIntervalInCycles, color, name, nextName) {
}
TimeData::~TimeData() {
}
bool TimeData::IsDataUpdated() {
  timeval tv;
  time_t now;
  gettimeofday(&tv, nullptr);
  now = time(nullptr);
  int year = localtime(&now)->tm_year;
  return (year != 70);
}
void TimeData::OnPerformUpdate() {
  char tm[64];
  timeval tv;
  time_t now;
  gettimeofday(&tv, nullptr);
  now = time(nullptr);
  int8_t hour = localtime(&now)->tm_hour;
  int8_t minute = localtime(&now)->tm_min;
  int8_t second = localtime(&now)->tm_sec;
  //sprintf(tm, "%02d%c%02d%c%02d ", hour, (showPoints) ? ':' : ' ', minute, (showPoints) ? ':' : ' ', second);
  sprintf(tm, "Time %02d%c%02d%c%02d  ", hour, ':', minute, ':', second);
  if (Cfg.GetShowTime()) {
    mDisplayString = String(tm);
  } else {
    mDisplayString = "";
  }
  //Serial.println(mDisplayString.c_str());
}
