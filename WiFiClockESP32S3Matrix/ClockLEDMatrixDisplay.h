#ifndef ClockLEDMatrixDisplay_h
#define ClockLEDMatrixDisplay_h

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include "Config.h"
#include "Period.h"
#include "DisplayStringHandler.h"
#include "DisplayStringManager.h"

class ClockLEDMatrixDisplay {
public:
  ClockLEDMatrixDisplay();
  virtual ~ClockLEDMatrixDisplay();
  void Init();
  void Check();
  void SetDisplayStringManager(DisplayStringManager* displayStringManager);
private:
  void OnEndOfScrolling();
  static void OnPeriodExpiredStaticScroll(void* instance);
  void OnPeriodExpiredScroll();
  static void OnPeriodExpiredStaticChange(void* instance);
  void OnPeriodExpiredChange();
private:
  Period* mPeriodScroll;
  Period* mPeriodChange;
  DisplayStringManager* mDisplayStringManager;
  DisplayStringHandler* mLastDisplayStringHandler;
  Adafruit_NeoMatrix* mMatrix;
  uint16_t mColor;
  int16_t mFirstColumnBackOffset;
  bool mIsWaiting;
};

#endif  //ClockLEDMatrixDisplay_h