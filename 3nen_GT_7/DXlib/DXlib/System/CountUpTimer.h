#pragma once

#include "Timer.h"

class CountUpTimer :
	public Timer
{
public:
	CountUpTimer();
	CountUpTimer(float t);
	~CountUpTimer();
	void Init() override;
	void Update() override;
	bool IsTime() override;
	void SetTime(const float second) override;//�G���[���o��̂łƂ肠����
	float Rate();
	float Now();//�G���[���o��̂łƂ肠����
};