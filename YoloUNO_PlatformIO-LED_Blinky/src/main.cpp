#include <Arduino.h>
#include "project/software_time.h"
#include "project/humidifier.h"
#include "project/scheduler.h"
#include "project/cooler.h"
#include "project/heater.h"
#include "project/led_blinky.h" 



void setup() {
  Serial.begin(115200);
  init_cooler();
  init_led_blinky(); 
  //init_humidifier();
  SCH_Init();
  //SCH_Add_Task(humidifier_fsm, 0, 1);
  // SCH_Add_Task(cooler_green, 0, 1);
  // SCH_Add_Task(cooler_task, 0,1);
  SCH_Add_Task(timerRun, 0, 1);
  // SCH_Add_Task(heater_task, 0, 1);
  SCH_Add_Task(led_blinky_task, 0, 1);  

}

void loop() {
  // Serial.println("Hello Custom Board");
  // delay(1000);
  SCH_Dispatch_Tasks();
  SCH_Update();
}