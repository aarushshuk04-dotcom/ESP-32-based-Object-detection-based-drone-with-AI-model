
# 🚁 Autonomous Object Detection Drone

### F450 Quadcopter | Pixhawk | ESP32 | ESP32-CAM | Edge Impulse AI | MAVLink

An experimental autonomous UAV platform combining **flight control, embedded systems, computer vision, and lightweight edge AI** for real-time object detection and autonomous drone applications.

---

## 📌 Project Overview

This project focuses on the development of an **autonomous object detection drone** built around an F450 quadcopter platform.

The system integrates:

- **Pixhawk** flight controller for UAV stabilization and flight control
- **ESP32** for embedded sensor processing
- **ESP32-CAM** for image acquisition and wireless video streaming
- **Edge Impulse** for lightweight machine-learning based object detection
- **HC-SR04 ultrasonic sensor** for distance measurement and obstacle-awareness experiments
- **MAVLink** for communication between the companion electronics and flight controller
- **QGroundControl** for mission planning, telemetry, and UAV configuration

The overall objective is to create a modular platform capable of combining **autonomous flight, object detection, sensor data, and intelligent decision-making**.

---

## 🎯 Project Objectives

The main objectives of the project are:

1. Build and configure an F450 quadcopter using a Pixhawk flight controller.
2. Integrate ESP32-based embedded electronics with the UAV platform.
3. Develop an ESP32-CAM based image acquisition and streaming system.
4. Explore lightweight AI inference using Edge Impulse.
5. Implement ultrasonic distance measurement for obstacle-awareness experiments.
6. Establish communication between the embedded system and Pixhawk using MAVLink.
7. Develop a foundation for autonomous waypoint navigation and intelligent UAV behaviour.
8. Evaluate the performance and limitations of an edge-AI based drone architecture.

---

## 🧠 System Architecture

```text
                       ┌──────────────────────┐
                       │     QGroundControl   │
                       │ Mission / Telemetry  │
                       └──────────┬───────────┘
                                  │
                                  │ Telemetry
                                  ▼
                       ┌──────────────────────┐
                       │       Pixhawk        │
                       │ Flight Controller    │
                       └───────┬───────┬──────┘
                               │       │
                         Motor │       │ MAVLink
                         Control│       │
                               ▼       ▼
                      ┌──────────┐  ┌──────────┐
                      │  ESCs    │  │  ESP32   │
                      │  +       │  │ Embedded │
                      │ Motors   │  │ System   │
                      └──────────┘  └────┬─────┘
                                         │
                              ┌──────────┴──────────┐
                              │                     │
                              ▼                     ▼
                       ┌────────────┐       ┌────────────┐
                       │ HC-SR04    │       │ ESP32-CAM  │
                       │ Ultrasonic │       │ OV2640     │
                       └────────────┘       └─────┬──────┘
                                                  │
                                                  │ Image
                                                  ▼
                                           ┌─────────────┐
                                           │ Edge Impulse│
                                           │ AI Model    │
                                           └─────────────┘
````

---

## 🛠️ Hardware

| Component                   | Purpose                         |
| --------------------------- | ------------------------------- |
| F450 Frame                  | Quadcopter airframe             |
| Pixhawk                     | Flight controller               |
| 2212 980KV Brushless Motors | Propulsion                      |
| 30A SimonK ESCs             | Motor speed control             |
| 10×4.5 Propellers           | Propulsion                      |
| 3S–4S 3300mAh LiPo          | Main power source               |
| GPS + Compass               | Positioning and navigation      |
| RC Receiver                 | Manual flight control           |
| ESP32                       | Embedded processing             |
| ESP32-CAM                   | Camera and image acquisition    |
| OV2640                      | Camera sensor                   |
| HC-SR04                     | Ultrasonic distance measurement |
| OLED Display                | Local sensor/status display     |

---

## 📷 Computer Vision & AI

The vision subsystem uses an **ESP32-CAM** to capture images and provide a lightweight video-streaming platform.

The intended AI pipeline is:

```text
Camera
   ↓
Image Capture
   ↓
Pre-processing
   ↓
Edge Impulse Model
   ↓
Object Detection
   ↓
Detection Result
   ↓
Decision / Future Autonomous Response
```

The project explores the use of **edge AI**, where machine-learning inference can be performed close to the sensing hardware rather than relying entirely on a remote computer.

---

## 📡 Embedded Sensor System

The ESP32 subsystem is used to interface with sensors and provide embedded processing capabilities.

### Ultrasonic Sensor

The HC-SR04 is used for distance measurement and obstacle-awareness experiments.

```text
HC-SR04
   │
   ├── TRIG → ESP32 GPIO 5
   │
   └── ECHO → ESP32 GPIO 18
```

### OLED Display

The OLED interface uses the ESP32 I²C bus:

```text
ESP32
 │
 ├── SDA → GPIO 21
 │
 └── SCL → GPIO 22
