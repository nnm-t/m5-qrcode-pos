#pragma once

#include <Arduino.h>

class IState
{
public:
	virtual void Begin() = 0;

	virtual void Update(const uint32_t delay_ms) = 0;

	virtual void OnHMIEncoderIncrement()
	{

	}

	virtual void OnHMIEncoderDecrement()
	{

	}

	virtual void OnHMIButtonSPressed()
	{

	}

	virtual void OnHMIButton1Pressed()
	{

	}

	virtual void OnHMIButton2Pressed()
	{

	}
};