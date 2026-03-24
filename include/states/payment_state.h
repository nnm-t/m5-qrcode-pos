#pragma once

#include <Arduino.h>
#include <lvgl.h>

#include "ui/ui.h"
#include "ui/ui_helpers.h"
#include "ui/ui_payment_state.h"

#include "i_state.h"
#include "i_state_selector.h"
#include "goods/goods.h"
#include "goods/amounts.h"
#include "io/json_io.h"
#include "io/csv_io.h"
#include "io/json_serial.h"
#include "util/clock.h"
#include "util/battery.h"

class PaymentState : public IState
{
    static PaymentState* _instance;

    IStateSelector* const _state_selector;
    Goods& _goods;
    Amounts& _amounts;
    JsonIO& _json_io;
    CsvIO& _csv_io;
    JsonSerial& _json_serial;
    Clock& _clock;
	Battery& _battery;

	lv_obj_t* _ui_time = nullptr;
	lv_obj_t* _ui_battery = nullptr;

    void Okay();

    void OkayFree();

public:
    PaymentState(IStateSelector* const state_selector, Goods& goods, Amounts& amounts, JsonIO& json_io, CsvIO& csv_io, JsonSerial& json_serial, Clock& clock, Battery& battery) : _state_selector(state_selector), _goods(goods), _amounts(amounts), _json_io(json_io), _csv_io(csv_io), _json_serial(json_serial), _clock(clock), _battery(battery)
    {
        _instance = this;
    }

    void Begin() override;

    void Update(const uint32_t delay_ms) override;

    void OnHMIButton1Pressed() override;

    void OnHMIButton2Pressed() override;

    static void OnOkayButtonClicked();

    static void OnFreeButtonClicked();
};