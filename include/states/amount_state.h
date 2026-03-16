#pragma once

#include <algorithm>
#include <string>
#include <unordered_map>

#include <Arduino.h>
#include <lvgl.h>
#include <ArduinoJson.h>

#include "goods/amounts.h"

#include "ui/ui_amount_state.h"

#include "i_state.h"
#include "i_state_selector.h"
#include "util/clock.h"
#include "util/battery.h"

class AmountState : public IState
{
    static AmountState* _instance;

    IStateSelector* const _state_selector;
    Amounts& _amounts;
    Clock& _clock;
	Battery& _battery;

	lv_obj_t* _ui_time = nullptr;
	lv_obj_t* _ui_battery = nullptr;

    void DrawList();

    void GetAmountValue();

public:
    AmountState(IStateSelector* const state_selector, Amounts& amounts, Clock& clock, Battery& battery) : _state_selector(state_selector), _amounts(amounts), _clock(clock), _battery(battery)
    {
        _instance = this;
    }

    void Begin() override;

    void Update(const uint32_t delay_ms) override;

    void OnHMIButton1Pressed() override;

    void OnHMIButton2Pressed() override;

    void OnHMIEncoderIncrement() override;

    void OnHMIEncoderDecrement() override;

    static void OnSpinBoxValueChanged();
};