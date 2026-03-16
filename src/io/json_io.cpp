#include "io/json_io.h"

void JsonIO::Open(JsonDocument& json_document, const char* file_name)
{
    json_document.clear();

    File file = SD.open(file_name, FILE_READ);

    const DeserializationError error = deserializeJson(json_document, file);

    if (error != DeserializationError::Code::Ok)
    {
        _serial->printf("JSON deserialization failed: %s, %d", file_name, static_cast<uint8_t>(error.code()));
    }

    file.close();
}

void JsonIO::Read()
{
    JsonDocument json_goods;
    Open(json_goods, goods_file_name);

    _goods.DeserializeGoods(json_goods);

    JsonDocument json_sales;
    Open(json_sales, sales_file_name);

    _goods.DeserializeSales(json_sales);
    _amounts.Deserialize(json_sales);
}

void JsonIO::Write()
{
    JsonDocument json_sales;

    _goods.SerializeSales(json_sales);
    _amounts.Serialize(json_sales);

    File file = SD.open(sales_file_name, FILE_WRITE);
    serializeJsonPretty(json_sales, file);

    file.close();
}