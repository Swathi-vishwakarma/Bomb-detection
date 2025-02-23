# 💣 Bomb Detection Robot  

## 📌 Introduction  
The **Bomb Detection Robot** is designed to detect metallic objects, such as explosives and landmines, using a **metal detector sensor**. Upon detecting metal, the system **triggers an alert via a buzzer** and displays the detection status on an **LCD screen**. This robot is useful in **security, military applications, and landmine detection**.  

---

## 🌟 Features  
- **Metal Detection** – Uses a **metal detector** to identify buried metallic objects.  
- **Real-time Alerts** – Triggers a **buzzer** when metal is detected.  
- **LCD Display** – Shows detection status in real time.  
- **Remote Operation** – Can be wirelessly controlled via an **RF module**.  
- **Autonomous or Manual Control** – Operates autonomously or via remote control.  

---

## 🔩 Components Used  

### **1️⃣ Hardware Components**  
- **Microcontroller**: Arduino Uno  
- **Metal Detector Sensor**: Detects metallic objects underground  
- **Buzzer**: Audible alert system  
- **LCD Display**: 16x2 I2C Display for real-time status updates  
- **RF Module (Optional)**: Wireless communication (HC-12 or NRF24L01)  
- **Motor Driver**: L298N for controlling robot movement  
- **DC Motors**: For mobility  
- **Battery**: 12V Li-ion or Lead Acid Battery  

---

## 🛠️ Circuit Connection  

| Component  | Connection to Arduino |
|------------|----------------------|
| **Metal Detector Sensor** | Analog Pin (A0) |
| **Buzzer** | Digital Pin (D3) |
| **LCD Display (I2C)** | SDA, SCL (A4, A5) |
| **Motor Driver (L298N)** | PWM Pins (D5, D6) |
| **RF Module (HC-12)** | Tx & Rx (Serial Communication) |
| **Battery** | Power Supply (12V or 9V) |

---

## ⚙️ Working Principle  
1️⃣ The **metal detector sensor** continuously scans the ground for metallic objects.  
2️⃣ When metal is detected, the **Arduino Uno** triggers a **buzzer** alert.  
3️⃣ The detection status is displayed on the **16x2 LCD** screen.  
4️⃣ The robot can be remotely controlled using an **RF Module** (if implemented).  

---

## 🛠️ Installation & Setup  

### **1️⃣ Hardware Setup**  
- Assemble the robot with motors, driver, and sensors.  
- Connect all components according to the circuit diagram.  
- Power the Arduino using a **9V/12V battery**.  

### **2️⃣ Software Setup**  
- Install **Arduino IDE** from [Arduino Official Site](https://www.arduino.cc/en/software).  
- Install necessary libraries:  
