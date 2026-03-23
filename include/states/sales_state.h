#pragma once

#include <Arduino.h>
#include <lvgl.h>

#include "ui/ui.h"
#include "ui/ui_helpers.h"
#include "ui/ui_sales_state.h"

#include "i_state.h"
#include "i_state_selector.h"
#include "goods/goods.h"
#include "goods/amounts.h"
#include "util/clock.h"
#include "util/battery.h"

class SalesState : public IState
{
    IStateSelector* const _state_selector;
    Goods& _goods;
    Amounts& _amounts;

    Clock& _clock;
    Battery& _battery;

	lv_obj_t* _ui_time = nullptr;
	lv_obj_t* _ui_battery = nullptr;

public:
    SalesState(IStateSelector* const state_selector, Goods& goods, Amounts& amounts, Clock& clock, Battery& battery) : _state_selector(state_selector), _goods(goods), _amounts(amounts), _clock(clock), _battery(battery)
    {

    }

    void Begin() override;

    void Update(const uint32_t delay_ms) override;

    void OnHMIButton2Pressed() override;
};