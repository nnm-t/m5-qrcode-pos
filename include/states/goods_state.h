#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <Arduino.h>
#include <lvgl.h>
#include <ArduinoJson.h>

#include "ui/ui_goods_state.h"

#include "i_state.h"
#include "i_state_selector.h"
#include "clock.h"
#include "good.h"

class GoodsState : public IState
{
	static GoodsState* _instance;

	std::vector<Good> _goods;
	std::unordered_map<std::string, size_t> _goods_hash;
	std::vector<Good>::iterator _current_good;

	IStateSelector* const _state_selector;
	Clock& _clock;

	void Draw();

public:
	GoodsState(IStateSelector* const state_selector, Clock& clock) : _state_selector(state_selector), _clock(clock)
	{
		_goods = std::vector<Good>();
		_goods_hash = std::unordered_map<std::string, size_t>();
		_current_good = _goods.begin();
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

	void Deserialize(JsonArray& json_goods);

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