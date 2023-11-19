#pragma once

#include <Arduino.h>

namespace buzzer
{
    const int BUZZER_PIN = 32;
    const int BUZZER_CHANNEL = 0;

    void setup()
    {
        ledcSetup(BUZZER_CHANNEL, 500, 15);
        ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
    }

    void playTone()
    {
        ledcWriteTone(BUZZER_CHANNEL, 880 /*Hz*/);
        delay(100);
        ledcWriteTone(BUZZER_CHANNEL, 1109 /*Hz*/);
        delay(100);
        ledcWriteTone(BUZZER_CHANNEL, 1480 /*Hz*/);
        delay(150);
        ledcWrite(BUZZER_CHANNEL, 0); // tone off
        delay(10);
    }

}
