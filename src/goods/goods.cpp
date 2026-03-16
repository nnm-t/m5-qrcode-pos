#include "goods/goods.h"

std::vector<Good>::iterator Goods::GetBeginIterator()
{
    return _goods.begin();
}

std::vector<Good>::iterator Goods::GetEndIterator()
{
    return _goods.end();
}

const int32_t Goods::GetSelectedTotalNumber()
{
    int32_t number = 0;

    for (Good& good : _goods)
    {
        number += good.GetSelectedNumber();
    }

    return number;
}

const int32_t Goods::GetSelectedTotalPrice()
{
    int32_t total_price = 0;

    for (Good& good : _goods)
    {
        total_price += good.GetSelectedAmountPrice();
    }

    return total_price;
}

const int32_t Goods::GetSoldTotalPrice()
{
    int32_t total_price = 0;

    for (Good& good : _goods)
    {
        total_price += good.GetSoldAmountPrice();
    }

    return total_price;
}

void Goods::ResetAll()
{
    for (Good& good : _goods)
    {
        good.ResetSelectedNumber();
    }
}

std::string Goods::RegisterSelectedToSold()
{
    std::string csv_line_str;
    bool is_first = true;

    for (Good& good : _goods)
    {
        // CSV用文字列生成
        char sales_str[5];
        const char* format_str = is_first ? "%d" : ",%d";
        snprintf(sales_str, sizeof(sales_str), format_str, good.GetSelectedNumber());

        // 売上反映
        good.RegisterSelectedToSold();

        is_first = false;
    }

    csv_line_str += "\n";
    return csv_line_str;
}

std::string Goods::GetSelectedNamesList()
{
    std::string str;
    bool is_first = true;

    for (Good& good : _goods)
    {
        if (good.GetSelectedNumber() == 0)
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

std::string Goods::GetSelectedNumbersList()
{
    std::string str;
    bool is_first = true;

    for (Good& good : _goods)
    {
        const int32_t number = good.GetSelectedNumber();
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

std::string Goods::GetSelectedPricesList()
{
    std::string str;
    bool is_first = true;

    for (Good& good : _goods)
    {
        if (good.GetSelectedNumber() == 0)
        {
            continue;
        }

        if (!is_first)
        {
            str += "\n";
        }

        char price[11];
        snprintf(price, sizeof(price), "%d円", good.GetSelectedAmountPrice());
        str += price;

        is_first = false;
    };

    return str;
}

std::string Goods::GetSoldNamesList()
{
    std::string str;
    bool is_first = true;

    for (Good& good : _goods)
    {
        if (good.GetSoldNumber() == 0)
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

std::string Goods::GetSoldNumbersList()
{
    std::string str;
    bool is_first = true;

    for (Good& good : _goods)
    {
        const int32_t number = good.GetSoldNumber();
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

std::string Goods::GetSoldPricesList()
{
    std::string str;
    bool is_first = true;

    for (Good& good : _goods)
    {
        if (good.GetSoldNumber() == 0)
        {
            continue;
        }

        if (!is_first)
        {
            str += "\n";
        }

        char price[11];
        snprintf(price, sizeof(price), "%d円", good.GetSoldAmountPrice());
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

    if (_goods.size() != json_array.size())
    {
        return;
    }

    for (size_t i = 0; i < json_array.size(); i++)
    {
        const int32_t number = json_array[i].as<int32_t>();
        _goods[i].SetSoldNumber(number);
    }
}

void Goods::SerializeSales(JsonDocument& json_sales)
{
    JsonArray json_array = json_sales["goods"].as<JsonArray>();

    for (Good& good : _goods)
    {
        json_array.add(good.GetSoldNumber());
    }
}