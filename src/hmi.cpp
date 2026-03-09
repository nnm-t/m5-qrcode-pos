#include "hmi.h"

void HMI::Begin(TwoWire* wire, const uint8_t sda, const uint8_t scl, const uint32_t speed)
{
    _module.begin(wire, HMI_ADDR, sda, scl, speed);

    _module.resetCounter();
}

void HMI::Update()
{
    const bool is_button_s_press = _module.getButtonS();
    const bool is_button_1_press = _module.getButton1();
    const bool is_button_2_press = _module.getButton2();

    if (!_is_button_s_pressed && is_button_s_press)
    {
        // Button S Pressed
        if (on_button_s_pressed != nullptr)
        {
            on_button_s_pressed();
        }
    }
    else if (_is_button_s_pressed && !is_button_s_press)
    {
        // Button S Released
        if (on_button_s_released != nullptr)
        {
            on_button_s_released();
        }
    }

    if (!_is_button_1_pressed && is_button_1_press)
    {
        // Button 1 Pressed
        if (on_button_1_pressed != nullptr)
        {
            on_button_1_pressed();
        }
    }
    else if (_is_button_1_pressed && !is_button_1_press)
    {
        // Button 1 Released
        if (on_button_1_released != nullptr)
        {
            on_button_1_released();
        }
    }

    if (!_is_button_2_pressed && is_button_2_press)
    {
        // Button 2 Pressed
        if (on_button_2_pressed != nullptr)
        {
            on_button_2_pressed();
        }
    }
    else if (_is_button_2_pressed && !is_button_2_press)
    {
        // Button 2 Released
        if (on_button_2_released != nullptr)
        {
            on_button_2_released();
        }
    }

    _is_button_s_pressed = is_button_s_press;
    _is_button_1_pressed = is_button_1_press;
    _is_button_2_pressed = is_button_2_press;

    const int32_t encoder_value = _module.getEncoderValue();

    if (encoder_value > _encoder_value)
    {
        // Encoder increment
        if (on_encoder_increment != nullptr)
        {
            on_encoder_increment();
        }
    }
    else if (encoder_value < _encoder_value)
    {
        // Encoder decrement
        if (on_encoder_decrement != nullptr)
        {
            on_encoder_decrement();
        }
    }

    _encoder_value = encoder_value;
}

void HMI::SetLEDOn(const HMILED led)
{
    _module.setLEDStatus(static_cast<uint8_t>(led), led_status_on);
}

void HMI::SetLEDOff(const HMILED led)
{
    _module.setLEDStatus(static_cast<uint8_t>(led), led_status_off);
}