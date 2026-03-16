#include "goods/amounts.h"

void Amounts::Deserialize(JsonDocument& json_sales)
{
    JsonObject json_amounts = json_sales["amounts"].as<JsonObject>();

    for (JsonPair key_value_pair : json_amounts)
    {
        const std::string key(key_value_pair.key().c_str());
        const int32_t value = key_value_pair.value().as<int32_t>();

        _values[key] = value;
    }
}

void Amounts::RegisterValue(const int32_t value)
{
    // map へ反映
    std::string value_str;
    value_str.reserve(6);

    snprintf(value_str.data(), value_str.size(), "%d", value);

    if (_values.find(value_str) == _values.end())
    {
        // 0個: 要素追加
        _values[value_str] = 1;
    }
    else
    {
        // 1個: インクリメント
        _values[value_str]++;
    }
}

void Amounts::RegisterCurrentValue()
{
    RegisterValue(_current_value);
}

const int32_t Amounts::GetCurrentValue()
{
    return _current_value;
}

void Amounts::SetCurrentValue(const int32_t value)
{
    _current_value = value;
}

std::string Amounts::GetAmountsList()
{
    std::string amounts_str;

    std::for_each(_values.begin(), _values.end(),
    [&](std::map<std::string, int32_t>::value_type pair){
        if (pair != *_values.begin())
        {
            amounts_str += "\n";
        }

        amounts_str += pair.first + "円";
    });

    return amounts_str;
}

std::string Amounts::GetNumbersList()
{
    std::string numbers_str;

    std::for_each(_values.begin(), _values.end(),
    [&](std::map<std::string, int32_t>::value_type pair){
        if (pair != *_values.begin())
        {
            numbers_str += "\n";
        }

        char number_str[6];
        snprintf(number_str, sizeof(number_str), "x%d", pair.second);
        numbers_str += number_str;
    });

    return numbers_str;
}

std::string Amounts::GetSubtotalsList()
{
    std::string subtotals_str;

    std::for_each(_values.begin(), _values.end(),
    [&](std::map<std::string, int32_t>::value_type pair){
        if (pair != *_values.begin())
        {
            subtotals_str += "\n";
        }

        const int32_t subtotal = std::stoi(pair.first) + pair.second;
        char subtotal_str[13];
        snprintf(subtotal_str, sizeof(subtotal_str), "%d円", subtotal);
        subtotals_str += subtotal_str;
    });

    return subtotals_str;
}