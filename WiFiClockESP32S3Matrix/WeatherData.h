#ifndef WeatherData_h
#define WeatherData_h

#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include "JSONReader.h"
#include "DisplayStringHandler.h"

class WeatherData : public JSONReader, public DisplayStringHandler {
public:
  WeatherData(uint32_t tryToUpdateIntervalInMS, uint32_t reupdateIntervalInCycles, const char* name, const char* nextName);
  virtual ~WeatherData();
  void Check();
  bool GetWeatherData(String& weather, String& temperature, String& maxWind);
  bool IsDataUpdated();
  void SetLocationData(String city, String latitude, String longitude);
protected:
  void OnPerformUpdate();
  void OnSuccessfulResponse();
protected:
  String mCity;
  String mLatitude;
  String mLongitude;
};

#endif  //WeatherData_h