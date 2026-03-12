#include "states/payment_state.h"

PaymentState* PaymentState::_instance;

void PaymentState::Begin()
{
    // 合計価格
    char sum_price[6];
    snprintf(sum_price, sizeof(sum_price), "%d", _goods_state.GetSumPrice());
    _ui_label_set_property(ui_sum_price_lbl_2, _UI_LABEL_PROPERTY_TEXT, sum_price);

    // タイトル
    _ui_label_set_property(ui_goods_list_title_lbl_2, _UI_LABEL_PROPERTY_TEXT, _goods_state.GetGoodsNames().c_str());
    // 数量
    _ui_label_set_property(ui_goods_list_number_lbl_2, _UI_LABEL_PROPERTY_TEXT, _goods_state.GetGoodsNumbers().c_str());
    // 品目別価格
    _ui_label_set_property(ui_goods_list_price_lbl_2, _UI_LABEL_PROPERTY_TEXT, _goods_state.GetGoodsPrices().c_str());
}

void PaymentState::Update(const uint32_t delay_ms)
{
    lv_obj_t* const ui_time_0 = ui_comp_get_child(ui_header_2, UI_COMP_HEADER_TIME_LBL);
    _clock.Update(ui_time_0, delay_ms);
}

void PaymentState::Okay()
{
    // 購入
}

void PaymentState::OkayFree()
{
    // 合計金額分の値を金額入力でマイナスして購入
}

void PaymentState::OnHMIButton1Pressed()
{
    // Okay
    Okay();
}

void PaymentState::OnHMIButton2Pressed()
{
    // 何もせずGoodsStateに戻る
}

void PaymentState::OnOkayButtonClicked()
{
    _instance->Okay();
}

void PaymentState::OnFreeButtonClicked()
{
    _instance->OkayFree();
}