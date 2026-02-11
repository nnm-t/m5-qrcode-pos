#pragma once

#include <Arduino.h>
#include <lvgl.h>
#include <M5Unified.h>

#include "ui/ui.h"
#include "ui/ui_helpers.h"

class Clock
{
    const uint32_t _duration_ms;
    uint32_t _count_ms = 0;

public:
    Clock(const uint32_t duration_ms) : _duration_ms(duration_ms)
    {

    }

    void Update(lv_obj_t* const label, const uint32_t delay_ms);
};