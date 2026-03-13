#pragma once

#include <Arduino.h>

class IStateSelector
{
public:
    virtual void Begin() = 0;

    virtual void Update(const uint32_t delay_ms) = 0;

    virtual void EnableQRCodeReader() = 0;

    virtual void BackToGoodsState() = 0;

    virtual void GoToPaymentState() = 0;
};