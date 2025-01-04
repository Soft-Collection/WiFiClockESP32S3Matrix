#ifndef WiFiConnection_h
#define WiFiConnection_h

#include <Arduino.h>
#include "Config.h"
#include <WiFi.h>
#include "esp_sntp.h"
#include <sntp.h>  //sntp_servermode_dhcp()
#include "DisplayStringHandler.h"

class WiFiConnection : public DisplayStringHandler {
public:
  WiFiConnection(uint32_t tryToUpdateIntervalInMS, uint32_t reupdateIntervalInCycles, const char* name, const char* nextName);
  virtual ~WiFiConnection();
  bool IsDataUpdated();
protected:
  void OnPerformUpdate();
};

#endif  //WiFiConnection_h