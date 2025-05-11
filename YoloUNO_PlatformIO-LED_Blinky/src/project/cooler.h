//TODO : IMPLEMENT COOLER TIẾN KHOAKHOA

//TODO : IMPLEMENT COOLER TIẾN KHOAKHOA
#ifndef COOLER_H
#define COOLER_H

#include <Arduino.h>  // For digitalWrite and pin definitions

// Pin definitions for Cooler LED
#define D5 8  // Cooler LED (bit 0)
#define D6 9  // Cooler LED (bit 1)
#define INIT 0;
#define COOLER_OFF 1;
#define COOLER_ON 2;
extern float cooler_threshold;  

void cooler_task();
void cooler_on();
void cooler_off();


#endif