#pragma once

#include <functional>

#include <Arduino.h>
#include <M5ModuleHMI.h>

#ifdef ARDUINO_M5STACK_CORES3
#define MODULE_HMI_PIN_I2C1_SDA                     12
#define MODULE_HMI_PIN_I2C1_SCL                     11
#elif ARDUINO_M5STACK_Core2
#define MODULE_HMI_PIN_I2C1_SDA                     21
#define MODULE_HMI_PIN_I2C1_SCL                     22
#elif ARDUINO_M5Stack_Core
#define MODULE_HMI_PIN_I2C1_SDA                     21
#define MODULE_HMI_PIN_I2C1_SCL                     22
#endif

#define MODULE_HMI_I2C_SPEED                        100000

enum class HMILED : uint8_t
{
    LED0 = 0,
    LED1 = 1
};

class HMI
{
    static constexpr const uint8_t led_status_on = 1;
    static constexpr const uint8_t led_status_off = 0;

    M5ModuleHMI& _module;

    bool _is_found = false;
    int32_t _encoder_value = 0;
    bool _is_button_s_pressed = false;
    bool _is_button_1_pressed = false;
    bool _is_button_2_pressed = false;

public:
    std::function<void()> on_button_s_pressed = nullptr;
    std::function<void()> on_button_s_released = nullptr;
    std::function<void()> on_button_1_pressed = nullptr;
    std::function<void()> on_button_1_released = nullptr;
    std::function<void()> on_button_2_pressed = nullptr;
    std::function<void()> on_button_2_released = nullptr;

    std::function<void()> on_encoder_increment = nullptr;
    std::function<void()> on_encoder_decrement = nullptr;

    HMI(M5ModuleHMI& module) : _module(module)
    {

    }

    void Begin(TwoWire* wire = &Wire1, const uint8_t sda = MODULE_HMI_PIN_I2C1_SDA, const uint8_t scl = MODULE_HMI_PIN_I2C1_SCL, const uint32_t speed = MODULE_HMI_I2C_SPEED);

    void Update();

    void SetLEDOn(const HMILED led);

    void SetLEDOff(const HMILED led);
};