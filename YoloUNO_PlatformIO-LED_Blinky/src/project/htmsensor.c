#include "Arduino.h"
#include "scheduler.h"
#include "software_time.h"
#include <Wire.h>
#include <AHT20.h> // Library for DHT20 sensor (humidity and temperature only)
#include <esp_sleep.h> // For low-power mode

// Sensor reading interval: 5 seconds (in milliseconds)
#define SENSOR_READ_INTERVAL 5000

// Timer indices
#define SENSOR_TIMER 0
#define RETRY_TIMER 1

// Serial baud rate
#define SERIAL_BAUD 115200

// Maximum retries for DHT20 initialization
#define MAX_SENSOR_RETRIES 5

// Buffer size for averaging sensor readings
#define AVG_BUFFER_SIZE 3

// Serial command buffer
#define COMMAND_BUFFER_SIZE 16

// Data structure for sensor readings (humidity and temperature)
struct ClimateData {
    float temperature;
    float humidity;
    bool valid;
};

// Global variables
ClimateData latestData; // Latest sensor reading
ClimateData readingBuffer[AVG_BUFFER_SIZE]; // Buffer for averaging
uint8_t bufferIndex = 0; // Current buffer position
uint8_t bufferCount = 0; // Number of valid readings in buffer
char commandBuffer[COMMAND_BUFFER_SIZE]; // Serial command buffer
uint8_t commandIndex = 0; // Current command buffer position

// DHT20 sensor instance
AHT20 dht20;

// Initialize hardware (DHT20 sensor and Serial)
bool initHardware() {
    // Initialize Serial for sensor data output and commands
    Serial.begin(SERIAL_BAUD);
    while (!Serial) {
        // Wait for Serial to initialize (non-blocking, no delay())
    }
    
    // Initialize I2C for DHT20
    Wire.begin();
    for (uint8_t retry = 0; retry < MAX_SENSOR_RETRIES; retry++) {
        if (dht20.begin()) {
            Serial.println("DHT20 initialized successfully");
            return true;
        }
        Serial.print("DHT20 initialization failed, retry ");
        Serial.print(retry + 1);
        Serial.print(" of ");
        Serial.println(MAX_SENSOR_RETRIES);
        // Wait 1 second between retries using software timer
        setTimer(RETRY_TIMER, 1000);
        while (!isTimerExpired(RETRY_TIMER)) {
            timerRun();
            SCH_Update();
            SCH_Dispatch_Tasks();
        }
    }
    Serial.println("DHT20 initialization failed after all retries!");
    return false;
}

/*
 * Average Sensor Readings
 * - Computes average of valid readings in readingBuffer
 * - Returns true if average is computed, false if insufficient valid data
 */
bool averageSensorReadings(ClimateData &result) {
    if (bufferCount < AVG_BUFFER_SIZE) {
        return false; // Not enough valid readings
    }
    
    float tempSum = 0.0;
    float humSum = 0.0;
    uint8_t validCount = 0;
    
    for (uint8_t i = 0; i < AVG_BUFFER_SIZE; i++) {
        if (readingBuffer[i].valid) {
            tempSum += readingBuffer[i].temperature;
            humSum += readingBuffer[i].humidity;
            validCount++;
        }
    }
    
    if (validCount == AVG_BUFFER_SIZE) {
        result.temperature = tempSum / AVG_BUFFER_SIZE;
        result.humidity = humSum / AVG_BUFFER_SIZE;
        result.valid = true;
        return true;
    }
    return false;
}

/*
 * Process Serial Commands
 * - Reads incoming serial data into commandBuffer
 * - Supports commands:
 *   - READ: Triggers immediate sensor reading
 *   - STATUS: Prints system status (uptime, valid readings count)
 * - Non-blocking, no delay()
 */
