#pragma once

#include <string>

#include <Arduino.h>
#include <SD.h>

#include "goods/goods.h"

class CsvIO
{
    static constexpr const char* file_name = "/sales.csv";

    Goods& _goods;

public:
    CsvIO(Goods& goods) : _goods(goods)
    {

    }

    void Write(std::string& csv_line);
};