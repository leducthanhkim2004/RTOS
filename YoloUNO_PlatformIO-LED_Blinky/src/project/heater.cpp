#include "heater.h"
#include "software_time.h"
#include <Arduino.h> // Include Arduino header for Serial
#include "DHT20.h"   // Include DHT20 library for temperature sensor
// Heater LED pins
#define HEATER_LED_PIN1 6 // D3
#define HEATER_LED_PIN2 7 // D4

// Heater states
#define HEATER_STATE_INIT 0
#define HEATER_CHECK_STATE 1

#define Timer_ID 2
static int heater_state = HEATER_STATE_INIT;
static DHT20 dht20;
static float current_temp = 0.0;
void heater_task()
{
    
    switch (heater_state)
    {
    case HEATER_STATE_INIT:
        /* code */
        pinMode(HEATER_LED_PIN1, OUTPUT); 
        pinMode(HEATER_LED_PIN2, OUTPUT);
        dht20.begin(); 
        Serial.begin(115200);
        Serial.println("Heater initialized");
        setTimer(Timer_ID,100);
        heater_state = HEATER_CHECK_STATE;
        break;
    case HEATER_CHECK_STATE:
        if(!isTimerExpired(Timer_ID))
            break;
        dht20.read();
        current_temp = dht20.getTemperature();
        Serial.print("Current temperature: ");
        Serial.print(current_temp);
        Serial.println("°C");
        if (current_temp <= THRESHOLD_LOW)
        {
            Serial.println("Temperature below low threshold. Starting heater sequence.Green led");
            digitalWrite(HEATER_LED_PIN1, HIGH); 
            digitalWrite(HEATER_LED_PIN2, LOW);  
            setTimer(Timer_ID, 5000);            
        }
        else if (THRESHOLD_LOW<current_temp <= THRESHOLD_NORMAL)
        {
            Serial.println("Temperature below normal threshold. Starting heater sequence.Yellow led");
            digitalWrite(HEATER_LED_PIN1, LOW); 
            digitalWrite(HEATER_LED_PIN2, HIGH);  
            setTimer(Timer_ID, 5000);            
        }
        else if (current_temp > THRESHOLD_NORMAL)
        {
            Serial.println("Temperature over normal. Starting heater sequence.Red led");
            digitalWrite(HEATER_LED_PIN1, HIGH); // Turn on LED1
            digitalWrite(HEATER_LED_PIN2, HIGH);  // Turn off LED2
            setTimer(Timer_ID, 5000);            // 5 seconds
        }
        heater_state = HEATER_CHECK_STATE;
    default:
        heater_state = HEATER_STATE_INIT; 
        break;
    }
}