#pragma once

#include <Arduino.h>
#include <M5Unified.h>

#include <lvgl.h>

#if LV_USE_FS_ARDUINO_SD == 0
#include "gfx/lv_fs_sd_memfs.h"
#endif

#define TFT_HOR_RES                     320
#define TFT_VER_RES                     240
#define TFT_ROTATION                    LV_DISPLAY_ROTATION_90
#define DRAW_BUF_DIVS                   5
#define DRAW_BUF_SIZE                   (TFT_HOR_RES * TFT_VER_RES / DRAW_BUF_DIVS * (LV_COLOR_DEPTH / 8))

void lv_my_init();

void lv_my_update();