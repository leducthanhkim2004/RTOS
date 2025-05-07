#ifndef SMART_CLIMATE_CONTROL_H
#define SMART_CLIMATE_CONTROL_H

// Include necessary headers
#include <Arduino.h>

// State definitions
#define INIT 0
#define RUNNING 1
#define WAITING 2

// Function declarations

void htmsensor_task();

// External variable declarations
extern float currentTemperature;
extern float currentHumidity;
extern bool sensorInitialized;

#endif // SMART_CLIMATE_CONTROL_H