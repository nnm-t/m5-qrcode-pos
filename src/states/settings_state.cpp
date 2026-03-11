#include "states/settings_state.h"

SettingsState* SettingsState::_instance;

void SettingsState::Begin()
{
    _rtc_datetime = M5.Rtc.getDateTime();
    DrawRTCSettings();
}

void SettingsState::Update(const uint32_t delay_ms)
{
    lv_obj_t* const ui_time_0 = ui_comp_get_child(ui_header_3, UI_COMP_HEADER_TIME_LBL);
    _clock.Update(ui_time_0, delay_ms);
}

void SettingsState::SetRTCSettingsTheme(lv_obj_t* const object, const RTCSettings rtc_settings)
{
    const ui_theme_variable_t* theme = _rtc_current == rtc_settings ? _ui_theme_color_yellow_light_1 : _ui_theme_color_white;

    ui_object_set_themeable_style_property(object, (uint32_t)LV_PART_MAIN | (uint32_t)LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR, theme);
    ui_object_set_themeable_style_property(object, (uint32_t)LV_PART_MAIN | (uint32_t)LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA, theme);
}

void SettingsState::DrawRTCSettings()
{
    // Year
    char year_str[5];
    snprintf(year_str, strlen(year_str), "%4d", _rtc_datetime.date.year);
    _ui_label_set_property(ui_time_yyyy_lbl_3, _UI_LABEL_PROPERTY_TEXT, year_str);

    SetRTCSettingsTheme(ui_time_yyyy_lbl_3, RTCSettings::Years);
    
    // Month
    char month_str[3];
    snprintf(month_str, strlen(month_str), "%2d", _rtc_datetime.date.month);
    _ui_label_set_property(ui_time_mm_lbl_3_0, _UI_LABEL_PROPERTY_TEXT, month_str);

    SetRTCSettingsTheme(ui_time_mm_lbl_3_0, RTCSettings::Months);

    // Day
    char day_str[3];
    snprintf(day_str, strlen(day_str), "%2d", _rtc_datetime.date.date);
    _ui_label_set_property(ui_time_dd_lbl_3, _UI_LABEL_PROPERTY_TEXT, day_str);

    SetRTCSettingsTheme(ui_time_dd_lbl_3, RTCSettings::Days);

    // Hour
    char hour_str[3];
    snprintf(hour_str, strlen(hour_str), "%2d", _rtc_datetime.time.hours);
    _ui_label_set_property(ui_tim_hh_lbl_3, _UI_LABEL_PROPERTY_TEXT, hour_str);

    SetRTCSettingsTheme(ui_tim_hh_lbl_3, RTCSettings::Hours);

    // Minute
    char minute_str[3];
    snprintf(minute_str, strlen(minute_str), "%2d", _rtc_datetime.time.minutes);
    _ui_label_set_property(ui_time_mm_lbl_3_1, _UI_LABEL_PROPERTY_TEXT, minute_str);

    SetRTCSettingsTheme(ui_time_mm_lbl_3_1, RTCSettings::Minutes);
}

void SettingsState::ChangeRTCCurrent(const RTCSettings rtc_settings)
{
    _rtc_current = rtc_settings;
    DrawRTCSettings();
}

void SettingsState::IncrementRTCSettings()
{
    const int16_t year = _rtc_datetime.date.year;
    const int8_t month = _rtc_datetime.date.month;
    const int8_t date = _rtc_datetime.date.date;

    switch (_rtc_current)
    {
        case RTCSettings::Years:
            if (year == 2099)
            {
                _rtc_datetime.date.year = 1900;
            }
            else
            {
                _rtc_datetime.date.year++;
            }
            break;
        case RTCSettings::Months:
            if (month == 12)
            {
                _rtc_datetime.date.month = 1;
            }
            else
            {
                _rtc_datetime.date.month++;
            }
            break;
        case RTCSettings::Days:
            switch (month)
            {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    if (date == 31)
                    {
                        _rtc_datetime.date.date = 1;
                    }
                    else
                    {
                        _rtc_datetime.date.date++;
                    }
                    break;
                case 4:
                case 6:
                case 9:
                case 11:
                    if (date < 30)
                    {
                        _rtc_datetime.date.date = 1;
                    }
                    else
                    {
                        _rtc_datetime.date.date++;
                    }
                    break;
                case 2:
                    if ((year % 4 == 0 || year != 1900) && date == 29)
                    {
                        _rtc_datetime.date.date = 1;
                    }
                    else if (date == 28)
                    {
                        _rtc_datetime.date.date = 1;
                    }
                    else
                    {
                        _rtc_datetime.date.date++;
                    }
                    break;
            }
            break;
        case RTCSettings::Hours:
            if (_rtc_datetime.time.hours == 23)
            {
                _rtc_datetime.time.hours = 0;
            }
            else
            {
                _rtc_datetime.time.hours++;
            }
            break;
        case RTCSettings::Minutes:
            if (_rtc_datetime.time.minutes == 59)
            {
                _rtc_datetime.time.minutes = 0;
            }
            else
            {
                _rtc_datetime.time.minutes++;
            }
            break;
    }

    DrawRTCSettings();
}

