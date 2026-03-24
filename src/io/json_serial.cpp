#include "io/json_serial.h"

void JsonSerial::SendJson(JsonDocument& json_document)
{
    serializeJson(json_document, _serial);
    _serial.print('\n');
}

void JsonSerial::SendCurrentGood(std::vector<Good>::iterator& current_good)
{
    JsonDocument json_good;

    json_good["name"] = current_good->GetName();
    json_good["unit_price"] = current_good->GetUnitPrice();
    json_good["number"] = current_good->GetSelectedNumber();
    json_good["total_price"] = _goods.GetSelectedTotalPrice();

    SendJson(json_good);
}

void JsonSerial::SendTotalPrice()
{
    JsonDocument json_total;

    json_total["total_number"] = _goods.GetSelectedTotalNumber();
    json_total["total_price"] = _goods.GetSelectedTotalPrice() + _amounts.GetCurrentValue();

    SendJson(json_total);
}

void JsonSerial::SendPaymentComplete()
{
    JsonDocument json_payment;

    json_payment["payment"] = "OK";

    SendJson(json_payment);
}