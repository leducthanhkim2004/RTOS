#include "led_blinky.h"
#include "software_time.h"
#include <Arduino.h>

// Hardware Definitions
#define LED_BLINKY_PIN  48  // Onboard LED (GPIO48)

// States
#define LED_OFF  0
#define LED_ON   1

// Global State
static int led_state = LED_OFF;

void init_led_blinky(void) {
  pinMode(LED_BLINKY_PIN, OUTPUT);
  digitalWrite(LED_BLINKY_PIN, LOW);  // Start with LED off
  setTimer(1, 1000);  // Initial 1s delay before first blink
}

void led_blinky_task(void) {
  if (isTimerExpired(1)) {
    switch (led_state) {
      case LED_OFF:
        digitalWrite(LED_BLINKY_PIN, HIGH);
        led_state = LED_ON;
        break;
      case LED_ON:
        digitalWrite(LED_BLINKY_PIN, LOW);
        led_state = LED_OFF;
        break;
      default:
        led_state = LED_OFF;  // Handle invalid states
        break;
    }
    setTimer(1, 1000);  // Reset timer for next state (1s interval)
  }
}
