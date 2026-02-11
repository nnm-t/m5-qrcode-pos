#include "qr.h"

void QR::Begin(std::function<void(std::string&)> scan_result_callback, HardwareSerial* const serial, const int pin_tx, const int pin_rx, const long baudrate)
{
    _scan_result_callback = scan_result_callback;

    M5ModuleQRCode::Config_t config = _module.getConfig();
    config.pin_tx = pin_tx;
    config.pin_rx = pin_rx;
    config.baudrate = baudrate;
    config.serial = serial;
    _module.setConfig(config);

    while (!_module.begin())
    {
        delay(100);
    }

    _module.setFillLightMode(QRCodeM14::FILL_LIGHT_ON_DECODE);
    _module.setPosLightMode(QRCodeM14::POS_LIGHT_ON_DECODE);

    _module.setTriggerMode(QRCodeM14::TRIGGER_MODE_PULSE);
}

void QR::Enable()
{
    _module.setTriggerLevel(false);

    delay(20);

    _module.setTriggerLevel(true);
}

void QR::Update()
{
    _module.update();

    if (!_module.available())
    {
        return;
    }

    if (_scan_result_callback == nullptr)
    {
        return;
    }

    std::string result = _module.getScanResult();
    _scan_result_callback(result);
}