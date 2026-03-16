#include "states/goods_state.h"

GoodsState* GoodsState::_instance;

void GoodsState::Begin()
{
    _ui_time = ui_comp_get_child(ui_header_0, UI_COMP_HEADER_TIME_LBL);
    _ui_battery = ui_comp_get_child(ui_header_0, UI_COMP_HEADER_BATTERY_IMG);

    _current_good = _goods.GetBeginIterator();

    Draw();
}

void GoodsState::Update(const uint32_t delay_ms)
{
    _clock.Update(_ui_time, delay_ms);
    _battery.Update(_ui_battery, delay_ms);
}

void GoodsState::Draw()
{
    if (_current_good == _goods.GetEndIterator())
    {
        return;
    }

    // 名称
    _ui_label_set_property(ui_title_lbl_0, _UI_LABEL_PROPERTY_TEXT, _current_good->GetName().c_str());

    // 画像
    lv_image_set_src(ui_image0, _current_good->GetImagePath().c_str());

    // 単価
    char unit_price_str[5];
    snprintf(unit_price_str, sizeof(unit_price_str), "%4d", _current_good->GetUnitPrice());
    _ui_label_set_property(ui_unit_price_lbl_0, _UI_LABEL_PROPERTY_TEXT, unit_price_str);

    // 数量
    char number_str[3];
    snprintf(number_str, sizeof(number_str), "%2d", _current_good->GetSelectedNumber());
    _ui_label_set_property(ui_number_lbl_0, _UI_LABEL_PROPERTY_TEXT, number_str);

    // 合計数量
    char total_number_str[4];
    snprintf(total_number_str, sizeof(total_number_str), "%3d", _goods.GetSelectedTotalNumber());
    _ui_label_set_property(ui_total_number_lbl_0, _UI_LABEL_PROPERTY_TEXT, total_number_str);

    // 合計
    char total_price_str[6];
    snprintf(total_price_str, sizeof(total_price_str), "%5d", _goods.GetSelectedTotalPrice());
    _ui_label_set_property(ui_total_price_lbl_0, _UI_LABEL_PROPERTY_TEXT, total_price_str);
}

void GoodsState::Next()
{
    if (++_current_good >= _goods.GetEndIterator())
    {
        _current_good = _goods.GetBeginIterator();
    }

    Draw();
}

void GoodsState::Prev()
{
    if (_current_good-- <= _goods.GetBeginIterator())
    {
        _current_good = _goods.GetEndIterator() - 1;
    }

    Draw();
}

void GoodsState::Plus()
{
    _current_good->IncrementSelectedNumber();
    Draw();
}

void GoodsState::Minus()
{
    _current_good->DecrementSelectedNumber();
    Draw();
}

void GoodsState::Reset()
{
    _current_good->ResetSelectedNumber();
    Draw();
}

void GoodsState::ResetAll()
{
    _goods.ResetSelectedAll();
    Draw();
}

void GoodsState::OnQRCodeScan(std::string& result)
{
    std::vector<Good>::iterator iterator = _goods.FindByCode(result);

    if (iterator == _goods.GetEndIterator())
    {
        return;
    }

    _current_good = iterator;
    Plus();
}

void GoodsState::OnHMIEncoderIncrement()
{
    Next();
}

void GoodsState::OnHMIEncoderDecrement()
{
    Prev();
}

void GoodsState::OnHMIButtonSPressed()
{
    ResetAll();
}

void GoodsState::OnHMIButton1Pressed()
{
    Plus();
}

void GoodsState::OnHMIButton2Pressed()
{
    Minus();
}

void GoodsState::OnQRCodeButtonClicked()
{
    _instance->_state_selector->EnableQRCodeReader();
}

void GoodsState::OnGoodsNextButtonClicked()
{
    _instance->Next();
}

void GoodsState::OnGoodsPrevButtonClicked()
{
    _instance->Prev();
}

void GoodsState::OnPlusButtonClicked()
{
    _instance->Plus();
}

void GoodsState::OnMinusButtonClicked()
{
    _instance->Minus();
}

void GoodsState::OnResetButtonClicked()
{
    _instance->Reset();
}