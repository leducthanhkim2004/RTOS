#include "humidifier.h"
#include "DHT20.h"
#include "software_time.h"
#include "htmsensor.h"
#define D7 10
#define D8 17
#define TIMER_ID 4  // Use a consistent timer ID

// Define states
#define INIT 0
#define CHECK_STATE 1
#define GREEN 2
#define YELLOW 3
#define RED 4

float humidifier_threshold = 40.0;
static int state = INIT;

void humidifier_fsm(void) {
  switch (state) {
    case INIT:
      pinMode(D7, OUTPUT);
      pinMode(D8, OUTPUT);
      setTimer(TIMER_ID, 10);
      state = OFF;
      Serial.println("Humidifier initialized.");
      break;

    case OFF:
      digitalWrite(D7, LOW);
      digitalWrite(D8, LOW);
      Serial.println("Humidifier state: OFF");
      if (isTimerExpired(TIMER_ID)) {
        if (currentHumidity < humidifier_threshold) {
          Serial.println("Humidifier state: ON");
          state = GREEN;
          setTimer(TIMER_ID, 500);
        } else {
          state = OFF;
        }
      }
      break;

    case GREEN:
      digitalWrite(D7, HIGH);
      digitalWrite(D8, LOW);
      Serial.println("GREEN LED ON");

      if (isTimerExpired(TIMER_ID)) {
        state = YELLOW;
        setTimer(TIMER_ID, 300);
      }
      break;
    case YELLOW:
      // todo: YELLOW LED
      digitalWrite(D7, LOW);
      digitalWrite(D8, HIGH);
      Serial.println("Humidifier sequence: YELLOW LED ON");
      if (isTimerExpired(TIMER_ID)) {
        state = RED;
        setTimer(TIMER_ID, 200);
      }
      break;
    case RED:
      digitalWrite(D7, HIGH);
      digitalWrite(D8, HIGH);
      Serial.println("Humidifier sequence: RED LED ON");
      if (isTimerExpired(TIMER_ID)) {
        state = OFF;
      }
      break;
    default:
      break;
  }
}