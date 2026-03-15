#include "states/amount_state.h"

AmountState* AmountState::_instance;

void AmountState::Begin()
{
    _ui_time = ui_comp_get_child(ui_header_1, UI_COMP_HEADER_TIME_LBL);
    _ui_battery = ui_comp_get_child(ui_header_1, UI_COMP_HEADER_BATTERY_IMG);

    GetAmountValue();
    DrawList();
}

void AmountState::Update(const uint32_t delay_ms)
{
    _clock.Update(_ui_time, delay_ms);
    _battery.Update(_ui_battery, delay_ms);
}

void AmountState::Deserialize(JsonObject& json_object)
{
    for (JsonPair key_value_pair : json_object)
    {
        const std::string key(key_value_pair.key().c_str());
        const int32_t value = key_value_pair.value().as<int32_t>();

        _amount_values[key] = value;
    }
}

void AmountState::RegisterValue(const int32_t value)
{
    AddAmountValue(value);
}

void AmountState::DrawList()
{
    std::string amounts_str;
    std::string numbers_str;
    std::string subtotals_str;

    std::for_each(_amount_values.begin(), _amount_values.end(),
    [&](std::unordered_map<std::string, int32_t>::value_type pair){
        if (pair != *_amount_values.begin())
        {
            amounts_str += "\n";
            numbers_str += "\n";
            subtotals_str += "\n";
        }

        amounts_str += pair.first + "円";

        char number_str[6];
        snprintf(number_str, sizeof(number_str), "x%d", pair.second);
        numbers_str += number_str;

        const int32_t subtotal = std::stoi(pair.first) + pair.second;
        char subtotal_str[13];
        snprintf(subtotal_str, sizeof(subtotal_str), "%d円", subtotal);
        subtotals_str += subtotal_str;
    });

    // 金額入力 一覧表示
    _ui_label_set_property(ui_goods_list_title_lbl_1, _UI_LABEL_PROPERTY_TEXT, amounts_str.c_str());
    _ui_label_set_property(ui_goods_list_number_lbl_1, _UI_LABEL_PROPERTY_TEXT, numbers_str.c_str());
    _ui_label_set_property(ui_goods_list_price_lbl_1, _UI_LABEL_PROPERTY_TEXT, subtotals_str.c_str());
}

void AmountState::AddAmountValue()
{
    AddAmountValue(_amount_value);
}

void AmountState::AddAmountValue(const int32_t value)
{
    // unorderd_map へ反映
    std::string value_str;
    value_str.reserve(6);

    snprintf(value_str.data(), value_str.size(), "%d", value);

    if (_amount_values.find(value_str) == _amount_values.end())
    {
        // 0個: 要素追加
        _amount_values[value_str] = 1;
    }
    else
    {
        // 1個: インクリメント
        _amount_values[value_str]++;
    }

    _amount_value = 0;
}

void AmountState::GetAmountValue()
{
    _amount_value = lv_spinbox_get_value(ui_amount_price_spn_1);
}

void AmountState::OnHMIButtonSPressed()
{

}

void AmountState::OnHMIButton1Pressed()
{
    AddAmountValue();
    // PaymentState へ移動
    _state_selector->GoToPaymentState();
}

void AmountState::OnHMIButton2Pressed()
{
    // GoodsState へ戻る
    _state_selector->BackToGoodsState();
}

void AmountState::OnHMIEncoderIncrement()
{
    // 金額入力 Plus
    lv_spinbox_increment(ui_amount_price_spn_1);
}

void AmountState::OnHMIEncoderDecrement()
{
    // 金額入力 Minus
    lv_spinbox_decrement(ui_amount_price_spn_1);
}

void AmountState::OnSpinBoxValueChanged()
{
    _instance->GetAmountValue();
}

void AmountState::OnPaymentButtonClicked()
{
    _instance->AddAmountValue();
}