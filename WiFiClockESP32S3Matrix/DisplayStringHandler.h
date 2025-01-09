#ifndef DisplayStringHandler_h
#define DisplayStringHandler_h

#include <Arduino.h>
#include "Period.h"

class DisplayStringHandler {
public:
  DisplayStringHandler(uint32_t tryToUpdateIntervalInMS, uint32_t reupdateIntervalInCycles, const char* color, const char* name, const char* nextName);
  virtual ~DisplayStringHandler();
  virtual void Check();
  virtual bool IsDataUpdated();
  String GetDisplayString();
  String GetColor();
  String GetName();
  String GetNextName();
protected:
  static void OnPeriodExpiredStaticUpdate(void* instance);
  void OnPeriodExpiredUpdate();
  virtual void OnPerformUpdate();
protected:
  Period* mPeriodUpdate;
  uint32_t mReupdateIntervalInCycles;
  uint32_t mReupdateIntervalCycleCounter;
  String mDisplayString;
  String mColor;
  String mName;
  String mNextName;
};

#endif  //DisplayStringHandler_h