#pragma once

#include <Arduino.h>
#include <SD.h>
#include <ArduinoJson.h>

class JsonIO
{
    static constexpr const char* goods_file_name = "/goods.json";
    static constexpr const char* sales_file_name = "/sales.json";

    HardwareSerial* const _serial;

    void Open(JsonDocument& json_document, const char* file_name);

public:
    JsonIO(HardwareSerial* const serial) : _serial(serial)
    {

    }

    void Read();

    void Write();
};