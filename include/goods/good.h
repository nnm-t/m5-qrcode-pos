#pragma once

#include <string>

#include <Arduino.h>
#include <M5Unified.h>
#include <ArduinoJson.h>

class Good
{
    const std::string _name;
    const std::string _image_path;
    const std::string _code;
    const uint32_t _unit_price;

    int32_t _selected_number = 0;
    int32_t _sold_number = 0;

public:
    Good(const std::string& name, const std::string& image_path, const std::string& code, const uint32_t unit_price) : _name(name), _image_path(image_path), _code(code), _unit_price(unit_price)
    {

    }

    Good(JsonObject& obj) : _name(obj["name"].as<std::string>()), _image_path( "A:" + obj["image_path"].as<std::string>()), _code(obj["code"].as<std::string>()), _unit_price(obj["price"].as<uint32_t>())
    {

    }

    const std::string& GetName() const;

    const std::string& GetCode() const;

    const std::string& GetImagePath() const;

    const uint32_t GetUnitPrice() const;

    const int32_t GetSelectedNumber();

    const int32_t GetSoldNumber();

    void SetSoldNumber(const int32_t number);

    void AddSoldNumber(const int32_t number);

    const int32_t GetSelectedAmountPrice();

    const int32_t GetSoldAmountPrice();

    void IncrementSelectedNumber();

    void DecrementSelectedNumber();

    void ResetSelectedNumber();
};