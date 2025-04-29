#include "heater.h"
#include "software_time.h"
#include <Arduino.h>  // Include Arduino header for Serial

// Heater LED pins
#define HEATER_LED_PIN1 6  // D3
#define HEATER_LED_PIN2 7  // D4

// Heater states
#define HEATER_STATE_INIT 0 
#define HEATER_STATE_SAFE 1  
#define HEATER_STATE_RISK 2 
#define HEATER_STATE_DANGEROUS 3 
#define HEATER_STATE_RUNNING 4 
#define HEATER_STATE_WAITING 5 

static int heater_state = HEATER_STATE_INIT; 

void heater_green() {
    digitalWrite(HEATER_LED_PIN1, HIGH);  // Green light
    digitalWrite(HEATER_LED_PIN2, LOW);
}

void heater_yellow() {
    digitalWrite(HEATER_LED_PIN1, HIGH);  // Yellow light (both LEDs on)
    digitalWrite(HEATER_LED_PIN2, HIGH);
}

void heater_red() {
    digitalWrite(HEATER_LED_PIN1, LOW);   // Red light
    digitalWrite(HEATER_LED_PIN2, HIGH);
}

void heater_off() {
    digitalWrite(HEATER_LED_PIN1, LOW);   // Turn off both LEDs
    digitalWrite(HEATER_LED_PIN2, LOW);
}

int determineTemperatureStage(float temperature) {
    if (temperature <= THRESHOLD_NORMAL && temperature >= THRESHOLD_LOW) {
        return HEATER_STATE_SAFE;
    }  
    if ((temperature < THRESHOLD_LOW && temperature >= THRESHOLD_FREEZING) 
         || (temperature > THRESHOLD_NORMAL && temperature <= THRESHOLD_HOT)) {
        return HEATER_STATE_RISK;
    }
    return HEATER_STATE_DANGEROUS;
}

void heater_task() {
    switch (heater_state) {
        case HEATER_STATE_INIT: {
            
            pinMode(HEATER_LED_PIN1, OUTPUT);  // Initialize heater LED pins
            pinMode(HEATER_LED_PIN2, OUTPUT);
            heater_state = HEATER_STATE_WAITING;
            setTimer(3, 399);
            break;
        }
        case HEATER_STATE_WAITING: {
            if (!isTimerExpired(3)) break;
            heater_state = HEATER_STATE_RUNNING;
            break;
        }
        case HEATER_STATE_RUNNING: {
            float current_temperature = 20.0;
            int temperature_stage = determineTemperatureStage(current_temperature);

            if (temperature_stage == HEATER_STATE_SAFE) {
                heater_green();
            } 
            else if (temperature_stage == HEATER_STATE_RISK) {
                heater_yellow();
            } 
            else if (temperature_stage == HEATER_STATE_DANGEROUS) {
                heater_red();
            }
            break;
        }
        default: {
            Serial.println("Unknown heater state. Resetting...");
            heater_state = HEATER_STATE_INIT;
            break;
        }
    }
}