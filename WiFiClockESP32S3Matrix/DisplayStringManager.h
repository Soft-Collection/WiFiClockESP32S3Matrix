#ifndef DisplayStringManager_h
#define DisplayStringManager_h

#include <Arduino.h>
#include "WiFiConnection.h"
#include "RTC.h"
#include "TimeData.h"
#include "DateData.h"
#include "LocationData.h"
#include "WeatherData.h"
#include "NewsData.h"
#include "DisplayStringHandler.h"

class DisplayStringManager {
public:
  DisplayStringManager();
  virtual ~DisplayStringManager();
  void Check();
  DisplayStringHandler* GetByName(const char* name);
  DisplayStringHandler* GetCurrent();
  void SwitchToNext();
private:
  WiFiConnection* mWiFiConnection;
  RTC* mRTC;
  TimeData* mTimeData;
  DateData* mDateData;
  LocationData* mLocationData;
  WeatherData* mWeatherData;
  NewsData* mNewsData;
  int mSize;
  DisplayStringHandler** mArray;
  DisplayStringHandler* mCurrent;
};

#endif  //DisplayStringManager_h