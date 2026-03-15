#include "gfx/lv_init.h"

static uint8_t draw_buf0[DRAW_BUF_SIZE / 4];
static uint8_t draw_buf1[DRAW_BUF_SIZE / 4];

static uint32_t lv_my_tick()
{
    return millis();
}

static void lv_my_disp_flush(lv_display_t* disp, const lv_area_t* area, uint8_t* px_map)
{
    uint32_t width = (area->x2 - area->x1 + 1);
    uint32_t height = (area->y2 - area->y1 + 1);

    lv_draw_sw_rgb565_swap(px_map, width * height);

    M5.Display.startWrite();
    M5.Display.pushImageDMA<uint16_t>(area->x1, area->y1, width, height, (uint16_t*)px_map);
    M5.Display.endWrite();

    lv_display_flush_ready(disp);
}

static void lv_my_touchpad_read(lv_indev_t* indev, lv_indev_data_t* data)
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

void lv_my_init()
{
    lv_init();
    lv_tick_set_cb(lv_my_tick);

    lv_display_t* disp = lv_display_create(TFT_HOR_RES, TFT_VER_RES);
    lv_display_set_flush_cb(disp, lv_my_disp_flush);
    lv_display_set_buffers(disp, draw_buf0, draw_buf1, sizeof(draw_buf0), LV_DISPLAY_RENDER_MODE_PARTIAL);

    lv_indev_t* indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, lv_my_touchpad_read);

    #if LV_USE_FS_ARDUINO_SD == 0
        lv_fs_arduino_sd_init();
    #endif
}

void lv_my_update()
{
    lv_timer_handler();
}