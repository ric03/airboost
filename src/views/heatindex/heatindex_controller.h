#pragma once

#include "components/oled_display_sh1106.h"
#include "components/sensor_scd30.h"

#include "views/abstract_controller.h"
#include "heatindex_view.h"

namespace heatindex
{
    class HeatIndexController : public AbstractController
    {
        HeatIndexView view;

    public:
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

        virtual void render(const sensor_scd30::SensorData *data) override
        {
            double headIndex = calculateHeatIndex(data->temperature, data->relative_humidity);
            view.renderData(headIndex);
        }
    };
}
