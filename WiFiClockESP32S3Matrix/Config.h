//https://randomnerdtutorials.com/esp32-flash-memory/
#if !defined(__CONFIG_H__)
#define __CONFIG_H__

#include "Arduino.h"
#include "EEPROM.h"

class Config {
public:
  Config();
  ~Config();
  bool begin();
  void Check();
  //-----------------------------------
  String GetStationSSID(uint8_t idx);
  String GetStationPSK(uint8_t idx);
  uint8_t GetStationCount();
  //-----------------------------------
  String GetMyTZ();
  uint8_t GetMatrixPin();
  String GetColor();
  //-----------------------------------
  String GetNewsApiKey();
  //-----------------------------------
  bool GetShowTime();
  bool GetShowDate();
  bool GetShowWeather();
  bool GetShowNews();
  //-----------------------------------
  void SaveData(String jsonString);
  String LoadData();
  bool ParseJSONString(String jsonString, String* stationSSID, String* stationPSK, uint8_t& stationCount, String& myTZ, uint8_t& matrixPin, String& color, String& newsApiKey, bool& showTime, bool& showDate, bool& showWeather, bool& showNews);
private:
  void Save_I8(int address, int8_t value);
  void Save_UI8(int address, uint8_t value);
  void Save_I16(int address, int16_t value);
  void Save_UI16(int address, uint16_t value);
  void Save_I32(int address, int32_t value);
  void Save_UI32(int address, uint32_t value);
  void Save_String(int address, String str, int maxLength);
  //-----------------------------------
  int8_t Load_I8(int address);
  uint8_t Load_UI8(int address);
  int16_t Load_I16(int address);
  uint16_t Load_UI16(int address);
  int32_t Load_I32(int address);
  uint32_t Load_UI32(int address);
  String Load_String(int address, int maxLength);
  //-----------------------------------
  const int EEPROM_SIZE = 1024;
  //-----------------------------------
  const int EEPROM_ADDRESS_INITIALIZED = 0;
  const int EEPROM_ADDRESS_DATA = 1;
  //-----------------------------------
  String mStationSSID[10];
  String mStationPSK[10];
  uint8_t mStationCount;
  //-----------------------------------
  String mMyTZ;
  uint8_t mMatrixPin;
  String mColor;
  //-----------------------------------
  String mNewsApiKey;
  //-----------------------------------
  bool mShowTime;
  bool mShowDate;
  bool mShowWeather;
  bool mShowNews;
};

extern Config Cfg;

#endif  // !defined(__CONFIG_H__)
