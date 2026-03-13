#include "states/settings_state.h"

SettingsState* SettingsState::_instance;

void SettingsState::Begin()
{
    _ui_time = ui_comp_get_child(ui_header_3, UI_COMP_HEADER_TIME_LBL);
    _ui_battery = ui_comp_get_child(ui_header_3, UI_COMP_HEADER_BATTERY_IMG);

    _rtc_datetime = M5.Rtc.getDateTime();
    DrawRTCSettings();

    // MACアドレス表示
    uint8_t mac_wifi[6];
    esp_read_mac(mac_wifi, ESP_MAC_WIFI_STA);

    char mac_wifi_str[18];
    snprintf(mac_wifi_str, sizeof(mac_wifi_str), "%02x:%02x:%02x:%02x:%02x:%02x", mac_wifi[0], mac_wifi[1], mac_wifi[2], mac_wifi[3], mac_wifi[4], mac_wifi[5]);
    _ui_label_set_property(ui_mac_addr_lbl_3, _UI_LABEL_PROPERTY_TEXT, mac_wifi_str);
}

void SettingsState::Update(const uint32_t delay_ms)
{
    _clock.Update(_ui_time, delay_ms);
    _battery.Update(_ui_battery, delay_ms);
}

void SettingsState::SetRTCSettingsTheme(lv_obj_t* const object, const RTCSettings rtc_settings)
{
    const ui_theme_variable_t* theme_color = _rtc_current == rtc_settings ? _ui_theme_color_yellow_light_1 : _ui_theme_color_white;
    const ui_theme_variable_t* theme_alpha = _rtc_current == rtc_settings ? _ui_theme_alpha_yellow_light_1 : _ui_theme_alpha_white;

    ui_object_set_themeable_style_property(object, (uint32_t)LV_PART_MAIN | (uint32_t)LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR, theme_color);
    ui_object_set_themeable_style_property(object, (uint32_t)LV_PART_MAIN | (uint32_t)LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA, theme_alpha);
}

void SettingsState::DrawRTCSettings()
{
    // Year
    char year_str[6];
    snprintf(year_str, sizeof(year_str), "%04d", _rtc_datetime.date.year);
    _ui_label_set_property(ui_time_yyyy_lbl_3, _UI_LABEL_PROPERTY_TEXT, year_str);

    SetRTCSettingsTheme(ui_time_yyyy_lbl_3, RTCSettings::Years);
    
    // Month
    char month_str[3];
    snprintf(month_str, sizeof(month_str), "%02d", _rtc_datetime.date.month);
    _ui_label_set_property(ui_time_mm_lbl_3_0, _UI_LABEL_PROPERTY_TEXT, month_str);

    SetRTCSettingsTheme(ui_time_mm_lbl_3_0, RTCSettings::Months);

    // Day
    char day_str[3];
    snprintf(day_str, sizeof(day_str), "%02d", _rtc_datetime.date.date);
    _ui_label_set_property(ui_time_dd_lbl_3, _UI_LABEL_PROPERTY_TEXT, day_str);

    SetRTCSettingsTheme(ui_time_dd_lbl_3, RTCSettings::Days);

    // Hour
    char hour_str[3];
    snprintf(hour_str, sizeof(hour_str), "%02d", _rtc_datetime.time.hours);
    _ui_label_set_property(ui_time_hh_lbl_3, _UI_LABEL_PROPERTY_TEXT, hour_str);

    SetRTCSettingsTheme(ui_time_hh_lbl_3, RTCSettings::Hours);

    // Minute
    char minute_str[3];
    snprintf(minute_str, sizeof(minute_str), "%02d", _rtc_datetime.time.minutes);
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
            if (year <= 1900)
            {
                _rtc_datetime.date.year = 2099;
            }
            else
            {
                _rtc_datetime.date.year--;
            }
            break;
        case RTCSettings::Months:
            if (month <= 1)
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
                    if (date <= 1)
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
                    if (date <= 1)
                    {
                        _rtc_datetime.date.date = 30;
                    }
                    else
                    {
                        _rtc_datetime.date.date--;
                    }
                    break;
                case 2:
                    if ((year % 4 == 0 || year != 1900) && date <= 1)
                    {
                        _rtc_datetime.date.date = 29;
                    }
                    else if (date <= 1)
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
            if (_rtc_datetime.time.hours <= 0)
            {
                _rtc_datetime.time.hours = 23;
            }
            else
            {
                _rtc_datetime.time.hours--;
            }
            break;
        case RTCSettings::Minutes:
            if (_rtc_datetime.time.minutes <= 0)
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

void SettingsState::CursorLeft()
{
    switch (_rtc_current)
    {
        case RTCSettings::Years:
            _rtc_current = RTCSettings::Minutes;
            break;
        case RTCSettings::Months:
            _rtc_current = RTCSettings::Years;
            break;
        case RTCSettings::Days:
            _rtc_current = RTCSettings::Months;
            break;
        case RTCSettings::Hours:
            _rtc_current = RTCSettings::Days;
            break;
        case RTCSettings::Minutes:
            _rtc_current = RTCSettings::Hours;
            break;
    }

    DrawRTCSettings();
}

void SettingsState::CursorRight()
{
    switch (_rtc_current)
    {
        case RTCSettings::Years:
            _rtc_current = RTCSettings::Months;
            break;
        case RTCSettings::Months:
            _rtc_current = RTCSettings::Days;
            break;
        case RTCSettings::Days:
            _rtc_current = RTCSettings::Hours;
            break;
        case RTCSettings::Hours:
            _rtc_current = RTCSettings::Minutes;
            break;
        case RTCSettings::Minutes:
            _rtc_current = RTCSettings::Years;
            break;
    }

    DrawRTCSettings();
}

void SettingsState::OnHMIEncoderIncrement()
{
    IncrementRTCSettings();
}

void SettingsState::OnHMIEncoderDecrement()
{
    DecrementRTCSettings();
}

void SettingsState::OnLeftButtonClicked()
{
    _instance->CursorLeft();
}

void SettingsState::OnRightButtonClicked()
{
    _instance->CursorRight();
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