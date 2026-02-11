#pragma once

#include <string>

#include <Arduino.h>

#include "i_state.h"
#include "i_state_selector.h"
#include "goods_state.h"
#include "qr.h"

class StateSelector : public IStateSelector
{
    QR& _qr;
	IState* _current_state = nullptr;

    void OnQRCodeScan(std::string& result);

public:
	GoodsState* goods_state = nullptr;

	StateSelector(QR& qr) : _qr(qr)
	{

	}

	void Begin() override;

	void Update(const uint32_t delay_ms) override;

    void EnableQRCodeReader() override;
};
