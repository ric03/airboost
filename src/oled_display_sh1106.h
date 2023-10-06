#pragma once

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
#define I2C_ADDRESS 0x3C

#define DEGREE_SYMBOL char(248)

namespace display
{
    void println(const String &s);

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

    void printSCD30Data(scd30::Data *data)
    {

        /**
         * Add some additional lineSpacing to improve the visual output
         *
         *    16 px text
         *     8 px spacing
         *    16 px text
         *     8 px spacing
         *  + 16 px text
         *  ===============
         *    64 px
         *
         * The exact textSize is set by the Adafruit library
         * Textsize 1 => 6x8
         * Textsize 2 => 12x16
         */
        const int lineHeight = 16;
        const int lineSpacing = 8;
        int textY = 0; // keep track of vertical cursor position, to support lineSpacing

        display::display.clearDisplay();

        display::display.setCursor(0, textY); // Start at top-left corner

        // 1. line
        display::display.printf("CO2");
        display::display.setTextSize(2);
        display::display.printf(" %4.0f ppm\n", data->CO2);
        display::display.setTextSize(1);

        textY += lineHeight + lineSpacing;
        // 2. line
        display::display.setCursor(0, textY);
        display::display.printf("T  ");
        display::display.setTextSize(2);
        display::display.printf(" %2.1f %cC\n", data->temperature, DEGREE_SYMBOL);
        display::display.setTextSize(1);

        textY += lineHeight + lineSpacing;
        // 3. line
        display::display.setCursor(0, textY);
        display::display.printf("RH ");
        display::display.setTextSize(2);
        display::display.printf(" %2.1f %%\n", data->relative_humidity);
        display::display.setTextSize(1);

        display::display.display();
    }

} // namespace display
