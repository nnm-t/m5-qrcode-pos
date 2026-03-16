#include "states/sales_state.h"

void SalesState::Begin()
{
    _ui_time = ui_comp_get_child(ui_header_4, UI_COMP_HEADER_TIME_LBL);
    _ui_battery = ui_comp_get_child(ui_header_4, UI_COMP_HEADER_BATTERY_IMG);

    // 売上
    char sum_price[8];
    snprintf(sum_price, sizeof(sum_price), "%d", _goods.GetSoldTotalPrice() + _amounts.GetTotalValue());
    _ui_label_set_property(ui_total_price_lbl_4, _UI_LABEL_PROPERTY_TEXT, sum_price);

    // 金額入力
    char amounts_price[8];
    snprintf(amounts_price, sizeof(amounts_price), "%d", _amounts.GetTotalValue());
    _ui_label_set_property(ui_amount_price_lbl_4, _UI_LABEL_PROPERTY_TEXT, amounts_price);

    // タイトル
    _ui_label_set_property(ui_goods_list_title_lbl_4, _UI_LABEL_PROPERTY_TEXT, _goods.GetSoldNamesList().c_str());
    // 数量
    _ui_label_set_property(ui_goods_list_number_lbl_4, _UI_LABEL_PROPERTY_TEXT, _goods.GetSoldNumbersList().c_str());
    // 品目別価格
    _ui_label_set_property(ui_goods_list_price_lbl_4, _UI_LABEL_PROPERTY_TEXT, _goods.GetSoldPricesList().c_str());
}

void SalesState::Update(const uint32_t delay_ms)
{
    _clock.Update(_ui_time, delay_ms);
    _battery.Update(_ui_battery, delay_ms);
}

void SalesState::OnHMIButton2Pressed()
{
    // 何もせずGoodsStateに戻る
    _state_selector->BackToGoodsState();
}