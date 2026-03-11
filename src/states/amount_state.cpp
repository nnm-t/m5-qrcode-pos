#include "states/amount_state.h"

AmountState* AmountState::_instance;

void AmountState::Begin()
{
    GetAmountValue();

    // 金額入力 一覧表示
}

void AmountState::Update(const uint32_t delay_ms)
{
    lv_obj_t* const ui_time_0 = ui_comp_get_child(ui_header_2, UI_COMP_HEADER_TIME_LBL);
    _clock.Update(ui_time_0, delay_ms);
}

void AmountState::GetAmountValue()
{
    _amount_value = lv_spinbox_get_value(ui_amount_price_spn_1);
}

void AmountState::OnHMIButton1Pressed()
{
    // PaymentState へ移動
}

void AmountState::OnHMIButton2Pressed()
{
    // GoodsState へ戻る
}

void AmountState::OnHMIEncoderIncrement()
{
    // 金額入力 Plus
    const int32_t step = lv_spinbox_get_step(ui_amount_price_spn_1);
    _amount_value = _amount_value + step > 9900 ? 9900 : _amount_value + step;
    lv_spinbox_set_value(ui_amount_price_spn_1, _amount_value);
}

void AmountState::OnHMIEncoderDecrement()
{
    // 金額入力 Minus
    const int32_t step = lv_spinbox_get_step(ui_amount_price_spn_1);
    _amount_value = _amount_value - step < -9900 ? -9900 : _amount_value - step;
    lv_spinbox_set_value(ui_amount_price_spn_1, _amount_value);
}

void AmountState::OnSpinBoxValueChanged()
{
    _instance->GetAmountValue();
}