# Deadzone-Patch 🕹️🤖

**A Robust Cyber-Physical Calibration Layer for Neutralizing Mechanical Hysteresis and Sensor Drift.**

## 📌 The Problem: Mechanical Logic Errors
In any system utilizing potentiometers or analog hall-effect sensors—from **gaming controllers** to **robotic actuators**—the physical hardware eventually experiences "mechanical noise." 

Whether it is a weakened centering spring in a thumbstick or a micro-voltage fluctuation in a robotic joint, the sensor sends a "drift" signal (phantom movement) when it should be at rest. This is a **Nonlinear Logic Error** where the hardware state does not match the software intent.

## 🛠 Features
- **Cyber-Physical Alignment:** Recalibrates the relationship between physical resistance and digital output.
- **Radial Magnitude Logic:** Unlike simple axial clipping (X/Y), this uses Euclidean distance to create a perfect circular "safe zone."
- **Hysteresis Mitigation:** Filters out low-level oscillation and "jitter" common in aging robotics sensors.
- **Universal X/Y Scaling:** Re-maps the remaining usable range to ensure full 100% responsiveness after the patch is applied.

## 🚀 The Physics-Informed Logic
This patch treats the sensor input as a **displacement vector**. By calculating the magnitude using the Pythagorean theorem, we define a threshold for "Noise" vs. "Signal":

$$magnitude = \sqrt{x^2 + y^2}$$

If the $magnitude$ falls below the **Deadzone Radius**, the patch forces the output to a true zero state, preventing "ghost" movement in survival systems or precision maneuvers.

## 💻 Hardware Implementation
This C++ logic is designed to sit at the **firmware level**, acting as a filter before the OS or the Robot Operating System (ROS) processes the input.

```cpp
// Define the Radial Threshold (e.g., 0.12f for 12% drift)
float threshold = 0.12f; 
StickInput signal = applyDeadzone(rawX, rawY, threshold);
```

### Flashing to a Physical Device
It is important to note that the `.ino` sketch file in the `deadzone_patch` directory does **not** automatically sync to a connected physical device. You must compile and upload (flash) it to your microcontroller (e.g., Arduino Pro Micro, Teensy).

You can flash the device using:
1. **Arduino IDE**: Open `deadzone_patch/deadzone_patch.ino`, select your board and port, and click "Upload".
2. **Command Line (`arduino-cli`)**: We have provided a `flash.sh` script to automate compiling and uploading if you have `arduino-cli` installed.

```bash
./flash.sh
```

## 📜 Acknowledgements
Developed at the intersection of systems architecture and physical engineering.

- **Lead Architect:** Don M. Feeney Jr.

- **AI Collaborator:** Gemini (Google AI), thank you sincerely.

This project is part of the **"Pact for AI for Good"**—leveraging software to extend the life of hardware and ensure precision in human-machine interfaces.

---
