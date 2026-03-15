#include "states/sales_state.h"

void SalesState::Begin()
{
    _ui_time = ui_comp_get_child(ui_header_4, UI_COMP_HEADER_TIME_LBL);
    _ui_battery = ui_comp_get_child(ui_header_4, UI_COMP_HEADER_BATTERY_IMG);

    // 売上

    // 金額入力

    // 一覧表示
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