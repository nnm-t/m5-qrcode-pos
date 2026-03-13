#include <Arduino.h>

#include <M5Unified.h>
#include <M5ModuleQRCode.h>
#include <M5ModuleHMI.h>

#include <lvgl.h>

#if LV_USE_FS_ARDUINO_SD == 0

#include "lv_fs_sd_memfs.h"

#endif

#include "states/state_selector.h"
#include "states/goods_state.h"
#include "states/amount_state.h"
#include "states/payment_state.h"
#include "states/settings_state.h"

#include "ui/ui.h"

#include "json_io.h"
#include "clock.h"
#include "qr.h"
#include "hmi.h"

#define TFT_HOR_RES                     320
#define TFT_VER_RES                     240
#define TFT_ROTATION                    LV_DISPLAY_ROTATION_90
#define DRAW_BUF_SIZE                   (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))

uint8_t draw_buf[DRAW_BUF_SIZE / 4];

namespace {
    static constexpr const uint8_t sd_cs_pin = 4;
    static constexpr const uint32_t delay_ms = 10;

    M5ModuleQRCode module_qrcode;
    M5ModuleHMI module_hmi;

    QR qrcode(module_qrcode);
    HMI hmi(module_hmi);
    Clock clock(delay_ms);

    StateSelector state_selector(qrcode, hmi);
    GoodsState goods_state(&state_selector, clock);
    AmountState amount_state(&state_selector, clock);
    PaymentState payment_state(&state_selector, goods_state, amount_state, clock);
    SettingsState settings_state(&state_selector, clock);

    JsonIO json_io(&Serial, goods_state, amount_state);
}

static uint32_t my_tick()
{
    return millis();
}

static void my_disp_flush(lv_display_t* disp, const lv_area_t* area, uint8_t* px_map)
{
    uint32_t width = (area->x2 - area->x1 + 1);
    uint32_t height = (area->y2 - area->y1 + 1);

    lv_draw_sw_rgb565_swap(px_map, width * height);

    M5.Display.startWrite();
    M5.Display.pushImageDMA<uint16_t>(area->x1, area->y1, width, height, (uint16_t*)px_map);
    M5.Display.endWrite();

    lv_display_flush_ready(disp);
}

static void my_touchpad_read(lv_indev_t* indev, lv_indev_data_t* data)
{
    const auto touch = M5.Touch.getDetail();

    if (!touch.isPressed())
    {
        data->state = LV_INDEV_STATE_RELEASED;
    }
    else
    {
        data->state = LV_INDEV_STATE_PRESSED;

        data->point.x = touch.x;
        data->point.y = touch.y;
    }
}

void setup()
{
    auto m5_config = M5.config();
    M5.begin(m5_config);
    SD.begin(sd_cs_pin);

    json_io.Read();

    lv_init();
    lv_tick_set_cb(my_tick);

    lv_display_t* disp = lv_display_create(TFT_HOR_RES, TFT_VER_RES);
    lv_display_set_flush_cb(disp, my_disp_flush);
    lv_display_set_buffers(disp, draw_buf, nullptr, sizeof(draw_buf), LV_DISPLAY_RENDER_MODE_PARTIAL);

    lv_indev_t* indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, my_touchpad_read);

#if LV_USE_FS_ARDUINO_SD == 0
    lv_fs_arduino_sd_init();
#endif

    ui_init();

    state_selector.goods_state = &goods_state;
    state_selector.amount_state = &amount_state;
    state_selector.payment_state = &payment_state;
    state_selector.settings_state = &settings_state;
    state_selector.Begin();
}

void loop()
{
    M5.update();

    state_selector.Update(delay_ms);

    lv_timer_handler();
    delay(delay_ms);
}