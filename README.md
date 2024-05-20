# Airboost

# Components

### Microcontroller

Arduino Nano ESP32

https://docs.arduino.cc/hardware/nano-esp32/


### Sensirion SCD30 (NDIR C02 Sensor) incl. temperature and relative humidity

https://sensirion.com/media/documents/4EAF6AF8/61652C3C/Sensirion_CO2_Sensors_SCD30_Datasheet.pdf

The CO2 Sensor does not require a calibration and works out of the box.

|                 | Description          |
| --------------- | -------------------- |
| I2C-Address     | 0x61                 |
| Accuracy        | 400 ppm – 10’000 ppm |
| Update interval | 2 sec                |

For development the Adafruit SCD30 https://learn.adafruit.com/adafruit-scd30


### Monochrome OLED Display

https://www.az-delivery.de/en/products/1-3zoll-i2c-oled-display

|                  | Description  |
| ---------------- | ------------ |
| Type             | SH1106       |
| Resolution       | 128x64 pixel |
| Size             | 1.3"         |
| Background Color | Black        |
| Text Color       | white        |
| I2C-Address      | 0x3C         |


### Passive Buzzer

The ESP-32 libraries don't have a tone() function (Arduino tone library).
We have to use PWM to control the output.

# Useful resources

- https://lastminuteengineers.com/handling-esp32-gpio-interrupts-tutorial/


# SonarLint

Linter to detect & fix coding issues locally

The plugin requires `compileCommands` in order to scan the code.

Create the configuration with PlatformIO

with a CLI command

    platformio run --target compiledb --environment az-delivery-devkit-v4

or through the PIO-UI. (PlatformIO > Advanced > Compilation Database)


## Other Microcontrollers (Config)

- **AZ Delivery** ESP32 NODEMCU Module WiFi Development Board with CP2102

  https://www.az-delivery.de/en/products/esp32-developmentboard
  ```ini platformio.ini
  [env:az-delivery-devkit-v4]
  platform = espressif32
  board = az-delivery-devkit-v4
  ```

- **AZ Delivery** AZ-Nano V3-Board with Atmega328 CH340

  https://www.az-delivery.de/en/products/nano-v3-mit-ch340-arduino-kompatibel
  ```ini
  [env:az-nano]
  platform = atmelavr
  board = nanoatmega328
  ```
