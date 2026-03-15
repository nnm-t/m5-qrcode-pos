#include "states/amount_state.h"

AmountState* AmountState::_instance;

void AmountState::Begin()
{
    _ui_time = ui_comp_get_child(ui_header_1, UI_COMP_HEADER_TIME_LBL);
    _ui_battery = ui_comp_get_child(ui_header_1, UI_COMP_HEADER_BATTERY_IMG);

    GetAmountValue();

    // 金額入力 一覧表示
    _ui_label_set_property(ui_goods_list_title_lbl_1, _UI_LABEL_PROPERTY_TEXT, "");
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