#include "states/goods_state.h"

GoodsState* GoodsState::_instance;

void GoodsState::Begin()
{

}

void GoodsState::Update(const uint32_t delay_ms)
{
    lv_obj_t* const ui_time_0 = ui_comp_get_child(ui_header_0, UI_COMP_HEADER_TIME_LBL);
    _clock.Update(ui_time_0, delay_ms);
}

void GoodsState::OnQRCodeScan(std::string& result)
{

}

void GoodsState::OnQRCodeButtonClicked()
{
    _instance->_state_selector->EnableQRCodeReader();
}