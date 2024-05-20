#pragma once

#include <Arduino.h>

namespace light_indicator
{

    /**
     * The assigned values are the physical pin numbers of the corresponding led.
     */
    enum Light
    {
        GREEN = D5,
        RED = D6,
        OFF = -1,
    };

    Light activeLigth = OFF;

    void powerOnSelfTest()
    {
        digitalWrite(GREEN, HIGH);
        digitalWrite(RED, HIGH);
        delay(500);
        digitalWrite(GREEN, LOW);
        digitalWrite(RED, LOW);
    }

    void setup()
    {
        pinMode(GREEN, OUTPUT);
        pinMode(RED, OUTPUT);
    }

    /**
     * threshold    color
     *    0 -  800  GREEN
     *  800 -  inf  RED
     *
     */
    light_indicator::Light mapCo2ToTrafficLight(float co2_ppm)
    {
        using namespace light_indicator;

        if (co2_ppm < 800)
        {
            return GREEN;
        }
        else
        {
            return RED;
        }
    }

    void changeLight(const Light newLight)
    {
        if (activeLigth != OFF)
        {
            // switch off active light
            digitalWrite(activeLigth, LOW);
        }

        if (newLight != OFF)
        {
            // switch on new light
            digitalWrite(newLight, HIGH);
        }

        // update active light
        activeLigth = newLight;
    }

    void updateLight(const float co2)
    {
        auto newLight = mapCo2ToTrafficLight(co2);
        if (newLight != activeLigth)
        {
            changeLight(newLight);
        }
    }

    void printSerial()
    {
        String light = "";
        switch (activeLigth)
        {
        case GREEN:
            light = "GREEN";
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
