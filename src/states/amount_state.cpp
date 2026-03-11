#include "states/amount_state.h"

AmountState* AmountState::_instance;

void AmountState::Begin()
{
    // 金額入力 一覧表示
}

void AmountState::Update(const uint32_t delay_ms)
{
    lv_obj_t* const ui_time_0 = ui_comp_get_child(ui_header_2, UI_COMP_HEADER_TIME_LBL);
    _clock.Update(ui_time_0, delay_ms);
}

void AmountState::OnHMIButtonSPressed()
{
    // SpinBox 桁変更
}

void AmountState::OnHMIButton1Pressed()
{
    //  PaymentState へ移動
}

void AmountState::OnHMIButton2Pressed()
{
    // GoodsState へ戻る
}

void AmountState::OnHMIEncoderIncrement()
{
    // 金額入力 Plus
}

void AmountState::OnHMIEncoderDecrement()
{
    // 金額入力 Minus
}

void AmountState::OnSpinBoxValueChanged()
{

}