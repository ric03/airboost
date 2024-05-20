#pragma once

#include <Arduino.h>
#include "views/view_service.h"
#include "buzzer.h"
#include "interrupt_flags.h"

namespace button
{

    const int BUTTON_MUTE_BUZZER = D2;
    const int BUTTON_NEXT_VIEW = D3;

    const unsigned long DEBOUNCE_TIME = 150; // ms

    void
#if defined(ESP32)
        IRAM_ATTR // Forces code into IRAM instead of flash (required for ESP32)
#endif
        isrMuteBuzzer()
    {
        // variable to keep track of the timing of recent interrupts
        static unsigned long last_button_time = 0;

        auto now = millis();
        if (now - last_button_time > DEBOUNCE_TIME)
        {
            Serial.println("Button pressed: mute buzzer");

            last_button_time = now;
            buzzer::toggleMute();
            view::viewService.switchToBuzzerMuteView();
            updateViewImmediatly = true;
        }
    }

    void
#if defined(ESP32)
        IRAM_ATTR // Forces code into IRAM instead of flash (required for ESP32)
#endif
        isrNextView()
    {
        // variable to keep track of the timing of recent interrupts
        static unsigned long last_button_time = 0;

        auto now = millis();
        if (now - last_button_time > DEBOUNCE_TIME)
        {
            Serial.println("Button pressed: next view");

            last_button_time = now;
            view::viewService.switchToNextView();
            updateViewImmediatly = true;
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
        Serial.print("Initializing buttons ...");
        setupButton(BUTTON_MUTE_BUZZER, isrMuteBuzzer);
        setupButton(BUTTON_NEXT_VIEW, isrNextView);
        Serial.println(" setup complete");
    }
}
