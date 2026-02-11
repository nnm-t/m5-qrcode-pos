#pragma once

#include <string>

#include <Arduino.h>
#include <lvgl.h>

#include "ui/ui_goods_state.h"

#include "i_state.h"
#include "i_state_selector.h"
#include "clock.h"

class GoodsState : public IState
{
	static GoodsState* _instance;

	IStateSelector* const _state_selector;
	Clock& _clock;

public:
	GoodsState(IStateSelector* const state_selector, Clock& clock) : _state_selector(state_selector), _clock(clock)
	{
		_instance = this;
	}

	void Begin() override;

	void Update(const uint32_t delay_ms) override;

	void OnQRCodeScan(std::string& result);

	static void OnQRCodeButtonClicked();
};