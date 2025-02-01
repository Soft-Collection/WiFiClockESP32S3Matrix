#include <Arduino.h>
#include "ClockLEDMatrixDisplay.h"
#include "DisplayStringManager.h"
#include "Config.h"

#if CONFIG_FREERTOS_UNICORE
#define TASK_RUNNING_CORE 0
#else
#define TASK_RUNNING_CORE 1
#endif

void TaskLeds(void *pvParameters);
void TaskOther(void *pvParameters);

ClockLEDMatrixDisplay clmd;
DisplayStringManager dsm(&clmd);

void setup() {
  Serial.begin(115200);
  Serial.setRxBufferSize(512);
  Cfg.begin();
  clmd.Init();
  clmd.SetDisplayStringManager(&dsm);  
  //---------------------------------------------------
  xTaskCreate(
    TaskLeds, "Task Leds"  // A name just for humans
    ,
    8192  // The stack size can be checked by calling `uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);`
    ,
    NULL  // When no parameter is used, simply pass NULL
    ,
    2  // High Priority
    ,
    NULL  // Task handle is not used here - simply pass NULL
  );
  //---------------------------------------------------
  // This variant of task creation can also specify on which core it will be run (only relevant for multi-core ESPs)
  xTaskCreatePinnedToCore(
    TaskOther, "Task Other"  // A name just for humans
    ,
    8192  // The stack size can be checked by calling `uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);`
    ,
    NULL  // When no parameter is used, simply pass NULL
    ,
    1  // Low Priority
    ,
    NULL  // Task handle is not used here - simply pass NULL
    ,
    TASK_RUNNING_CORE  // Core on which the task will run
  );
}
void loop() {
}
void TaskLeds(void *pvParameters) {
  while (true) {
    clmd.Check();
  }
}
void TaskOther(void *pvParameters) {
  while (true) {
    Cfg.Check();
    dsm.Check();
  }
}
