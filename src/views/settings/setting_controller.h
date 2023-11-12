#pragma once

#include <Arduino.h>
#include "../abstract_controller.h"
#include "setting_view.h"
#include "setting_model.h"

namespace settings
{
    class SettingController : public AbstractController
    {
        SettingView view;

        Settings settings;

        Item *display;
        Item *led;
        Item *sound;

        Item *activeItem;

    public:
        SettingController()
        {
            this->display = new Item(ItemName::Display, nullptr, this->led, std::bind(&Settings::toggleDisplayOn, &settings));
            this->led = new Item(ItemName::Led, this->display, this->sound, std::bind(&Settings::toggleLedOn, &settings));
            this->sound = new Item(ItemName::Sound, this->led, nullptr, std::bind(&Settings::toggleSoundOn, &settings));

            this->activeItem = this->display;
        }

        virtual void render(const sensor_scd30::SensorData *unused) override
        {
            view.renderSettings(&settings, activeItem->getName());
        }

        virtual AbstractController *getPreviousView() override
        {
            Item *previousItem = activeItem->getPreviousItem();

            if (previousItem == nullptr)
            {
                return this->previousView;
            }
            else
            {
                this->activeItem = previousItem;
                return this;
            }
        }

        virtual AbstractController *getNextView() override
        {
            Item *nextItem = activeItem->getNextItem();

            Serial.println("get next view");
            if (nextItem == nullptr)
            {
                return this->nextView;
            }
            else
            {
                Serial.println("go to next item (not view)");
                this->activeItem = nextItem;
                return this;
            }
        }

        virtual void actionOk() override
        {
            this->activeItem->toggleStateFn();
        }
    };
}
