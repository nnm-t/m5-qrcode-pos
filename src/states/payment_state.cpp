#include "states/payment_state.h"

PaymentState* PaymentState::_instance;

void PaymentState::Begin()
{
    _ui_time = ui_comp_get_child(ui_header_2, UI_COMP_HEADER_TIME_LBL);
    _ui_battery = ui_comp_get_child(ui_header_2, UI_COMP_HEADER_BATTERY_IMG);

    // 合計価格
    char sum_price[7];
    snprintf(sum_price, sizeof(sum_price), "%d", _goods.GetSelectedTotalPrice() + _amounts.GetCurrentValue());
    _ui_label_set_property(ui_sum_price_lbl_2, _UI_LABEL_PROPERTY_TEXT, sum_price);

    // タイトル
    _ui_label_set_property(ui_goods_list_title_lbl_2, _UI_LABEL_PROPERTY_TEXT, _goods.GetSelectedNamesList().c_str());
    // 数量
    _ui_label_set_property(ui_goods_list_number_lbl_2, _UI_LABEL_PROPERTY_TEXT, _goods.GetSelectedNumbersList().c_str());
    // 品目別価格
    _ui_label_set_property(ui_goods_list_price_lbl_2, _UI_LABEL_PROPERTY_TEXT, _goods.GetSelectedPricesList().c_str());
}

void PaymentState::Update(const uint32_t delay_ms)
{
    _clock.Update(_ui_time, delay_ms);
    _battery.Update(_ui_battery, delay_ms);
}

void PaymentState::Okay()
{
    // 購入
    // 文字列生成
    char amount_str[7];
    snprintf(amount_str, sizeof(amount_str), ",%d", _amounts.GetCurrentValue());
    // 金額入力 確定
    _amounts.RegisterCurrentValue();
    // 登録済み商品 確定
    std::string csv_line_str = _goods.RegisterSelectedToSold() + amount_str;

    // sales.json 反映
    _json_io.Write();

    // CSV 書き出し
    _csv_io.Write(csv_line_str);

    // Beep
    M5.Speaker.tone(2000, 50);

    // 選択解除
    _goods.ResetSelectedAll();
    // GoodsState へ戻る
    _state_selector->BackToGoodsState();
}

void PaymentState::OkayFree()
{
    // 合計金額分の値を金額入力でマイナス
    _amounts.RegisterValue(_goods.GetSelectedTotalPrice() * -1);

    // 購入
    Okay();
}

void PaymentState::OnHMIButton1Pressed()
{
    // Okay
    Okay();
    // GoodsStateに戻る
    _state_selector->BackToGoodsState();
    _ui_screen_change(&ui_goods_state, LV_SCR_LOAD_ANIM_OUT_RIGHT, 500, 0, &ui_goods_state_screen_init);
}

void PaymentState::OnHMIButton2Pressed()
{
    // 何もせずGoodsStateに戻る
    _state_selector->BackToGoodsState();
    _ui_screen_change(&ui_goods_state, LV_SCR_LOAD_ANIM_OUT_RIGHT, 500, 0, &ui_goods_state_screen_init);
}

void PaymentState::OnOkayButtonClicked()
{
    _instance->Okay();
}

void PaymentState::OnFreeButtonClicked()
{
    _instance->OkayFree();
}