#pragma once
#include "../Device/Dx.h"

class Timer
{
public:
	Timer();
	Timer(float t);
	virtual ~Timer() {};
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual bool IsTime() = 0;
	virtual void SetTime(const float second) = 0;
	virtual float Now() = 0;
	virtual float Rate() = 0;
protected:
	float limitTime;
	float currentTime;
};
