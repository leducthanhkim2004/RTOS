//TODO : IMPLEMENT COOLER TIẾN KHOAKHOA

//TODO : IMPLEMENT COOLER TIẾN KHOAKHOA
#ifndef COOLER_H
#define COOLER_H

#include <Arduino.h>  // For digitalWrite and pin definitions

// Pin definitions for Cooler LED
#define D5 8  // Cooler LED (bit 0)
#define D6 9  // Cooler LED (bit 1)

// Cooler thresholds and timing
#define COOLER_THRESHOLD 30.0  // Temperature threshold for cooler activation
#define COOLER_DURATION_TICKS 5  // Duration in ticks (5 seconds)

#ifdef __cplusplus
extern "C" {
#endif

// Function prototypes
void cooler_green();
void cooler_off();
void cooler_task();
void init_cooler();
#ifdef __cplusplus
}
#endif

#endif