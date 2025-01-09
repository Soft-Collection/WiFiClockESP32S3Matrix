#include "config.h"
#include <ArduinoJson.h>

/*
{
	"tz": "EST5EDT,M3.2.0,M11.1.0",
	"matrix_pin": "14",
	"color": "000000",
	"stations": [
		{
			"ssid": "your_ssid1",
			"psk": "your_password1"
		},
		{
			"ssid": "your_ssid2",
			"psk": "your_password2"
		},
		{
			"ssid": "your_ssid3",
			"psk": "your_password3"
		}
	],
  "news_api_key": "your_newsapi.org_api_key",
  "newspaper": "fox-news",
  "show_time": "true",
  "show_date": "true",
  "show_weather": "true",
  "show_news": "true"
}
*/

Config::Config(void) {
  mStationCount = 0;
  mMyTZ = "";
  mMatrixPin = 14;
  mColor = "000000";
  mNewsApiKey = "";
  mNewspaper = "fox-news";
  mShowTime = false;
  mShowDate = false;
  mShowWeather = false;
  mShowNews = false;
}
Config::~Config(void) {
}
bool Config::begin() {
  if (!EEPROM.begin(EEPROM_SIZE)) return false;
  //Save_UI8(EEPROM_ADDRESS_INITIALIZED, 255);
  if (Load_UI8(EEPROM_ADDRESS_INITIALIZED) != 25) {
    //------------------------------------------------
    SaveData("{\"tz\":\"EST5EDT,M3.2.0,M11.1.0\",\"matrix_pin\":\"14\",\"color\":\"000000\",\"stations\":[{\"ssid\":\"your_ssid1\",\"psk\":\"your_password1\"},{\"ssid\":\"your_ssid2\",\"psk\":\"your_password2\"},{\"ssid\":\"your_ssid3\",\"psk\":\"your_password3\"}],\"news_api_key\": \"your_newsapi.org_api_key\",\"newspaper\":\"fox-news\",\"show_time\":\"true\",\"show_date\":\"true\",\"show_weather\":\"true\",\"show_news\":\"true\"}");
    //------------------------------------------------
    Save_UI8(EEPROM_ADDRESS_INITIALIZED, 25);
  }
  if (!ParseJSONString(LoadData(), mStationSSID, mStationPSK, mStationCount, mMyTZ, mMatrixPin, mColor, mNewsApiKey, mNewspaper, mShowTime, mShowDate, mShowWeather, mShowNews)) {
    Save_UI8(EEPROM_ADDRESS_INITIALIZED, 255);
    ESP.restart();
    return false;
  }
  return true;
}
void Config::Check() {
  String inputString = "";
  while (Serial.available()) {
    inputString += (char)Serial.read();
  }
  inputString.trim();
  if (inputString.length()) {
    if (inputString == "help") {
      Serial.println("1. Use help command to get description of all commands.");
      Serial.println("2. Use get command to get all data in JSON format.");
      Serial.println("3. Use reset command to reset all data to its dafault values.");
      Serial.println("4. Enter the edited JSON string you have got using get command.");
      Serial.println("5. See your Time Zone here: https://github.com/esp8266/Arduino/blob/master/cores/esp8266/TZ.h");
      Serial.println("6. Validate your JSON String here: https://jsonlint.com");
      Serial.println("7. If you want to see News, you must get Newsapi.org API Key here: https://newsapi.org");
    } else if (inputString == "get") {
      Serial.println(LoadData());
    } else if (inputString == "reset") {
      Save_UI8(EEPROM_ADDRESS_INITIALIZED, 255);
      Serial.println("Default values set.");
      Serial.println("Restarting...");
      ESP.restart();
    } else {
      String tempData = LoadData();
      if (!ParseJSONString(inputString, mStationSSID, mStationPSK, mStationCount, mMyTZ, mMatrixPin, mColor, mNewsApiKey, mNewspaper, mShowTime, mShowDate, mShowWeather, mShowNews)) {
        SaveData(tempData);
        Serial.println("Wrong data/command provided.");
        Serial.println("Restarting...");
        ESP.restart();
      }
      SaveData(inputString);
      Serial.println("Configuration Updated Successfully.");
      Serial.println("Restarting...");
      ESP.restart();
    }
  }
}
//-----------------------------------------------------------
void Config::Save_I8(int address, int8_t value) {
  EEPROM.writeByte(address, value);
  EEPROM.commit();
}
void Config::Save_UI8(int address, uint8_t value) {
  EEPROM.writeByte(address, value);
  EEPROM.commit();
}
void Config::Save_I16(int address, int16_t value) {
  EEPROM.writeShort(address, value);
  EEPROM.commit();
}
void Config::Save_UI16(int address, uint16_t value) {
  EEPROM.writeUShort(address, value);
  EEPROM.commit();
}
void Config::Save_I32(int address, int32_t value) {
  EEPROM.writeInt(address, value);
  EEPROM.commit();
}
void Config::Save_UI32(int address, uint32_t value) {
  EEPROM.writeUInt(address, value);
  EEPROM.commit();
}
void Config::Save_String(int address, String str, int maxLength) {
  if (str.length() < maxLength) {
    EEPROM.writeString(address, str);
    EEPROM.commit();
  }
}
//-----------------------------------------------------------
int8_t Config::Load_I8(int address) {
  return (EEPROM.readByte(address));
}
uint8_t Config::Load_UI8(int address) {
  return (EEPROM.readByte(address));
}
int16_t Config::Load_I16(int address) {
  return (EEPROM.readShort(address));
}
uint16_t Config::Load_UI16(int address) {
  return (EEPROM.readUShort(address));
}
int32_t Config::Load_I32(int address) {
  return (EEPROM.readInt(address));
}
uint32_t Config::Load_UI32(int address) {
  return (EEPROM.readUInt(address));
}
String Config::Load_String(int address, int maxLength) {
  String str = EEPROM.readString(address);
  return (str.length() < maxLength) ? str : "";
}
//-----------------------------------------------------------
String Config::GetStationSSID(uint8_t idx) {
  return mStationSSID[idx];
}
String Config::GetStationPSK(uint8_t idx) {
  return mStationPSK[idx];
}
uint8_t Config::GetStationCount() {
  return mStationCount;
}
String Config::GetMyTZ() {
  return mMyTZ;
}
uint8_t Config::GetMatrixPin() {
  return mMatrixPin;
}
String Config::GetColor() {
  return mColor;
}
String Config::GetNewsApiKey(){
  return mNewsApiKey;
}
String Config::GetNewspaper(){
  return mNewspaper;
}
bool Config::GetShowTime() {
  return mShowTime;
}
bool Config::GetShowDate() {
  return mShowDate;
}
bool Config::GetShowWeather() {
  return mShowWeather;
}
bool Config::GetShowNews() {
  return mShowNews;
}
void Config::SaveData(String jsonString) {
  Save_String(EEPROM_ADDRESS_DATA, jsonString, EEPROM_SIZE - 10);
}
String Config::LoadData() {
  return (Load_String(EEPROM_ADDRESS_DATA, EEPROM_SIZE - 10));
}
bool Config::ParseJSONString(String jsonString, String* stationSSID, String* stationPSK, uint8_t& stationCount, String& myTZ, uint8_t& matrixPin, String& color, String& newsApiKey, String& newspaper, bool& showTime, bool& showDate, bool& showWeather, bool& showNews) {
  JsonDocument jd;
  DeserializationError error = deserializeJson(jd, jsonString);
  if (error) {
    Serial.println("Wrong JSON String:");
    Serial.println(jsonString);
    Serial.println("Validate it here: https://jsonlint.com");
    return false;
  }
  //-----------------------------------------------------------
  if (!jd["tz"]) {
    Serial.println("No Time Zone information.");
    return false;
  }
  myTZ = jd["tz"].as<String>();
  //-----------------------------------------------------------
  if (!jd["matrix_pin"]) {
    Serial.println("No Matrix Pin information.");
    return false;
  }
  matrixPin = jd["matrix_pin"].as<uint8_t>();
  //-----------------------------------------------------------
  if (!jd["color"]) {
    Serial.println("No Color information.");
    return false;
  }
  color = jd["color"].as<String>();
  //-----------------------------------------------------------
  if (!jd["stations"]) {
    Serial.println("No Stations information.");
    return false;
  }
  stationCount = jd["stations"].size();
  //-----------------------------------------------------------
  for (uint8_t i = 0; i < stationCount; i++) {
    if (!jd["stations"][i]["ssid"]) {
      Serial.println("No SSID information.");
      return false;
    }
    stationSSID[i] = jd["stations"][i]["ssid"].as<String>();
    //-----------------------------------------------------------
    if (!jd["stations"][i]["psk"]) {
      Serial.println("No PSK Information.");
      return false;
    }
    stationPSK[i] = jd["stations"][i]["psk"].as<String>();
  }
  //-----------------------------------------------------------
  if (!jd["news_api_key"]) {
    Serial.println("No News API Key information.");
    return false;
  }
  newsApiKey = jd["news_api_key"].as<String>();
  //-----------------------------------------------------------
  if (!jd["newspaper"]) {
    Serial.println("No Newspaper information.");
    return false;
  }
  newspaper = jd["newspaper"].as<String>();
  //-----------------------------------------------------------
  if (!jd["show_time"]) {
    Serial.println("No Show Time information.");
    return false;
  }
  showTime = jd["show_time"].as<bool>();
  //-----------------------------------------------------------
  if (!jd["show_date"]) {
    Serial.println("No Show Date information.");
    return false;
  }
  showDate = jd["show_date"].as<bool>();
  //-----------------------------------------------------------
  if (!jd["show_weather"]) {
    Serial.println("No Show Weather information.");
    return false;
  }
  showWeather = jd["show_weather"].as<bool>();
  //-----------------------------------------------------------
  if (!jd["show_news"]) {
    Serial.println("No Show News information.");
    return false;
  }
  showNews = jd["show_news"].as<bool>();
  //-----------------------------------------------------------
  return true;
}

Config Cfg;
