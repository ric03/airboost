#pragma once

#include "oled_display_sh1106.h"
#include "setting_model.h"

namespace settings
{

    class SettingView
    {
        bool isActive(const ItemName activeItem, const ItemName itemName)
        {
            return activeItem == itemName;
        }

        void printSettingItem(bool isActive, const char *text, const bool isOn)
        {
            char *activeIndicator = getActiveIndicator(isActive);
            char *state = getState(isOn);

            display::display.printf("%1s%8s", activeIndicator, text);
            if (isActive)
                display::invertTextColor();
            display::display.printf(" %3s\n", state);
            if (isActive)
                display::setNormalTextColor();
        }

        char *getActiveIndicator(bool isActive)
        {
            return (char *)(isActive ? ">" : " ");
        }

        char *getState(const bool isOn)
        {
            return (char *)(isOn ? "on" : "off");
        }

    public:
        void renderSettings(Settings *settings, ItemName activeItem)
        {
            display::display.clearDisplay();
            display::display.setCursor(0, 0);

            display::display.setTextSize(2);
            display::display.println("Settings");
            display::display.setTextSize(1);
            display::display.println();

            printSettingItem(isActive(activeItem, ItemName::Display), "Display", settings->isDisplayOn);
            printSettingItem(isActive(activeItem, ItemName::Led), "LED", settings->isLedOn);
            printSettingItem(isActive(activeItem, ItemName::Sound), "Sound", settings->isSoundOn);

            display::display.display();
        }
    };
}
