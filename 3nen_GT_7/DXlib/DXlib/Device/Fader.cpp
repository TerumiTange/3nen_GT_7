#include "Fader.h"

Fader::Fader()
{
}

Fader::~Fader()
{
}

//������
void Fader::Init()
{
	limitTime = 0;
}

//0�F�t�F�[�h�C���@1�F�t�F�[�h�A�E�g�@(���Ԏw��̓t���[���P�ʂ�)
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

//�t�F�[�h�C��
void Fader::FadeIn(int time)
{

}

//�t�F�[�h�A�E�g
void Fader::FadeOut(int time)
{
}
