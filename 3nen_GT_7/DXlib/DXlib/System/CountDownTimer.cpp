#include "CountDownTimer.h"

CountDownTimer::CountDownTimer():Timer()
{
	Init();
}

CountDownTimer::CountDownTimer(float t):Timer(t)
{
	SetTime(t);
}

CountDownTimer::~CountDownTimer()
{
}

void CountDownTimer::Init()
{
	currentTime = limitTime;
}

void CountDownTimer::Update()
{
	currentTime = std::fmaxf(currentTime - 1.0f, 0.0f);
}

bool CountDownTimer::IsTime()
{
	return currentTime <= 0.0f;
}

void CountDownTimer::SetTime(const float second)
{
	limitTime = 60.0f * second;
	Init();
}

float CountDownTimer::Rate()
{
	return 1.0f - currentTime / limitTime;
}

float CountDownTimer::Now()
{
	return currentTime / 60.0f;
}

