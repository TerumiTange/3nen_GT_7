#include "CountUpTimer.h"

CountUpTimer::CountUpTimer():Timer(1.0f)
{
	Init();
}

CountUpTimer::CountUpTimer(float t) : Timer(t)
{
	SetTime(t);
}

CountUpTimer::~CountUpTimer()
{
}

void CountUpTimer::Init()
{
	currentTime = 0.f;
}

void CountUpTimer::Update()
{
	//currentTime = std::fminf(currentTime + 1.0f, limitTime);//limitTime
	currentTime = currentTime + 0.016666f;
}

bool CountUpTimer::IsTime()
{
	return currentTime >= limitTime;
}

void CountUpTimer::SetTime(const float second)
{
}

float CountUpTimer::Rate()
{
	return currentTime / limitTime;
}

float CountUpTimer::Now()
{
	return currentTime;
}

