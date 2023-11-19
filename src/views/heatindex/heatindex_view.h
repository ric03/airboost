#pragma once

#include "components/oled_display_sh1106.h"
#include "components/sensor_scd30.h"

namespace heatindex
{

    class HeatIndexView
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
        void renderData(const double heatIndex)
        {
            display::display.clearDisplay();

            // print title
            display::display.setCursor(0, 8);
            display::display.setTextSize(2);
            display::display.print("Heat index");

            // print data
            display::display.setTextSize(4);
            display::display.setCursor(0, 32);
            display::display.printf("%2.1f", heatIndex);

            // print unit
            display::display.setTextSize(2);
            display::display.setCursor(128 - 24, 32);
            display::display.printf("%cC", display::DEGREE_SYMBOL);

            display::display.display();
        }
    };
}
