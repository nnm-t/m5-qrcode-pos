#pragma once

#include <algorithm>
#include <string>
#include <unordered_map>

#include <Arduino.h>
#include <lvgl.h>
#include <ArduinoJson.h>

#include "ui/ui_amount_state.h"

#include "i_state.h"
#include "i_state_selector.h"
#include "util/clock.h"
#include "util/battery.h"

class AmountState : public IState
{
    static AmountState* _instance;

    IStateSelector* const _state_selector;
    Clock& _clock;
	Battery& _battery;

	lv_obj_t* _ui_time = nullptr;
	lv_obj_t* _ui_battery = nullptr;

    std::unordered_map<std::string, int32_t> _amount_values = std::unordered_map<std::string, int32_t>();
    int32_t _amount_value = 0;

    void DrawList();

    void AddAmountValue();

    void AddAmountValue(const int32_t value);

    void GetAmountValue();

public:
    AmountState(IStateSelector* const state_selector, Clock& clock, Battery& battery) : _state_selector(state_selector), _clock(clock), _battery(battery)
    {
        _instance = this;
    }

    void Begin() override;

    void Update(const uint32_t delay_ms) override;

    void Deserialize(JsonObject& json_object);

    void RegisterValue(const int32_t value);

    void OnHMIButtonSPressed() override;

    void OnHMIButton1Pressed() override;

    void OnHMIButton2Pressed() override;

    void OnHMIEncoderIncrement() override;

    void OnHMIEncoderDecrement() override;

    static void OnSpinBoxValueChanged();

    static void OnPaymentButtonClicked();
};