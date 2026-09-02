

# 🔧 Hardware Documentation

This section documents the hardware architecture, components, interfaces, and integration of the autonomous object detection drone.

---

## 🛩️ UAV Platform

The UAV is based on an **F450 quadcopter frame** configured as a four-motor multirotor platform.

### Main Flight Hardware

| Component | Specification / Description | Function |
|---|---|---|
| F450 Frame | Quadcopter frame | Mechanical structure |
| Brushless Motors | 2212 980KV × 4 | Propulsion |
| ESC | 30A SimonK × 4 | Motor speed control |
| Propellers | 10 × 4.5 | Thrust generation |
| Flight Controller | Pixhawk | Flight stabilization and control |
| GPS + Compass | UAV navigation module | Position and heading |
| RC Receiver | Radio control receiver | Manual pilot input |
| LiPo Battery | 3S–4S, 3300mAh | Main power source |

---

## 🧠 Embedded Electronics

The embedded subsystem extends the capabilities of the flight controller by providing sensing, camera interfacing, and experimental edge-AI functionality.

### ESP32

The ESP32 is used as the primary embedded processing platform for:

- Ultrasonic distance measurement
- OLED status display
- Sensor data processing
- Experimental communication with Pixhawk
- Future MAVLink integration

### ESP32-CAM

The ESP32-CAM provides:

- Image acquisition
- OV2640 camera interfacing
- Wi-Fi video streaming
- Input for object-detection experiments
- Edge-AI experimentation

---

## 📡 Sensors

### HC-SR04 Ultrasonic Sensor

The HC-SR04 is used for distance measurement and obstacle-awareness experiments.

| Signal | ESP32 Pin |
|---|---|
| TRIG | GPIO 5 |
| ECHO | GPIO 18 |

```text
HC-SR04
   │
   ├── TRIG ──────> ESP32 GPIO 5
   │
   └── ECHO ──────> ESP32 GPIO 18
````

---

## 🖥️ OLED Display

An OLED display is connected to the ESP32 using the I²C interface.

| OLED Signal | ESP32 Pin |
| ----------- | --------- |
| SDA         | GPIO 21   |
| SCL         | GPIO 22   |

```text
ESP32
 │
 ├── GPIO 21 ───> SDA
 │
 └── GPIO 22 ───> SCL
```

The display can be used to monitor sensor measurements and embedded-system status during testing.

---

## 🎮 Flight Controller

The **Pixhawk** is responsible for the primary flight-control functions of the UAV.

It interfaces with:

* Brushless motor ESCs
* GPS/Compass
* RC receiver
* Telemetry systems
* Companion/embedded electronics

The flight controller provides the stabilization and control layer while the ESP32-based subsystem is intended to provide additional sensing and AI capabilities.

---

## 🔗 Communication Architecture

The planned communication architecture is:

```text
                ┌─────────────────┐
                │ QGroundControl  │
                └────────┬────────┘
                         │
                     Telemetry
                         │
                         ▼
                ┌─────────────────┐
                │     Pixhawk     │
                │ Flight Control  │
                └────────┬────────┘
                         │
                      MAVLink
                         │
                         ▼
                ┌─────────────────┐
                │      ESP32      │
                └───────┬─────────┘
                        │
              ┌─────────┴─────────┐
              ▼                   ▼
        ┌───────────┐       ┌───────────┐
        │  HC-SR04  │       │ ESP32-CAM │
        │ Distance  │       │  Camera   │
        └───────────┘       └───────────┘
```

---

## 🔋 Power System

The drone uses a LiPo battery as the primary power source.

The project hardware is designed around a **3S–4S 3300mAh LiPo battery**.

Power distribution must be designed carefully to accommodate:

* Motor current
* ESC requirements
* Pixhawk power requirements
* ESP32 power requirements
* Camera power consumption
* Sensor and peripheral loads

> ⚠️ Power-system specifications and current measurements should be experimentally verified before final flight operation.

---

## 🧩 Hardware Integration

The overall hardware stack can be divided into four layers:

### Layer 1 — Propulsion

```text
Battery
   ↓
Power Distribution
   ↓
ESCs
   ↓
Brushless Motors
   ↓
Propellers
```

### Layer 2 — Flight Control

```text
GPS + Compass
      ↓
   Pixhawk
      ↑
RC Receiver
      ↓
Flight Control
```

### Layer 3 — Embedded Sensing

```text
HC-SR04 ──┐
          ├──> ESP32
OLED ─────┘
```

### Layer 4 — Vision & AI

```text
OV2640
   ↓
ESP32-CAM
   ↓
Image / Video
   ↓
Edge Impulse
   ↓
Object Detection
```

---

## 📋 Bill of Materials

A detailed Bill of Materials will be maintained as the hardware configuration develops.

| Category          | Component                  | Quantity |
| ----------------- | -------------------------- | -------: |
| Frame             | F450 Frame                 |        1 |
| Motor             | 2212 980KV Brushless Motor |        4 |
| ESC               | 30A SimonK ESC             |        4 |
| Propeller         | 10 × 4.5                   |        4 |
| Flight Controller | Pixhawk                    |        1 |
| GPS               | GPS + Compass Module       |        1 |
| Receiver          | RC Receiver                |        1 |
| MCU               | ESP32                      |        1 |
| Camera            | ESP32-CAM                  |        1 |
| Camera Sensor     | OV2640                     |        1 |
| Distance Sensor   | HC-SR04                    |        1 |
| Display           | OLED                       |        1 |
| Battery           | 3S–4S 3300mAh LiPo         |        1 |

---

## 📸 Hardware Images

Hardware photographs, wiring diagrams, and integration images will be added as the project develops.

Planned documentation:

* [ ] Complete drone assembly
* [ ] Pixhawk installation
* [ ] ESC and motor wiring
* [ ] ESP32 connections
* [ ] ESP32-CAM setup
* [ ] HC-SR04 wiring
* [ ] OLED wiring
* [ ] Complete electronics integration
* [ ] Final UAV configuration

---

## ⚠️ Safety

All flight testing should be performed in a controlled environment with appropriate safety precautions.

Before powered flight:

* Verify motor direction
* Verify propeller orientation
* Check battery connections
* Verify RC control
* Perform Pixhawk pre-arm checks
* Verify GPS status where required
* Keep the testing area clear
* Conduct initial tests without unnecessary payloads

---

**Hardware documentation status:** 🚧 Active Development

````

