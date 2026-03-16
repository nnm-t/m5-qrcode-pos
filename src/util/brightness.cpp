#include "util/brightness.h"

void Brightness::Begin()
{
    M5.Lcd.setBrightness(_value);
}

const uint8_t Brightness::GetValue()
{
    return _value;
}

void Brightness::SetValue(const uint8_t value)
{
    _value = value;
    M5.Lcd.setBrightness(value);
}