#pragma once
#include "Dx.h";
#include "../System/CountDownTimer.h"

class Fader
{
public:
	Fader();
	~Fader();

	void Init();
	void Update(int fadetype,int limitTime);
	void FadeIn(int time);
	void FadeOut(int time);

private:
	int limitTime;

};