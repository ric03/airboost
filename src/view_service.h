#pragma once

#include "views/data/data_controller.h"
#include "views/co2/co2_controller.h"
#include "views/heatindex/heatindex_controller.h"

namespace view
{
    class ViewService
    {
        data::DataController dataController;
        co2::Co2Controller co2Controller;
        heatindex::HeatIndexController heatIndexController;

        AbstractController *activeView;

    public:
        ViewService()
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

    ViewService viewService;
}
