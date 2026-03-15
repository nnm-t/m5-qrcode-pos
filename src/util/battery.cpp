#include "util/battery.h"

void Battery::Update(lv_obj_t* const image, const uint32_t delay_ms)
{
    _count_ms += delay_ms;

    if (_count_ms < _duration_ms)
    {
        return;
    }

    _count_ms = 0;

    const int32_t battery_level = M5.Power.getBatteryLevel();
    const lv_image_dsc_t* battery_image = &ui_img_battery_android_0_24dp_e3e3e3_fill0_wght400_grad0_opsz24_png;

    if (M5.Power.isCharging())
    {
        battery_image = &ui_img_battery_android_bolt_24dp_e3e3e3_fill0_wght400_grad0_opsz24_png;
    }
    else if (battery_level > 92)
    {
        battery_image = &ui_img_battery_android_full_24dp_e3e3e3_fill0_wght400_grad0_opsz24_png;
    }
    else if (battery_level > 78)
    {
        battery_image = &ui_img_battery_android_6_24dp_e3e3e3_fill0_wght400_grad0_opsz24_png;
    }
    else if (battery_level > 64)
    {
        battery_image = &ui_img_battery_android_5_24dp_e3e3e3_fill0_wght400_grad0_opsz24_png;
    }
    else if (battery_level > 50)
    {
        battery_image = &ui_img_battery_android_4_24dp_e3e3e3_fill0_wght400_grad0_opsz24_png;
    }
    else if (battery_level > 36)
    {
        battery_image = &ui_img_battery_android_3_24dp_e3e3e3_fill0_wght400_grad0_opsz24_png;
    }
    else if (battery_level > 22)
    {
        battery_image = &ui_img_battery_android_2_24dp_e3e3e3_fill0_wght400_grad0_opsz24_png;
    }
    else if (battery_level > 8)
    {
        battery_image = &ui_img_battery_android_1_24dp_e3e3e3_fill0_wght400_grad0_opsz24_png;
    }

    lv_image_set_src(image, battery_image);
}