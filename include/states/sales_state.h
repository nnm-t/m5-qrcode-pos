#pragma once

#include <Arduino.h>
#include <lvgl.h>

#include "ui/ui_sales_state.h"

#include "i_state.h"
#include "i_state_selector.h"
#include "goods_state.h"
#include "amount_state.h"
#include "util/clock.h"
#include "util/battery.h"

class SalesState : public IState
{
    IStateSelector* const _state_selector;
    GoodsState& _goods_state;
    AmountState& _amount_state;

    Clock& _clock;
    Battery& _battery;

	lv_obj_t* _ui_time = nullptr;
	lv_obj_t* _ui_battery = nullptr;

public:
    SalesState(IStateSelector* const state_selector, GoodsState& goods_state, AmountState& amount_state, Clock& clock, Battery& battery) : _state_selector(state_selector), _goods_state(goods_state), _amount_state(amount_state), _clock(clock), _battery(battery)
    {

    }

    void Begin() override;

    void Update(const uint32_t delay_ms) override;

    void OnHMIButton2Pressed() override;
};