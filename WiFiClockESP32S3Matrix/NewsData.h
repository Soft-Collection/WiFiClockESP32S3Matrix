#ifndef NewsData_h
#define NewsData_h

#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include "JSONReader.h"
#include "DisplayStringHandler.h"

class NewsData : public JSONReader, public DisplayStringHandler {
public:
  NewsData(uint32_t tryToUpdateIntervalInMS, uint32_t reupdateIntervalInCycles, const char* name, const char* nextName);
  virtual ~NewsData();
  void Check();
  bool IsDataUpdated();
protected:
  void OnPerformUpdate();
  void OnSuccessfulResponse();
};

#endif  //NewsData_h