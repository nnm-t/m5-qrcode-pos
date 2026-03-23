#pragma once

#include <Arduino.h>
#include <M5Unified.h>
#include <lvgl.h>

#include "esp_mac.h"

#include "ui/ui.h"
#include "ui/ui_helpers.h"
#include "ui/ui_settings_state.h"

#include "i_state.h"
#include "i_state_selector.h"
#include "util/clock.h"
#include "util/battery.h"
#include "util/brightness.h"

enum class RTCSettings : uint8_t
{
    Years = 0x01,
    Months = 0x02,
    Days = 0x04,
    Hours = 0x11,
    Minutes = 0x12
};

class SettingsState : public IState
{
    static SettingsState* _instance;

    IStateSelector* const _state_selector;
    Clock& _clock;
	Battery& _battery;
    Brightness& _brightness;

    RTCSettings _rtc_current = RTCSettings::Years;
    m5::rtc_datetime_t _rtc_datetime = m5::rtc_datetime_t();

	lv_obj_t* _ui_time = nullptr;
	lv_obj_t* _ui_battery = nullptr;

    void SetRTCSettingsTheme(lv_obj_t* const object, const RTCSettings rtc_settings);

    void DrawRTCSettings();

    void IncrementRTCSettings();

    void DecrementRTCSettings();

    void ApplySettings();

    const uint8_t GetBrightness();

    void SetBrightness(const uint8_t value);

public:
    SettingsState(IStateSelector* const state_selector, Clock& clock, Battery& battery, Brightness& brightness) : _state_selector(state_selector), _clock(clock), _battery(battery), _brightness(brightness)
    {
        _instance = this;
    }

    void Begin() override;

    void Update(const uint32_t delay_ms) override;

    void ChangeRTCCurrent(const RTCSettings rtc_settings);

    void CursorLeft();

    void CursorRight();

    void OnHMIEncoderIncrement() override;

    void OnHMIEncoderDecrement() override;

    void OnHMIButton2Pressed() override;

    static void OnLeftButtonClicked();

    static void OnRightButtonClicked();

    static void OnPlusButtonClicked();

    static void OnMinusButtonClicked();

    static void OnOkayButtonClicked();

    static void OnYYYYLabelClicked();

    static void OnMM0LabelClicked();

    static void OnDDLabelClicked();

    static void OnHHLabelClicked();

    static void OnMM1LabelClicked();

    static void OnBrightnessSliderValueChanged();
};