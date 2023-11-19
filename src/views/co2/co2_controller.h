#pragma once

#include "oled_display_sh1106.h"
#include "sensor_scd30.h"
#include "../abstract_controller.h"
#include "co2_view.h"

namespace co2
{
    class Co2Controller : public AbstractController
    {
        Co2View view;

    public:
        virtual void render(const sensor_scd30::SensorData *data) override
        {
            view.renderData(data);
        }
    };
}
