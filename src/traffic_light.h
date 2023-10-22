#pragma once

#include <Arduino.h>

namespace traffic_light
{

    /**
     * The assigned values are the physical pin numbers of the corresponding led.
     */
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
            // the light is already active
            return;
        }

        if (activeLigth != OFF)
        {
            // switch off active light
            digitalWrite(activeLigth, LOW);
        }

        if (light != OFF)
        {
            // switch on new light
            digitalWrite(light, HIGH);
        }

        // update active light
        activeLigth = light;
    }

    void printSerial()
    {
        String light = "OFF";
        switch (activeLigth)
        {
        case GREEN:
            light = "GREEN";
            break;

        case YELLOW:
            light = "YELLOW";
            break;

        case RED:
            light = "RED";
            break;

        default:
            light = "OFF";
            break;
        }
        Serial.printf("Active Light: %s\n", light.c_str());
    }

    // for debug purposes
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
