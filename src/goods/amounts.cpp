#include "goods/amounts.h"

void Amounts::Deserialize(JsonDocument& json_sales)
{
    JsonObject json_amounts = json_sales["amounts"].as<JsonObject>();

    for (JsonPair key_value_pair : json_amounts)
    {
        const int32_t key = std::stoi(key_value_pair.key().c_str());
        const int32_t value = key_value_pair.value().as<int32_t>();

        _values[key] = value;
    }
}

void Amounts::Serialize(JsonDocument& json_sales)
{
    JsonObject json_amounts = json_sales["amounts"].to<JsonObject>();

    std::for_each(_values.begin(), _values.end(),
    [&](std::map<int32_t, int32_t>::value_type pair){
        char key[6];
        snprintf(key, sizeof(key), "%d", pair.first);

        json_amounts[key] = pair.second;
    });
}

void Amounts::RegisterValue(const int32_t value)
{
    // 0円は登録しない
    if (value == 0)
    {
        return;
    }

    // map へ反映
    if (_values.find(value) == _values.end())
    {
        // 0個: 要素追加
        _values[value] = 1;
    }
    else
    {
        // 1個: インクリメント
        _values[value]++;
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

const int32_t Amounts::GetTotalValue()
{
    int32_t total_value = 0;

    std::for_each(_values.begin(), _values.end(),
    [&](std::map<int32_t, int32_t>::value_type pair){
        total_value += pair.first * pair.second;
    });

    return total_value;
}

std::string Amounts::GetAmountsList()
{
    std::string amounts_str;

    std::for_each(_values.begin(), _values.end(),
    [&](std::map<int32_t, int32_t>::value_type pair){
        if (pair != *_values.begin())
        {
            amounts_str += "\n";
        }

        char amount_str[8];
        snprintf(amount_str, sizeof(amount_str), "%d円", pair.first);
        amounts_str += amount_str;
    });

    return amounts_str;
}

std::string Amounts::GetNumbersList()
{
    std::string numbers_str;

    std::for_each(_values.begin(), _values.end(),
    [&](std::map<int32_t, int32_t>::value_type pair){
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
    [&](std::map<int32_t, int32_t>::value_type pair){
        if (pair != *_values.begin())
        {
            subtotals_str += "\n";
        }

        const int32_t subtotal = pair.first * pair.second;
        char subtotal_str[13];
        snprintf(subtotal_str, sizeof(subtotal_str), "%d円", subtotal);
        subtotals_str += subtotal_str;
    });

    return subtotals_str;
}