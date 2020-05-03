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
	void SetTime(const float second) override;//エラーが出るのでとりあえず
	float Rate();
	float Now();//エラーが出るのでとりあえず
};