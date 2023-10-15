#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
#define I2C_ADDRESS 0x3C

namespace display
{
    Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

    void setup()
    {
        if (!display.begin(I2C_ADDRESS, true))
        {
            Serial.println(F("SSD1306 allocation failed"));
            for (;;)
                ; // Don't proceed, loop forever
        }

        display.setTextColor(SH110X_WHITE); // Draw white text (the default is black), because the display is black
        display.setTextSize(1);             // Normal 1:1 pixel scale
        display.cp437(true);                // Enable correct CP437 character values, to print degree symbol (°)

        display.clearDisplay();
        display.display();
    }

} // namespace display
