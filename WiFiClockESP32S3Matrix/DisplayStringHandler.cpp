#include "DisplayStringHandler.h"
#include "CommonFunctions.h"

DisplayStringHandler::DisplayStringHandler(uint32_t tryToUpdateIntervalInMS, uint32_t reupdateIntervalInCycles, const char* name, const char* nextName) {
  mReupdateIntervalInCycles = reupdateIntervalInCycles;
  mReupdateIntervalCycleCounter = 0;
  mDisplayString = "";
  mName = String(name);
  mNextName = String(nextName);
  mPeriodUpdate = new Period(this, tryToUpdateIntervalInMS, true);
  mPeriodUpdate->AddOnPeriodExpiredHandler(DisplayStringHandler::OnPeriodExpiredStaticUpdate);
}
DisplayStringHandler::~DisplayStringHandler() {
  if (mPeriodUpdate) {
    delete mPeriodUpdate;
    mPeriodUpdate = NULL;
  }
}
void DisplayStringHandler::Check() {
  mPeriodUpdate->Check(millis());
}
bool DisplayStringHandler::IsDataUpdated() {
  return false;
}
String DisplayStringHandler::GetDisplayString() {
  return mDisplayString;
}
String DisplayStringHandler::GetName() {
  return mName;
}
String DisplayStringHandler::GetNextName() {
  return mNextName;
}
void DisplayStringHandler::OnPeriodExpiredStaticUpdate(void* instance) {
  DisplayStringHandler* dsh = (DisplayStringHandler*)instance;
  if (dsh != NULL) dsh->OnPeriodExpiredUpdate();
}
void DisplayStringHandler::OnPeriodExpiredUpdate() {
  if (!IsDataUpdated()) {
    OnPerformUpdate();
  } else if (mReupdateIntervalInCycles > 0) {
    if (mReupdateIntervalCycleCounter == (mReupdateIntervalInCycles - 1)) {
      OnPerformUpdate();
    }
    increment_modulo(mReupdateIntervalCycleCounter, mReupdateIntervalInCycles);
  }
}
void DisplayStringHandler::OnPerformUpdate() {
}
