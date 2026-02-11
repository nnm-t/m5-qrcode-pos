#pragma once

#include <Arduino.h>
#include <SD.h>
#include <ArduinoJson.h>

#include "states/goods_state.h"

class JsonIO
{
    static constexpr const char* goods_file_name = "/goods.json";
    static constexpr const char* sales_file_name = "/sales.json";

    HardwareSerial* const _serial;
    GoodsState& _goods_state;

    void Open(JsonDocument& json_document, const char* file_name);

public:
    JsonIO(HardwareSerial* const serial, GoodsState& goods_state) : _serial(serial), _goods_state(goods_state)
    {

    }

    void Read();

    void Write();
};