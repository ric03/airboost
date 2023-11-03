#pragma once

#include <Arduino.h>

namespace speaker
{
    // setup is not required

    const int SPEAKER_PIN = 32;

    void playTone()
    {
        tone(SPEAKER_PIN, 500 /*Hz*/, 500 /*ms*/);
    }
}
