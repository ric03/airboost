#pragma once

#include "oled_display_sh1106.h"
#include "sensor_scd30.h"

namespace co2
{

    class Co2View
    {

    public:
        /**
         * Display the SCD30 Data (CO2-Sensor) on the display.
         *
         * Diplay Size: 64x128px (wxh)
         *
         * Textsize 1 => 6x8
         * Textsize 2 => 12x16
         * Textsize 3 => 18x24
         * Textsize 4 => 24x32
         */
        void renderData(const sensor_scd30::SensorData *data)
        {
            display::display.clearDisplay();

            // Start at top-left corner
            display::display.setCursor(0, 0);

            // print capital CO
            display::display.setTextSize(3);
            display::display.print("CO");

            // print subscript 2
            display::display.setTextSize(2);
            display::display.setCursor(36, 8);
            display::display.print("2");

            // print unit
            display::display.setTextSize(1);
            display::display.setCursor(110, 16);
            display::display.print("ppm");

            // print data
            display::display.setTextSize(4);
            display::display.setCursor(4, 32);
            display::display.printf("%5.0f", data->CO2);

            // reset textSize
            display::display.setTextSize(1);

            display::display.display();
        }
    };
}
