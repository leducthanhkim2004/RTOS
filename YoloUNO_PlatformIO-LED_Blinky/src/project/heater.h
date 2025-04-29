//TODO: IMPLEMENT HEATER MINH TRÍ 

#ifndef HEATER_H
#define HEATER_H

#include <Arduino.h>  // For digitalWrite, pinMode, Serial, etc.

// #ifdef __cplusplus
// extern "C" {
// #endif


// Heater state definitions
#define HEATER_STATE_INIT 0 
#define HEATER_STATE_SAFE 1  
#define HEATER_STATE_RISK 2 
#define HEATER_STATE_DANGEROUS 3 
#define HEATER_STATE_RUNNING 4 
#define HEATER_STATE_WAITING 5

#define THRESHOLD_FREEZING 0.0   // Example: 0°C
#define THRESHOLD_LOW 5.0        // Example: 5°C
#define THRESHOLD_NORMAL 25.0    // Example: 25°C
#define THRESHOLD_HOT 35.0       // Example: 35°C


// Function prototypes
void heater_task();
int determineTemperatureStage(float temperature);

// #ifdef __cplusplus
// }
// #endif

#endif // HEATER_H