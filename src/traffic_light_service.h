#pragma once

#include <Arduino.h>

#include "sensor_scd30.h"
#include "traffic_light.h"

namespace traffic_light_service
{

    traffic_light::Light getMatchingLight(float co2)
    {
        using namespace traffic_light;
        if (co2 < 800)
        {
            return GREEN;
        }
        else if (co2 < 1100)
        {
            return YELLOW;
        }
        else
        {
            return RED;
        }
    }

    void updateLight(const sensor_scd30::SensorData *data)
    {
        traffic_light::Light newlight = getMatchingLight(data->CO2);
        traffic_light::changeLight(newlight);
    }
}
