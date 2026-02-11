#pragma once

#include <string>
#include <functional>

#include <Arduino.h>
#include <M5Unified.h>
#include <M5ModuleQRCode.h>

#ifdef ARDUINO_M5STACK_CORES3
#define MODULE_QRCODE_PIN_TX                43
#define MODULE_QRCODE_PIN_RX                44
#elif ARDUINO_M5STACK_Core2
#define MODULE_QRCODE_PIN_TX                1
#define MODULE_QRCODE_PIN_RX                3
#elif ARDUINO_M5Stack_Core
#define MODULE_QRCODE_PIN_TX                1
#define MODULE_QRCODE_PIN_RX                3
#endif

class QR
{
    M5ModuleQRCode& _module;
    std::function<void(std::string&)> _scan_result_callback = nullptr;

public:
    QR(M5ModuleQRCode& module) : _module(module)
    {

    }

    void Begin(std::function<void(std::string&)> scan_result_callback, HardwareSerial* const serial = &Serial, const int pin_tx = MODULE_QRCODE_PIN_TX, const int pin_rx = MODULE_QRCODE_PIN_RX, const long baudrate = 115200);

    void Enable();

    void Update();
};