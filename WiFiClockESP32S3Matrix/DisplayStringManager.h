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
  typedef void (*dlgOnDisplayStringHandlerChanged)(void* instance);	
public:
  DisplayStringManager(void* instance);
  virtual ~DisplayStringManager();
  void Check();
  DisplayStringHandler* GetByName(const char* name);
  DisplayStringHandler* GetCurrent();
  void SwitchToNext();
  void AddOnDisplayStringHandlerChanged(dlgOnDisplayStringHandlerChanged onDisplayStringHandlerChanged);
private:
  void* mInstance;
  dlgOnDisplayStringHandlerChanged mOnDisplayStringHandlerChanged;
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