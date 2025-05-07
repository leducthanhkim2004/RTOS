#include "cooler.h"
#include "software_time.h"
#include "DHT20.h"
#define TIMER_ID 3
static int state = INIT;
static DHT20 dht20;
static float current_temp = 0.0;
float cooler_threshold = 25.0;
void cooler_task()
{
    switch (state)
    {
    case INIT:
        /* code */
        Serial.begin(115200);
        pinMode(D5, OUTPUT);
        pinMode(D6, OUTPUT);
        dht20.begin();
        state = CHECK_STATE;
        Serial.println("Cooler initialized.");
        setTimer(TIMER_ID, 100);
        break;
    case CHECK_STATE:
        if (!isTimerExpired(TIMER_ID))
            break;

        dht20.read();
        current_temp = dht20.getTemperature();
        Serial.print("Current temperature: ");
        Serial.print(current_temp);
        Serial.println("°C");

        if (current_temp > cooler_threshold)
        {
            Serial.println("Temperature above threshold. Starting cooler sequence.");
            digitalWrite(D5, HIGH);
            digitalWrite(D6, LOW);
            setTimer(TIMER_ID, 5000);
        }
        else
        {
            Serial.println("Temperature is below threshold, no action needed.");
            digitalWrite(D5, LOW);
            digitalWrite(D6, LOW);
            setTimer(TIMER_ID, 3000);
            break;
        default:
            state = INIT; 
            break;
        }
    }
}