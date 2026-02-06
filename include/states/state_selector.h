#pragma once

#include <Arduino.h>

#include "i_state.h"

class StateSelector
{
public:
	IState* goods_state = nullptr;

	StateSelector()
	{

	}

	void Begin();

	void Update();
};
