#pragma once

#include <Arduino.h>
#include <SD.h>
#include <ArduinoJson.h>
#include <lvgl.h>

#include "ui/ui_helpers.h"
#include "ui/ui_goods_state.h"

#include "goods/goods.h"
#include "goods/amounts.h"

class JsonIO
{
    static constexpr const char* goods_file_name = "/goods.json";
    static constexpr const char* sales_file_name = "/sales.json";

    Goods& _goods;
    Amounts& _amounts;

    void Open(JsonDocument& json_document, const char* file_name);

public:
    JsonIO(Goods& goods, Amounts& amounts) : _goods(goods), _amounts(amounts)
    {

    }

    void Read();

    void Write();
};