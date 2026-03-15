#pragma once

#include <string>

#include <Arduino.h>

#include "i_state.h"
#include "i_state_selector.h"
#include "goods_state.h"
#include "amount_state.h"
#include "payment_state.h"
#include "settings_state.h"
#include "module/qr.h"
#include "module/hmi.h"

class StateSelector : public IStateSelector
{
	static StateSelector* _instance;

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
	AmountState* amount_state = nullptr;
	PaymentState* payment_state = nullptr;
	SettingsState* settings_state = nullptr;

	StateSelector(QR& qr, HMI& hmi) : _qr(qr), _hmi(hmi)
	{
		_instance = this;
	}

	void Begin() override;

	void Update(const uint32_t delay_ms) override;

    void EnableQRCodeReader() override;

	void BackToGoodsState() override;

	void GoToPaymentState() override;

	static void ToGoodsState();

	static void ToAmountState();

	static void ToPaymentState();

	static void ToSettingsState();
};
