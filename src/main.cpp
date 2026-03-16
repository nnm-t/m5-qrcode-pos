#include <Arduino.h>
#include <M5Unified.h>
#include <lvgl.h>

#include "gfx/lv_init.h"

#include "goods/goods.h"
#include "goods/amounts.h"

#include "states/state_selector.h"
#include "states/goods_state.h"
#include "states/amount_state.h"
#include "states/payment_state.h"
#include "states/settings_state.h"
#include "states/sales_state.h"

#include "ui/ui.h"

#include "io/json_io.h"
#include "util/clock.h"
#include "util/battery.h"
#include "module/qr.h"
#include "module/hmi.h"

namespace {
    static constexpr const uint8_t sd_cs_pin = 4;
    static constexpr const uint32_t delay_ms = 10;
    static constexpr const uint32_t duration_ms = 500;

    M5ModuleQRCode module_qrcode;
    M5ModuleHMI module_hmi;

    QR qrcode(module_qrcode);
    HMI hmi(module_hmi);
    Clock clock(duration_ms);
    Battery battery(duration_ms);

    Goods goods;
    Amounts amounts;
    JsonIO json_io(&Serial, goods, amounts);

    StateSelector state_selector(qrcode, hmi);
    GoodsState goods_state(&state_selector, goods, clock, battery);
    AmountState amount_state(&state_selector, amounts, clock, battery);
    PaymentState payment_state(&state_selector, goods, amounts, json_io, clock, battery);
    SettingsState settings_state(&state_selector, clock, battery);
    SalesState sales_state(&state_selector, goods, amounts, clock, battery);
}

void setup()
{
    auto m5_config = M5.config();
    M5.begin(m5_config);
    SD.begin(sd_cs_pin);

    json_io.Read();

    lv_my_init();
    ui_init();

    state_selector.goods_state = &goods_state;
    state_selector.amount_state = &amount_state;
    state_selector.payment_state = &payment_state;
    state_selector.settings_state = &settings_state;
    state_selector.sales_state = &sales_state;
    state_selector.Begin();
}

void loop()
{
    M5.update();

    state_selector.Update(delay_ms);

    lv_my_update();
    delay(delay_ms);
}