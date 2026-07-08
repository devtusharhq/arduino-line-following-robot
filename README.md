# 🤖 Arduino-Based Line Following Robot

## 📖 Overview

The **Arduino-Based Line Following Robot** is an embedded systems project designed to autonomously follow a predefined path using infrared (IR) sensors. The robot continuously detects the line, processes sensor inputs through an Arduino Uno, and controls DC motors using an L298N motor driver. Python utilities were also developed for automatic hardware testing, sensor validation, line-following logic simulation, and manual robot control.

---

## ✨ Features

- 🤖 Autonomous line following using dual IR sensors
- 🎯 Real-time line detection and path correction
- ⚙️ Arduino Uno-based embedded control
- 🚗 Motor control using L298N motor driver
- 📡 IR sensor calibration and testing
- 🧪 Automatic hardware testing with Python
- 🎮 Manual robot control using WASD keyboard commands
- 🧠 Line-following logic simulation
- 🔌 Serial communication between Arduino and computer
- 🏗️ Modular and reusable embedded system design

---

## 🛠️ Technologies Used

- Arduino Uno
- Embedded C (Arduino IDE)
- Python
- IR Sensors
- L298N Motor Driver
- DC Geared Motors
- Serial Communication
- Embedded Systems

---

## 📂 Project Structure

```text
Arduino-Line-Following-Robot/
│
├── Arduino/
│   ├── LineFollower.ino
│   └── IR_Sensor_Test.ino
│
├── Python/
│   ├── auto_line.py
│   ├── wasd.py
│   └── test_line_follower_logic.py
│
├── Images/
│   └── Robot.jpg
│
├── Documentation/
│   └── Line_Following_Robot_Report.pdf
│
├── README.md
├── LICENSE
└── .gitignore
```

---

## 🔧 Hardware Components

- Arduino Uno
- L298N Motor Driver
- Dual IR Sensors
- Four DC Geared Motors
- Robot Chassis
- Wheels
- 9V Battery
- Jumper Wires

---

## 💻 Software Components

- Arduino IDE
- Embedded C
- Python
- Serial Communication Libraries

---

## ⚙️ Working Principle

1. The IR sensors continuously detect the surface beneath the robot.
2. Sensor readings are sent to the Arduino Uno.
3. The Arduino processes the sensor inputs.
4. Based on the detected line position, the Arduino controls the motors through the L298N motor driver.
5. The robot automatically adjusts its direction to remain on the line.
6. Python utilities are used for hardware testing, logic validation, and manual robot control.

---

## 📸 Project Images

### Robot

![Robot](Images/Robot.jpg)

### Circuit Diagram

![Circuit Diagram](Images/Circuit_Diagram.png)

### Flowchart

![Flowchart](Images/Flowchart.png)

---

## 🚀 How to Run

### Arduino Program

1. Open the project in Arduino IDE.
2. Connect the Arduino Uno.
3. Select the correct COM port.
4. Upload the Arduino sketch.
5. Place the robot on the track and power it on.

### Python Utilities

Run the required Python script.

```bash
python auto_line.py
```

or

```bash
python wasd.py
```

or

```bash
python test_line_follower_logic.py
```

---

## 🎯 Learning Outcomes

This project strengthened my understanding of:

- Embedded Systems
- Arduino Programming
- Sensor Interfacing
- Motor Driver Control
- Serial Communication
- Robotics
- Hardware Testing
- Python Automation
- Real-Time Decision Making

---

## 🚀 Future Enhancements

- Obstacle detection using ultrasonic sensors
- Bluetooth-based robot control
- Wi-Fi/IoT integration
- PID-based speed optimization
- Camera-based line tracking
- Maze-solving capability
- Rechargeable battery management
- AI-assisted navigation

---

## 📄 Documentation

The repository includes:

- Arduino Source Code
- Python Testing Utilities
- Robot Images
- README.md
- MIT License
- .gitignore

---

## 👨‍💻 Developed By

**Tushar L. Devendra**

B.Sc. Information Technology

SVKM's Usha Pravin Gandhi College (Mumbai University)

### 🔗 GitHub

https://github.com/devtusharhq

---

## ⭐ Support

If you found this project useful, consider giving it a ⭐ on GitHub.
