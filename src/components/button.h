#pragma once

#include <Arduino.h>
#include "view_service.h"

namespace button
{

    const int BUTTON_LEFT_PIN = 19;
    const int BUTTON_UP_PIN = 18;
    const int BUTTON_RIGHT_PIN = 17;
    const int BUTTON_DOWN_PIN = 16;
    const int BUTTON_OK_PIN = 5;

    const unsigned long DEBOUNCE_TIME = 150; // ms

    void IRAM_ATTR isrLeft()
    {
        // variable to keep track of the timing of recent interrupts
        static unsigned long last_button_time = 0;

        auto now = millis();
        if (now - last_button_time > DEBOUNCE_TIME)
        {
            last_button_time = now;
            view::viewService.scrollLeft();
        }
    }

    void IRAM_ATTR isrUp()
    {
        // variable to keep track of the timing of recent interrupts
        static unsigned long last_button_time = 0;

        auto now = millis();
        if (now - last_button_time > DEBOUNCE_TIME)
        {
            last_button_time = now;
            view::viewService.scrollUp();
        }
    }

    void IRAM_ATTR isrRight()
    {
        // variable to keep track of the timing of recent interrupts
        static unsigned long last_button_time = 0;

        auto now = millis();
        if (now - last_button_time > DEBOUNCE_TIME)
        {
            last_button_time = now;
            view::viewService.scrollRight();
        }
    }

    void IRAM_ATTR isrDown()
    {
        // variable to keep track of the timing of recent interrupts
        static unsigned long last_button_time = 0;

        auto now = millis();
        if (now - last_button_time > DEBOUNCE_TIME)
        {
            last_button_time = now;
            view::viewService.scrollDown();
        }
    }

    void IRAM_ATTR isrOk()
    {
        // variable to keep track of the timing of recent interrupts
        static unsigned long last_button_time = 0;

        auto now = millis();
        if (now - last_button_time > DEBOUNCE_TIME)
        {
            last_button_time = now;
            view::viewService.actionOk();
        }
    }

    /**
     * Arduinos have an internal pullup
     */
    void setupButton(uint8_t pin, void (*intRoutine)())
    {
        pinMode(pin, INPUT_PULLUP);
        attachInterrupt(pin, intRoutine, FALLING);
    }

    void setup()
    {
        setupButton(BUTTON_LEFT_PIN, isrLeft);
        setupButton(BUTTON_UP_PIN, isrUp);
        setupButton(BUTTON_RIGHT_PIN, isrRight);
        setupButton(BUTTON_DOWN_PIN, isrDown);
        setupButton(BUTTON_OK_PIN, isrOk);
    }
}
