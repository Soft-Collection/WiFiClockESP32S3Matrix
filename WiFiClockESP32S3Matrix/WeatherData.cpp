#include "WeatherData.h"
#include "Config.h"

WeatherData::WeatherData(uint32_t tryToUpdateIntervalInMS, uint32_t reupdateIntervalInCycles, const char* name, const char* nextName)
  : JSONReader(1024, 5000, true), DisplayStringHandler(tryToUpdateIntervalInMS, reupdateIntervalInCycles, name, nextName) {
  mCity = "";
  mLatitude = "";
  mLongitude = "";
}
WeatherData::~WeatherData() {
}
void WeatherData::Check() {
  DisplayStringHandler::Check();
  mPeriodResponse->Check(millis());
}
bool WeatherData::GetWeatherData(String& weather, String& temperature, String& maxWind) {
  if (!mJD) return false;
  //------------------------------------------------------------------
  if (!(*mJD)["dataseries"][0]["weather"]) return false;
  if (!(*mJD)["dataseries"][0]["temp2m"]["min"]) return false;
  if (!(*mJD)["dataseries"][0]["temp2m"]["max"]) return false;
  if (!(*mJD)["dataseries"][0]["wind10m_max"]) return false;
  //------------------------------------------------------------------
  String site_weather = ((*mJD)["dataseries"][0]["weather"]).as<String>();
  //Temperature measured at 2 meters height
  String site_temp2m_min = ((*mJD)["dataseries"][0]["temp2m"]["min"]).as<String>();
  String site_temp2m_max = ((*mJD)["dataseries"][0]["temp2m"]["max"]).as<String>();
  //Wind Speed measured at 10 meters height in Beaufort scale.
  String site_wind10m_max = ((*mJD)["dataseries"][0]["wind10m_max"]).as<String>();
  //------------------------------------------------------------------
  temperature = String((site_temp2m_min.toInt() + site_temp2m_max.toInt()) / 2);
  //---------------------------------
  if (site_weather == "clear") weather = "Clear";
  else if (site_weather == "pcloudy") weather = "Partly Cloudy";
  else if (site_weather == "mcloudy") weather = "Mostly Cloudy";
  else if (site_weather == "cloudy") weather = "Cloudy";
  else if (site_weather == "humid") weather = "Humid";
  else if (site_weather == "lightrain") weather = "Light Rain";
  else if (site_weather == "oshower") weather = "Occasional Showers";
  else if (site_weather == "ishower") weather = "Isolated Showers";
  else if (site_weather == "rain") weather = "Rain";
  else if (site_weather == "lightsnow") weather = "Light Snow";
  else if (site_weather == "snow") weather = "Snow";
  else if (site_weather == "rainsnow") weather = "Freezing Rain";
  //---------------------------------
  if (site_wind10m_max == "0") maxWind = "Calm";
  else if (site_wind10m_max == "1") maxWind = "Light Air";
  else if (site_wind10m_max == "2") maxWind = "Light Breeze";
  else if (site_wind10m_max == "3") maxWind = "Gentle Breeze";
  else if (site_wind10m_max == "4") maxWind = "Moderate Breeze";
  else if (site_wind10m_max == "5") maxWind = "Fresh Breeze";
  else if (site_wind10m_max == "6") maxWind = "Strong Breeze";
  else if (site_wind10m_max == "7") maxWind = "Moderate Gale";
  else if (site_wind10m_max == "8") maxWind = "Gale";
  else if (site_wind10m_max == "9") maxWind = "Strong Gale";
  else if (site_wind10m_max == "10") maxWind = "Storm";
  else if (site_wind10m_max == "11") maxWind = "Violent Storm";
  else if (site_wind10m_max == "12") maxWind = "Hurricane";
  //------------------------------------------------------------------
  return true;
}
bool WeatherData::IsDataUpdated() {
  return mResponseDeserializedSuccessfully;
}
void WeatherData::OnPerformUpdate() {
  if (!Cfg.GetShowWeather()) return;
  if (!mClient) return;
  if (WiFi.status() != WL_CONNECTED) return;
  if ((mLatitude == "") || (mLongitude == "")) return;
  ((WiFiClientSecure*)mClient)->setInsecure();
  if (!mClient->connect("www.7timer.info", 443)) return;
  String request = String("GET /bin/civillight.php?lat=") + mLatitude + String("&lon=") + mLongitude + String("&ac=0&unit=metric&output=json&tzshift=0 HTTP/1.1");
  mClient->println(request.c_str());
  mClient->println("Host: www.7timer.info");
  mClient->println("Connection: close");
  mClient->println();
  mPeriodResponse->Reset();
}
void WeatherData::SetLocationData(String city, String latitude, String longitude) {
  mCity = city;
  mLatitude = latitude;
  mLongitude = longitude;
}
void WeatherData::OnSuccessfulResponse() {
  if ((mLatitude == "") || (mLongitude == "") || (mCity == "")) return;
  String weather;
  String temperature;
  String maxWind;
  GetWeatherData(weather, temperature, maxWind);
  if (Cfg.GetShowWeather()) {
    mDisplayString = String("Weather in ") + mCity + String(" ") + temperature + String("~C ") + weather + String(" Wind ") + maxWind + String("  ");
  } else {
    mDisplayString = "";
  }
  //Serial.println(mDisplayString.c_str());
}
