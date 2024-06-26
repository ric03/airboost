#pragma once

#include "components/oled_display_sh1106.h"
#include "components/sensor_scd30.h"
#include "views/abstract_view.h"

namespace data
{

    class RawDataView : public AbstractView
    {
        /**
         * Display the SCD30 Data (CO2-Sensor) on the display.
         *
         * Diplay Size: 64x128px (hxw)
         */
        void renderData(const sensor_scd30::SensorData *data)
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
            const uint16_t lineHeight = 16;
            const uint16_t lineSpacing = 8;
            uint16_t textY = 0; // keep track of vertical cursor position, to support lineSpacing

            display::display.clearDisplay();
            display::display.setCursor(0, 0); // Start at top-left corner

            // 1. line
            display::display.setTextSize(1);
            display::display.printf("CO2");
            display::display.setTextSize(2);
            display::display.printf(" %4.0f ppm\n", data->CO2);

            textY += lineHeight + lineSpacing;
            // 2. line
            display::display.setCursor(0, textY);
            display::display.setTextSize(1);
            display::display.printf("T  ");
            display::display.setTextSize(2);
            display::display.printf(" %2.1f %cC\n", data->temperature, display::DEGREE_SYMBOL);

            textY += lineHeight + lineSpacing;
            // 3. line
            display::display.setCursor(0, textY);
            display::display.setTextSize(1);
            display::display.printf("RH ");
            display::display.setTextSize(2);
            display::display.printf(" %2.1f %%\n", data->relative_humidity);

            display::display.display();
        }

    public:
        virtual void render() override
        {
            auto data = &sensor_scd30::sensorData;
            renderData(data);
        }
    };
}
