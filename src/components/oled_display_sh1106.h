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

    const uint16_t WHITE = SH110X_WHITE;
    const uint16_t BLACK = SH110X_BLACK;

    /**
     * Using the Degree symbol requires the display to support the correct "Code Page 437".
     */
    const char DEGREE_SYMBOL = char(248);

    void setNormalTextColor()
    {
        // Draw white text (the default is black), because the display is black
        display.setTextColor(WHITE);
    }

    void invertTextColor()
    {
        display.setTextColor(BLACK, WHITE);
    }

    void setup()
    {
        if (!display.begin(I2C_ADDRESS, true))
        {
            Serial.println(F("SSD1306 allocation failed"));
            for (;;)
                ; // Don't proceed, loop forever
        }

        setNormalTextColor();
        display.setTextSize(1); // Normal 1:1 pixel scale
        display.cp437(true);    // Enable correct CP437 character values, to print degree symbol (°)

        display.clearDisplay();
        display.display();
    }

    void printWelcomeMessage()
    {
        display.setTextSize(2);
        display.println("AIRBOOST");
        display.println();
        display.println("Air");
        display.println("Quality");
        display.display();
    }

}
