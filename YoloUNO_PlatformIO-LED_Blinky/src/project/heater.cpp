#include "heater.h"
#include "software_time.h"
#include <Arduino.h> // Include Arduino header for Serial
#include "DHT20.h"   // Include DHT20 library for temperature sensor
#include "htmsensor.h"
// Heater LED pins
#define HEATER_LED_PIN1 6 // D3
#define HEATER_LED_PIN2 7 // D4

// Heater states
#define HEATER_STATE_INIT 0
#define HEATER_CHECK_STATE 1

#define Timer_ID 2
static int heater_state = HEATER_STATE_INIT;

void heater_task()
{

    switch (heater_state)
    {
    case HEATER_STATE_INIT:
        /* code */
        pinMode(HEATER_LED_PIN1, OUTPUT);
        pinMode(HEATER_LED_PIN2, OUTPUT);
        Serial.begin(115200);
        Serial.println("Heater initialized");
        setTimer(Timer_ID ,10);
        heater_state = HEATER_GREEN;
        break;
    case HEATER_GREEN:
        digitalWrite(HEATER_LED_PIN1, HIGH);
        digitalWrite(HEATER_LED_PIN2, LOW);
        Serial.println("HEATER GREEN");
        if (isTimerExpired(Timer_ID))
        {
            if (THRESHOLD_LOW > currentTemperature)
            {
                heater_state = HEATER_RED;
            }
            else if (currentTemperature >= THRESHOLD_NORMAL)
            {
                heater_state = HEATER_YELLOW;
            }
        }
        break;
    case HEATER_YELLOW:
        //TODO: YELLOW LED
        digitalWrite(HEATER_LED_PIN1, LOW);
        digitalWrite(HEATER_LED_PIN2, HIGH);
        Serial.println("HEATER YELLOW");
        if(isTimerExpired(Timer_ID))
        {
            if (currentTemperature <= THRESHOLD_NORMAL && currentTemperature >= THRESHOLD_LOW)
            {
                heater_state = HEATER_GREEN;
            }
            else if (currentTemperature < THRESHOLD_LOW)
            {
                heater_state = HEATER_RED;
            }
            
        }
        break;
    case HEATER_RED:
        //TODO: RED LED
        digitalWrite(HEATER_LED_PIN1, HIGH);
        digitalWrite(HEATER_LED_PIN2, HIGH);
        Serial.println("HEATER RED");
        if (isTimerExpired(Timer_ID))
        {
            if (currentTemperature > THRESHOLD_NORMAL)
            {
                heater_state = HEATER_YELLOW;
            }
            else if (currentTemperature <= THRESHOLD_NORMAL && currentTemperature >= THRESHOLD_LOW )
            {
                heater_state = HEATER_GREEN;
            }
        }
        break;
    default:
        break;
    }
}