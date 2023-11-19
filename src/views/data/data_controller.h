#pragma once

#include "components/oled_display_sh1106.h"
#include "components/sensor_scd30.h"
#include "views/abstract_controller.h"
#include "data_view.h"

namespace data
{
    class DataController : public AbstractController
    {
        DataView view;

    public:
        virtual void render(const sensor_scd30::SensorData *data) override
        {
            view.renderData(data);
        }
    };
}
