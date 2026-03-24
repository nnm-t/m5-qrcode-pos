#pragma once

#include <vector>

#include <Arduino.h>
#include <ArduinoJson.h>

#include "goods/good.h"
#include "goods/goods.h"
#include "goods/amounts.h"

class JsonSerial
{
    HardwareSerial& _serial;
    Goods& _goods;
    Amounts& _amounts;

    void SendJson(JsonDocument& json_document);

public:
    JsonSerial(HardwareSerial& serial, Goods& goods, Amounts& amounts) : _serial(serial), _goods(goods), _amounts(amounts)
    {

    }

    void SendCurrentGood(std::vector<Good>::iterator& current_good);

    void SendTotalPrice();

    void SendPaymentComplete();
};