#pragma once

#include <algorithm>
#include <map>
#include <string>

#include <Arduino.h>
#include <ArduinoJson.h>

class Amounts
{
    std::map<int32_t, int32_t> _values = std::map<int32_t, int32_t>();
    int32_t _current_value = 0;

public:
    Amounts()
    {

    }

    void Deserialize(JsonDocument& json_sales);

    void Serialize(JsonDocument& json_sales);

    void RegisterValue(const int32_t value);

    void RegisterCurrentValue();

    const int32_t GetCurrentValue();

    void SetCurrentValue(const int32_t value);

    const int32_t GetTotalValue();

    std::string GetAmountsList();

    std::string GetNumbersList();

    std::string GetSubtotalsList();
};