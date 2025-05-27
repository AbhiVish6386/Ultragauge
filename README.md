

**A smart object detection and distance measurement system powered by ESP32 and HC-SR04.**

---

## 🚗 Project Description
Ultragauge is a real-time distance measurement system designed for smart car parking, robotics, and obstacle avoidance. Built using ESP32 DevKit and an HC-SR04 ultrasonic sensor, the system displays distance on a 128x64 OLED and triggers alerts when objects are too close. This embedded project integrates visual animation, hardware interfacing, and object-oriented programming (OOP) for clean modular design.

---

## ✨ Features
- Real-time distance measurement (cm, inch, feet, meter)
- OLED-based animated UI and multi-screen welcome interface
- Crash alert buzzer when object is too close
- Mode switching via push button (unit toggle)
- Boot-time car animation with frame-by-frame display
- Modular OOP design with reusable classes

---

## 🔧 Hardware Used
- ESP32 WROOM32 DevKit V1
- HC-SR04 Ultrasonic Sensor
- SH1106 128x64 OLED Display
- Tactile Push Button
- Buzzer
- Jumper Wires, Breadboard, USB Cable, Resistors (if needed)

---

## 💻 Software Used
- PlatformIO (VS Code Extension)
- Arduino Framework
- U8g2 Graphics Library

---

## 📁 Folder Structure
```plaintext
ultragauge/
├── .pio/                  # PlatformIO build system
├── include/               # Header files
│   ├── Button.h
│   ├── car_frames.h
│   └── u8g2_oledPrint.h
├── lib/                   # Custom libraries (if extended)
├── src/                   # Main source code
│   ├── main.cpp
│   ├── Button.cpp
│   ├── car_frames.cpp
│   └── u8g2_oledPrint.cpp
├── platformio.ini         # Project configuration
└── .gitignore
```

---

## ⚙️ Working Principle
1. Trigger pin sends a 10μs pulse to start measurement.
2. HC-SR04 emits a 40kHz ultrasonic wave.
3. Echo pin goes HIGH when echo returns.
4. Duration is captured and distance calculated:
   ```
Distance = (duration × 0.0343) / 2
```  
5. Value is averaged over 5 samples.
6. If the distance < 4cm (or equivalent), buzzer alerts.

---

## 🧠 Code Highlights
- **OOP Concepts**: Button handling is abstracted via a `Button` class with encapsulated debounce logic.
- **Method Overloading**: The `oledPrint` function is overloaded to handle both string and float inputs with positional arguments for consistent OLED rendering.
- **Animations**: `car_frames[]` (stored in PROGMEM) animates a boot sequence by drawing frame-by-frame.

---

## 🔌 Circuit Diagram
*📌 Placeholder — Add your image here (e.g., circuit_diagram.png)*
```

[Schematic_Ultrasonic_2025-05-27.pdf](https://github.com/user-attachments/files/20463920/Schematic_Ultrasonic_2025-05-27.pdf)# Ultragauge - Get Distance Digitally

```

---

## 🚀 Getting Started
### Prerequisites
- Install [PlatformIO](https://platformio.org/) in VS Code
- Clone the repository

```bash
git clone https://github.com/your-username/ultragauge.git
cd ultragauge
```

### Build and Upload
1. Connect your ESP32 via USB
2. Select the correct COM port
3. Click on "Upload" in PlatformIO

### Optional
- Modify animation frames in `car_frames.h`
- Adjust threshold values in `main.cpp`

---

## 📈 Future Enhancements
- Add Li-ion battery module for portability
- Implement I2C-based multiple sensor expansion
- Add Bluetooth for wireless monitoring

---

## 👤 Author
**Abhishek Kumar Vishwakarma**  
B.Tech CSE | Electronics & Embedded Systems Enthusiast

---

## 📄 License
This project is licensed under the **GPLv3** — see the [LICENSE](LICENSE) file for details.
