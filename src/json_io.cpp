#include "json_io.h"

void JsonIO::Open(JsonDocument& json_document, const char* file_name)
{
    json_document.clear();

    File file = SD.open(file_name, FILE_READ);

    const DeserializationError error = deserializeJson(json_document, file);

    if (error != DeserializationError::Code::Ok)
    {
        _serial->printf("JSON deserialization failed: %s, %d", file_name, static_cast<uint8_t>(error.code()));
    }
}

void JsonIO::Read()
{
    JsonDocument json_goods;
    Open(json_goods, goods_file_name);

    JsonArray json_goods_array = json_goods["goods"].as<JsonArray>();
    _goods_state.Deserialize(json_goods_array);

    JsonDocument json_sales;
    Open(json_sales, sales_file_name);
}

void JsonIO::Write()
{

}