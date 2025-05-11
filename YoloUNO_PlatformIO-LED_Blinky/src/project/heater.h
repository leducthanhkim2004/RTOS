//TODO: IMPLEMENT HEATER MINH TRÍ 

#ifndef HEATER_H
#define HEATER_H

#include <Arduino.h>  


#define HEATER_STATE_INIT 0 
#define HEATER_CHECK_STATE 1
#define HEATER_GREEN 2
#define HEATER_YELLOW 3
#define HEATER_RED 4
#define THRESHOLD_LOW 5.0        // Example: 5°C
#define THRESHOLD_NORMAL 25.0    // Example: 25°C



// Function prototypes
void heater_task();

#endif 