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

    void powerOnSelfTest()
    {
        digitalWrite(GREEN, HIGH);
        digitalWrite(YELLOW, HIGH);
        digitalWrite(RED, HIGH);
        delay(500);
        digitalWrite(GREEN, LOW);
        digitalWrite(YELLOW, LOW);
        digitalWrite(RED, LOW);
    }

    void setup()
    {
        pinMode(GREEN, OUTPUT);
        pinMode(YELLOW, OUTPUT);
        pinMode(RED, OUTPUT);
    }

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

    void changeLight(Light light)
    {
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

    void updateLight(const float co2)
    {
        auto light = getMatchingLight(co2);
        if (light != activeLigth)
        {
            changeLight(light);
        }
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
}
