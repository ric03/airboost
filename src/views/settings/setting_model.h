#pragma once

namespace settings
{
    class Settings
    {
    public:
        bool isDisplayOn = true;
        bool isLedOn = true;
        bool isSoundOn = true;

        void toggleDisplayOn()
        {
            this->isDisplayOn = !this->isDisplayOn;
        }

        void toggleLedOn()
        {
            this->isLedOn = !this->isLedOn;
        }

        void toggleSoundOn()
        {
            this->isSoundOn = !this->isSoundOn;
        }
    };

    enum class ItemName
    {
        Display,
        Led,
        Sound,
    };

    class Item
    {
        Item *previous;
        Item *next;

        ItemName name;

    public:
        typedef std::function<void()> TToggleStateFn;
        TToggleStateFn toggleStateFn;

        Item(ItemName name, Item *previous, Item *next, TToggleStateFn toggleStateFn)
        {
            this->previous = previous;
            this->next = next;
            this->toggleStateFn = toggleStateFn;
            this->name = name;
        }

        Item *getPreviousItem()
        {
            return this->previous;
        }

        Item *getNextItem()
        {
            return this->next;
        }

        ItemName getName()
        {
            return name;
        }
    };
}
