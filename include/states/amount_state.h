#pragma once

#include <Arduino.h>
#include <lvgl.h>

#include "ui/ui_amount_state.h"

#include "i_state.h"
#include "i_state_selector.h"
#include "clock.h"

class AmountState : public IState
{
    static AmountState* _instance;

    IStateSelector* const _state_selector;
    Clock& _clock;

public:
    AmountState(IStateSelector* const state_selector, Clock& clock) : _state_selector(state_selector), _clock(clock)
    {
        _instance = this;
    }

    void Begin() override;

    void Update(const uint32_t delay_ms) override;

    void OnHMIButtonSPressed() override;

    void OnHMIButton1Pressed() override;

    void OnHMIButton2Pressed() override;

    void OnHMIEncoderIncrement() override;

    void OnHMIEncoderDecrement() override;

    static void OnSpinBoxValueChanged();
};