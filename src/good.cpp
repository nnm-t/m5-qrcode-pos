#include "good.h"

const std::string& Good::GetName() const
{
    return _name;
}

const std::string& Good::GetCode() const
{
    return _code;
}

const uint32_t Good::GetUnitPrice() const
{
    return _unit_price;
}

const int32_t Good::GetNumber()
{
    return _number;
}

const int32_t Good::GetAmountPrice()
{
    return _unit_price * _number;
}

void Good::IncrementNumber()
{
    if (_number++ >= 99)
    {
        return;
    }
}

void Good::DecrementNumber()
{
    if (_number-- <= -99)
    {
        return;
    }
}

void Good::ResetNumber()
{
    _number = 0;
}