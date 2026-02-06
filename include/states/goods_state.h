#pragma once

#include <Arduino.h>

#include "i_state.h"
#include "state_selector.h"

class GoodsState : public IState
{
	StateSelector* const _state_selector;

public:
	GoodsState(StateSelector* const state_selector) : _state_selector(state_selector)
	{

	}

	void Begin() override;

	void Update() override;
};