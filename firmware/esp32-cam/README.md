# ESP32-CAM Firmware

This directory contains the firmware and machine-learning deployment resources for the ESP32-CAM subsystem of the Autonomous Object Detection Drone.

## Edge Impulse Integration

The object detection workflow uses an Edge Impulse machine-learning model exported for embedded deployment and tested through the Arduino IDE.

The generated Edge Impulse SDK contains the components required for running the trained inference pipeline on supported embedded hardware.

## Development Environment

- Arduino IDE
- ESP32 development platform
- Edge Impulse generated inference SDK
- ESP32-CAM
- OV2640 camera module

## Current Status

- [x] Edge Impulse model exported
- [x] Edge Impulse SDK generated
- [x] SDK tested through Arduino IDE
- [ ] Complete autonomous flight integration
- [ ] MAVLink integration
- [ ] Real-time object-triggered flight response

## Repository Contents

The Edge Impulse SDK archive is stored in the main repository for reference and reproducibility.

Further firmware source files will be added as the project development continues.
