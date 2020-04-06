#pragma once

#include "Timer.h"

class CountUpTimer :
	public Timer
{
	CountUpTimer();
	CountUpTimer(float t);
	~CountUpTimer();
	void Init() override;
	void Update() override;
	bool IsTime() override;
	float Rate();

};