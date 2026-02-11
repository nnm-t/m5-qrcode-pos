#pragma once

#include <Arduino.h>

class IState
{
public:
	virtual void Begin() = 0;

	virtual void Update(const uint32_t delay_ms) = 0;
};