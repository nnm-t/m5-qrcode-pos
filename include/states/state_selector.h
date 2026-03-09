#pragma once

#include <string>

#include <Arduino.h>

#include "i_state.h"
#include "i_state_selector.h"
#include "goods_state.h"
#include "qr.h"
#include "hmi.h"

class StateSelector : public IStateSelector
{
    QR& _qr;
	HMI& _hmi;
	IState* _current_state = nullptr;

    void OnQRCodeScan(std::string& result);

	void OnHMIButtonSPressed();
	
	void OnHMIButton1Pressed();

	void OnHMIButton2Pressed();

	void OnHMIEncoderIncrement();

	void OnHMIEncoderDecrement();

public:
	GoodsState* goods_state = nullptr;

	StateSelector(QR& qr, HMI& hmi) : _qr(qr), _hmi(hmi)
	{

	}

	void Begin() override;

	void Update(const uint32_t delay_ms) override;

    void EnableQRCodeReader() override;
};
