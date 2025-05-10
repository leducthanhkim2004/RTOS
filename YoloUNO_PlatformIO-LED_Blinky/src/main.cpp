#include <Arduino.h>
#include "project/software_time.h"
#include "project/humidifier.h"
#include "project/scheduler.h"
#include "project/cooler.h"
#include "project/heater.h"
#include "project/led_blinky.h"
#include "project/htmsensor.h"
void setup()
{   
    
    SCH_Init();
    SCH_Add_Task(timerRun, 0, 1);
    SCH_Add_Task(led_blinky_task,0,100);
    SCH_Add_Task(htmsensor_task, 0, 500);
    SCH_Add_Task(heater_task,0,100);
    SCH_Add_Task(cooler_task,0,100);
    SCH_Add_Task(humidifier_fsm,0,100);
}

void loop()
{
   
    SCH_Update();
    SCH_Dispatch_Tasks();
    delay(10);
}