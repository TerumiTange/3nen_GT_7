#pragma once

#include "Timer.h"

class CountDownTimer :
	public Timer
{
	CountDownTimer();
	CountDownTimer(float t);
	~CountDownTimer();
	void Init() override;
	void Update() override;
	bool IsTime() override;
	void SetTime(const float second) override;
	float Rate();
	float Now();
};