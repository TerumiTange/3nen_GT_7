#pragma once
#include "Dx.h";
#include "../System/CountDownTimer.h"

class Fader
{
public:
	Fader();
	~Fader();

	void Init();
	void Update();
	void SetFadeIn(float setTime);
	void SetFadeOut(float setTime);
	void FadeIn(float time);
	void FadeOut(float time);
	bool SwitchFade(bool value);

	void Draw();

private:
	int bright;
	float setTime_in;
	float setTime_out;
	bool inOut;  //true : out  false : in

};