void processSerialCommands() {
    while (Serial.available() && commandIndex < COMMAND_BUFFER_SIZE - 1) {
        char c = Serial.read();
        if (c == '\n' || c == '\r') {
            commandBuffer[commandIndex] = '\0';
            if (strcmp(commandBuffer, "READ") == 0) {
                // Trigger immediate sensor reading
                setTimer(SENSOR_TIMER, 0); // Expire timer to force reading
                Serial.println("Triggered immediate sensor reading");
            } else if (strcmp(commandBuffer, "STATUS") == 0) {
                // Print system status
                Serial.print("Uptime: ");
                Serial.print(millis() / 1000);
                Serial.print(" s, Valid readings: ");
                Serial.println(bufferCount);
            }
            commandIndex = 0;
        } else {
            commandBuffer[commandIndex++] = c;
        }
 septum
    if (commandIndex >= COMMAND_BUFFER_SIZE - 1) {
        commandIndex = 0; // Reset buffer on overflow
    }
}

/*
 * Sensor Read Task
 * - Executes every 5 seconds (SENSOR_READ_INTERVAL = 5000ms)
 * - Reads humidity and temperature from DHT20 sensor via I2C
 * - Stores data in readingBuffer for averaging
 * - Outputs averaged data to Serial with timestamp if available
 * - Processes serial commands (READ, STATUS)
 * - Uses software timer (SENSOR_TIMER) to enforce 5-second interval
 * - Scheduled via provided scheduler, no delay() calls
 * - Enters light sleep between scheduler ticks for power efficiency
 */
void SensorReadTask(void) {
    if (isTimerExpired(SENSOR_TIMER)) {
        // Read humidity and temperature from DHT20
        if (dht20.available()) {
            latestData.temperature = dht20.getTemperature();
            latestData.humidity = dht20.getHumidity();
            latestData.valid = true;
            
            // Store in buffer for averaging
            readingBuffer[bufferIndex] = latestData;
            bufferIndex = (bufferIndex + 1) % AVG_BUFFER_SIZE;
            if (bufferCount < AVG_BUFFER_SIZE) {
                bufferCount++;
            }
            
            // Compute and output average if buffer is full
            ClimateData avgData;
            if (averageSensorReadings(avgData)) {
                Serial.print("[");
                Serial.print(millis());
                Serial.print(" ms] Averaged Temperature: ");
                Serial.print(avgData.temperature);
                Serial.print(" °C, Humidity: ");
                Serial.print(avgData.humidity);
                Serial.println(" %");
            } else {
                Serial.print("[");
                Serial.print(millis());
                Serial.print(" ms] Raw Temperature: ");
                Serial.print(latestData.temperature);
                Serial.print(" °C, Humidity: ");
                Serial.print(latestData.humidity);
                Serial.println(" %");
            }
        } else {
            latestData.valid = false;
            readingBuffer[bufferIndex].valid = false;
            bufferIndex = (bufferIndex + 1) % AVG_BUFFER_SIZE;
            if (bufferCount < AVG_BUFFER_SIZE) {
                bufferCount++;
            }
            Serial.print("[");
            Serial.print(millis());
            Serial.println(" ms] Failed to read from DHT20 sensor!");
        }
        
        // Reset timer for next 5-second interval
        setTimer(SENSOR_TIMER, SENSOR_READ_INTERVAL);
        
        // Enter light sleep until next scheduler tick
        esp_sleep_enable_timer_wakeup(INTERRUPT_CYCLE * 1000); // Wake up in 10ms
        esp_light_sleep_start();
    }
    
    // Process serial commands
    processSerialCommands();
}

/*
 * Task Interactions and Features:
 * - SensorReadTask:
 *   - Runs every 5 seconds (SENSOR_READ_INTERVAL = 5000ms)
 *   - Reads humidity and temperature from DHT20 sensor via I2C
 *   - Stores data in readingBuffer for averaging (last 3 readings)
 *   - Outputs raw or averaged data to Serial at 115200 baud with millisecond timestamps
 *   - Processes serial commands (READ, STATUS)
 *   - Operates independently, with no other tasks
 * - Scheduler:
 *   - Uses provided scheduler.h with 10ms interrupt cycle (INTERRUPT_CYCLE)
 *   - SensorReadTask is scheduled to check timer every 10ms, but readings occur every 5 seconds
 *   - SCH_Add_Task configures 5-second periodicity (5000ms / 10ms = 500 ticks)
 * - Software Timer:
 *   - Uses provided software_time.h to enforce 5-second interval (SENSOR_TIMER)
 *   - Retry timer (RETRY_TIMER) used for 1-second intervals during initialization retries
 *   - timerRun() updates timers every 10ms via scheduler in loop()
 * - Features:
 *   - Data Logging: Serial output includes millisecond timestamps
 *   - Error Retry: Retries DHT20 initialization up to 5 times with 1-second intervals
 *   - Data Averaging: Averages last 3 valid readings to reduce noise
 *   - Low-Power Mode: Uses light sleep between scheduler ticks (10ms)
 *   - Serial Commands: Supports READ (immediate reading) and STATUS (system info)
 * - No actuators or control logic:
 *   - Excludes heater, cooler, and humidifier (previously LEDs on D3-D8)
 *   - No FSM or control task, as only sensor readings are required
 * - No delay() calls:
 *   - All timing handled by provided scheduler (10ms ticks) and software timer
 *   - Serial output, command processing, and retry logic are non-blocking
 */

void setup() {
    // Initialize hardware (DHT20 sensor and Serial)
    if (!initHardware()) {
        // Handle persistent initialization failure
        while (1) {
            timerRun();
            SCH_Update();
            SCH_Dispatch_Tasks();
        }
    }
    
    // Initialize scheduler
    SCH_Init();
    
    // Add sensor read task
    // Period = 5000ms / 10ms = 500 ticks for 5-second interval
    SCH_Add_Task(SensorReadTask, 0, SENSOR_READ_INTERVAL / INTERRUPT_CYCLE);
    
    // Initialize software timer for 5-second sensor readings
    setTimer(SENSOR_TIMER, SENSOR_READ_INTERVAL);
}

void loop() {
    // Update software timers
    timerRun();
    
    // Update scheduler
    SCH_Update();
    
    // Dispatch tasks
    SCH_Dispatch_Tasks();
}
