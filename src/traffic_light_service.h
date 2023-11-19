#pragma once

#include <Arduino.h>

#include "components/sensor_scd30.h"
#include "components/traffic_light.h"

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
}
