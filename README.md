# Dual ICM-20948 SPI IMU Communication with ESP32

This project demonstrates how to connect **two ICM-20948 IMU sensors** to an **ESP32** using the **SPI protocol**, where both sensors share common MISO, MOSI, and SCLK lines, but have **separate CS pins**.

---

## 🧠 Objective

To **alternately fetch accelerometer and gyroscope data** from two IMU sensors by toggling chip select lines on each SPI cycle. Since SPI allows communication with one slave at a time, the ESP32 reads from one sensor per cycle, giving near-simultaneous data from both.

---

## ⚙️ Hardware Used

- 2x SparkFun ICM-20948 IMU (9DoF) Breakout
- ESP32 (VSPI port used)
- Jumper wires
- Breadboard or PCB

---

## 🧩 Wiring

| ESP32 Pin | Function     | IMU 1 | IMU 2 |
|-----------|--------------|-------|-------|
| GPIO 4    | SCLK         | ✅    | ✅    |
| GPIO 19   | MISO (SDO)   | ✅    | ✅    |
| GPIO 23   | MOSI (SDI)   | ✅    | ✅    |
| GPIO 16   | CS (Sensor 1)| ✅    | ❌    |
| GPIO 21   | CS (Sensor 2)| ❌    | ✅    |
| 3.3V      | Power        | ✅    | ✅    |
| GND       | Ground       | ✅    | ✅    |

---
## 🔌 Connection Diagram

![Connection Diagram](connection.png)

---

## 🔁 Logic Flow

- A boolean variable `m` is toggled each loop cycle.
- Depending on its value, one of the two CS pins is activated.
- SPI is initialized with the corresponding CS pin.
- The sensor is initialized once and reused.
- Accelerometer and gyroscope data is fetched and printed from the active sensor.

---

## 📦 Library Used

- [SparkFun ICM-20948 Arduino Library](https://github.com/sparkfun/SparkFun_ICM-20948_ArduinoLibrary)

---

## 🖥️ Sample Output (Serial Monitor)

Output from sensor 1
0.02, -0.01, 9.81, 0.01, 0.02, 0.00
Output from sensor 2
0.01, 0.00, 9.79, 0.02, 0.01, -0.01

---

## 🔮 Future Improvements

- Can be used in motion and orientation tracker
- Synchronize data logging and timestamps
- Add SD card or cloud upload support
- Extend to 3+ sensors with a shift register or demux
- Visualize motion using 3D rendering tools

---

## 👨‍💻 Author

Soumyadeep Chakraborty

---
