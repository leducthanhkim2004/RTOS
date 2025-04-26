# 👨‍🏫 Smart Climate Control System (RTOS Project)

**Real-Time Operating System (RTOS) Demo Project**

---

## 🎯 Project Objective

Develop a Smart Climate Control System to demonstrate the principles and application of Real-Time Operating Systems (RTOS). The system actively monitors and adjusts temperature and humidity using sensors and actuators, with all tasks managed through an RTOS scheduler. Crucially, the project avoids the use of any blocking `delay()` functions.

---

## 🚩 Deadline

**28 April 2024, before 12:00 AM (Midnight)**

---

## 📌 Task Assignments and Responsibilities

| Task                           | Assigned Member       | Implementation Details                          |
| ------------------------------ | --------------------- | ----------------------------------------------- |
| 🟢 **BLINKY Task**             | 🫀 Tuấn Anh           | LED blink every 1 second                        |
| 🌡️ **Temperature & Humidity** |  👨‍❤️‍👨 Khôi Vĩ            | Sensor reading every 5 seconds                  |
| ❄️ **Cooler Task**             | 🙂 Tiến Khoa          | Activate based on temperature thresholds        |
| 🔥 **Heater Task**             | ❤️‍🔥: Minh Trí           | LED indication: Green, Orange, Red based on temperature range |
| 💧 **Humidifier Task**         | 👏 Thanh Kim          | FSM implementation: Green (5s) → Yellow (3s) → Red (2s) cycle |
| 📑 **Final Report & Docs**     | ✨ Anh Toàn, ✨ Thái An | Documentation, GitHub README, and final report  |

---

## 🛠️ Hardware and Implementation

- **Microcontroller**: YoloUNO platform (ESP32 S3)
- **Sensors**: DHT20 sensor (I2C interface)
- **Actuators (Simulation using LEDs)**:
  - Heater: LEDs (pins D3, D4)
  - Cooler: LEDs (pins D5, D6)
  - Humidifier: LEDs (pins D7, D8)

---

## 📝 Guidelines

- Use RTOS scheduling strictly.
- No `delay()` calls; all tasks must use RTOS tick scheduling.
- Clearly document FSM implementations and task interactions.

---
