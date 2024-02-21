# NRF24 Arduino UNO node

## Overview

This project is designed to monitor various environmental metrics in forested areas and transmit the collected data wirelessly using the NRF24 module. The project leverages the PlatformIO ecosystem for an efficient and streamlined development process.

## Features

- **Real-Time Data Collection:** Measures temperature, humidity, soil moisture, and more.
- **Wireless Communication:** Utilizes NRF24 modules for long-range, low-power data transmission.
- **Easy to Deploy:** Compact and simple design for hassle-free deployment.
- **PlatformIO Integration:** Benefit from easy compilation, upload, and dependency management.

## Hardware Requirements

- Arduino-enabled Microcontroller (Arduino UNO)
- NRF24L01+ Wireless Module
- Sensors (Rain, Soil moisture, CO, dust, DHT22)
- Power Source (e.g., batteries, solar panels)
- Miscellaneous (wires, PCB, enclosures, etc.)

## Software Dependencies

- PlatformIO Core
- Arduino Framework
- NRF24 Library

## Getting Started

### Setup and Configuration

1. **Clone the Repository**

```bash
git clone https://github.com/your-github-username/forest-data-collector-node.git
cd forest-data-collector-node
```

2. **Install Dependencies**

Install [PlatformIO Extension](https://platformio.org/) to IDE of your preference or use the CLI version.

Open the project folder in PlatformIO IDE or use the `platformio lib install` command to install the necessary libraries.

3. **Hardware Assembly**

Install sensor according to the pinout table below

### Build and Upload

Utilize PlatformIO's command-line interface (CLI) or IDE integration to compile and upload the firmware to your microcontroller.

```bash
platformio run --target upload
```

## Hardware pinout:
| NRF24 Label | Sensor Name    | Arduino UNO Pin |
|-------------|----------------|-----------------|
| GND         |                | GND             |
| VCC         |                | 3.3V            |
| CE          |                | 8               |
| CSN         |                | 10              |
| SCK         |                | 13              |
| MOSI        |                | 11              |
| MISO        |                | 12              |
| IRQ         |                | 9               |
|             | Rain Sensor    | A0              |
|             | Soil Moisture  | A1              |
|             | CO Sensor      | A4              |
|             | Dust Sensor    | A5              |
|             | DHT22          | 2               |
