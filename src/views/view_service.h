#pragma once

#include "views/raw_data_view.h"
#include "views/co2_view.h"
#include "views/heatindex_view.h"
#include "views/buzzer_mute_view.h"

namespace view
{
    class ViewService
    {
        data::RawDataView dataView;
        co2::Co2View co2View;
        heatindex::HeatIndexView heatIndexView;
        buzzer::BuzzerMuteView buzzerMuteView;

        AbstractView *activeView;

    public:
        ViewService()
        {
            dataView.setNextView(&co2View);
            co2View.setNextView(&heatIndexView);
            heatIndexView.setNextView(&buzzerMuteView);
            buzzerMuteView.setNextView(&dataView);

            this->activeView = &dataView;
        }

        void switchToNextView()
        {
            activeView = activeView->getNextView();
        }

        void render()
        {
            activeView->render();
        }

        void switchToBuzzerMuteView()
        {
            activeView = &buzzerMuteView;
        }
    };

    ViewService viewService;
}
