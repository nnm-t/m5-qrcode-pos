#include "states/goods_state.h"

GoodsState* GoodsState::_instance;

void GoodsState::Begin()
{
    _ui_time = ui_comp_get_child(ui_header_0, UI_COMP_HEADER_TIME_LBL);
    _ui_battery = ui_comp_get_child(ui_header_0, UI_COMP_HEADER_BATTERY_IMG);

    Draw();
}

void GoodsState::Update(const uint32_t delay_ms)
{
    _clock.Update(_ui_time, delay_ms);
    _battery.Update(_ui_battery, delay_ms);
}

void GoodsState::Draw()
{
    if (_current_good == _goods.end())
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
    snprintf(number_str, sizeof(number_str), "%2d", _current_good->GetNumber());
    _ui_label_set_property(ui_number_lbl_0, _UI_LABEL_PROPERTY_TEXT, number_str);

    int32_t total_number = 0;
    int32_t total_price = 0;

    for (Good& good : _goods)
    {
        total_number += good.GetNumber();
        total_price += good.GetAmountPrice();
    }

    // 合計数量
    char total_number_str[4];
    snprintf(total_number_str, sizeof(total_number_str), "%3d", total_number);
    _ui_label_set_property(ui_total_number_lbl_0, _UI_LABEL_PROPERTY_TEXT, total_number_str);

    // 合計
    char total_price_str[6];
    snprintf(total_price_str, sizeof(total_price_str), "%5d", total_price);
    _ui_label_set_property(ui_total_price_lbl_0, _UI_LABEL_PROPERTY_TEXT, total_price_str);
}

void GoodsState::Next()
{
    if (++_current_good >= _goods.end())
    {
        _current_good = _goods.begin();
    }

    Draw();
}

void GoodsState::Prev()
{
    if (_current_good-- <= _goods.begin())
    {
        _current_good = _goods.end() - 1;
    }

    Draw();
}

void GoodsState::Plus()
{
    _current_good->IncrementNumber();
    Draw();
}

void GoodsState::Minus()
{
    _current_good->DecrementNumber();
    Draw();
}

void GoodsState::Reset()
{
    _current_good->ResetNumber();

    Draw();
}

void GoodsState::ResetAll()
{
    for (Good& good : _goods)
    {
        good.ResetNumber();
    }

    Draw();
}

const int32_t GoodsState::GetSumPrice()
{
    int32_t sum_price = 0;

    for (Good& good : _goods)
    {
        sum_price += good.GetAmountPrice();
    }

    return sum_price;
}

const std::string GoodsState::GetGoodsNames()
{
    std::string str;

    for (size_t i = 0; i < _goods.size(); i++)
    {
        if (_goods[i].GetNumber() == 0)
        {
            continue;
        }

        str += _goods[i].GetName();

        if (i < _goods.size() - 1)
        {
            str += "\n";
        }
    }

    return str;
}

const std::string GoodsState::GetGoodsNumbers()
{
    std::string str;

    for (size_t i = 0; i < _goods.size(); i++)
    {
        const int32_t number = _goods[i].GetNumber();
        if (number == 0)
        {
            continue;
        }

        char num[5];
        snprintf(num, sizeof(num), "x%1d", number);
        str += num;

        if (i < _goods.size() - 1)
        {
            str += "\n";
        }
    }

    return str;
}

const std::string GoodsState::GetGoodsPrices()
{
    std::string str;

    for (size_t i = 0; i < _goods.size(); i++)
    {
        if (_goods[i].GetNumber() == 0)
        {
            continue;
        }

        char price[8];
        snprintf(price, sizeof(price), "%d円", _goods[i].GetAmountPrice());
        str += price;

        if (i < _goods.size() - 1)
        {
            str += "\n";
        }
    }

    return str;
}

void GoodsState::OnQRCodeScan(std::string& result)
{
    std::unordered_map<std::string, size_t>::iterator iterator = _goods_hash.find(result);

    if (iterator == _goods_hash.end())
    {
        return;
    }

    _current_good = _goods.begin() + iterator->second;

    Plus();
}

void GoodsState::Deserialize(JsonArray& json_goods)
{
    _goods.clear();
    _goods.reserve(json_goods.size());

    for (size_t i = 0; i < json_goods.size(); i++)
    {
        JsonObject obj = json_goods[i].as<JsonObject>();

        _goods.push_back(Good(obj));
        _goods_hash[_goods[i].GetCode()] = i;
    }

    _current_good = _goods.begin();
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