```

---

## 🔗 MAVLink Integration

MAVLink is planned as the communication protocol between the embedded subsystem and Pixhawk.

The intended architecture is:

```text
ESP32
  │
  │ MAVLink
  ▼
Pixhawk
  │
  ▼
UAV Flight Control
```

This interface provides a foundation for exchanging sensor information, telemetry, and future autonomous commands.

**Current status:** Experimental / under development.

---

## 🛰️ Flight Control

The Pixhawk flight controller is responsible for the primary UAV flight-control functions.

The project uses **QGroundControl** for:

* Flight-controller configuration
* UAV setup
* Mission planning
* Waypoint configuration
* Telemetry monitoring
* Flight-data observation
* Pre-arm and safety checks

---

## 🧪 Development Status

| Subsystem                               | Status                |
| --------------------------------------- | --------------------- |
| F450 drone platform                     | 🔧 Developed          |
| Pixhawk integration                     | 🔧 Developed          |
| ESP32 sensor system                     | ✅ Tested              |
| HC-SR04 distance measurement            | ✅ Tested              |
| OLED display interface                  | ✅ Tested              |
| ESP32-CAM Wi-Fi streaming               | 🔧 Developed          |
| Edge Impulse AI                         | 🧪 Experimental       |
| MAVLink integration                     | 🧪 Under Development  |
| Autonomous waypoint navigation          | 📋 Planned            |
| Sensor fusion                           | 📋 Planned            |
| Object-triggered autonomous response    | 📋 Planned            |
| Full autonomous object-detection flight | 📋 Future Development |

> **Note:** Project status is intentionally separated into implemented, experimental, and planned features to accurately represent the development stage.

---

## 📊 Testing & Evaluation

The project is intended to be evaluated across multiple stages.

### 1. Bench Testing

* Sensor connectivity
* ESP32 communication
* Ultrasonic distance measurement
* Camera operation
* Power behaviour
* Serial communication

### 2. Hardware Integration

* Pixhawk integration
* Motor and ESC operation
* GPS functionality
* RC control
* Embedded subsystem integration

### 3. Flight Testing

* Stabilized flight
* Hover testing
* Waypoint missions
* Telemetry monitoring
* Autonomous navigation experiments

### 4. AI Evaluation

Potential metrics include:

* Detection accuracy
* Inference latency
* Camera frame rate
* ESP32 memory usage
* Model size
* Detection reliability
* Operating range

---

## ⚠️ Engineering Challenges

During development, several engineering challenges are being investigated:

* Vibration affecting sensors and flight hardware
* Limited processing resources on ESP32-class hardware
* Wi-Fi range and reliability
* Power consumption
* Thermal behaviour
* MAVLink communication reliability
* Real-time AI inference limitations
* Integration of multiple subsystems

---

## 🚀 Future Development

Planned development includes:

* [ ] Complete ESP32-CAM object detection
* [ ] Optimize Edge Impulse model
* [ ] Establish reliable MAVLink communication
* [ ] Integrate sensor data with Pixhawk
* [ ] Implement sensor fusion
* [ ] Develop GPS waypoint navigation
* [ ] Explore object-triggered autonomous behaviour
* [ ] Perform outdoor flight testing
* [ ] Add telemetry and flight-data logging
* [ ] Benchmark AI inference performance
* [ ] Improve autonomous decision-making

---

## 📁 Repository Structure

```text
autonomous-object-detection-drone/
│
├── README.md
│
├── docs/
│   ├── project-report/
│   ├── system-architecture/
│   ├── hardware/
│   └── testing/
│
├── hardware/
│   ├── wiring/
│   ├── schematics/
│   └── bill-of-materials/
│
├── firmware/
│   ├── esp32/
│   └── esp32-cam/
│
├── ai/
│   ├── dataset/
│   ├── edge-impulse/
│   ├── model/
│   └── evaluation/
│
├── pixhawk/
│   ├── qgroundcontrol/
│   ├── parameters/
│   └── missions/
│
├── results/
│   ├── flight-tests/
│   ├── detection-results/
│   └── benchmarks/
│
└── images/
    ├── drone/
    ├── electronics/
    ├── wiring/
    └── detection/
```

---

## 🎓 Project Context

This project was developed as part of an engineering project focused on the integration of:

**Embedded Systems + UAV Technology + Computer Vision + Edge AI**

The project explores how low-cost embedded hardware can be combined with a flight controller and machine-learning models to create a modular autonomous UAV platform.

---

## 👨‍💻 Author

**Aarush Shukla**

B.Tech — Electronics & Communication Engineering (VLSI)

Manipal University Jaipur

---

## 📌 Project Status

**Status:** 🚧 Active Development

This repository documents the development, experiments, hardware integration, software, testing, and future evolution of the autonomous UAV platform.

