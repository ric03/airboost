#pragma once

#include <Arduino.h>
#include "views/view_controller.h"

#define BUTTON_LEFT_PIN 19
#define BUTTON_UP_PIN 18
#define BUTTON_RIGHT_PIN 17
#define BUTTON_DOWN_PIN 16
#define BUTTON_OK_PIN 5

#define DEBOUNCE_TIME 250

namespace button
{

    void IRAM_ATTR isrLeft()
    {
        // variable to keep track of the timing of recent interrupts
        static unsigned long last_button_time = 0;

        auto now = millis();
        if (now - last_button_time > DEBOUNCE_TIME)
        {
            last_button_time = now;
            view::viewController.scrollLeft();
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
            view::viewController.scrollUp();
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
            view::viewController.scrollRight();
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
            view::viewController.scrollDown();
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
            view::viewController.actionOk();
        }
    }

    void setup()
    {
        pinMode(BUTTON_LEFT_PIN, INPUT_PULLUP);
        attachInterrupt(BUTTON_LEFT_PIN, isrLeft, FALLING);

        pinMode(BUTTON_UP_PIN, INPUT_PULLUP);
        attachInterrupt(BUTTON_UP_PIN, isrUp, FALLING);

        pinMode(BUTTON_RIGHT_PIN, INPUT_PULLUP);
        attachInterrupt(BUTTON_RIGHT_PIN, isrRight, FALLING);

        pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP);
        attachInterrupt(BUTTON_DOWN_PIN, isrDown, FALLING);

        pinMode(BUTTON_OK_PIN, INPUT_PULLUP);
        attachInterrupt(BUTTON_OK_PIN, isrOk, FALLING);
    }
}
