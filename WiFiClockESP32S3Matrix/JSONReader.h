#ifndef JSONReader_h
#define JSONReader_h

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "Period.h"

class JSONReader {
public:
  JSONReader(uint16_t size, uint32_t responseTime, bool isSecure);
  virtual ~JSONReader();
protected:
  static void OnPeriodExpiredStaticResponse(void* instance);
  void OnPeriodExpiredResponse();
  virtual void OnSuccessfulResponse();
protected:
  WiFiClient* mClient;
  JsonDocument* mJD;
  Period* mPeriodResponse;
  bool mResponseDeserializedSuccessfully;
};

#endif  //JSONReader_h