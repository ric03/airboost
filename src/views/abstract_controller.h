#pragma once

#include "sensor_scd30.h"

class AbstractController
{
protected:
    AbstractController *previousView;
    AbstractController *nextView;

public:
    void setViews(AbstractController *previous, AbstractController *next)
    {
        this->previousView = previous;
        this->nextView = next;
    }

    virtual ~AbstractController() {}
    virtual void render(const sensor_scd30::SensorData *data) = 0;
    virtual AbstractController *getPreviousView() { return previousView; };
    virtual AbstractController *getNextView() { return nextView; };
    virtual void actionOk() {}
};
