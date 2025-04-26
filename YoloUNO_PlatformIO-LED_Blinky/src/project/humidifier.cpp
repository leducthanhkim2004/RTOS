#include "humidifier.h"
#include "software_time.h"
#include <Arduino.h>

// Define pins
#define D7 10
#define D8 17

// Define states
#define CHECK_HUMID_STATE 0  // Check humidity state
#define GREEN_STATE 1        // Green LED state - 3 seconds
#define YELLOW_STATE 2       // Yellow LED state - 2 seconds
#define RED_STATE 3          // Red LED state - 5 seconds

// Global variables
static int state = CHECK_HUMID_STATE;
float humidifier_threshold = 35.0;

// Function to turn off all LEDs
void ledOff() {
  digitalWrite(D7, LOW);
  digitalWrite(D8, LOW);
}

// Function for GREEN LED
void greenLed() {
  digitalWrite(D7, HIGH);
  digitalWrite(D8, LOW);
}

// Function for YELLOW LED
void yellowLed() {
  digitalWrite(D7, LOW);
  digitalWrite(D8, HIGH);
}

// Function for RED LED
void redLed() {
  digitalWrite(D7, HIGH);
  digitalWrite(D8, HIGH);
}

// Function to read humidity
float read_humid() {
  // Generate random humidity between 30% and 60%
  float humidity = 30.0 + (random(300) / 10.0);
  return humidity;
}

void humidifier_fsm(void) {
  switch(state) {
    case CHECK_HUMID_STATE:
      // Only change state when timer expires
      if (isTimerExpired(0)) {
        // Check humidity and compare to threshold
        float current_humid = read_humid();
        
        // Simplified logic - just check humidity against threshold
        if (current_humid < humidifier_threshold) {
          state = GREEN_STATE;
          greenLed();
          setTimer(0, 5000); // 5 seconds for GREEN
        } else {
          // Reset timer to check again later
          setTimer(0, 1000); // Check every second
        }
      }
      break;
      
    case GREEN_STATE:
      if (isTimerExpired(0)) {
        state = YELLOW_STATE;
        yellowLed();
        setTimer(0, 3000); // 3 seconds for YELLOW
      }
      break;
      
    case YELLOW_STATE:
      if (isTimerExpired(0)) {
        state = RED_STATE;
        redLed();
        setTimer(0, 2000); // 2 seconds for RED
      }
      break;
      
    case RED_STATE:
      if (isTimerExpired(0)) {
        // After RED, go back to CHECK_HUMID_STATE to check humidity again
        state = CHECK_HUMID_STATE;
        ledOff();
        setTimer(0, 3000); // 3 seconds before checking humidity again
      }
      break;
      
    default:
      break;
  }
}

void init_humidifier(void) {
  // Configure pins
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  
  // Initialize random number generator
  randomSeed(analogRead(0));
  
  // Initialize with LEDs off
  ledOff();
  setTimer(0, 100);
}