#include "Fader.h"

Fader::Fader()
{
}

Fader::~Fader()
{
}

//初期化
void Fader::Init()
{
	limitTime = 0;
}

//0：フェードイン　1：フェードアウト　(時間指定はフレーム単位で)
void Fader::Update(int fadetype, int limitTime)
{
	if (fadetype == 0)
	{
		FadeIn(limitTime);
	}
	if (fadetype == 1)
	{
		FadeOut(limitTime);
	}
}

//フェードイン
void Fader::FadeIn(int time)
{

}

//フェードアウト
void Fader::FadeOut(int time)
{
}
