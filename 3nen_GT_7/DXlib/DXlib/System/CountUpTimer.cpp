#include "CountUpTimer.h"

CountUpTimer::CountUpTimer():Timer()
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
	currentTime = std::fminf(currentTime + 1.0f, limitTime);
}

bool CountUpTimer::IsTime()
{
	return currentTime >= limitTime;
}

float CountUpTimer::Rate()
{
	return currentTime / limitTime;
}

