//TODO: IMPLEMENT HEATER MINH TRÍ 

#ifndef HEATER_H
#define HEATER_H

#include <Arduino.h>  


#define HEATER_STATE_INIT 0 
#define HEATER_GREEN 1
#define HEATER_YELLOW 2
#define HEATER_RED 3
 
#define THRESHOLD_LOW 5.0        // Example: 5°C DUOI 5 D0 MAU DO
#define THRESHOLD_NORMAL 25.0    // Example: 25°C TREN 25 MAU VANG GIUA LA XANH




// Function prototypes
void heater_task();

#endif 