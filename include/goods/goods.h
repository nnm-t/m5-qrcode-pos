#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <Arduino.h>
#include <M5Unified.h>
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

    const int32_t GetSelectedTotalNumber();

    const int32_t GetSelectedTotalPrice();

    const int32_t GetSoldTotalPrice();

    void ResetSelectedAll();

    std::string GetCommaSeparatedAllNames();

    std::string RegisterSelectedToSold();

    std::string GetSelectedNamesList();

    std::string GetSelectedNumbersList();

    std::string GetSelectedPricesList();

    std::string GetSoldNamesList();

    std::string GetSoldNumbersList();

    std::string GetSoldPricesList();

    std::vector<Good>::iterator FindByCode(std::string& code);

    void DeserializeGoods(JsonDocument& json_goods);

    void DeserializeSales(JsonDocument& json_sales);

    void SerializeSales(JsonDocument& json_sales);
};