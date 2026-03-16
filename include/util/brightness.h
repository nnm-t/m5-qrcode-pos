#pragma once

#include <Arduino.h>
#include <M5Unified.h>

class Brightness
{
    static constexpr const uint8_t default_value = 63;

    uint8_t _value = default_value;

public:
    Brightness()
    {

    }

    void Begin();

    const uint8_t GetValue();

    void SetValue(const uint8_t value);
};