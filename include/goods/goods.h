#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <Arduino.h>
#include <ArduinoJson.h>

#include "good.h"

class Goods
{
	std::vector<Good> _goods = std::vector<Good>();
	std::unordered_map<std::string, size_t> _goods_hash = std::unordered_map<std::string, size_t>();

public:
    Goods()
    {

    }

    std::vector<Good>::iterator GetBeginIterator();

    std::vector<Good>::iterator GetEndIterator();

    const int32_t GetTotalNumber();

    const int32_t GetTotalPrice();

    void ResetAll();

    std::string GetNamesList();

    std::string GetNumbersList();

    std::string GetPricesList();

    std::vector<Good>::iterator FindByCode(std::string& code);

    void DeserializeGoods(JsonDocument& json_goods);

    void DeserializeSales(JsonDocument& json_sales);
};