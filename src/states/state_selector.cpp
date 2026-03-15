#include "states/state_selector.h"

StateSelector* StateSelector::_instance;

void StateSelector::Begin()
{
    _hmi.on_button_s_pressed = [&]{ OnHMIButtonSPressed(); };
    _hmi.on_button_1_pressed = [&]{ OnHMIButton1Pressed(); };
    _hmi.on_button_2_pressed = [&]{ OnHMIButton2Pressed(); };
    _hmi.on_encoder_increment = [&]{ OnHMIEncoderIncrement(); };
    _hmi.on_encoder_decrement = [&]{ OnHMIEncoderDecrement(); };

    _hmi.Begin();

    _qr.Begin([&](std::string& result){ OnQRCodeScan(result); });

    _current_state = goods_state;

    if (_current_state == nullptr)
    {
        return;
    }

    _current_state->Begin();
}

void StateSelector::Update(const uint32_t delay_ms)
{
    if (_current_state == nullptr)
    {
        return;
    }

    _hmi.Update();
    _qr.Update();

    _current_state->Update(delay_ms);
}

void StateSelector::EnableQRCodeReader()
{
    _qr.Enable();
}

void StateSelector::OnQRCodeScan(std::string& result)
{
    if (_current_state == nullptr)
    {
        return;
    }

    if (_current_state != goods_state)
    {
        return;
    }

    goods_state->OnQRCodeScan(result);
}

void StateSelector::OnHMIButtonSPressed()
{
    if (_current_state == nullptr)
    {
        return;
    }

    _current_state->OnHMIButtonSPressed();
}

void StateSelector::OnHMIButton1Pressed()
{
    if (_current_state == nullptr)
    {
        return;
    }

    _current_state->OnHMIButton1Pressed();
}

void StateSelector::OnHMIButton2Pressed()
{
    if (_current_state == nullptr)
    {
        return;
    }

    _current_state->OnHMIButton2Pressed();
}

void StateSelector::OnHMIEncoderIncrement()
{
    if (_current_state == nullptr)
    {
        return;
    }

    _current_state->OnHMIEncoderIncrement();
}

void StateSelector::OnHMIEncoderDecrement()
{
    if (_current_state == nullptr)
    {
        return;
    }

    _current_state->OnHMIEncoderDecrement();
}

void StateSelector::BackToGoodsState()
{
    ToGoodsState();
}

void StateSelector::GoToPaymentState()
{
    ToPaymentState();
}

void StateSelector::ToGoodsState()
{
    _instance->_current_state = _instance->goods_state;

    if (_instance->_current_state == nullptr)
    {
        return;
    }

    _instance->_current_state->Begin();
}

void StateSelector::ToAmountState()
{
    _instance->_current_state = _instance->amount_state;

    if (_instance->_current_state == nullptr)
    {
        return;
    }

    _instance->_current_state->Begin();
}

void StateSelector::ToPaymentState()
{
    _instance->_current_state = _instance->payment_state;

    if (_instance->_current_state == nullptr)
    {
        return;
    }

    _instance->_current_state->Begin();
}

void StateSelector::ToSettingsState()
{
    _instance->_current_state = _instance->settings_state;

    if (_instance->_current_state == nullptr)
    {
        return;
    }

    _instance->_current_state->Begin();
}

void StateSelector::ToSalesState()
{
    _instance->_current_state = _instance->sales_state;

    if (_instance->_current_state == nullptr)
    {
        return;
    }

    _instance->_current_state->Begin();
}