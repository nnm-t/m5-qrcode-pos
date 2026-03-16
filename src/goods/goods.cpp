#include "goods/goods.h"

std::vector<Good>::iterator Goods::GetBeginIterator()
{
    return _goods.begin();
}

std::vector<Good>::iterator Goods::GetEndIterator()
{
    return _goods.end();
}

const int32_t Goods::GetTotalNumber()
{
    int32_t number = 0;

    for (Good& good : _goods)
    {
        number += good.GetNumber();
    }

    return number;
}

const int32_t Goods::GetTotalPrice()
{
    int32_t total_price = 0;

    for (Good& good : _goods)
    {
        total_price += good.GetAmountPrice();
    }

    return total_price;
}

void Goods::ResetAll()
{
    for (Good& good : _goods)
    {
        good.ResetNumber();
    }
}

std::string Goods::GetNamesList()
{
    std::string str;
    bool is_first = true;

    for (Good& good : _goods)
    {
        if (good.GetNumber() == 0)
        {
            continue;
        }

        if (!is_first)
        {
            str += "\n";
        }

        str += good.GetName();
        is_first = false;
    };

    return str;
}

std::string Goods::GetNumbersList()
{
    std::string str;
    bool is_first = true;

    for (Good& good : _goods)
    {
        const int32_t number = good.GetNumber();
        if (number == 0)
        {
            continue;
        }

        if (!is_first)
        {
            str += "\n";
        }

        char num[6];
        snprintf(num, sizeof(num), "x%1d", number);
        str += num;

        is_first = false;
    };

    return str;
}

std::string Goods::GetPricesList()
{
    std::string str;
    bool is_first = true;

    for (Good& good : _goods)
    {
        if (good.GetNumber() == 0)
        {
            continue;
        }

        if (!is_first)
        {
            str += "\n";
        }

        char price[11];
        snprintf(price, sizeof(price), "%d円", good.GetAmountPrice());
        str += price;

        is_first = false;
    };

    return str;
}

std::vector<Good>::iterator Goods::FindByCode(std::string& code)
{
    std::unordered_map<std::string, size_t>::iterator iterator = _goods_hash.find(code);

    if (iterator == _goods_hash.end())
    {
        return _goods.end();
    }

    return _goods.begin() + iterator->second;
}

void Goods::DeserializeGoods(JsonDocument& json_goods)
{
    JsonArray json_array = json_goods["goods"].as<JsonArray>();

    _goods.clear();
    _goods.reserve(json_array.size());

    for (size_t i = 0; i < json_array.size(); i++)
    {
        JsonObject obj = json_array[i].as<JsonObject>();

        _goods.push_back(Good(obj));
        _goods_hash[_goods[i].GetCode()] = i;
    }
}

void Goods::DeserializeSales(JsonDocument& json_sales)
{
    JsonArray json_array = json_sales["goods"].as<JsonArray>();
}