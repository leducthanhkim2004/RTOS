
#include "htmsensor.h"
#include "software_time.h"
#include <Arduino.h>
#include <Wire.h>
#include "DHT20.h"
float currentTemperature = 0.0;
float currentHumidity = 0.0;

DHT20 dht20;
static int state = INIT;
void htmsensor_task()
{
    switch (state)
    {
    case INIT:
        Serial.begin(115200);
        dht20.begin();
        setTimer(1, 100);
        state = RUNNING;
        Serial.println("Sensor initialized.");
        break;

    case RUNNING:
        if (!isTimerExpired(1))
            break;
        state = WAITING;
        setTimer(1, 500);
        dht20.read();
        currentTemperature = dht20.getTemperature();
        currentHumidity = dht20.getHumidity();
        Serial.print("Temperature: ");
        Serial.print(currentTemperature); // FIXED: Added printing the temperature value
        Serial.println(" C");             // FIXED: Added units
        Serial.print("Humidity: ");
        Serial.print(currentHumidity);
        Serial.println("%"); // FIXED: Added println
        break;               // FIXED: Removed duplicate state assignment

    case WAITING:
        if (!isTimerExpired(1))
            break;       // FIXED: Added timer check
        state = RUNNING; // FIXED: Changed to RUNNING (was INIT)
        Serial.println("HTMSensor waiting for next reading.");
        setTimer(1, 100); // FIXED: Set 5 seconds between readings
        break;             // FIXED: Added break statement

    default:
        break;
    }
}