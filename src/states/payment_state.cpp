#include "states/payment_state.h"

PaymentState* PaymentState::_instance;

void PaymentState::Begin()
{
    _ui_time = ui_comp_get_child(ui_header_2, UI_COMP_HEADER_TIME_LBL);
    _ui_battery = ui_comp_get_child(ui_header_2, UI_COMP_HEADER_BATTERY_IMG);

    // 合計価格
    char sum_price[6];
    snprintf(sum_price, sizeof(sum_price), "%d", _goods.GetTotalPrice());
    _ui_label_set_property(ui_sum_price_lbl_2, _UI_LABEL_PROPERTY_TEXT, sum_price);

    // タイトル
    _ui_label_set_property(ui_goods_list_title_lbl_2, _UI_LABEL_PROPERTY_TEXT, _goods.GetNamesList().c_str());
    // 数量
    _ui_label_set_property(ui_goods_list_number_lbl_2, _UI_LABEL_PROPERTY_TEXT, _goods.GetNumbersList().c_str());
    // 品目別価格
    _ui_label_set_property(ui_goods_list_price_lbl_2, _UI_LABEL_PROPERTY_TEXT, _goods.GetPricesList().c_str());
}

void PaymentState::Update(const uint32_t delay_ms)
{
    _clock.Update(_ui_time, delay_ms);
    _battery.Update(_ui_battery, delay_ms);
}

void PaymentState::Okay()
{
    // 購入

    // sales.json 反映

    // CSV 追記

    // GoodsState へ戻る
    _state_selector->BackToGoodsState();
}

void PaymentState::OkayFree()
{
    // 合計金額分の値を金額入力でマイナス
    _amounts.RegisterValue(_goods.GetTotalPrice() * -1);

    // 購入
    Okay();
}

void PaymentState::OnHMIButton1Pressed()
{
    // Okay
    Okay();
}

void PaymentState::OnHMIButton2Pressed()
{
    // 何もせずGoodsStateに戻る
    _state_selector->BackToGoodsState();
}

void PaymentState::OnOkayButtonClicked()
{
    _instance->Okay();
}

void PaymentState::OnFreeButtonClicked()
{
    _instance->OkayFree();
}