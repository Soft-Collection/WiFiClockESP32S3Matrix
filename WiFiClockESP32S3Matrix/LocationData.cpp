#include "LocationData.h"
#include "Config.h"

LocationData::LocationData(uint32_t tryToUpdateIntervalInMS, uint32_t reupdateIntervalInCycles, const char* name, const char* nextName)
  : JSONReader(1024, 5000, true), DisplayStringHandler(tryToUpdateIntervalInMS, reupdateIntervalInCycles, name, nextName) {
}
LocationData::~LocationData() {
}
void LocationData::Check() {
  DisplayStringHandler::Check();
  mPeriodResponse->Check(millis());
}
bool LocationData::GetLocationData(String& ip, String& city, String& latitude, String& longitude) {
  if (!mJD) return false;
  //------------------------------------------------------------------
  if (!(*mJD)["ip"]) return false;
  if (!(*mJD)["city"]) return false;
  if (!(*mJD)["loc"]) return false;
  //------------------------------------------------------------------
  ip = ((*mJD)["ip"]).as<String>();
  city = ((*mJD)["city"]).as<String>();
  String loc = ((*mJD)["loc"]).as<String>();
  int idx = loc.indexOf(',');
  latitude = loc.substring(0, idx - 1);
  longitude = loc.substring(idx + 1, loc.length() - 1);
  //------------------------------------------------------------------
  return true;
}
bool LocationData::IsDataUpdated() {
  return mResponseDeserializedSuccessfully;
}
void LocationData::OnPerformUpdate() {
  if (!Cfg.GetShowWeather()) return;
  if (!mClient) return;
  if (WiFi.status() != WL_CONNECTED) return;
  ((WiFiClientSecure*)mClient)->setInsecure();
  if (!mClient->connect("ipinfo.io", 443)) return;
  mClient->println("GET /json HTTP/1.1");
  mClient->println("Host: ipinfo.io");
  mClient->println("Connection: close");
  mClient->println();
  mPeriodResponse->Reset();
}
