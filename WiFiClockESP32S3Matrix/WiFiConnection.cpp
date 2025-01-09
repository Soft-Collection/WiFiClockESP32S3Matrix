#include "WiFiConnection.h"
#include "CommonFunctions.h"

WiFiConnection::WiFiConnection(uint32_t tryToUpdateIntervalInMS, uint32_t reupdateIntervalInCycles, const char* color, const char* name, const char* nextName)
  : DisplayStringHandler(tryToUpdateIntervalInMS, reupdateIntervalInCycles, color, name, nextName) {
}
WiFiConnection::~WiFiConnection() {
}
bool WiFiConnection::IsDataUpdated() {
  mDisplayString = (WiFi.status() == WL_CONNECTED) ? "" : "Connecting...  ";
  return (WiFi.status() == WL_CONNECTED);
}
void WiFiConnection::OnPerformUpdate() {
  static int8_t i = 0;
  WiFi.begin(Cfg.GetStationSSID(i), Cfg.GetStationPSK(i));
  esp_sntp_servermode_dhcp(1);  //(optional)
  increment_modulo(i, Cfg.GetStationCount());
}
