
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
        // read data while running
        dht20.read();
        currentTemperature = dht20.getTemperature();
        currentHumidity = dht20.getHumidity();
        Serial.print("Temperature: ");
        Serial.print(currentTemperature);
        Serial.print(" °C, Humidity: ");
        Serial.print(currentHumidity);
        if (isTimerExpired(1) == 1)
        {
            state = WAITING;
            setTimer(1, 500); // Wait for 1 second before next reading
        }
        break;

    case WAITING:
        Serial.println("Waiting for next reading...");
        if (isTimerExpired(1) == 1)
        {
            state = RUNNING;
            setTimer(1, 100);
        }
        break;

    default:
        break;
    }
}