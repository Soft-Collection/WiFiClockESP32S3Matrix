#include "DateData.h"
#include "CommonFunctions.h"
#include "Config.h"

DateData::DateData(uint32_t tryToUpdateIntervalInMS, uint32_t reupdateIntervalInCycles, const char* color, const char* name, const char* nextName)
  : DisplayStringHandler(tryToUpdateIntervalInMS, reupdateIntervalInCycles, color, name, nextName) {
}
DateData::~DateData() {
}
bool DateData::IsDataUpdated() {
  timeval tv;
  time_t now;
  gettimeofday(&tv, nullptr);
  now = time(nullptr);
  int year = localtime(&now)->tm_year;
  return (year != 70);
}
void DateData::OnPerformUpdate() {
  char dt[64];
  timeval tv;
  time_t now;
  gettimeofday(&tv, nullptr);
  now = time(nullptr);
  int8_t day = localtime(&now)->tm_mday;
  int8_t month = localtime(&now)->tm_mon + 1;
  int8_t year = localtime(&now)->tm_year;
  sprintf(dt, "Date %02d/%02d/%04d  ", day, month, year + 1900);
  if (Cfg.GetShowDate()) {
    mDisplayString = String(dt);
  } else {
    mDisplayString = "";
  }
  //Serial.println(mDisplayString.c_str());
}
