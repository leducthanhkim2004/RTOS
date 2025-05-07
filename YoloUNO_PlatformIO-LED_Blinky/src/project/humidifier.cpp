#include "humidifier.h"
#include "DHT20.h"
#include "software_time.h"

#define D7 10
#define D8 17
#define TIMER_ID 4 // Use a consistent timer ID

// Define states
#define INIT 0
#define CHECK_STATE 1
#define GREEN 2
#define YELLOW 3
#define RED 4

float humidifier_threshold = 90.0;
static int state = INIT;
static DHT20 dht20;
float current_humid = 0.0;

void humidifier_fsm(void)
{
  switch (state)
  {
  case INIT:
    Serial.begin(115200);
    pinMode(D7, OUTPUT);
    pinMode(D8, OUTPUT);
    dht20.begin();
    setTimer(TIMER_ID, 100);
    state = CHECK_STATE;
    Serial.println("Humidifier initialized.");
    break;
  
  case CHECK_STATE:
    if (!isTimerExpired(TIMER_ID))
      break;
      
    dht20.read();
    current_humid = dht20.getHumidity();
    Serial.print("Current humidity: ");
    Serial.print(current_humid);
    Serial.println("%");
    
    if(current_humid < humidifier_threshold){
      Serial.println("Humidity below threshold. Starting humidifier sequence.");
      state = GREEN;
      digitalWrite(D7, HIGH);  // Turn on GREEN
      digitalWrite(D8, LOW);
      setTimer(TIMER_ID, 500);  // 5 seconds
    }
    else{
      Serial.println("Humidity is above threshold, no action needed.");
      digitalWrite(D7, LOW);   // Turn LEDs off
      digitalWrite(D8, LOW);
      setTimer(TIMER_ID, 300);  // Check again in 3 seconds
    }
    break;
    
  case GREEN:
    if (!isTimerExpired(TIMER_ID))
      break;
      
    Serial.println("Humidifier sequence: GREEN complete -> YELLOW");
    digitalWrite(D7, LOW);    // Change to YELLOW
    digitalWrite(D8, HIGH);
    setTimer(TIMER_ID, 300);  // 3 seconds
    state = YELLOW;
    break;
    
  case YELLOW:
    if (!isTimerExpired(TIMER_ID))
      break;
      
    Serial.println("Humidifier sequence: YELLOW complete -> RED");
    digitalWrite(D7, HIGH);   // Change to RED
    digitalWrite(D8, HIGH);
    setTimer(TIMER_ID, 200);  // 2 seconds
    state = RED;
    break;
    
  case RED:
    if (!isTimerExpired(TIMER_ID))
      break;
      
    Serial.println("Humidifier sequence complete. Checking humidity again.");
    digitalWrite(D7, LOW);    // Turn LEDs off
    digitalWrite(D8, LOW);
    setTimer(TIMER_ID, 100);  // Small delay before checking again
    state = CHECK_STATE;
    break;
    
  default:
    state = INIT;
    break;
  }
}