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

void AmountState::DrawList()
{
    // 金額入力 一覧表示
    _ui_label_set_property(ui_goods_list_title_lbl_1, _UI_LABEL_PROPERTY_TEXT, _amounts.GetAmountsList().c_str());
    _ui_label_set_property(ui_goods_list_number_lbl_1, _UI_LABEL_PROPERTY_TEXT, _amounts.GetNumbersList().c_str());
    _ui_label_set_property(ui_goods_list_price_lbl_1, _UI_LABEL_PROPERTY_TEXT, _amounts.GetSubtotalsList().c_str());
}

void AmountState::AddAmountValue()
{
    _amounts.RegisterCurrentValue();
}

void AmountState::GetAmountValue()
{
    const int32_t value = lv_spinbox_get_value(ui_amount_price_spn_1);
    _amounts.SetCurrentValue(value);
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
