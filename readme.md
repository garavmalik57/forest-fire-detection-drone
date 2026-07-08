# 🚁 Forest Fire Detection Drone using ESP32, LoRa & ThingSpeak

## Overview

This project presents an **IoT-based Forest Fire Detection System** that combines **ESP32 microcontrollers, LoRa communication, and the ThingSpeak IoT Cloud** to monitor environmental conditions in remote areas.

The drone is equipped with sensors to measure **temperature**, **humidity**, and **air quality (gas concentration)**. These readings are processed by an ESP32 and transmitted over **LoRa (433 MHz)** to a ground-based receiver for reliable long-range communication.

In addition to LoRa transmission, the ESP32 also uploads the sensor readings to **ThingSpeak**, allowing users to remotely monitor environmental conditions through live graphs and historical data visualization.

This hybrid communication architecture provides both **local long-range communication** and **cloud-based remote monitoring**, making the system suitable for wildfire detection and environmental monitoring.

---

# Features

* 🚁 Drone-based environmental monitoring
* 🌡️ Real-time temperature monitoring
* 💧 Real-time humidity monitoring
* 🌫️ Smoke and gas detection using MQ135
* 📡 Long-range wireless communication using LoRa (433 MHz)
* ☁️ ThingSpeak cloud integration
* 📈 Automatic graph generation on ThingSpeak
* 📊 Historical data logging and visualization
* 📶 Reliable communication in remote locations
* ⚡ Low-power embedded system
* 🔥 Early fire detection through environmental monitoring

---

# System Architecture

```text
                         +-----------------------------+
                         |         Drone Unit          |
                         |-----------------------------|
                         | ESP32                       |
                         | DHT11 Temperature Sensor    |
                         | MQ135 Gas Sensor            |
                         | LoRa Transmitter            |
                         | Wi-Fi                       |
                         +--------------+--------------+
                                        |
                 +----------------------+----------------------+
                 |                                             |
                 |                                             |
          LoRa Communication                          Internet / Wi-Fi
                 |                                             |
                 |                                             |
        +--------v---------+                         +----------v----------+
        |    Base Station  |                         |     ThingSpeak      |
        | ESP8266 + LoRa   |                         |     IoT Cloud       |
        +--------+---------+                         +----------+----------+
                 |                                             |
                 |                                             |
          Local Monitoring                         Live Dashboard & Graphs
                 |
                 |
          Local Server / PC
```

---

# Hardware Components

## Drone Unit

* ESP32 Development Board
* SX1278 LoRa Module (433 MHz)
* DHT11 Temperature & Humidity Sensor
* MQ135 Gas Sensor
* Drone Platform
* Battery Pack

### Base Station

* ESP8266 NodeMCU
* SX1278 LoRa Module (433 MHz)
* Wi-Fi Connection
* Local Computer

---

# Software Used

* Arduino IDE
* ESP32 Board Package
* ESP8266 Board Package
* LoRa Library
* SPI Library
* DHT Sensor Library
* WiFi Library
* ESP8266WiFi Library
* ESP8266HTTPClient Library
* ThingSpeak Library

---

# Working Principle

## Drone Unit

The ESP32 onboard the drone continuously collects environmental data from the attached sensors.

The DHT11 sensor measures:

* Temperature
* Humidity

The MQ135 sensor measures:

* Smoke concentration
* Air quality
* Harmful gases

After acquiring the sensor values, the ESP32 performs basic processing and creates a formatted data packet.

The data is then transmitted using the LoRa module to the ground station every few seconds.

At the same time, whenever internet connectivity is available, the ESP32 uploads the same sensor readings to the ThingSpeak IoT Cloud for remote monitoring and permanent storage.

---

## Base Station

The ground station consists of a NodeMCU connected to another LoRa module.

It continuously listens for incoming LoRa packets from the drone.

Whenever a packet is received, the receiver:

* Decodes the transmitted information
* Extracts the temperature value
* Extracts the humidity value
* Extracts the MQ135 sensor readings
* Converts the data into JSON format
* Makes the data available for further processing or storage on a local server

This enables reliable local monitoring even when internet connectivity is unavailable.

---

# ThingSpeak Cloud Integration

Alongside LoRa communication, the project integrates with the **ThingSpeak IoT Cloud**, enabling remote monitoring of environmental conditions.

The ESP32 periodically uploads sensor readings to a ThingSpeak channel.

The uploaded parameters include:

* Temperature
* Humidity
* MQ135 Raw Sensor Value
* MQ135 Sensor Voltage

ThingSpeak automatically stores every reading and generates live graphs for each parameter.

This allows users to monitor environmental conditions remotely through a web browser without requiring direct access to the drone or base station.

The historical data can also be analyzed to observe long-term environmental trends and identify abnormal changes that may indicate the presence of fire.

---

# Cloud Features

* Live sensor monitoring
* Automatic graph generation
* Historical data storage
* Remote access from anywhere
* Continuous environmental monitoring
* Data visualization
* Easy export of collected sensor data
* MATLAB analytics support within ThingSpeak

---

# Fire Detection Logic

The project does not rely on a single sensor to detect fire.

Instead, it monitors multiple environmental parameters simultaneously.

Possible fire conditions include:

* Sudden increase in temperature
* Rapid decrease in humidity
* High MQ135 gas sensor readings indicating smoke or combustion gases

By combining these sensor values, the system can provide an early indication of potential fire incidents before they spread significantly.

---

# Applications

* Forest Fire Detection
* Wildfire Monitoring
* Environmental Monitoring
* Smart Agriculture
* Air Pollution Monitoring
* Disaster Management
* Wildlife Reserve Monitoring
* Industrial Safety Monitoring
* Remote Sensor Networks
* Border/Perimeter Surveillance

---

# Conclusion

This project demonstrates a hybrid IoT monitoring system that combines **embedded systems, wireless communication, and cloud computing** to provide an efficient solution for remote environmental monitoring.

By integrating **ESP32**, **LoRa**, and **ThingSpeak**, the system enables both long-range local communication and cloud-based visualization of sensor data. The combination of temperature, humidity, and gas sensing provides a practical approach for early fire detection in forests and other remote environments where continuous monitoring is essential.
