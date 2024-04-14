#pragma once

#include "components/oled_display_sh1106.h"
#include "components/buzzer.h"
#include "views/abstract_view.h"

namespace buzzer
{
    class BuzzerMuteView : public AbstractView
    {

        /**
         * Display the state of the sound alarm (buzzer).
         *
         * Diplay Size: 64x128px (hxw)
         *
         * Textsize 1 => 6x8
         * Textsize 2 => 12x16
         * Textsize 3 => 18x24
         * Textsize 4 => 24x32
         */
        void renderData(const bool isMuted)
        {
            display::display.clearDisplay();

            // Start at top-left corner
            display::display.setCursor(0, 0);

            display::display.setTextSize(2);
            display::display.print("Sound is\n");
            if (isMuted)
            {
                display::display.print("disabled");
            }
            else
            {
                display::display.print("enabled");
            }

            // reset textSize
            display::display.setTextSize(1);

            display::display.display();
        }

    public:
        void render() override
        {
            auto isMuted = buzzer::isMuted;
            renderData(isMuted);
        }
    };
}
