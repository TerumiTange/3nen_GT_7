#include "Fader.h"

Fader::Fader()
{
	Init();
}

Fader::~Fader()
{
}

//初期化
void Fader::Init()
{
	bright = 256;
	setTime_in = 0;
	setTime_out = 0;
	inOut = true;
	mNowFader = false;
}

void Fader::Update()
{
	if (!inOut)
	{
		FadeIn(setTime_in);
	}
	if (inOut)
	{
		FadeOut(setTime_out);
	}
}

void Fader::SetFadeIn(float setTime)
{
	setTime_in = 255 /( setTime * 60);
	mNowFader = true;
}

void Fader::SetFadeOut(float setTime)
{
	setTime_out = 255/(setTime * 60);
	mNowFader = true;
}

//フェードイン
void Fader::FadeIn(float speed)
{
	if (bright > 255)
	{
		SetDrawBright(255, 255, 255);
		mNowFader = false;
		return;
	}

	SetDrawBright(bright, bright, bright);

	bright += speed;
}

//フェードアウト
void Fader::FadeOut(float speed)
{
	if (bright <= 0)
	{
		SetDrawBright(0, 0, 0);
		mNowFader = false;
		return;
	}

	SetDrawBright(bright, bright, bright);

	bright -= speed;
}

//false：フェードイン　true：フェードアウト
bool Fader::SwitchFade(bool value)
{
	return inOut = value;
}

bool Fader::GetNowFader()
{
	return mNowFader;
}

void Fader::Draw()
{
	//DrawFormatString(50, 100, GetColor(0, 0, 0), "%d", bright);

}
