#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <Arduino.h>
#include <lvgl.h>
#include <ArduinoJson.h>

#include "ui/ui.h"
#include "ui/ui_helpers.h"
#include "ui/ui_goods_state.h"

#include "i_state.h"
#include "i_state_selector.h"
#include "goods/goods.h"
#include "goods/amounts.h"
#include "io/json_serial.h"
#include "util/clock.h"
#include "util/battery.h"

class GoodsState : public IState
{
	static GoodsState* _instance;


	IStateSelector* const _state_selector;
	Goods& _goods;
	Amounts& _amounts;
	JsonSerial& _json_serial;
	Clock& _clock;
	Battery& _battery;

	std::vector<Good>::iterator _current_good;

	lv_obj_t* _ui_time = nullptr;
	lv_obj_t* _ui_battery = nullptr;

	void Draw();

public:
	GoodsState(IStateSelector* const state_selector, Goods& goods, Amounts& amounts, JsonSerial& json_serial, Clock& clock, Battery& battery) : _state_selector(state_selector), _goods(goods), _amounts(amounts), _json_serial(json_serial), _clock(clock), _battery(battery)
	{
		_current_good = _goods.GetBeginIterator();
		_instance = this;
	}

	void Begin() override;

	void Update(const uint32_t delay_ms) override;

	void Next();

	void Prev();

	void Plus();

	void Minus();

	void Reset();
	
	void ResetAll();

	void OnQRCodeScan(std::string& result);

	void OnHMIEncoderIncrement() override;

	void OnHMIEncoderDecrement() override;

	void OnHMIButtonSPressed() override;

	void OnHMIButton1Pressed() override;

	void OnHMIButton2Pressed() override;

	static void OnQRCodeButtonClicked();

	static void OnGoodsNextButtonClicked();

	static void OnGoodsPrevButtonClicked();

	static void OnPlusButtonClicked();

	static void OnMinusButtonClicked();

	static void OnResetButtonClicked();
};