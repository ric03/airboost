#pragma once

#include "data/data_controller.h"
#include "co2/co2_controller.h"
#include "heatindex/heatindex_controller.h"

namespace view
{
    class ViewController
    {
        data::DataController dataController;
        co2::Co2Controller co2Controller;
        heatindex::HeatIndexController heatIndexController;

        AbstractController *activeView;

    public:
        ViewController()
        {
            dataController.setViews(&heatIndexController, &co2Controller);
            co2Controller.setViews(&dataController, &heatIndexController);
            heatIndexController.setViews(&co2Controller, &dataController);
            this->activeView = &dataController;
        }

        void scrollLeft()
        {
            // noop
        }

        void scrollUp()
        {
            activeView = activeView->getPreviousView();
        }

        void scrollRight()
        {
            // noop
        }

        void scrollDown()
        {
            activeView = activeView->getNextView();
        }

        void actionOk()
        {
            activeView->actionOk();
        }

        void render(const sensor_scd30::SensorData *data)
        {
            activeView->render(data);
        }
    };

    ViewController viewController;
}
