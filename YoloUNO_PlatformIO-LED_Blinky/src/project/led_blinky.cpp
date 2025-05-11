#include <Arduino.h>
#include "software_time.h"
#include "led_blinky.h"

// State definitions
#define LED_ON 0
#define LED_OFF 1
#define INIT 2

// Use pin definitions for clarity - LED_BUILTIN or specific pin number
#define LED_PIN GPIO_NUM_48 // Green LED pin

static int state = INIT;

void led_blinky_task(void)
{
    switch (state)
    {
    case INIT:
        pinMode(LED_PIN, OUTPUT);
        setTimer(0, 100);
        state = LED_ON;
        break;
    case LED_ON:

        if (isTimerExpired(0) != 1)
        {
            break;
        }

        setTimer(0, 100);
        state = LED_OFF;
        digitalWrite(LED_PIN, HIGH);
        break;

    case LED_OFF:
        if (isTimerExpired(0) != 1)
        {
            break;
        }
        setTimer(0, 100);
        state = LED_ON;
        digitalWrite(LED_PIN, LOW);
        break;
    }
}
