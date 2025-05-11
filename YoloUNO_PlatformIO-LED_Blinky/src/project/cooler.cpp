#include "cooler.h"
#include "software_time.h"
#include "htmsensor.h"
#define TIMER_ID 2
static int state = INIT;
float cooler_threshold = 25.0;
void cooler_on()
{
    digitalWrite(D5, HIGH); 
    digitalWrite(D6, LOW);  
}
void cooler_off()
{
    digitalWrite(D5, LOW); 
    digitalWrite(D6, LOW);
    
}
void cooler_task()
{
    switch (state)
    {
    case INIT:
        /* code */
        Serial.begin(115200);
        pinMode(D5, OUTPUT);
        pinMode(D6, OUTPUT);
        state = COOLER_OFF;
        Serial.println("Cooler initialized.");
        setTimer(TIMER_ID, 100);
        break;
    case COOLER_OFF:
        if(!isTimerExpired(TIMER_ID))
            break;
        setTimer(TIMER_ID, 100);
        cooler_off();
        if(currentTemperature > cooler_threshold)
        {
            
            Serial.print("Current temperature:");
            Serial.println(currentTemperature);
            Serial.println("Cooler state:  ON");
            state = COOLER_ON;
            cooler_on();
        }
        break;
    case COOLER_ON:
        if(!isTimerExpired(TIMER_ID))
            break;
        setTimer(TIMER_ID, 100);
        cooler_on();
        if(currentTemperature <= cooler_threshold)
        {
            Serial.print("Current temperature:");
            Serial.println(currentTemperature);
            Serial.println("Cooler state:  OFF");
            state = COOLER_OFF;
            cooler_off();
        }
        break;
    }
}