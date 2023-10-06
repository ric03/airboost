# Airboost

# Components

### Microcontroller

AZ Delivery DevKit ESP32

#### Pinout ESP32

|           | Pin     |
| --------- | ------- |
| SDA (I2C) | GPIO 21 |
| SCL (I2C) | GPIO 22 |

![Pinout ESP32](docs/ESP-32_NodeMCU_Developmentboard_Pinout.png)


### C02 Sensor (incl. temperature and relative humidity)

Adafruit SCD30 based on the Sensirion SCD30 (NDIR C02 Sensor)

|             | Description |
| ----------- | ----------- |
| I2C-Address | 0x61        |

### Monochrome OLED Display

|                  | Description  |
| ---------------- | ------------ |
| Type             | SH1106       |
| Resolution       | 128x64 pixel |
| Size             | 1.3"         |
| Background Color | Black        |
| Text Color       | Blue (white) |
| I2C-Address      | 0x3C         |

