#pragma once

#include <string>
#include <functional>

#include "lvgl.h"

#if LV_USE_FS_ARDUINO_SD == 0

#define USER_FS_ARDUINO_SD_LETTER 'A'

#include <SD.h>

extern "C" void lv_fs_arduino_sd_init();

#endif