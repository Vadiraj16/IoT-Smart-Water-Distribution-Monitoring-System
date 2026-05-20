# IoT Based Smart Water Distribution Monitoring System

## Overview
This project presents an IoT-Based Smart Water Distribution Monitoring System using ESP32 for real-time monitoring of water level, water flow rate, and water quality. The system helps reduce water wastage, detect leakages, and provide instant alert notifications through the Telegram application.

The project uses multiple sensors integrated with the ESP32 microcontroller and communicates wirelessly using built-in Wi-Fi technology.

## Features
- Real-time water level monitoring
- Water flow rate monitoring
- Water quality monitoring using pH sensor
- Leakage detection system
- Automatic alert notifications using Telegram Bot
- Relay and buzzer-based warning system
- Wireless monitoring using ESP32 Wi-Fi
- Low-cost and efficient IoT solution

## Components Used
### Hardware
- ESP32 Development Board
- Ultrasonic Sensor (HC-SR04)
- Water Flow Sensor
- pH Sensor
- Relay Module
- Buzzer
- Jumper Wires
- Breadboard
- Power Supply

### Software
- Arduino IDE
- Wokwi Simulator
- Telegram Bot API

## Working Principle
The ESP32 continuously reads data from the ultrasonic sensor, water flow sensor, and pH sensor.

- The ultrasonic sensor measures the water level.
- The flow sensor measures water flow rate.
- The pH sensor checks water quality.

The ESP32 processes all sensor data and detects abnormal conditions such as:
- Water leakage
- Empty tank
- Unsafe pH values
- High water flow

Whenever abnormal conditions are detected:
- The buzzer is activated
- Relay operation is triggered
- Instant alert notifications are sent to the Telegram application through Wi-Fi communication

## Applications
- Smart Homes
- Agricultural Irrigation Systems
- Industrial Water Monitoring
- Smart City Water Management
- Leakage Detection Systems
- Apartment Water Tank Monitoring

## Advantages
- Reduces water wastage
- Real-time remote monitoring
- Low-cost implementation
- Fast emergency alerts
- Improves water management efficiency

## Future Improvements
- Mobile application integration
- AI-based water usage prediction
- Data logging and analytics
- Solar-powered implementation
- Integration with smart city infrastructure

## Conclusion
The project successfully demonstrates an IoT-based smart water monitoring system using ESP32 and Telegram alerts. The system provides efficient water management, automatic leakage detection, and real-time monitoring with wireless communication support.

## Author
Vadiraj Kulkarni

Department of Electronics and Communication Engineering
KLS Gogte Institute of Technology

## License
This project is developed for educational and academic purposes.
