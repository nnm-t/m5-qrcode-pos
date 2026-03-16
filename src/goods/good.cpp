#include "goods/good.h"

const std::string& Good::GetName() const
{
    return _name;
}

const std::string& Good::GetCode() const
{
    return _code;
}

const std::string& Good::GetImagePath() const
{
    return _image_path;
}

const uint32_t Good::GetUnitPrice() const
{
    return _unit_price;
}

const int32_t Good::GetSelectedNumber()
{
    return _selected_number;
}

const int32_t Good::GetSoldNumber()
{
    return _sold_number;
}

void Good::SetSoldNumber(const int32_t number)
{
    _sold_number = number;
}

void Good::AddSoldNumber(const int32_t number)
{
    _sold_number += number;
}

const int32_t Good::GetSelectedAmountPrice()
{
    return _unit_price * _selected_number;
}

const int32_t Good::GetSoldAmountPrice()
{
    return _unit_price * _sold_number;
}

void Good::RegisterSelectedToSold()
{
    _sold_number += _selected_number;
    _selected_number = 0;
}

void Good::IncrementSelectedNumber()
{
    if (_selected_number++ >= 99)
    {
        return;
    }
}

void Good::DecrementSelectedNumber()
{
    if (_selected_number-- <= -99)
    {
        return;
    }
}

void Good::ResetSelectedNumber()
{
    _selected_number = 0;
}