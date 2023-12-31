#pragma once

#include <Arduino.h>

namespace buzzer
{
    const int BUZZER_PIN = 32;
    const int BUZZER_CHANNEL = 0;

    const unsigned long INTERVAL_MS = 10000; // ms

    void setup()
    {
        ledcSetup(BUZZER_CHANNEL, 500, 15);
        ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
    }

    void play(int freq /*Hz*/, int duration_ms)
    {
        ledcWriteTone(BUZZER_CHANNEL, freq);
        if (duration_ms > 0)
        {
            delay(duration_ms);
        }
    }

    void toneOff()
    {
        play(0, 0);
    }

    void playWelcomeTone()
    {
        play(880, 100);
        play(1109, 100);
        play(1480, 150);
        toneOff();
    }

    void playWarning()
    {
        play(300, 100);
        toneOff();
    }
}
