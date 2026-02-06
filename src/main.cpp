#include <Arduino.h>

#include <M5Unified.h>
#include <M5ModuleQRCode.h>

#include <lvgl.h>

#include "states/state_selector.h"
#include "states/goods_state.h"

#include "ui/ui.h"

#define TFT_HOR_RES                     320
#define TFT_VER_RES                     240
#define TFT_ROTATION                    LV_DISPLAY_ROTATION_90
#define DRAW_BUF_SIZE                   (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))

uint8_t draw_buf[DRAW_BUF_SIZE / 4];

namespace {
    M5ModuleQRCode module_qrcode;

    StateSelector state_selector;
    GoodsState goods_state(&state_selector);
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

void setup()
{
    auto m5_config = M5.config();
    M5.begin(m5_config);

    state_selector.goods_state = &goods_state;

    lv_init();
    lv_tick_set_cb(my_tick);

    lv_display_t* disp;
    disp = lv_display_create(TFT_HOR_RES, TFT_VER_RES);
    lv_display_set_flush_cb(disp, my_disp_flush);
    lv_display_set_buffers(disp, draw_buf, nullptr, sizeof(draw_buf), LV_DISPLAY_RENDER_MODE_PARTIAL);

    ui_init();

    state_selector.Begin();
}

void loop()
{
    M5.update();

    state_selector.Update();

    m5::rtc_time_t time = M5.Rtc.getTime();
    char time_str[9];
    snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d", time.hours, time.minutes, time.seconds);

    lv_obj_t* ui_time_0 = ui_comp_get_child(ui_header0, UI_COMP_HEADER_TIME_LBL);
    _ui_label_set_property(ui_time_0, _UI_LABEL_PROPERTY_TEXT, time_str);

    lv_timer_handler();

}