#pragma once

#include "data/data_controller.h"
#include "settings/setting_controller.h"

namespace view
{
    class ViewController
    {
        data::DataController dataController;
        settings::SettingController settingController;

        AbstractController *activeView;

    public:
        ViewController()
        {
            dataController.setViews(&settingController, &settingController);
            settingController.setViews(&dataController, &dataController);
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
