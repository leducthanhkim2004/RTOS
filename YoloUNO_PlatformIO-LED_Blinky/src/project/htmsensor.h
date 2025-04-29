/*
 * SmartClimateControl.h
 * 
 * Header file for the Smart Climate Control System on the YoloUNO platform (ESP32 S3).
 * Manages humidity and temperature readings from the DHT20 sensor (I2C) every 5 seconds
 * using a custom scheduler and software timer. Includes features like serial output with
 * timestamps, error retry, data averaging, low-power mode, and serial command interface.
 * No actuators or delay() calls are used.
 * 
 * Note: Uses DHT20 sensor for humidity and temperature readings via I2C.
 * 
 * Author: Generated based on user specifications
 * Date: April 29, 2025
 */

#ifndef SMART_CLIMATE_CONTROL_H
#define SMART_CLIMATE_CONTROL_H

#include "Arduino.h"
#include "scheduler.h"
#include "software_time.h"
#include <Wire.h>
#include <DHT20.h> // Library for DHT20 sensor (humidity and temperature)
#include <esp_sleep.h>

// Configuration constants
#define SENSOR_READ_INTERVAL 5000       // Sensor reading interval: 5 seconds (ms)
#define SENSOR_TIMER 0                  // Timer index for sensor readings
#define RETRY_TIMER 1                   // Timer index for initialization retries
#define SERIAL_BAUD 115200              // Serial baud rate
#define MAX_SENSOR_RETRIES 5            // Maximum retries for DHT20 initialization
#define AVG_BUFFER_SIZE 3               // Buffer size for averaging sensor readings
#define COMMAND_BUFFER_SIZE 16          // Serial command buffer size

// Data structure for sensor readings (humidity and temperature)
struct ClimateData {
    float temperature;
    float humidity;
    bool valid;
};

// Function prototypes
bool initHardware();                    // Initialize DHT20 sensor and Serial
bool averageSensorReadings(ClimateData &result); // Average last 3 sensor readings
void processSerialCommands();           // Process serial commands (READ, STATUS)
void SensorReadTask();                  // Task to read sensor and handle features

#endif 
// SMART_CLIMATE_CONTROL_H//TODO: IMPLEMENT HTMSENSOR KHÔI VĨ 
