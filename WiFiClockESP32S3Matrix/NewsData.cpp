#include "NewsData.h"
#include "Config.h"

NewsData::NewsData(uint32_t tryToUpdateIntervalInMS, uint32_t reupdateIntervalInCycles, const char* color, const char* name, const char* nextName)
  : JSONReader(8192, 10000, true), DisplayStringHandler(tryToUpdateIntervalInMS, reupdateIntervalInCycles, color, name, nextName) {
}
NewsData::~NewsData() {
}
void NewsData::Check() {
  DisplayStringHandler::Check();
  mPeriodResponse->Check(millis());
}
bool NewsData::IsDataUpdated() {
  return mResponseDeserializedSuccessfully;
}
void NewsData::OnPerformUpdate() {
  if (!Cfg.GetShowNews()) return;
  if (!mClient) return;
  if (WiFi.status() != WL_CONNECTED) return;
  ((WiFiClientSecure*)mClient)->setInsecure();
  if (!mClient->connect("newsapi.org", 443)) return;
  String request = String("GET /v2/top-headlines?sources=") + Cfg.GetNewspaper() + String("&pageSize=3&apiKey=") + Cfg.GetNewsApiKey() + String(" HTTP/1.1");
  mClient->println(request.c_str());
  mClient->println("Host: newsapi.org");
  mClient->println("User-Agent: Matrix/1.0");
  mClient->println("Connection: close");
  mClient->println();
  mClient->println();
  mPeriodResponse->Reset();
}
void NewsData::OnSuccessfulResponse() {
  if (xSemaphoreTake(mDisplayStringMutex, portMAX_DELAY) == pdTRUE) {
    mDisplayString = "";
  }
  xSemaphoreGive(mDisplayStringMutex);
  String tempDisplayString = "News >>> ";
  //-----------------------------------------------------------
  if (!(*mJD)["status"]) return;
  if (!(*mJD)["articles"]) return;
  //-----------------------------------------------------------
  uint8_t articlesCount = (*mJD)["articles"].size();
  for (uint8_t i = 0; i < articlesCount; i++) {
    if (!(*mJD)["articles"][i]["title"]) return;
    tempDisplayString += (*mJD)["articles"][i]["title"].as<String>() + " >>> ";
  }
  //-----------------------------------------------------------
  if (Cfg.GetShowNews()) {
    if (xSemaphoreTake(mDisplayStringMutex, portMAX_DELAY) == pdTRUE) {
      mDisplayString = tempDisplayString;
    }
    xSemaphoreGive(mDisplayStringMutex);
  } else {
    if (xSemaphoreTake(mDisplayStringMutex, portMAX_DELAY) == pdTRUE) {
      mDisplayString = "";
    }
    xSemaphoreGive(mDisplayStringMutex);
  }
  //Serial.println(mDisplayString.c_str());
}
