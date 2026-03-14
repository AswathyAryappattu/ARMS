# 🦾 ARMS — Assisted Robot for Medical Suite

A robotic arm designed for contagious isolation wards that monitors patient vitals in real time, automates IV infusion management, and enables remote monitoring via a web dashboard — reducing direct contact between healthcare workers and patients.

> Project by Aswathy A S, Dubin Ummer K, Gopika C, Krishnapriya PH
> Supervised by Dr. Silpa Sangeeth L R
> Government Engineering College, Palakkad — Department of Information Technology

---

## 📌 Overview

In contagious wards like COVID-19 isolation units, frequent patient monitoring increases infection risk for healthcare workers. ARMS addresses this by deploying a robotic arm that:

- Measures **heart rate, SpO2, and body temperature** without physical contact
- Tracks **IV fluid levels** and alerts nurses when a drip runs out
- Identifies patients via **RFID tags** for accurate record-keeping
- Streams all data to a **Firebase cloud database** accessible via a secure web dashboard

---

## ✨ Features

- Real-time vital sign monitoring (heart rate, SpO2, temperature)
- Automated IV fluid level tracking with nurse alerts
- RFID-based patient identification and data linking
- Servo-driven robotic arm for flexible sensor placement
- Firebase Realtime Database for continuous cloud data sync
- React web dashboard with secure Firebase authentication
- Reduces infection risk by minimizing nurse-patient contact

---

## 🛠️ Hardware Components

| Component | Function |
|---|---|
| ESP32-WROOM | Central microcontroller — sensors, actuators, wireless |
| MAX30102 | Heart rate and SpO2 monitoring |
| MLX90614 | Non-contact infrared body temperature |
| RFID-RC522 | Patient identification via RFID tags |
| Servo Motors | Robotic arm movement (rotation, lifting, gripping) |
| Solenoid Valve | IV fluid flow regulation |
| Relay Module | Automated infusion control |

---

## 💻 Software Stack

| Layer | Technology |
|---|---|
| Firmware | Arduino IDE, Embedded C |
| Cloud Database | Firebase Realtime Database |
| Authentication | Firebase SDK |
| Web Dashboard | React, CSS |

---

## 🏗️ System Architecture

```
Sensors (MAX30102, MLX90614, RFID)
        ↓
ESP32-WROOM (Central Processing)
        ↓              ↓
Actuators          Firebase DB
(Servo, Solenoid,  (Realtime sync)
 Relay)                ↓
                  React Web Dashboard
                  (Remote monitoring)
```

---

## 🚀 How to Run

### Firmware (ESP32)

**1. Clone the repository:**
```bash
git clone https://github.com/AswathyAryappattu/ARMS.git
cd ARMS
```

**2. Open in Arduino IDE:**
- Open `firmware/arms_main.ino`
- Install required libraries:
  - `MAX30105` (SparkFun)
  - `MLX90614` (Adafruit)
  - `MFRC522` (RFID)
  - `Firebase ESP32 Client`

**3. Configure Firebase credentials in the code:**
```cpp
#define FIREBASE_HOST "your-project.firebaseio.com"
#define FIREBASE_AUTH "your-firebase-secret"
```

**4. Upload to ESP32**

### Web Dashboard

```bash
cd dashboard
npm install
npm start
```

---

## 📁 Project Structure

```
ARMS/
├── firmware/
│   ├── arms_main.ino        # Main ESP32 firmware
│   ├── sensors.h            # Sensor reading functions
│   └── firebase_config.h    # Firebase credentials
├── dashboard/
│   ├── src/
│   │   ├── App.js           # Main React app
│   │   └── components/      # Dashboard components
│   └── package.json
└── README.md
```

---

## 📊 Results

- All 3 vitals (heart rate, SpO2, temperature) monitored successfully in real time
- IV alert system tested and functional
- Web dashboard live with secure login and real-time data updates
- Successfully reduces need for physical nurse-patient contact

---

## 👥 Team

| Name | Role |
|---|---|
| Aswathy A S | Hardware integration, firmware |
| Dubin Ummer K | Firmware, sensor interfacing |
| Gopika C | Firebase, web dashboard |
| Krishnapriya PH | React frontend, authentication |

**Supervisor:** Dr. Silpa Sangeeth L R

---

## 📄 Status

✅ Completed — Government Engineering College, Palakkad
