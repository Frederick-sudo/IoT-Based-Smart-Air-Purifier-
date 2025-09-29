# IoT-Based-Smart-Air-Purifier-
Code for capstone thesis project required for the Computer Engineering program at De La Salle Araneta University

An IoT-enabled smart air purification system designed to monitor, filter, and improve indoor air quality in real time. This project combines hardware sensors, microcontrollers, and a web-based dashboard to track environmental conditions and automate air purification.

Features 
The system provides real-time air quality monitoring by detecting particulate matter, humidity, and temperature through IoT sensors. It includes an automated filtration system that activates the air purifier’s fans once pollution levels cross set thresholds. Users can remotely monitor the device through a web dashboard or mobile interface, which displays live air quality data. In addition, the system stores historical sensor readings for data logging and trend analysis, while maintaining energy efficiency by optimizing power consumption to avoid unnecessary usage.

Tech Used
The hardware implementation is based on Arduino or ESP32 microcontrollers, combined with air quality sensors capable of measuring PM2.5, gas levels, humidity, and temperature. On the software side, the backend is developed using either Flask or Node.js, while the frontend is a web dashboard for real-time monitoring. Data is managed with an SQL database to store sensor logs and readings, and the system communicates using IoT protocols such as MQTT and HTTP.

Usage 
This IoT-based smart air purifier is designed for practical use in different environments. It can improve air quality in homes and offices located in polluted urban areas, help hospitals and clinics maintain clean air for patients and staff, and provide safer learning environments in schools and universities by ensuring consistently healthy indoor air conditions.

How to Run
Connect IoT sensors and microcontroller.

Upload firmware to ESP32/Arduino.

Run the backend server

Access the mobile app via Blynk
