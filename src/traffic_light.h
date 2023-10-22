#pragma once

#include <Arduino.h>

namespace traffic_light
{

    enum Light
    {
        GREEN = 25,
        YELLOW = 26,
        RED = 27,
        OFF = -1,
    };

    Light activeLigth = OFF;

    void setup()
    {
        pinMode(GREEN, OUTPUT);
        pinMode(YELLOW, OUTPUT);
        pinMode(RED, OUTPUT);
    }

    void changeLight(Light light)
    {
        if (light == activeLigth)
        {
            return; // the light is already set
        }

        // switch off active light
        if (activeLigth != OFF)
        {
            digitalWrite(activeLigth, LOW);
        }

        // turn on new light
        switch (light)
        {
        case GREEN:
            digitalWrite(GREEN, HIGH);
            break;

        case YELLOW:
            digitalWrite(YELLOW, HIGH);
            break;

        case RED:
            digitalWrite(RED, HIGH);
            break;

        default:
            break;
        }

        // update active light
        activeLigth = light;
    }

    // for initial debug purposes
    void cycleLights()
    {
        static unsigned long lastLightSwitch = 0;

        // debounce loop interval
        if (millis() - lastLightSwitch < 1000)
        {
            return;
        }
        else
        {
            lastLightSwitch = millis();
        }

        switch (activeLigth)
        {
        case GREEN:
            changeLight(YELLOW);
            break;

        case YELLOW:
            changeLight(RED);
            break;

        case RED:
            changeLight(OFF);
            break;

        case OFF:
            changeLight(GREEN);
            break;

        default:
            break;
        }
    }
}
