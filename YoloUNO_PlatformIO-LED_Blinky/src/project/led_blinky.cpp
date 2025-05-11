#include <Arduino.h>
#include "software_time.h"
#include "led_blinky.h"

// State definitions
#define LED_ON 0
#define LED_OFF 1
#define INIT 2
#define TIMER_ID 0
// Use pin definitions for clarity - LED_BUILTIN or specific pin number
#define LED_PIN GPIO_NUM_48 // Green LED pin

static int state = INIT;

void led_blinky_task(void)
{
    switch (state)
    {
    case INIT:
        pinMode(LED_PIN, OUTPUT);
        setTimer(0, 10);
        state = LED_ON;
        Serial.println(TIMER_ID);
        break;
    case LED_ON:
        digitalWrite(LED_PIN, HIGH);
        if (isTimerExpired(TIMER_ID) == 1)
        {
            setTimer(0, 100);
            state = LED_OFF;
        }
        break;

    case LED_OFF:
        digitalWrite(LED_PIN, LOW);
        if (isTimerExpired(TIMER_ID) == 1)
        {
            setTimer(0, 100);
            state = LED_ON;
        }
        break;
    }
}
