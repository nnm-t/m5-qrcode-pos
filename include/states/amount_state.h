#pragma once

#include <unordered_map>

#include <Arduino.h>
#include <lvgl.h>
#include <ArduinoJson.h>

#include "ui/ui_amount_state.h"

#include "i_state.h"
#include "i_state_selector.h"
#include "clock.h"

class AmountState : public IState
{
    static AmountState* _instance;

    IStateSelector* const _state_selector;
    Clock& _clock;

    std::unordered_map<std::string, int32_t> _amount_values = std::unordered_map<std::string, int32_t>();
    int32_t _amount_value = 0;

    void AddAmountValue();

    void GetAmountValue();

public:
    AmountState(IStateSelector* const state_selector, Clock& clock) : _state_selector(state_selector), _clock(clock)
    {
        _instance = this;
    }

    void Begin() override;

    void Update(const uint32_t delay_ms) override;

    void Deserialize(JsonObject& json_object);

    void OnHMIButton1Pressed() override;

    void OnHMIButton2Pressed() override;

    void OnHMIEncoderIncrement() override;

    void OnHMIEncoderDecrement() override;

    static void OnSpinBoxValueChanged();

    static void OnPaymentButtonClicked();
};