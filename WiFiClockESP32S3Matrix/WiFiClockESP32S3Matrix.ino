#include <Arduino.h>
#include "ClockLEDMatrixDisplay.h"
#include "DisplayStringManager.h"
#include "Config.h"

ClockLEDMatrixDisplay clmd;
DisplayStringManager dsm(&clmd);

void setup() {
  Serial.begin(115200);
  Serial.setRxBufferSize(512);
  Cfg.begin();
  clmd.Init();
  clmd.SetDisplayStringManager(&dsm);
}
void loop() {
  Cfg.Check();
  clmd.Check();
  dsm.Check();
}
