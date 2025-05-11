#include "cooler.h"
#include "software_time.h"
#include "htmsensor.h"
#define TIMER_ID 3
static int state = INIT;
float cooler_threshold = 25.0;
void cooler_on() {
  digitalWrite(D5, HIGH);
  digitalWrite(D6, LOW);
}
void cooler_off() {
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
}
void cooler_task() {
  switch (state) {
    case INIT:
      /* code */
      Serial.begin(115200);
      pinMode(D5, OUTPUT);
      pinMode(D6, OUTPUT);
      state = COOLER_OFF;
      Serial.println("Cooler initialized.");
      setTimer(TIMER_ID, 10);
      break;
    case COOLER_OFF:
      cooler_off();
      Serial.println("COOLER OFF");
      if (isTimerExpired(TIMER_ID) == 1) {
        if (currentTemperature > cooler_threshold) {
          Serial.println("Cooler state:  ON");
          state = COOLER_ON;
          setTimer(TIMER_ID, 500);
        } 
        else {
          state = COOLER_OFF;
          Serial.println("Cooler state: OFF");
        }
      }
      break;
    case COOLER_ON:
        cooler_on();
        Serial.println("COOLER ON");
      if (isTimerExpired(TIMER_ID) == 1) {
          state = COOLER_OFF;
      }
      break;
  }
}