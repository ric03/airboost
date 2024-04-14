#pragma once

#include "components/oled_display_sh1106.h"
#include "components/sensor_scd30.h"
#include "views/abstract_view.h"

namespace heatindex
{

    class HeatIndexView : public AbstractView
    {

        /**
         * t temperature in degrees Celcius
         * r relative Humidity in percentage value between 0 and 100
         *
         * see: https://en.wikipedia.org/wiki/Heat_index#Formula
         */
        double calculateHeatIndex(double t, double r)
        {
            double c1 = -8.78469475556,
                   c2 = 1.61139411,
                   c3 = 2.33854883889,
                   c4 = -0.14611605,
                   c5 = -0.012308094,
                   c6 = -0.0164248277778,
                   c7 = 0.002211732,
                   c8 = 0.00072546,
                   c9 = -0.000003582;

            double heatIndex = c1                    //
                               + c2 * t              //
                               + c3 * r              //
                               + c4 * t * r          //
                               + c5 * t * t          //
                               + c6 * r * r          //
                               + c7 * t * t * r      //
                               + c8 * t * r * r      //
                               + c9 * t * t * r * r; //

            return heatIndex;
        }

        /**
         * Display the SCD30 Data (CO2-Sensor) on the display.
         *
         * Diplay Size: 64x128px (hxw)
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

    public:
        virtual void render() override
        {
            auto data = &sensor_scd30::sensorData;
            double headIndex = calculateHeatIndex(data->temperature, data->relative_humidity);
            renderData(headIndex);
        }
    };
}
