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


### Passive Buzzer

The ESP-32 libraries don't have a tone() function (Arduino tone library).
We have to use PWM to control the output.

# Useful resources

- https://cdn.shopify.com/s/files/1/1509/1638/files/ESP-32_NodeMCU_Developmentboard_Pinout.pdf?v=1609851295 AZ-Delivery
- https://learn.adafruit.com/adafruit-scd30
- https://lastminuteengineers.com/handling-esp32-gpio-interrupts-tutorial/


# SonarLint

Linter to detect & fix coding issues locally

The plugin requires `compileCommands` in order to scan the code.

Create the configuration with PlatformIO

with a CLI command

    platformio run --target compiledb --environment az-delivery-devkit-v4

or through the PIO-UI. (PlatformIO > Advanced > Compilation Database)
