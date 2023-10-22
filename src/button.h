#pragma once

#include <Arduino.h>

#define BUTTON_PIN 23
#define DEBOUNCE_TIME 250

namespace button
{

    void IRAM_ATTR isr()
    {
        // variable to keep track of the timing of recent interrupts
        static unsigned long last_button_time = 0;
        static unsigned long btn_counter = 0;

        auto now = millis();
        if (now - last_button_time > DEBOUNCE_TIME)
        {
            Serial.printf("Button is pressed #%lu\n", btn_counter); // todo remove this line, its used only for intial tests
            last_button_time = now;
            btn_counter++;
        }
    }

    void setup()
    {
        pinMode(BUTTON_PIN, INPUT_PULLUP);
        attachInterrupt(BUTTON_PIN, isr, FALLING);
    }
}
