# 🔌 Fego Robot: Arduino Firmware

This directory contains the low-level microcontroller code responsible for translating high-level commands from the Raspberry Pi into physical motor movements.

## 📌 Overview
The `firmware.ino` script runs on the Arduino and acts as the direct hardware driver for the differential drive system. It listens for serial commands from the ROS 2 `diffdrive_arduino` hardware interface and outputs the corresponding PWM signals to the motor drivers.

## ⚙️ Communication Protocol
- **Baud Rate:** 115200
- **Format:** The Arduino expects a string in the format `m <left_pwm> <right_pwm>\r`.
  - Example: `m 120 120` drives both motors forward.
  - Example: `m -100 100` turns the robot in place.

## 🛡️ Safety Features
- **Watchdog Timeout:** The firmware includes a 500ms safety check. If the serial connection drops or the Raspberry Pi stops sending `cmd_vel` data, the Arduino will automatically halt all motor outputs to prevent the robot from driving out of control.

## 🔌 Pin Configuration
Ensure your wiring matches the defined pins in the sketch:

| Component | Arduino Pin | Function |
| :--- | :--- | :--- |
| **Left Motor** | 5 | PWM (Speed) |
| | 6 | IN1 (Direction) |
| | 7 | IN2 (Direction) |
| **Right Motor** | 10 | PWM (Speed) |
| | 8 | IN3 (Direction) |
| | 9 | IN4 (Direction) |

## 🚀 How to Upload
1. Open `firmware.ino` in the Arduino IDE.
2. Select your Arduino board and the corresponding port.
3. Click **Upload**.
4. Keep the Arduino connected via USB to the Raspberry Pi 5 before launching the main ROS 2 stack.