void SettingsState::DecrementRTCSettings()
{
    const int16_t year = _rtc_datetime.date.year;
    const int8_t month = _rtc_datetime.date.month;
    const int8_t date = _rtc_datetime.date.date;

    switch (_rtc_current)
    {
        case RTCSettings::Years:
            if (year == 1900)
            {
                _rtc_datetime.date.year = 2099;
            }
            else
            {
                _rtc_datetime.date.year--;
            }
            break;
        case RTCSettings::Months:
            if (month == 1)
            {
                _rtc_datetime.date.month = 12;
            }
            else
            {
                _rtc_datetime.date.month--;
            }
            break;
        case RTCSettings::Days:
            switch (month)
            {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    if (date == 1)
                    {
                        _rtc_datetime.date.date = 31;
                    }
                    else
                    {
                        _rtc_datetime.date.date--;
                    }
                    break;
                case 4:
                case 6:
                case 9:
                case 11:
                    if (date == 1)
                    {
                        _rtc_datetime.date.date = 30;
                    }
                    else
                    {
                        _rtc_datetime.date.date--;
                    }
                    break;
                case 2:
                    if ((year % 4 == 0 || year != 1900) && date == 1)
                    {
                        _rtc_datetime.date.date = 29;
                    }
                    else if (date == 1)
                    {
                        _rtc_datetime.date.date = 28;
                    }
                    else
                    {
                        _rtc_datetime.date.date--;
                    }
                    break;
            }
            break;
        case RTCSettings::Hours:
            if (_rtc_datetime.time.hours == 0)
            {
                _rtc_datetime.time.hours = 23;
            }
            else
            {
                _rtc_datetime.time.hours--;
            }
            break;
        case RTCSettings::Minutes:
            if (_rtc_datetime.time.minutes == 0)
            {
                _rtc_datetime.time.minutes = 59;
            }
            else
            {
                _rtc_datetime.time.minutes--;
            }
            break;
    }

    DrawRTCSettings();
}

void SettingsState::ApplySettings()
{
    // Write to RTC
    M5.Rtc.setDateTime(_rtc_datetime);
}

void SettingsState::OnHMIEncoderIncrement()
{
    IncrementRTCSettings();
}

void SettingsState::OnHMIEncoderDecrement()
{
    DecrementRTCSettings();
}

void SettingsState::OnPlusButtonClicked()
{
    _instance->IncrementRTCSettings();
}

void SettingsState::OnMinusButtonClicked()
{
    _instance->DecrementRTCSettings();
}

void SettingsState::OnOkayButtonClicked()
{
    _instance->ApplySettings();
}

void SettingsState::OnYYYYLabelClicked()
{
    _instance->ChangeRTCCurrent(RTCSettings::Years);
}

void SettingsState::OnMM0LabelClicked()
{
    _instance->ChangeRTCCurrent(RTCSettings::Months);
}

void SettingsState::OnDDLabelClicked()
{
    _instance->ChangeRTCCurrent(RTCSettings::Days);
}

void SettingsState::OnHHLabelClicked()
{
    _instance->ChangeRTCCurrent(RTCSettings::Hours);
}

void SettingsState::OnMM1LabelClicked()
{
    _instance->ChangeRTCCurrent(RTCSettings::Minutes);
}