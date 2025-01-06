#include "JSONReader.h"

JSONReader::JSONReader(uint16_t size, uint32_t responseTime, bool isSecure) {
  if (isSecure) {
    mClient = new WiFiClientSecure();
  } else {
    mClient = new WiFiClient();
  }
  mJD = new DynamicJsonDocument(size);
  mResponseDeserializedSuccessfully = false;
  mPeriodResponse = new Period(this, responseTime, false);
  mPeriodResponse->AddOnPeriodExpiredHandler(JSONReader::OnPeriodExpiredStaticResponse);
}
JSONReader::~JSONReader() {
  if (mPeriodResponse) {
    delete mPeriodResponse;
    mPeriodResponse = NULL;
  }
  if (mJD) {
    delete mJD;
    mJD = NULL;
  }
  if (mClient) {
    delete mClient;
    mClient = NULL;
  }
}
void JSONReader::OnPeriodExpiredStaticResponse(void* instance) {
  JSONReader* jr = (JSONReader*)instance;
  if (jr != NULL) jr->OnPeriodExpiredResponse();
}
void JSONReader::OnPeriodExpiredResponse() {
  if (!mClient) return;
  if (!mJD) return;
  String response;
  String currentResponseLine = "";
  bool flagWeatherDataForecastRaw = false;
  while (mClient->available()) {
    currentResponseLine = mClient->readStringUntil('\n');
    if (currentResponseLine.charAt(0) == '{') {
      flagWeatherDataForecastRaw = true;
    }
    if (flagWeatherDataForecastRaw == true) {
      response += currentResponseLine;
    }
    if (currentResponseLine == "}") {
      break;
    }
  }
  mClient->clear();
  mClient->stop();
  Serial.println(response);
  DeserializationError error = deserializeJson(*mJD, response);
  if (error) {
    mResponseDeserializedSuccessfully = false;
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  mResponseDeserializedSuccessfully = true;
  OnSuccessfulResponse();
}
void JSONReader::OnSuccessfulResponse() {
}