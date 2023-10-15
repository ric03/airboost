#pragma once

namespace display_service
{

    /**
     * Using the Degree symbol requires the display to support the correct "Code Page 437".
     */
    const char DEGREE_SYMBOL = char(248);

    /**
     * Display the SCD30 Data (CO2-Sensor) on the display.
     *
     * Diplay Size: 64x128px (wxh)
     */
    void displaySCD30Data(scd30::Data *data)
    {

        /**
         * Add additional lineSpacing to improve the visual output
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
        display::display.setCursor(0, 0); // Start at top-left corner

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

}
