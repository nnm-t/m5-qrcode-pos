#include "clock.h"

void Clock::Update(lv_obj_t* const label, const uint32_t delay_ms)
{
    _count_ms += delay_ms;

    if (_count_ms < _duration_ms)
    {
        return;
    }

    _count_ms = 0;

    m5::rtc_time_t time = M5.Rtc.getTime();

    char time_str[9];
    snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d", time.hours, time.minutes, time.seconds);

    _ui_label_set_property(label, _UI_LABEL_PROPERTY_TEXT, time_str);
}