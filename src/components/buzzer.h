#pragma once

#include <Arduino.h>

namespace buzzer
{
    volatile bool isMuted = false;

    const int BUZZER_PIN = D8;
    const int BUZZER_CHANNEL = 0;

    void setup()
    {
        Serial.print("Initializing buzzer ...");

        ledcSetup(BUZZER_CHANNEL, 500, 15);
        ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);

        Serial.println(" setup complete");
    }

    void play(int freq_Hz, int duration_ms)
    {
        ledcWriteTone(BUZZER_CHANNEL, freq_Hz);
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
        if (isMuted)
            return;

        play(300, 100);
        toneOff();
    }

    void toggleMute()
    {
        isMuted = !isMuted;
    }
}
