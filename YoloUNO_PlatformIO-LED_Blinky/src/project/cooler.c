#include "cooler.h"
#include "software_time.h"
#include <Arduino.h>  // Include Arduino header for Serial

#define COOLER_TIMER_DURATION 5000  // Timer duration in milliseconds
static float temperature = 35.0;  // Shared temperature variable
static int cooler_state;          // FSM state: 0=Check, 1=Active
static int cooler_counter;        // Countdown for active duration

void cooler_green() {
    digitalWrite(D5, HIGH);  // 10 = Green
    digitalWrite(D6, LOW);
}

void cooler_off() {
    digitalWrite(D5, LOW);   // 00 = Off
    digitalWrite(D6, LOW);
}

void handle_check_state() {
    
    Serial.print("Temperature: ");
    Serial.println(temperature);
    if (temperature > COOLER_THRESHOLD) {
        Serial.println("Cooler activated.");
        cooler_green();
        cooler_state = 1;
    } 
}

void handle_active_state() {
    Serial.println("Cooler deactivated.");
    cooler_off();
    cooler_state = 0;
}

void cooler_task() {
    switch (cooler_state) {
        case 0:
            handle_check_state();
            break;
        case 1:
            handle_active_state();
            break;
        default:
            Serial.println("Unknown state. Resetting to default state.");
            cooler_state = 0;
            break;
    }
}

void init_cooler() {
    pinMode(D5, OUTPUT);  // Set D5 as output for cooler LED
    pinMode(D6, OUTPUT);  // Set D6 as output for cooler LED
    cooler_off();         // Ensure cooler is off initially
    cooler_state = 0;     // Initialize state to "Check"
    cooler_counter = 0;   // Reset counter
    Serial.println("Cooler initialized.");
}