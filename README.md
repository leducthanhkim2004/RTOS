Real-Time Operating System (RTOS) Project

Smart Climate Control System

🚩 Project Deadline: 28.04.2024 before 12:00 AM (Midnight)

🎯 Project Overview

This project demonstrates the practical application of Real-Time Operating System (RTOS) principles through a Smart Climate Control System. The system continuously monitors and adjusts environmental temperature and humidity using sensors and actuators, implementing a Finite State Machine (FSM) where necessary. Critical implementation constraint: do NOT use delay() function.

📌 Task Assignments

Task

Team Member

Implementation Requirements

🟢 BLINKY Task

👏 Tuấn Anh

Period: 1 second

🌡️ Temperature & Humidity

🎉 Khôi Vĩ

Period: 5 seconds

❄️ Cooler Task

🙂 Tiến Khoa

RTOS-based periodic control

🔥 Heater Task

😂 Minh Trí

LED indicators (Green, Orange, Red)

💧 Humidifier Task

👏 Thanh Kim

FSM: Green(5s) → Yellow(3s) → Red(2s) cycle

📑 Final Report

✨ Anh Toàn, ✨ Thái An

Comprehensive documentation & GitHub README

📂 Project Structure

Project/
├── include/
│   ├── scheduler.h
│   ├── software_timer.h
│   └── tasks/
│       ├── blinky_task.h
│       ├── temperature_humidity_task.h
│       ├── cooler_task.h
│       ├── heater_task.h
│       └── humidifier_task.h
├── src/
│   ├── main.c
│   ├── scheduler.c
│   └── tasks/
│       ├── blinky_task.c
│       ├── temperature_humidity_task.c
│       ├── cooler_task.c
│       ├── heater_task.c
│       └── humidifier_task.c
└── README.md

⚙️ Implementation Notes

Sensors: DHT20 Temperature and Humidity sensor connected via I2C.

Actuators: Simulated through LEDs for demonstration:

Heater LEDs (D3, D4)

Cooler LEDs (D5, D6)

Humidifier LEDs (D7, D8)

📝 Coding Guidelines

Adhere strictly to RTOS principles; no blocking delay() function allowed.

Implement FSM clearly for the Humidifier Task, updating states at 1 TICK intervals.

Use provided libraries and task scheduling methods effectively.

🗓️ Submission

Ensure code is fully tested, functional, and pushed to the project’s GitHub repository.

Final documentation must reflect the individual contributions and collaborative efforts clearly.

🎖️ Acknowledgments

Thank you to all team members for your efforts and commitment. Let's ensure timely submission and successful demonstration of our RTOS project!

