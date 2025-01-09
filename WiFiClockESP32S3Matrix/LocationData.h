#ifndef LocationData_h
#define LocationData_h

#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include "JSONReader.h"
#include "DisplayStringHandler.h"

class LocationData : public JSONReader, public DisplayStringHandler {
public:
  LocationData(uint32_t tryToUpdateIntervalInMS, uint32_t reupdateIntervalInCycles, const char* color, const char* name, const char* nextName);
  virtual ~LocationData();
  void Check();
  bool GetLocationData(String& ip, String& city, String& latitude, String& longitude);
  bool IsDataUpdated();
protected:
  void OnPerformUpdate();
};

#endif  //LocationData_h