#include "SmartClimateControl.h"
#include "software_time.h"
#include <Arduino.h>
#include <Wire.h>
#include <DHT20.h> // Library for DHT20 sensor (humidity and temperature)

// Hardware Definitions
#define SERIAL_BAUD 115200              // Serial baud rate
#define SENSOR_READ_INTERVAL 5000       // Sensor reading interval: 5 seconds (ms)
#define SENSOR_READ_TICKS 500           // 5000ms / 10ms = 500 ticks
#define SENSOR_TIMER 0                  // Timer index for sensor readings

// Global State
static DHT20 dht20; // DHT20 sensor instance
static bool sensorInitialized = false; // Sensor initialization status

// Initialize hardware (DHT20 sensor and Serial)
void init_smart_climate_control(void) {
    // Initialize Serial for sensor data output
    Serial.begin(SERIAL_BAUD);
    while (!Serial) {
        // Wait for Serial to initialize (non-blocking, no delay())
    }
    
    // Initialize I2C for DHT20
    Wire.begin();
    if (dht20.begin()) {
        Serial.println("DHT20 initialized successfully");
        sensorInitialized = true;
    } else {
        Serial.println("DHT20 initialization failed!");
        sensorInitialized = false;
    }
    
    setTimer(SENSOR_TIMER, SENSOR_READ_INTERVAL); // Initial 5s timer
}

/*
 * Smart Climate Control Task
 * - Executes every 5 seconds (SENSOR_READ_INTERVAL = 5000ms)
 * - Reads humidity and temperature from DHT20 sensor via I2C
 * - Outputs data to Serial at 115200 baud with millisecond timestamps
 * - Uses software timer (SENSOR_TIMER) to enforce 5-second interval
 * - Scheduled via provided scheduler, no delay() calls
 */
void smart_climate_control_task(void) {
    if (isTimerExpired(SENSOR_TIMER)) {
        if (sensorInitialized) {
            // Read humidity and temperature from DHT20
            if (dht20.available()) {
                float temperature = dht20.readTemperature();
                float humidity = dht20.readHumidity();
                Serial.print("[");
                Serial.print(millis());
                Serial.print(" ms] Temperature: ");
                Serial.print(temperature);
                Serial.print(" °C, Humidity: ");
                Serial.print(humidity);
                Serial.println(" %");
            } else {
                Serial.print("[");
                Serial.print(millis());
                Serial.println(" ms] Failed to read from DHT20 sensor!");
            }
        } else {
            Serial.print("[");
            Serial.print(millis());
            Serial.println(" ms] Sensor not initialized!");
        }
        
        // Reset timer for next 5-second interval
        setTimer(SENSOR_TIMER, SENSOR_READ_INTERVAL);
    }
}

// Main setup and loop for integration with scheduler
void setup() {
    init_smart_climate_control();
    SCH_Init();
    SCH_Add_Task(smart_climate_control_task, 0, SENSOR_READ_TICKS);
}

void loop() {
    timerRun();
    SCH_Update();
    SCH_Dispatch_Tasks();
}
