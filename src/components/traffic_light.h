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

    /**
     * threshold    color
     *    0 -  800  GREEN
     *  800 - 1100  YELLOW
     * 1100 - inf   RED
     *
     */
    traffic_light::Light mapCo2ToTrafficLight(float co2_ppm)
    {
        using namespace traffic_light;
        if (co2_ppm < 800)
        {
            return GREEN;
        }
        else if (co2_ppm < 1100)
        {
            return YELLOW;
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
