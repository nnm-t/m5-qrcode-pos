#include "states/state_selector.h"

void StateSelector::Begin()
{
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