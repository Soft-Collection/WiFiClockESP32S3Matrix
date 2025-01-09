#include "DisplayStringManager.h"

DisplayStringManager::DisplayStringManager(void* instance) {
  mWiFiConnection = new WiFiConnection(5000, 0, "646464", "WiFi", "WiFi");
  mRTC = new RTC(1000, 300, "646464", "RTC", "RTC");
  mTimeData = new TimeData(100, 1, "646464", "Time", "Date");
  mDateData = new DateData(100, 1, "646464", "Date", "Weather");
  mLocationData = new LocationData(10000, 1440, "646464", "Location", "Location");
  mWeatherData = new WeatherData(10000, 360, "646400", "Weather", "News");
  mNewsData = new NewsData(20000, 180, "C80000", "News", "Time");
  mSize = 7;
  mArray = new DisplayStringHandler*[mSize];
  mArray[0] = mWiFiConnection;
  mArray[1] = mRTC;
  mArray[2] = mTimeData;
  mArray[3] = mDateData;
  mArray[4] = mLocationData;
  mArray[5] = mWeatherData;
  mArray[6] = mNewsData;
  mCurrent = mArray[0];
  mInstance = instance;
  mOnDisplayStringHandlerChanged = NULL;
}
DisplayStringManager::~DisplayStringManager() {
  if (mArray != NULL) {
    delete mArray;
    mArray = NULL;
  }
  if (mNewsData != NULL) {
    delete mNewsData;
    mNewsData = NULL;
  }
  if (mWeatherData != NULL) {
    delete mWeatherData;
    mWeatherData = NULL;
  }
  if (mLocationData != NULL) {
    delete mLocationData;
    mLocationData = NULL;
  }
  if (mDateData != NULL) {
    delete mDateData;
    mDateData = NULL;
  }
  if (mTimeData != NULL) {
    delete mTimeData;
    mTimeData = NULL;
  }
  if (mRTC != NULL) {
    delete mRTC;
    mRTC = NULL;
  }
  if (mWiFiConnection != NULL) {
    delete mWiFiConnection;
    mWiFiConnection = NULL;
  }
}
void DisplayStringManager::Check() {
  static bool oneTime = false;
  //--------------------------------
  mWiFiConnection->Check();
  mRTC->Check();
  mTimeData->Check();
  mDateData->Check();
  mLocationData->Check();
  mWeatherData->Check();
  mNewsData->Check();
  //--------------------------------
  if (!mWiFiConnection->IsDataUpdated()) {
    if (mCurrent != mWiFiConnection) {
      oneTime = false;
      if (mOnDisplayStringHandlerChanged) mOnDisplayStringHandlerChanged(mInstance);
      mCurrent = mWiFiConnection;
    }
  } else if (!mRTC->IsDataUpdated()) {
    if (mCurrent != mRTC) {
      oneTime = false;
      if (mOnDisplayStringHandlerChanged) mOnDisplayStringHandlerChanged(mInstance);
      mCurrent = mRTC;
    }
  } else {
    if (!oneTime) {
      if (mCurrent != mTimeData) {
        if (mOnDisplayStringHandlerChanged) mOnDisplayStringHandlerChanged(mInstance);
        mCurrent = mTimeData;
      }
      oneTime = true;
    }
  }
  if (mLocationData->IsDataUpdated()) {
    String ip;
    String city;
    String latitude;
    String longitude;
    mLocationData->GetLocationData(ip, city, latitude, longitude);
    mWeatherData->SetLocationData(city, latitude, longitude);
  }
}
DisplayStringHandler* DisplayStringManager::GetByName(const char* name) {
  for (int8_t i = 0; i < mSize; i++) {
    if (mArray[i]->GetName() == name) return mArray[i];
  }
  return NULL;
}
DisplayStringHandler* DisplayStringManager::GetCurrent() {
  return mCurrent;
}
void DisplayStringManager::SwitchToNext() {
  DisplayStringHandler* temp = mCurrent;
  while (true) {
    mCurrent = GetByName(mCurrent->GetNextName().c_str());
    if ((mCurrent->GetDisplayString() != "") || (mCurrent == temp)) break;
  }
  if (mOnDisplayStringHandlerChanged) mOnDisplayStringHandlerChanged(mInstance);
}
void DisplayStringManager::AddOnDisplayStringHandlerChanged(dlgOnDisplayStringHandlerChanged onDisplayStringHandlerChanged) {
  mOnDisplayStringHandlerChanged = onDisplayStringHandlerChanged;
  if (mOnDisplayStringHandlerChanged) mOnDisplayStringHandlerChanged(mInstance);
}