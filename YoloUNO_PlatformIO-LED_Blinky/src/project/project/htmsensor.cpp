
#include "htmsensor.h"
#include "software_time.h"
#include <Arduino.h>
#include <Wire.h>
#include "DHT20.h"
float currentTemperature = 0.0;
float currentHumidity = 0.0;
#define Timer 1
DHT20 dht20;
static int state = INIT;
void htmsensor_task()
{
    switch (state)
    {
    case INIT:
        Serial.begin(115200);
        dht20.begin();
        state = RUNNING;
        Serial.println("Sensor initialized.");
    case RUNNING:
        // read data while running
        dht20.read();
        currentTemperature = dht20.getTemperature();
        currentHumidity = dht20.getHumidity();
        Serial.print("Temperature: ");
        Serial.print(currentTemperature);
        Serial.print(" °C, Humidity: ");
        Serial.print(currentHumidity);
        Serial.println("%");
        break;
    }
}